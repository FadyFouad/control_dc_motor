//part of every ROS embedded linux program
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
// allows our program to create publishers and subscribers
ros::NodeHandle  nh;
std_msgs::String str_msg;
char hello[13] = "LeaveMessage";
ros::Publisher chatter("chatter", &str_msg);

#define MOTOR_LEFT_F_IN1 13
#define MOTOR_LEFT_F_IN2 7
#define MOTOR_LEFT_F_ENABLE 5
#define MOTOR_LEFT_B_IN1 3
#define MOTOR_LEFT_B_IN2 4
#define MOTOR_LEFT_B_ENABLE 2

#define MOTOR_RIGHT_F_IN1 10 
#define MOTOR_RIGHT_F_IN2 9
#define MOTOR_RIGHT_F_ENABLE 8 
#define MOTOR_RIGHT_B_IN1 13
#define MOTOR_RIGHT_B_IN2 12
#define MOTOR_RIGHT_B_ENABLE 11 

// ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){

  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("motor_move", &messageCb );
ros::Subscriber<std_msgs::Empty> sub2("motor_move", &messageCb );

void setup()
{ 
// pinMode(13, OUTPUT);
// initialize ROS node handle
nh.initNode();
// Advertise any topics being published, and subscribe to any topics you wish to listen to.
nh.advertise(chatter);
nh.subscribe(sub);
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

//   pinMode(20, INPUT);
//  attachInterrupt(digitalPinToInterrupt(20), leftticks, CHANGE);
//   pinMode(21, INPUT);
//  attachInterrupt(digitalPinToInterrupt(21), rightticks, CHANGE);

}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}
void motorsmove(int left_motor_speed , char *left_motor_dir ,int right_motor_speed , char *right_motor_dir){
  motordir(left_motor_dir ,right_motor_dir );
  analogWrite(MOTOR_LEFT_F_ENABLE,constrain(left_motor_speed,0,255));
  analogWrite(MOTOR_RIGHT_F_ENABLE,constrain(right_motor_speed,0,255));
}

void motordir(char *left_motor_dir ,char *right_motor_dir){ 
  // left motor (Front) dir
  if ( left_motor_dir[0] == 'f'){
    digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
    digitalWrite(MOTOR_LEFT_F_IN2,LOW); 
  }
  else if ( left_motor_dir[0] == 'b'){
    digitalWrite(MOTOR_LEFT_F_IN1,LOW);
    digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }
  else if ( left_motor_dir[0] == 's'){   
    digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
    digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }
  else if ( left_motor_dir[0] == 'e'){
    digitalWrite(MOTOR_LEFT_F_IN1,LOW);
    digitalWrite(MOTOR_LEFT_F_IN2,LOW);
  }
  // left motor (Back) dir
  if ( left_motor_dir[0] == 'f'){
    digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
    digitalWrite(MOTOR_LEFT_F_IN2,LOW); 
  }
  else if ( left_motor_dir[0] == 'b'){
    digitalWrite(MOTOR_LEFT_F_IN1,LOW);
    digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }
  else if ( left_motor_dir[0] == 's'){   
    digitalWrite(MOTOR_LEFT_F_IN1,HIGH);
    digitalWrite(MOTOR_LEFT_F_IN2,HIGH);
  }
  else if ( left_motor_dir[0] == 'e'){
    digitalWrite(MOTOR_LEFT_F_IN1,LOW);
    digitalWrite(MOTOR_LEFT_F_IN2,LOW);
  }
  // right (Front) motor dir
  if ( right_motor_dir[0] == 'f'){
    digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
    digitalWrite(MOTOR_RIGHT_F_IN2,LOW);   
  }
  else if ( right_motor_dir[0] == 'b'){
    digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);   
  }
  else if ( right_motor_dir[0] == 's'){   
    digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
    digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
  }
  else if ( right_motor_dir[0] == 'e'){
    digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_F_IN2,LOW);
  }
  // right motor (Back) dir
  if ( right_motor_dir[0] == 'f'){
    digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
    digitalWrite(MOTOR_RIGHT_F_IN2,LOW); 
    digitalWrite(MOTOR_RIGHT_B_IN1,HIGH);
    digitalWrite(MOTOR_RIGHT_B_IN2,LOW);   
  }
  else if ( right_motor_dir[0] == 'b'){
    digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);   
  }
  else if ( right_motor_dir[0] == 's'){   
    digitalWrite(MOTOR_RIGHT_F_IN1,HIGH);
    digitalWrite(MOTOR_RIGHT_F_IN2,HIGH);
  }
  else if ( right_motor_dir[0] == 'e'){
    digitalWrite(MOTOR_RIGHT_F_IN1,LOW);
    digitalWrite(MOTOR_RIGHT_F_IN2,LOW);
  }
}
