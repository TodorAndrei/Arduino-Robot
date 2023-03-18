#include <IRremote.h>

const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;

int enA=5;
int in1=7;
int in2=8;
int enB=6;
int in3=9;
int in4=10;

void setup(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value);

        switch(results.value) {
          case 16718055:
            pedala(255, 255);
            break;
     
          case 16734885:
            pedala(160, -160);
            break;

          case 16730805:
            pedala(-255, -255);
            break;

          case 16716015:
            pedala(-160, 160);
            break;

          case 16726215:
            pedala(0, 0);
            break;
        }
        irrecv.resume();
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
