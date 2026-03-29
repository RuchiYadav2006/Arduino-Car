/* * Robot Obstacle Avoidance System
 * Language: Arduino C 
 */

// --- Pin Definitions ---
#define TRIG_FRONT 2
#define ECHO_FRONT 3
#define TRIG_BACK  4
#define ECHO_BACK  5
#define TRIG_LEFT  6
#define ECHO_LEFT  7
#define TRIG_RIGHT 8
#define ECHO_RIGHT 9

#define EN_LEFT    10
#define IN1_LEFT   11
#define IN2_LEFT   12
#define EN_RIGHT   13
#define IN1_RIGHT  A0
#define IN2_RIGHT  A1

// --- Function Prototypes ---
long measureDistance(int trigPin, int echoPin);
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();

void setup() {
    // Initialize Motor Pins
    pinMode(IN1_LEFT, OUTPUT);
    pinMode(IN2_LEFT, OUTPUT);
    pinMode(EN_LEFT, OUTPUT);
    pinMode(IN1_RIGHT, OUTPUT);
    pinMode(IN2_RIGHT, OUTPUT);
    pinMode(EN_RIGHT, OUTPUT);

    // Initialize Sensor Pins
    pinMode(TRIG_FRONT, OUTPUT);
    pinMode(ECHO_FRONT, INPUT);
    pinMode(TRIG_BACK, OUTPUT);
    pinMode(ECHO_BACK, INPUT);
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);

    Serial.begin(9600);
}

void loop() {
    // 1. Sense Environment
    long distFront = measureDistance(TRIG_FRONT, ECHO_FRONT);
    long distLeft  = measureDistance(TRIG_LEFT, ECHO_LEFT);
    long distRight = measureDistance(TRIG_RIGHT, ECHO_RIGHT);
    long distBack  = measureDistance(TRIG_BACK, ECHO_BACK);

    // 2. Decision Logic
    if (distFront > 15) {
        // Path is clear
        moveForward();
    } 
    else if (distRight > 25) {
        // Obstacle ahead, but right is clear
        turnRight();
        delay(300); 
    } 
    else if (distLeft > 25) {
        // Obstacle ahead/right, but left is clear
        turnLeft();
        delay(300);
    } 
    else if (distBack > 15) {
        // Boxed in - move back slowly
        moveBackward();
        delay(500);
    } 
    else {
        // Completely stuck
        stopMotors();
    }
    
    delay(50); // Small stability delay
}

// --- Function Definitions ---

long measureDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout added
    // Formula: Distance = (Time x Speed of Sound) / 2
    return duration * 0.034 / 2;
}

void moveForward() {
    digitalWrite(IN1_LEFT, HIGH);
    digitalWrite(IN2_LEFT, LOW);
    digitalWrite(IN1_RIGHT, HIGH);
    digitalWrite(IN2_RIGHT, LOW);
    analogWrite(EN_LEFT, 200);  
    analogWrite(EN_RIGHT, 200); 
}

void moveBackward() {
    digitalWrite(IN1_LEFT, LOW);
    digitalWrite(IN2_LEFT, HIGH);
    digitalWrite(IN1_RIGHT, LOW);
    digitalWrite(IN2_RIGHT, HIGH);
    analogWrite(EN_LEFT, 180);
    analogWrite(EN_RIGHT, 180);
}

void turnLeft() {
    digitalWrite(IN1_LEFT, LOW);
    digitalWrite(IN2_LEFT, HIGH);
    digitalWrite(IN1_RIGHT, HIGH);
    digitalWrite(IN2_RIGHT, LOW);
    analogWrite(EN_LEFT, 200);
    analogWrite(EN_RIGHT, 200);
}

void turnRight() {
    digitalWrite(IN1_LEFT, HIGH);
    digitalWrite(IN2_LEFT, LOW);
    digitalWrite(IN1_RIGHT, LOW);
    digitalWrite(IN2_RIGHT, HIGH);
    analogWrite(EN_LEFT, 200);
    analogWrite(EN_RIGHT, 200);
}

void stopMotors() {
    digitalWrite(IN1_LEFT, LOW);
    digitalWrite(IN2_LEFT, LOW);
    digitalWrite(IN1_RIGHT, LOW);
    digitalWrite(IN2_RIGHT, LOW);
}

 

