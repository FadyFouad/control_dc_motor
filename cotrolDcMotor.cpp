// connect motor controller pins to Arduino digital pins
// motor one
int enA = 7;
int in1 = 6;
int in2 = 5;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}


void loop()
{
    analogWrite(enA, 255);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
}