#include <Keyboard.h>

const int numValidKeys = 29; // A - Z, [Space], [Enter], [Clear]
const int fsrPins[] {A0, A1};

// MUX select pins: S0 ~ 2, S1 ~ 3, etc.
const int selectPins1[] {2,3,4,5}; // MUX 1: Letters A - P (16 chars)
const int selectPins2[] {10,11,12,13}; // MUX 2: Letters Q - [Space], [Enter] (12 chars)

const char keyOutputs[]  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',' '};
int fsrReadout[numValidKeys];
bool keyPressed[numValidKeys];

const int threshold = 40; // Set threshold for "pressed"

bool flag = false;

void setup() {
  Keyboard.begin();  // Initialize serial communication
  
  // Initialize MUX select pins
  for(int i = 2; i < 6; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  for(int i = 10; i < 14; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  

  // Initialize input pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void updateKey(int index){
  if(keyPressed[index] && fsrReadout[index] < threshold){
    keyPressed[index] = false;
  }
  
  else if(fsrReadout[index] > threshold && !keyPressed[index]){
    flag = true;
    keyPressed[index] = true;
    if(index == 26){
      Keyboard.print(" ");
    }
    else if (index == 27){
      Keyboard.press(KEY_BACKSPACE);
      delay(10);
      Keyboard.release(KEY_BACKSPACE);
    }
    else if (index == 28){
      Keyboard.press(KEY_BACKSPACE);
      delay(5000);
      Keyboard.release(KEY_BACKSPACE);
    }
    else{
      Keyboard.print(keyOutputs[index]);
    }
  }

  return;
}

void selectMuxPin(byte pin, int mux_n){
  if (pin > 16) return; // Exit if pin is out of scope
  const int *sp = selectPins1;
  if(mux_n == 1){
    sp = selectPins2;
  }

  for (int i=0; i<4; i++)
  {
    if (pin & (1<<i))
      digitalWrite(sp[i], HIGH);
    else
      digitalWrite(sp[i], LOW);
  }
}
void loop() {  
  flag = false;
  for(int pin = 0; pin < numValidKeys; pin++){
    selectMuxPin(pin%16, pin/16);
    fsrReadout[pin] = analogRead(fsrPins[pin/16]);
//     DEBUGGING PRINT STATEMENTS
//   Serial.print(pin);
//   Serial.print(": ");
//   Serial.println(fsrReadout[pin]);
//   Serial.print(" ");
//   Serial.println(keyOutputs[pin]);
    if(!flag) updateKey(pin);
    delay(20);
  }
}
