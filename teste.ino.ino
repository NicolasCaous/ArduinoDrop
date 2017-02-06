int motorPin1 = 8; // Blue / Синий - 28BYJ48 pin 1
int motorPin2 = 9; // Pink / Розовый - 28BYJ48 pin 2
int motorPin3 = 10; // Yellow / Желтый - 28BYJ48 pin 3
int motorPin4 = 11; // Orange / Оранжевый - 28BYJ48 pin 4
int motorSpeed = 1200; //variable to set stepper speed.
int count = 0; // count of steps made.


int base[8] = {
  B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001
};
int lookup[8] = {
  B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001
};

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

bool apenas1Vez = true;

void loop() {
  if(analogRead(A0) > 1000) {
    if(apenas1Vez) {
      for(int i=0; i<8; i++)
        lookup[i] = base[i];
      apenas1Vez = false;
    }
    clockwise();
  } else if(analogRead(A1) > 1000) {
    if(apenas1Vez) {
      for(int i=0; i<8; i++)
        lookup[i] = base[i];
      apenas1Vez = false;
    }
    anticlockwise();
  } else {
    for(int i=0; i<8; i++)
      lookup[i] = 0;
      apenas1Vez = true;
    }
}

//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)

void anticlockwise() {
  for(int i = 0; i < 8; i++) {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise() {
  for(int i = 7; i >= 0; i--) {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out) {
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

void stopServo() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

