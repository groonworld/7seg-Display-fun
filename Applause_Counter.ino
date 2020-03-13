/*
 * Sketch for counting spikes from audio data and printing 
 * the count to a 7-segment LED display.
 * 
 * 14.03.2020 by pgroon
 */

// Pins for the LED display
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int D1 = 9;
const int D2 = 10;
const int D3 = 11;
const int D4 = 12;

// Pins & Variables for the Sound Sensor Module
int sensorAnalogPin = A15;   
int sensorDigitalPin = 52;   
int sensorAnalogValue = 0;
int sensorDigitalValue;
int analogUpperBound = 516;   // Adjust these to your Sound Sensor Module's settings
int analogLowerBound = 411; 

// Variables for replacing delay()
unsigned long prevDisplayTime = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Variables for program logic
int digits[4] = {0, 0, 0, 0};
int counter = 0;
byte digitCounter = 0;
unsigned long nowTime = 0;
long displayInterval = 2;


void setup() {
  // initialize the display pins as outputs.
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  
  // Initialize common display pins
  // For common cathode displays, these need to be set to LOW to activate the corresponding segment. For common anode displays, invert all values.
  pinMode(D1, OUTPUT);    
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  // Initialize Serial Monitor & Sound Sensor Pins
  Serial.begin(9600);               // The IDE settings for Serial Monitor/Plotter (preferred) must match this speed
  pinMode(sensorDigitalPin,INPUT);  
  
}

void loop() {
  
  writeNum(counter);
  Serial.println(sensorAnalogValue);
  sensorAnalogValue  = analogRead(sensorAnalogPin);
  sensorDigitalValue = digitalRead(sensorDigitalPin); 

  if(sensorDigitalValue == HIGH) {
    counter++;
    delay(50);
  }
} 

void writeNum(int value) {
  digitCounter = 0;
  getDigits(value);
  while (digitCounter < 4) {
    nowTime = millis();
    if (nowTime - prevDisplayTime >= displayInterval) {
      writeDig(digits[digitCounter], digitCounter);
      digitCounter++;
      prevDisplayTime = nowTime;
    }  
  }
}

/*
 * Calculates the individual digits from a given int value and stores them in the digits[] array.
 */
void getDigits(int value) {
  digits[3] = value % 10;             // Get lowest digit
  if (value >= 10 && value <= 99) {
    digits[2] = (value / 10);
  } else if (value >= 100 && value <= 999) {
    digits[2] = (value / 10) % 10;
    digits[1] = (value / 100);
  } else if (value >= 1000 && value <= 9999) {
    digits[2] = (value / 10) % 10;
    digits[1] = (value / 100) % 10;
    digits[0] = (value / 1000);
  } else if (value >= 10000) {          
    // For values that exceed display length, this sets all digits to -1, which will display as '-----'.
    for (byte i = 0; i < 4; i++) {
      digits[i] = -1;
    }
  }
}

/*  
 *  Prints a given value to the specified position on the 4-digit LED display.
 *  Value 0-9, otherwise will show '-'.
 *  Pos   1-3, otherwise will print to rightmost digit
 */
void writeDig(int value, int pos) {
   
  // Specifies LED status for numeral values from 0 through 9.
  switch (value) {
    case 0:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      delay(1);   // This is needed to reduce ghosting
      break;
    case 1:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 2:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 3:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 4:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 5:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 6:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 7:  
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 8:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
      break;  
    case 9: 
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH); 
      delay(1);   // This is needed to reduce ghosting
      break;
    default:    // default to a "-" sign as a kind of error message
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      delay(1);   // This is needed to reduce ghosting
  }
      
  // Specifies position on the display
  switch (pos) {
    case 0:     // leftmost digit
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
    case 1:     // middle-left digit
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      break;
    case 2:     // middle-right digit
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
      break; 
    case 3:  // rightmost digit
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      break;   
  } 
}
