#define LIR 8      // left IR sensor
//#define RIR 29     // right IR sensor

void setup() {
  // put your setup code here, to run once:

  pinMode(LIR,INPUT);    
 // pinMode(RIR,INPUT);

    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
if(!digitalRead(LIR)){
        Serial.println("DRIVE");

}
else{
  Serial.println("Nothing");
}
}
