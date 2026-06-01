//DISTANCE
float distance;
float raw;

//BUZZER
unsigned long buzzDuration = 100;
unsigned long buzzSeparation = 100;
unsigned long lastBuzz;
float buzzDistanceMultiplicationFactor = 1.25;
bool buzzing = false;


void setup() {
  Serial.begin(9600);

  pinMode(7, OUTPUT);
  pinMode(8, INPUT);

  pinMode(12, OUTPUT);
}

void loop() {
  raw = readDistance(7, 8);

  if(raw != 0) {
    distance = raw * 0.034/2;
    Serial.println(distance);
  }


  Buzz();
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);

  return pulseIn(echoPin, HIGH, 3000);
}

void Buzz() {
  if(!buzzing && millis() - lastBuzz > buzzSeparation * (distance * buzzDistanceMultiplicationFactor)) {
    buzzing = true;
    lastBuzz = millis();
    tone(12, 1000);
  }

  if(buzzing && millis() - lastBuzz > buzzDuration) {
    buzzing = false;
    noTone(12);
  }
}