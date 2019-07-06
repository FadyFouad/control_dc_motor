// Arduino Pins | Bluetooth Pins
// RX (Pin 0) ———> TX
// TX (Pin 1) ———> RX
// 5V ———> VCC
// GND ———> GND

// motor one
int MOTOR_F_RIGHT_ENABLE = 4;
int MOTOR_F_RIGHT_IN1 = 3;
int MOTOR_F_RIGHT_IN2 = 2;
// motor two
int MOTOR_F_LEFT_ENABLE = 7;
int MOTOR_F_LEFT_IN1 = 6;
int MOTOR_F_LEFT_IN2 = 5;

void setup()
{
    Serial.begin(9600);
    // set all the motor control pins to outputs
    pinMode(MOTOR_F_RIGHT_ENABLE, OUTPUT);
    pinMode(MOTOR_F_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_F_RIGHT_IN2, OUTPUT);
    pinMode(MOTOR_F_LEFT_ENABLE, OUTPUT);
    pinMode(MOTOR_F_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_F_LEFT_IN2, OUTPUT);
}
void baseMove()
{
    analogWrite(MOTOR_F_LEFT_ENABLE, 255);
    analogWrite(MOTOR_F_RIGHT_ENABLE, 255);

    if (Serial.available() > 0)
    {
        char state = Serial.read();
        if (state == 'W' || state == 'w') //forword
        {
            moveForword();
        }
        if (state == 'S' || state == 's') //backword
        {
            moveBackword();
        }
        if (state == 'D' || state == 'd') //right
        {
            moveRight();
        }
        if (state == 'A' || state == 'a') //left
        {
            moveLeft();
        }
        if (state == 'X' || state == 'x')
        {
            stopMoving();
        }
    }
}

void moveForword()
{
    digitalWrite(MOTOR_F_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_F_LEFT_IN2, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

    Serial.println("Moving Forword");
}
void moveBackword()
{
    digitalWrite(MOTOR_F_LEFT_IN1, LOW);
    digitalWrite(MOTOR_F_LEFT_IN2, HIGH);
    digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN2, HIGH);

    Serial.println("Moving Backword");
}
void moveLeft()
{
    digitalWrite(MOTOR_F_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_F_LEFT_IN2, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

    Serial.println("Moving Left");
}
void moveRight()
{
    digitalWrite(MOTOR_F_LEFT_IN1, LOW);
    digitalWrite(MOTOR_F_LEFT_IN2, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

    Serial.println("Moving Right");
}
void stopMoving()
{
    digitalWrite(MOTOR_F_LEFT_IN1, LOW);
    digitalWrite(MOTOR_F_LEFT_IN2, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

    Serial.println("Stop!");
}

void loop()
{
    baseMove();
}
