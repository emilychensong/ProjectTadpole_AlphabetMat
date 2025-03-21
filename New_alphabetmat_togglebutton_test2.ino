// For new alphabet mat with toggle buttons - test w/ 2 buttons
// TinkerCAD schematic: https://www.tinkercad.com/things/01DHOdLPJu6/editel?returnTo=%2Fdashboard

const int buttonPin1 = 2;  // Toggle switch 1 pin
const int buttonPin2 = 3; // Toggle switch 2 pin
bool lastState1 = LOW;  // Store previous state of switch 1
bool lastState2 = LOW; // Store previous state of switch 2

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  delay(1000);
}

void loop() {
  bool currentState1 = digitalRead(buttonPin1);  // Read toggle switch state
  bool currentState2 = digitalRead(buttonPin2);


  if (currentState1 != lastState1) {  // Detect any change (ON → OFF or OFF → ON)
    Serial.print("A");
    delay(200); // prevent internal bouncing
  }

  if (currentState2 != lastState2) {  // Detect any change (ON → OFF or OFF → ON)
    Serial.print("B");
    delay(200); // prevent internal bouncing
  }

  lastState1 = currentState1;  // Update last known state
  lastState2 = currentState2;  // Update last known state
}



