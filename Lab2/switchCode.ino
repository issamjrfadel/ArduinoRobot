int ledPin = 52; // choose the pin for the LED
int inPin = 50;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status
/*
 * gnd on com 
 * vcc to NO and pin 50 also on NO use resistor for VCC
 */
void setup() {
  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
     Serial.begin(9600);

}

void loop(){
  val = digitalRead(inPin);  // read input value
  if (val == LOW){
    Serial.println("CLICKED");
  }
  if (val == LOW) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin, HIGH);  // turn LED OFF
  } else {

    digitalWrite(ledPin, LOW);  // turn LED ON
  }
}
