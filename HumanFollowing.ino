#define TRIG 11
#define ECHO 12

#define IR_RIGHT 2
#define IR_LEFT 3

//Left motor
int enA = 5;
int in1 = 7;
int in2 = 8;

//Right motor
int enB = 6;
int in3 = 9;
int in4 = 10;

float pulse_width, distance;

void setup()
{
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  pedala(0,0);   
}


void loop()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  pulse_width = pulseIn(ECHO, HIGH);
  distance = (pulse_width*.0343)/2;      //CM
  
  int rightValue = digitalRead(IR_RIGHT);
  int leftValue = digitalRead(IR_LEFT);
  //NOTE: If IR sensor detects the hand then its value will be LOW else the value will be HIGH

  if (rightValue == HIGH && leftValue == HIGH)
  {
    pedala(0, 0);
  }

  if (rightValue == LOW && leftValue == LOW && distance > 10)           
  {
    pedala(150, 150);
  }

  if (rightValue == LOW && leftValue == LOW && distance > 10)
  {
    pedala(150, 150);
  }

  //If right sensor detects hand, then turn right. Rotate the left motor
  if (rightValue == LOW && leftValue == HIGH )
  {
      pedala(170, 0); 
  }
  
  //If left sensor detects hand, then turn left. Rotate the right motor
  if (rightValue == HIGH && leftValue == LOW )
  {
      pedala(0, 170); 
  }
}

void pedala(int left, int right)
{
  if (left < 0)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH); 
    analogWrite(enA, abs(left));  
  }
  if (left > 0)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(enA, left);      
  }
  if (left == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0); 
  }
  if (right < 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, abs(right));
  }
  if (right > 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, right);
  }
  if (right == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, 0);
  }
}
