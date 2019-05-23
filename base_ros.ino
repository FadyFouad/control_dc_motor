#include <ros.h>
#include <std_msgs/Int16.h>

#define ENA 6
#define ENB 11
#define IN1 8
#define IN2 9
#define IN3 12
#define IN4 13

void cmdLeftWheelCB( const std_msgs::Int16& msg)
{
if(msg.data >= 0)
{
analogWrite(ENA,msg.data);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
}
else
{
analogWrite(ENA,-msg.data);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
}
}
void cmdRightWheelCB( const std_msgs::Int16& msg)
{
if(msg.data >= 0)
{
analogWrite(ENB,msg.data);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
else
{
analogWrite(ENB,-msg.data);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
}