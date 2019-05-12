// motor one
int MOTOR_F_RIGHT_ENABLE = 4;
int MOTOR_F_RIGHT_IN1 = 3;
int MOTOR_F_RIGHT_IN2 = 2;
// motor two
int MOTOR_F_LEFT_ENABLE = 7;
int MOTOR_F_LEFT_IN1 = 6;
int MOTOR_F_LEFT_IN2 = 5;
// motor three
int MOTOR_B_RIGHT_ENABLE = 10;
int MOTOR_B_RIGHT_IN1 = 9;
int MOTOR_B_RIGHT_IN2 = 8;
// motor four
int MOTOR_B_LEFT_ENABLE = 13;
int MOTOR_B_LEFT_IN1 = 12;
int MOTOR_B_LEFT_IN2 = 11;

void setup()
{
    // set all the motor control pins to outputs
    pinMode(MOTOR_F_RIGHT_ENABLE, OUTPUT);
    pinMode(MOTOR_F_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_F_RIGHT_IN2, OUTPUT);

    pinMode(MOTOR_F_LEFT_ENABLE, OUTPUT);
    pinMode(MOTOR_F_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_F_LEFT_IN2, OUTPUT);

    pinMode(MOTOR_B_RIGHT_ENABLE, OUTPUT);
    pinMode(MOTOR_B_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_B_RIGHT_IN2, OUTPUT);

    pinMode(MOTOR_B_LEFT_ENABLE, OUTPUT);
    pinMode(MOTOR_B_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_B_LEFT_IN2, OUTPUT);
}
void motorMove()
{
    char state = 'W';

    if (state == 'W')//forword
    {
        digitalWrite(MOTOR_F_LEFT_IN1, HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2, LOW);
        analogWrite(MOTOR_F_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_F_RIGHT_IN1, HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2, LOW);
        analogWrite(MOTOR_F_RIGHT_ENABLE, 255);

        digitalWrite(MOTOR_B_LEFT_IN1, HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2, LOW);
        analogWrite(MOTOR_B_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_B_RIGHT_IN1, HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2, LOW);
        analogWrite(MOTOR_B_RIGHT_ENABLE, 255);

    }
    if (state == 'S')//backword
    {
        digitalWrite(MOTOR_F_LEFT_IN1, LOW);
        digitalWrite(MOTOR_F_LEFT_IN2, HIGH);
        analogWrite(MOTOR_F_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_F_RIGHT_IN2, HIGH);

        digitalWrite(MOTOR_B_LEFT_IN1, LOW);
        digitalWrite(MOTOR_B_LEFT_IN2, HIGH);

        digitalWrite(MOTOR_B_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_B_RIGHT_IN2, HIGH);
    }
    if (state == 'D')//right
    {
        digitalWrite(MOTOR_F_LEFT_IN1, LOW);
        digitalWrite(MOTOR_F_LEFT_IN2, LOW);
        analogWrite(MOTOR_F_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_F_RIGHT_IN1, HIGH);
        digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

        digitalWrite(MOTOR_B_LEFT_IN1, HIGH);
        digitalWrite(MOTOR_B_LEFT_IN2, LOW);

        digitalWrite(MOTOR_B_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_B_RIGHT_IN2, LOW);
    }
    if (state == 'A')//left
    {
        digitalWrite(MOTOR_F_LEFT_IN1, HIGH);
        digitalWrite(MOTOR_F_LEFT_IN2, LOW);
        analogWrite(MOTOR_F_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

        digitalWrite(MOTOR_B_LEFT_IN1, LOW);
        digitalWrite(MOTOR_B_LEFT_IN2, LOW);

        digitalWrite(MOTOR_B_RIGHT_IN1, HIGH);
        digitalWrite(MOTOR_B_RIGHT_IN2, LOW);
    }
    if (state == 'X')
    {
        digitalWrite(MOTOR_F_LEFT_IN1, LOW);
        digitalWrite(MOTOR_F_LEFT_IN2, LOW);
        analogWrite(MOTOR_F_LEFT_ENABLE, 255);

        digitalWrite(MOTOR_F_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_F_RIGHT_IN2, LOW);

        digitalWrite(MOTOR_B_LEFT_IN1, LOW);
        digitalWrite(MOTOR_B_LEFT_IN2, LOW);

        digitalWrite(MOTOR_B_RIGHT_IN1, LOW);
        digitalWrite(MOTOR_B_RIGHT_IN2, LOW);
    }
}

void loop()
{
    motorMove();
}