enum States { OFF, AUTO, MANUAL };
States currentState = OFF;
States nextState = OFF;

bool read = HIGH;
bool lastRead = HIGH;
bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool buttonPressed = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool ledState = LOW;

int rawValue = 0;
float potValue = 0;

void setup() {
  Serial.begin(9600);

  pinMode(8, INPUT_PULLUP);
  pinMode(A0, INPUT);

  pinMode(11, OUTPUT);
}

void loop() {
  nextState = currentState;
  rawValue = analogRead(A0);
  potValue = rawValue / 4;

  handleButton();

  switch(currentState) {
    case(OFF):
      OffState();
      break;

    case(AUTO):
      AutoState();
      break;
    
    case(MANUAL):
      ManualState();
      break;
      
  }

  currentState = nextState;
  buttonPressed = false;
}

void handleButton() {
  read = digitalRead(8);

  if(lastRead != read) {
    lastDebounceTime = millis();
  }

  if(millis() - lastDebounceTime > debounceDelay) {
    if(read != buttonState) {
      buttonState = read;
    }

    if(buttonState == HIGH && lastButtonState == LOW) {
      buttonPressed = true;
    }
  }

  if(buttonPressed) Serial.println("CHANGE");

  lastButtonState = buttonState;
  lastRead = read;
}

void OffState() {
  digitalWrite(11, LOW);

  if(buttonPressed) nextState = AUTO;
}

void AutoState() {
  digitalWrite(11, HIGH);

  if(buttonPressed) nextState = MANUAL;
}

void ManualState() {
  analogWrite(11, potValue);
  if(buttonPressed) nextState = OFF;
}
