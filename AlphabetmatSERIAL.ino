const int numValidKeys = 3;
const int fsrPins[]      {A0,   A1,  A2};
const char keyOutputs[]  {'A', 'B', 'C'};
int fsrReadout[numValidKeys];
bool keyPressed[numValidKeys];

const int threshold = 50;

int count = 0;
bool flag = false;



void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(7, INPUT);
}

void updateKey(int index){
  if(keyPressed[index] && fsrReadout[index] < threshold){
    keyPressed[index] = false;
  }
  
  else if(fsrReadout[index] > threshold && !keyPressed[index]){
    keyPressed[index] = true;
    Serial.print(keyOutputs[index]);
  }

  return;
}
int val = 0;
void loop() {
  
  val = digitalRead(7);
  if(val > 0){
    Serial.print("Guh");
  }
  
  for(int i = 0; i < numValidKeys; i++){
    fsrReadout[i] = analogRead(fsrPins[i]);
    updateKey(i);
  }

  delay(250);
}
