#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define echoL 3      // ultrasonic sensor
#define trigL 4      // ultrasonic sensor

#define echoR 5      // ultrasonic sensor
#define trigR 6      // ultrasonic sensor


#define echoFront 100
#define trigFront 100

int inPinR = 50;   // choose the input pin (for a pushbutton)
int inPinL = 51;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

// defines variables
long durationR, durationL, durationFront;
int distanceR, distanceL, durationFront;



/*-------definning Outputs------*/
#define LM1 8       // left motor
#define LM2 7       // left motor
#define RM1 12      // right motor
#define RM2 13      // right motor
void setup()
{
  pinMode(echoR,INPUT);
  pinMode(trigR,OUTPUT);
  pinMode(echoL,INPUT);
  pinMode(trigL,OUTPUT);

  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);
  Serial.begin(9600);

  //need new pinMode for the ultrasonic sensor
  pinMode(echoFront,INPUT);
  pinMode(trigFront,OUTPUT);

  //push sensor
  pinMode(inPinR, INPUT);    // declare pushbutton as input
  pinMode(inPinL, INPUT);
}


void searchObject()
{

//-------------------------------------------------------------------------------
    //front ultrasonic sensor
    digitalWrite(trigFront, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigFront, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigFront, LOW);

    durationFront = pulseIn(echoFront, HIGH);
    distanceFront = durationFront*0.034/2;

//-------------------------------------------------------------------------------

//left and right sensors
    // Clears the trigPin
    digitalWrite(trigL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigR, LOW);
    delayMicroseconds(2);
        
    // Sets the trigPin on HIGH state for 10 micro seconds

    digitalWrite(trigL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigL, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
    durationL = pulseIn(echoL, HIGH);
    // Calculating the distance
    distanceL = durationL*0.034/2;


    digitalWrite(trigR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigR, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
    durationR = pulseIn(echoR, HIGH);
    // Calculating the distance
    distanceR = durationR*0.034/2;



    
//-------------------------------------------------------------------------------
    //object is less than 20cm infront of us
    if (distanceFront <= 20)
    {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        analogWrite(PWML, 60);

        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        analogWrite(PWMR, 60);
        Serial.println("Found: Stop");

        valR = digitalRead(inPinR);
        valL = digitalRead(inPinL);
        //object found, move forward
        if (valR == LOW || valL == LOW)
        {
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
            analogWrite(PWML, 60);

            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            analogWrite(PWMR, 60);
            Serial.println("CLICKED");
        }
    }

    //if something is less than length of table then it is an object and moves toward it
    if (distanceFront >= 20 && distanceFront <= 150 && distanceR <= 10 && distanceL <= 10)
    {
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        analogWrite(PWML, 60);

        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        analogWrite(PWMR, 60);
        Serial.println("Found: Move forward");
    }
    
    //left sensor doesn't matter when turning right
    else if (distanceFront >= 150 && distanceR <= 10)
    {
          //turn right
          digitalWrite(LM1, HIGH);
          digitalWrite(LM2, LOW);
          analogWrite(PWML, 60);

          digitalWrite(RM1, LOW);
          digitalWrite(RM2, HIGH);
          analogWrite(PWMR, 60); 
          Serial.println("Not Found: Move right");

    
    }
    
    //right sensor doesn't matter when turning left
    else if (distanceFront >= 150 && distanceL <= 10)
    {
        //turn left
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, HIGH);
        analogWrite(PWML, 60);

        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        analogWrite(PWMR, 60);
        Serial.println("Not Found: Move left");     
    }
  
}

void loop()
{
        //----------------------------------
        //run the search function up top
        searchObject();
        //----------------------------------
        // Clears the trigPin
        digitalWrite(trigL, LOW);
        delayMicroseconds(2);
        digitalWrite(trigR, LOW);
        delayMicroseconds(2);
        
        // Sets the trigPin on HIGH state for 10 micro seconds

        digitalWrite(trigL, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigL, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
        durationL = pulseIn(echoL, HIGH);
        // Calculating the distance
        distanceL = durationL*0.034/2;


        digitalWrite(trigR, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigR, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
        durationR = pulseIn(echoR, HIGH);
        // Calculating the distance
        distanceR = durationR*0.034/2;
        // Prints the distance on the Serial Monitor

        Serial.print("DistanceL: ");
        Serial.println(distanceL);
        Serial.print("DistanceR: ");
        Serial.println(distanceR);
        //????
        //delay(1000);


    if(distanceR <= 10 && distanceL <= 10) //move forward
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      Serial.println("DRIVE");

    }
    else if(distanceL > 10 && distanceR <= 10) //turn right
    {
      
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 
      
      Serial.println("TURN RIGHT");
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(1000);

      Serial.println("DONE TURNING RIGHT");

    }
    else if(distanceL <= 10 && distanceR > 10) //turn left
    {

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 
      
      Serial.println("TURN LEFT");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      Serial.println("DONE TURN LEFT");

    }
    else if(distanceL > 10 && distanceR > 10)     // stop
    {
      
      Serial.println("BOTH SENSORS OFF");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);

      delay(1000);

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(800); 
      /*
      delay(1000);

      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);

      delay(2000);
      */

      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(PWMR, 60);
      delay(1000);
      Serial.println("DONE BOTH SENSORS OFF");

    }
}
