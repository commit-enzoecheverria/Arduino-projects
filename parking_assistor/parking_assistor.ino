// DISTANCE
float distance;
float raw;

//BUZZER
unsigned long buzzDuration = 50;
unsigned long buzzSeparation = 100;
unsigned long lastBuzz;
float distanceDivisionFactor = 0.67;
float closeThreshold = 3;
bool buzzing;

//LEDs
int ledsPins[3] = {11, 10, 9};
unsigned long ledSeparation = 500;
unsigned long leds[3] = {11, 10, 9};


void setup() {
  Serial.begin(9600);


  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(8, INPUT);
}

void loop() {
  raw = readDistance(7, 8) * 0.034/2;

  manageDistanceOutput();

  //manageBuzzer();

  if(distance < 26) {
    digitalWrite(leds[0], HIGH);
  }
  else {
    digitalWrite(leds[0], LOW);
  }

  if(distance <)
}

void manageDistanceOutput() {
  if(raw != 0) {
    distance = raw;
  }

  if(distance > closeThreshold) {
    Serial.println(distance);
  }
  else {
    Serial.println("CLOSE");
  }
}

void manageBuzzer() {
  if(distance > closeThreshold) {
    if(!buzzing && millis() - lastBuzz > buzzSeparation * (distance/distanceDivisionFactor)) {
     buzzing = true;
      lastBuzz = millis();
      tone(12, 1000);
    }

    if(buzzing && millis() - lastBuzz > buzzDuration) {
      buzzing = false;
      noTone(12);
    }
  }
  else {
    buzzing = true;
    tone(12, 1000);
  }
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);

  return pulseIn(echoPin, HIGH, 30000);
}

