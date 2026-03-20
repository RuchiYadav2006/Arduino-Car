// Define ultrasonic sensor pins
const int trigFront = 2;
const int echoFront = 3;
const int trigBack = 4;
const int echoBack = 5;
const int trigLeft = 6;
const int echoLeft = 7;
const int trigRight = 8;
const int echoRight = 9;

// Define motor pins
const int enLeft = 10;
const int in1Left = 11;
const int in2Left = 12;
const int enRight = 13;
const int in1Right = A0;
const int in2Right = A1;

void setup() {
  // Motor pins as outputs
  pinMode(in1Left, OUTPUT);
  pinMode(in2Left, OUTPUT);
  pinMode(enLeft, OUTPUT);
  pinMode(in1Right, OUTPUT);
  pinMode(in2Right, OUTPUT);
  pinMode(enRight, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  // Start serial for debugging
  Serial.begin(9600);
}

// Function to measure distance
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert time to distance in cm
}

// Function to move motors
void moveForward() {
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);
  analogWrite(enLeft, 255);  // Full speed
  analogWrite(enRight, 255); // Full speed
}

void moveBackward() {
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);
  analogWrite(enLeft, 255);
  analogWrite(enRight, 255);
}

void turnLeft() {
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);
  analogWrite(enLeft, 255);
  analogWrite(enRight, 255);
}

void turnRight() {
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);
  analogWrite(enLeft, 255);
  analogWrite(enRight, 255);
}

void stopMotors() {
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, LOW);
}

void loop() {
  // Measure distances from all sensors
  long distFront = measureDistance(trigFront, echoFront);
  long distBack = measureDistance(trigBack, echoBack);
  long distLeft = measureDistance(trigLeft, echoLeft);
  long distRight = measureDistance(trigRight, echoRight);

  // Debugging output
  Serial.print("Front: "); Serial.println(distFront);
  Serial.print("Back: "); Serial.println(distBack);
  Serial.print("Left: "); Serial.println(distLeft);
  Serial.print("Right: "); Serial.println(distRight);

  // Logic for object avoidance
  if (distFront > 10) {
    moveForward();  // Move forward if front distance > 30 cm
  } else if (distRight > 20) {
      turnRight();  // Turn right if space on the right
      delay(500);
    } else if (distLeft > 20) {
      turnLeft();   // Turn left if space on the left
      delay(500);
    } else {
      // If no space on either side, move backward
      while (distBack > 20) {
        moveBackward();
        distBack = measureDistance(trigBack, echoBack);  // Keep checking back sensor
      }
    }
  }

 

