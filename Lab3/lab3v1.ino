#define PWML 9     // left motor power
#define PWMR 11    // right motor power

#define Kp 0.1 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 0.2 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightMaxSpeed 60 // max speed of the robot
#define leftMaxSpeed 60 // max speed of the robot
#define rightBaseSpeed 60 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 11  // this is the speed at which the motors should spin when the robot is perfectly on the line

#define echoL 3      // ultrasonic sensor
#define trigL 4      // ultrasonic sensor

#define echoR 5      // ultrasonic sensor
#define trigR 6      // ultrasonic sensor

#include <QTRSensors.h>

// defines variables
long durationR, durationL;
int distanceR, distanceL;
/*-------definning Outputs------*/
#define LM1 8       // left motor
#define LM2 7       // left motor
#define RM1 12      // right motor
#define RM2 13      // right motor

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  0, 1, 2, 3, 4, 5, 6, 7
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  pinMode(echoR, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigL, OUTPUT);

  pinMode(PWML, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWMR, OUTPUT);

  //Calibrate the 8 ir sensors
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

int irPosition() {
  //Ir sensor
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values

  delay(250);

  return position;
}

void turnLeft() {

  Serial.println("TURN LEFT");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  analogWrite(PWML, 60);

  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(PWMR, 60);

  delay(500);

  Serial.println("DONE TURN LEFT");
}
void turnRight() {
  Serial.println("TURN RIGHT");
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  analogWrite(PWML, 60);

  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(PWMR, 60);

  delay(500);
}
void moveStraight() {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      Serial.println("DRIVE");
}
void followLine() {
  do {
        getDistanceLR();

    if(3000 < irPosition() <5000){
      moveStraight();
    }
    else if (irPosition() < 3000) {
      turnRight();
    }
    else if (irPosition() > 5000){
      turnLeft();
    }
  }while((0 > irPosition() < 8000) && (distanceR <= 10 && distanceL <= 10));
}

void getDistanceLR(){
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
  distanceL = durationL * 0.034 / 2;


  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(echoR, HIGH);
  // Calculating the distance
  distanceR = durationR * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  Serial.print("DistanceL: ");
  Serial.println(distanceL);
  Serial.print("DistanceR: ");
  Serial.println(distanceR);
  //????
  //delay(1000);
}
void moveOnTable() {



  while (irPosition() == 0) {
      getDistanceLR();

    if (distanceR <= 10 && distanceL <= 10) //move forward
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWML, 60);

      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(PWMR, 60);
      Serial.println("DRIVE");


    }
    else if (distanceL > 10 && distanceR <= 10) //turn right
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
    else if (distanceL <= 10 && distanceR > 10) //turn left
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
    else if (distanceL > 10 && distanceR > 10)    // stop
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
}
void loop()
{
  moveOnTable();
  return;
  followLine();

}
