
#include<ros.h>
#include<std_msgs/String.h>
#include<std_msgs/UInt16.h>
#include<std_msgs/Empty.h>
#include<geometry_msgs/Twist.h>

ros::NodeHandle nh;

// motor one
        int MOTOR_F_RIGHT_ENABLE=4;
        int MOTOR_F_RIGHT_IN1=3;
        int MOTOR_F_RIGHT_IN2=2;
// motor two
        int MOTOR_F_LEFT_ENABLE=7;
        int MOTOR_F_LEFT_IN1=6;
        int MOTOR_F_LEFT_IN2=5;
// motor three
        int MOTOR_B_RIGHT_ENABLE=10;
        int MOTOR_B_RIGHT_IN1=9;
        int MOTOR_B_RIGHT_IN2=8;
// motor four
        int MOTOR_B_LEFT_ENABLE=13;
        int MOTOR_B_LEFT_IN1=12;
        int MOTOR_B_LEFT_IN2=11;

        float v=0.0;
        float w=0.0;
        float vl=0.0;
        float vr=0.0;

        std_msgs::UInt16 str_msg;
        ros::Publisher chatter("chatter",&str_msg);
        char hello[13]="hello world!";

        void roverCallBack(const geometry_msgs::Twist&cmd_vel)
        {
        v=cmd_vel.linear.x;
        w=cmd_vel.angular.z;

        if(Serial.available()>0)
        {
        char state=Serial.read();

        if(v>0&&w==0||state=='W'||state=='w'){
        analogWrite(MOTOR_F_LEFT_ENABLE,255);
        digitalWrite(MOTOR_F_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2,LOW);
        analogWrite(MOTOR_F_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_F_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2,LOW);
        analogWrite(MOTOR_B_LEFT_ENABLE,255);
        digitalWrite(MOTOR_B_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2,LOW);
        analogWrite(MOTOR_B_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_B_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2,LOW);
        Serial.println("Moving forword");

        }else if(v==0&&w==0||state=='X'||state=='x'){
        analogWrite(MOTOR_F_LEFT_ENABLE,200);
        digitalWrite(MOTOR_F_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2,HIGH);
        analogWrite(MOTOR_F_RIGHT_ENABLE,200);
        digitalWrite(MOTOR_F_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2,HIGH);
        analogWrite(MOTOR_B_LEFT_ENABLE,200);
        digitalWrite(MOTOR_B_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2,HIGH);
        analogWrite(MOTOR_B_RIGHT_ENABLE,200);
        digitalWrite(MOTOR_B_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2,HIGH);
        Serial.println("Stop");
        }else if(v< 0&&w==0||state=='S'||state=='s'){
        analogWrite(MOTOR_F_LEFT_ENABLE,200);
        digitalWrite(MOTOR_F_LEFT_IN1,LOW);
        digitalWrite(MOTOR_F_LEFT_IN2,HIGH);
        analogWrite(MOTOR_F_RIGHT_ENABLE,200);
        digitalWrite(MOTOR_F_RIGHT_IN1,LOW);
        digitalWrite(MOTOR_F_RIGHT_IN2,HIGH);

        analogWrite(MOTOR_B_LEFT_ENABLE,200);
        digitalWrite(MOTOR_B_LEFT_IN1,LOW);
        digitalWrite(MOTOR_B_LEFT_IN2,HIGH);
        analogWrite(MOTOR_B_RIGHT_ENABLE,200);
        digitalWrite(MOTOR_B_RIGHT_IN1,LOW);
        digitalWrite(MOTOR_B_RIGHT_IN2,HIGH);
        Serial.println("Moving backword");
        }else if(w>0&&v==0||state=='D'||state=='d'){
        analogWrite(MOTOR_F_LEFT_ENABLE,255);
        digitalWrite(MOTOR_F_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2,LOW);
        analogWrite(MOTOR_F_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_F_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2,HIGH);

        analogWrite(MOTOR_B_LEFT_ENABLE,255);
        digitalWrite(MOTOR_B_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2,LOW);
        analogWrite(MOTOR_B_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_B_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2,HIGH);
        Serial.println("Right");
        }else if(w< 0&&v==0||state=='A'||state=='a'){
        analogWrite(MOTOR_F_LEFT_ENABLE,255);
        digitalWrite(MOTOR_F_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2,HIGH);
        analogWrite(MOTOR_F_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_F_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2,LOW);

        analogWrite(MOTOR_B_LEFT_ENABLE,255);
        digitalWrite(MOTOR_B_LEFT_IN1,HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2,HIGH);
        analogWrite(MOTOR_B_RIGHT_ENABLE,255);
        digitalWrite(MOTOR_B_RIGHT_IN1,HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2,LOW);
        Serial.println("Left");
        }
        }
        }
        ros::Subscriber<geometry_msgs::Twist>sub2("/cmd_vel",roverCallBack);

        void setup()
        {

        Serial.begin(57600);

        pinMode(13,OUTPUT);
        nh.initNode();
        nh.advertise(chatter);
        nh.subscribe(sub2);
        Serial.begin(57600);

        pinMode(MOTOR_F_LEFT_IN1,OUTPUT);
        pinMode(MOTOR_F_LEFT_IN2,OUTPUT);
        pinMode(MOTOR_F_LEFT_ENABLE,OUTPUT);
        pinMode(MOTOR_F_RIGHT_IN1,OUTPUT);
        pinMode(MOTOR_F_RIGHT_IN2,OUTPUT);
        pinMode(MOTOR_F_RIGHT_ENABLE,OUTPUT);

        pinMode(MOTOR_B_LEFT_IN1,OUTPUT);
        pinMode(MOTOR_B_LEFT_IN2,OUTPUT);
        pinMode(MOTOR_B_LEFT_ENABLE,OUTPUT);
        pinMode(MOTOR_B_RIGHT_IN1,OUTPUT);
        pinMode(MOTOR_B_RIGHT_IN2,OUTPUT);
        pinMode(MOTOR_B_RIGHT_ENABLE,OUTPUT);

//         pinMode(20,INPUT);
//         attachInterrupt(digitalPinToInterrupt(20),leftticks,CHANGE);
//         pinMode(21,INPUT);
//         attachInterrupt(digitalPinToInterrupt(21),rightticks,CHANGE);

        }

        void loop()
        {
        chatter.publish(&str_msg);
        nh.spinOnce();
        delay(500);
        }
