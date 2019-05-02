//part of every ROS embedded linux program
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

// allows our program to create publishers and subscribers
ros::NodeHandle  nh;
#define MOTOR_LEFT_F_IN1 13
#define MOTOR_LEFT_F_IN2 12
#define MOTOR_LEFT_F_ENABLE 11
#define MOTOR_LEFT_B_IN1 10
#define MOTOR_LEFT_B_IN2 9
#define MOTOR_LEFT_B_ENABLE 8

#define MOTOR_RIGHT_F_IN1 7 
#define MOTOR_RIGHT_F_IN2 7
#define MOTOR_RIGHT_F_ENABLE 5 
#define MOTOR_RIGHT_B_IN1 4
#define MOTOR_RIGHT_B_IN2 3
#define MOTOR_RIGHT_B_ENABLE 2 

float v = 0.0 ;
float w = 0.0 ;
float vl = 0.0 ;
float vr = 0.0 ;

//ENCODER
bool leftflage = false ;
bool rightflage = false ;
long DL = 0;
long DR = 0;
int lefttickscount = 0 ;
int righttickscount = 0 ;
int leftencoderval = 0;
int rightencoderval = 0;
unsigned int rpm_l;
unsigned int w_l;
unsigned long timeold_l;
unsigned int rpm_r;
unsigned int w_r;
unsigned long timeold_r;

//instantiate the publishers and subscribers
std_msgs::UInt16 str_msg;
ros::Publisher chatter("chatter", &str_msg);

void roverCallBack(const geometry_msgs::Twist & cmd_vel)
{
  v = cmd_vel.linear.x   ;
  w = cmd_vel.angular.z  ;
  vl = v - ((w*0.32)/2) ;
  vr = v + ((w*0.32)/2) ;
  vl = map(vl, -0.5, 0.5, -255, 255);
  vr = map(vr, -0.5, 0.5, -255, 255);
  int constrainVL =  constrain(sqrt(sq(vl)),0,255);
  int constrainVR = constrain(sqrt(sq(vr)),0,255);
  
  if(v > 0 && w == 0){
      analogWrite(MOTOR_LEFT_F_ENABLE,constrainVL);
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW);
      analogWrite(MOTOR_RIGHT_F_ENABLE,constrainVR);
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW);   
  }else if( v == 0 && w == 0){
      analogWrite(MOTOR_LEFT_F_ENABLE,200);
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
      analogWrite(MOTOR_RIGHT_F_ENABLE,200);
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);  
  }else if (v < 0 && w == 0){
    analogWrite(MOTOR_LEFT_F_ENABLE,200);
    digitalWrite(MOTOR_LEFT_F_IN1,LOW);
    digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
    analogWrite(MOTOR_RIGHT_F_ENABLE,200);
    digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
  }else if (w > 0 && v == 0){
      analogWrite(MOTOR_LEFT_F_ENABLE,constrainVL);
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW);
      analogWrite(MOTOR_RIGHT_F_ENABLE,constrainVR);
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
    }else if (w < 0 && v == 0){
      analogWrite(MOTOR_LEFT_F_ENABLE,constrainVL);
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
      analogWrite(MOTOR_RIGHT_F_ENABLE,constrainVR);
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW);
    }
  
}

ros::Subscriber <geometry_msgs::Twist> sub2("/cmd_vel", roverCallBack);

void setup()
{
  pinMode(13, OUTPUT);
  // initialize ROS node handle
  nh.initNode();
  //Advertise any topics being published, and subscribe to any topics you wish to listen to.
  nh.advertise(chatter);
  //nh.subscribe(sub);
  nh.subscribe(sub2);
  
  pinMode(MOTOR_LEFT_F_IN1,OUTPUT);
  pinMode(MOTOR_LEFT_F_IN2,OUTPUT);
  pinMode(MOTOR_LEFT_F_ENABLE,OUTPUT);  
  pinMode(MOTOR_LEFT_B_IN1,OUTPUT);
  pinMode(MOTOR_LEFT_B_IN2,OUTPUT);
  pinMode(MOTOR_LEFT_B_ENABLE,OUTPUT);
 
  pinMode(MOTOR_RIGHT_F_IN1,OUTPUT);
  pinMode(MOTOR_RIGHT_F_IN2,OUTPUT);
  pinMode(MOTOR_RIGHT_F_ENABLE,OUTPUT);
  pinMode(MOTOR_RIGHT_B_IN1,OUTPUT);
  pinMode(MOTOR_RIGHT_B_IN2,OUTPUT);
  pinMode(MOTOR_RIGHT_B_ENABLE,OUTPUT);

  pinMode(20, INPUT);
  attachInterrupt(digitalPinToInterrupt(20), leftticks, CHANGE);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), rightticks, CHANGE);

}

//ENCODER
void leftticks(){
    //    Serial.println(val);
    if(digitalRead(20) == 1 ){
      leftflage = true ;
    }else{
      if(leftflage == true){
        lefttickscount ++ ;

      }
      if(lefttickscount%20 == 0 && leftflage == true){
        DL ++;
        rpm_l =(lefttickscount)*30*1000/(millis() - timeold_l);
        str_msg.data = rpm_l;
        w_l = (2*3.14*rpm_l)/60 ;
        timeold_l = millis();
        lefttickscount = 0;
      }
      leftflage = false ;
  }
}

void rightticks(){
    //    Serial.println(val);
    if(digitalRead(21) == 1  ){
      rightflage = true ;
    }else{
      if(rightflage == true){
        righttickscount ++ ;
      }
      if(righttickscount%20 == 0 && rightflage == true){
        DR ++;
        rpm_r =(righttickscount)*30*1000/(millis() - timeold_r);
        str_msg.data = rpm_r;
        w_r = (2*3.14*rpm_r)/60 ;
        timeold_r = millis();
        righttickscount = 0;    
      }
      rightflage = false ;
  }
}



void loop()
{
  //str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}
void motorsmove(int left_motor_speed , char left_motor_dir ,int right_motor_speed , char right_motor_dir){
  motordir(left_motor_dir ,right_motor_dir );
  analogWrite(MOTOR_LEFT_F_ENABLE,constrain(left_motor_speed,0,255));
  analogWrite(MOTOR_RIGHT_F_ENABLE,constrain(right_motor_speed,0,255));
}
void motordir(char *left_motor_dir ,char *right_motor_dir){ 
  // left motor (Front) dir
  if ( left_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW); 
  }else if ( left_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_LEFT_F_IN1,LOW);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }else if ( left_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }else if ( left_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_LEFT_F_IN1,LOW);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW);
  }
  // left motor (Back) dir
  if ( left_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW); 
  }else if ( left_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_LEFT_F_IN1,LOW);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }else if ( left_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }else if ( left_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_LEFT_F_IN1,LOW);
      digitalWrite(MOTOR_LEFT_F_IN2,LOW);
  }
  // right (Front) motor dir
  if ( right_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW);   
  }else if ( right_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);   
  }else if ( right_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
  }else if ( right_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW);
  }
  // right motor (Back) dir
  if ( right_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW); 
      digitalWrite(MOTOR_RIGHT_B_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_B_IN2,LOW);   
  }else if ( right_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);   
  }else if ( right_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
  }else if ( right_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_F_IN2,LOW);
  }
}
