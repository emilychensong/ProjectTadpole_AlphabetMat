const int fsrPin = A0;  // Analog pin connected to FSR

const int threshold = 100;

int count = 0;
bool flag = false;
void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int fsrReading = analogRead(fsrPin);  // Read analog value from FSR
  //Serial.println(fsrReading);
  if(fsrReading > threshold && !flag){
    flag = true;
    //Serial.println(count++);
    Serial.print("Pressed: ");
    Serial.println(fsrReading);
    /*delay(200);
    int fsrReading2 = analogRead(fsrPin);
    Serial.println(fsrReading2);
    if(fsrReading < fsrReading2){
      Serial.println("I'M LARGER");
    }*/
  }
  else if(flag && fsrReading < threshold){
    flag = false;
  }
  delay(250);
}
