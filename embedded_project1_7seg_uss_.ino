#define A 3
#define B 4
#define C 5
#define D 6
#define E 7
#define F 8
#define G 9
#define trigPin 12
#define echoPin 13


// Pins driving common anodes
#define CA1 2
#define CA2 10

// Pins for A B C D E F G, in sequence
const int segs[7] = { A, B, C, D, E, F, G };

// Segments that make each number
const byte numbers[10] = { 0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010,
0b0000010, 0b1111000, 0b0000000, 0b0010000 };

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);

  //Serial.print("Enter the Range = ");
  //while(Serial.available()==0){ }
  //check=Serial.parseInt();
}

void loop() {

  long duration, cm;

 
  for (int digit1=0; digit1 < 10; digit1++ ) {
    for (int digit2=0; digit2 < 10; ) {
      unsigned long startTime = millis();
      for (unsigned long elapsed=0; elapsed < 600; elapsed = millis() - startTime) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("distance = ");
  Serial.print(cm);
  Serial.println("cm");

  if(cm<50)
  {
    digit2++;
    delay(300);
  }
        
        lightDigit1(numbers[digit1]);
        delay(5);
        lightDigit2(numbers[digit2]);
        delay(5);
      }
    }
  }
}

void lightDigit1(byte number) {
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  lightSegments(number);
}

void lightDigit2(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  lightSegments(number);
}

void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
