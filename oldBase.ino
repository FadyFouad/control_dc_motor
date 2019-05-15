/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

#define MOTOR_LEFT_IN1 6
#define MOTOR_LEFT_IN2 7
#define MOTOR_LEFT_ENABLE 5
#define MOTOR_RIGHT_IN1 10
#define MOTOR_RIGHT_IN2 9
#define MOTOR_RIGHT_ENABLE 8 
int counter = 1 ;
int speed_l = 0 ;
int speed_r = 0 ;
char *dir_l ;
char *dir_r ;
char *buf ;
char *buf_s ;
float v = 0.0 ;
float w = 0.0 ;
float vl = 0.0 ;
float vr = 0.0 ;

std_msgs::UInt16 str_msg;
ros::Publisher chatter("chatter", &str_msg);

//void messageCb( const std_msgs::String& toggle_msg){
//  String(toggle_msg.data).toCharArray(buf_s, String(toggle_msg.data).length());
//  buf = strtok (buf_s,",");
//  while (buf != NULL)
//  {
//    int result = 0 ;
//    if(counter == 1 || counter == 3){
//      result = atoi(buf);
//      if(counter == 1){speed_l = result ;}else{speed_r = result ;}
//      
//    }else{
//      if(counter == 2){dir_l = buf ;}else{dir_r = buf ;}
//    }
//    buf = strtok (NULL, " ,.-");
//    counter ++ ;
//  }
//  motorsmove(speed_l,dir_l,speed_r,dir_r);
//}

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{
  v = cmd_vel.linear.x   ;
  w = cmd_vel.angular.z  ;
  vl = v - ((w*0.32)/2) ;
  vr = v + ((w*0.32)/2) ;
  vl = map(vl, -0.5, 0.5, -255, 255);
  vr = map(vr, -0.5, 0.5, -255, 255);
  if(v > 0 && w == 0){
      analogWrite(MOTOR_LEFT_ENABLE,constrain(sqrt(sq(vl)),0,255));
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,LOW);
      analogWrite(MOTOR_RIGHT_ENABLE,constrain(sqrt(sq(vr)),0,255));
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,LOW);   
  }else if( v == 0 && w == 0){
      analogWrite(MOTOR_LEFT_ENABLE,200);
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE,200);
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,HIGH);  
  }else if (v < 0 && w == 0){
    analogWrite(MOTOR_LEFT_ENABLE,200);
    digitalWrite(MOTOR_LEFT_IN1,LOW);
    digitalWrite(MOTOR_LEFT_IN2,HIGH);
    analogWrite(MOTOR_RIGHT_ENABLE,200);
    digitalWrite(MOTOR_RIGHT_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_IN2,HIGH);
  }else if (w > 0 && v == 0){
      analogWrite(MOTOR_LEFT_ENABLE,constrain(sqrt(sq(vl)),0,255));
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,LOW);
      analogWrite(MOTOR_RIGHT_ENABLE,constrain(sqrt(sq(vr)),0,255));
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,HIGH);
    }else if (w < 0 && v == 0){
      analogWrite(MOTOR_LEFT_ENABLE,constrain(sqrt(sq(vl)),0,255));
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE,constrain(sqrt(sq(vr)),0,255));
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,LOW);
    }
  
}

//ros::Subscriber<std_msgs::String> sub("motors_dir", messageCb );
ros::Subscriber <geometry_msgs::Twist> sub2("/cmd_vel", roverCallBack);




char hello[13] = "hello world!";

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  //nh.subscribe(sub);
  nh.subscribe(sub2);
  
  pinMode(MOTOR_LEFT_IN1,OUTPUT);
  pinMode(MOTOR_LEFT_IN2,OUTPUT);
  pinMode(MOTOR_LEFT_ENABLE,OUTPUT);
  pinMode(MOTOR_RIGHT_IN1,OUTPUT);
  pinMode(MOTOR_RIGHT_IN2,OUTPUT);
  pinMode(MOTOR_RIGHT_ENABLE,OUTPUT);

  pinMode(20, INPUT);
  attachInterrupt(digitalPinToInterrupt(20), leftticks, CHANGE);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), rightticks, CHANGE);

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
  analogWrite(MOTOR_LEFT_ENABLE,constrain(left_motor_speed,0,255));
  analogWrite(MOTOR_RIGHT_ENABLE,constrain(right_motor_speed,0,255));
}
void motordir(char *left_motor_dir ,char *right_motor_dir){
  // left motor dir
  if ( left_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,LOW); 
  }else if ( left_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_LEFT_IN1,LOW);
      digitalWrite(MOTOR_LEFT_IN2,HIGH);
  }else if ( left_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_LEFT_IN1,HIGH);
      digitalWrite(MOTOR_LEFT_IN2,HIGH);
  }else if ( left_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_LEFT_IN1,LOW);
      digitalWrite(MOTOR_LEFT_IN2,LOW);
  }
  // right motor dir
  if ( right_motor_dir[0] == 'f'){
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,LOW);   
  }else if ( right_motor_dir[0] == 'b'){
      digitalWrite(MOTOR_RIGHT_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_IN2,HIGH);   
  }else if ( right_motor_dir[0] == 's'){   
      digitalWrite(MOTOR_RIGHT_IN1,HIGH);
      digitalWrite(MOTOR_RIGHT_IN2,HIGH);
  }else if ( right_motor_dir[0] == 'e'){
      digitalWrite(MOTOR_RIGHT_IN1,LOW);
      digitalWrite(MOTOR_RIGHT_IN2,LOW);
  }
}