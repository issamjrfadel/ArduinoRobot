#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define LIR 2      // left IR sensor
#define RIR 4      // right IR sensor

/*-------definning Outputs------*/
#define LM1 8       // left motor
#define LM2 7       // left motor
#define RM1 12      // right motor
#define RM2 13      // right motor
void setup()
{
  pinMode(LIR,INPUT);    
  pinMode(RIR,INPUT);
  
  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);
  Serial.begin(9600);

}
void loop()
{
    if(!digitalRead(LIR) && !digitalRead(RIR)) //move forward
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      Serial.println("DRIVE");

    }
    if(digitalRead(LIR) && !(digitalRead(RIR))) //turn right
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

                  delay(3000);

            Serial.println("TURN RIGHT");
    
    }
    if(!(digitalRead(LIR)) && digitalRead(RIR)) //turn left
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);  

            delay(3000);

                    Serial.println("TURN LEFT");

    }
   if(digitalRead(LIR) && digitalRead(RIR))     // stop
    {
      /*digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60); 
*/

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60); 

      delay(2000);

      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);
      
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      
                  Serial.println("STOP");

    }
}
