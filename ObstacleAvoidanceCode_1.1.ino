// -------------------- Motor Driver Pins (PWM Compatible) --------------------
#define LEFT_MOTOR_FORWARD  11
#define LEFT_MOTOR_REVERSE  10
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_REVERSE 8

// -------------------- Ultrasonic Sensor Pins --------------------
#define FRONT_TRIG 4
#define FRONT_ECHO 5
#define RIGHT_TRIG 2
#define RIGHT_ECHO 3
#define LEFT_TRIG  6
#define LEFT_ECHO  7

// -------------------- Movement and Distance Settings --------------------
const int BASE_SPEED = 90;             // Base forward speed
const int TURN_SPEED = BASE_SPEED + 10; // Speed during turns
const int TURN_DELAY = 350;             // Duration for ~90° turn

// Safe distance thresholds (in cm)
const int FRONT_SAFE_DISTANCE = 4;      // Stop distance
const int RIGHT_SAFE_DISTANCE = 10;      // Safety margin right
const int LEFT_SAFE_DISTANCE  = 10;      // Safety margin left

// Motor fine-tuning (adjust for balance)
const int LEFT_MOTOR_ADJUST = 20;
const int RIGHT_MOTOR_ADJUST = 20;

// ---------------------------------------------------------------------------

void setup() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_REVERSE, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_REVERSE, OUTPUT);

  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  Serial.begin(9600);

  stopMotors();
  delay(300);
}

// ---------------------------------------------------------------------------

void loop() {
  // --- Read all distances ---
  int frontDistance = getDistance(FRONT_TRIG, FRONT_ECHO);
  int rightDistance = getDistance(RIGHT_TRIG, RIGHT_ECHO);
  int leftDistance  = getDistance(LEFT_TRIG, LEFT_ECHO);

  // Debug info
  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.print(" cm | Right: ");
  Serial.print(rightDistance);
  Serial.print(" cm | Left: ");
  Serial.print(leftDistance);
  Serial.println(" cm");

  // -------------------- MAIN LOGIC --------------------
  if (frontDistance > FRONT_SAFE_DISTANCE) {
    // Move forward with side-distance correction
    adjustAndMoveForward(leftDistance, rightDistance);
  } else {
    // Obstacle detected ahead
    stopMotors();
    delay(200);

    // Reverse slightly
    reverse();
    delay(400);
    stopMotors();
    delay(200);

    // Decide turn direction based on available space
    if (rightDistance > leftDistance + 1) {
      Serial.println("Turning RIGHT (more space on right)...");
      smoothTurnRight();
    } 
    else if (leftDistance > rightDistance + 1) {
      Serial.println("Turning LEFT (more space on left)...");
      smoothTurnLeft();
    } 
    else {
      Serial.println("Both sides similar → turning RIGHT by default...");
      smoothTurnRight();
    }

    delay(TURN_DELAY);
    stopMotors();
    delay(200);
  }
}

// ---------------------------------------------------------------------------
// -------------------- Distance Measurement Function ------------------------
int getDistance(int trigPin, int echoPin) {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000UL); // Timeout after 20ms
  if (duration == 0) return 200; // No echo = assume clear path

  distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// ---------------------------------------------------------------------------
// -------------------- Forward Motion with Opposite Correction --------------
void adjustAndMoveForward(int leftDist, int rightDist) {
  int leftSpeed = BASE_SPEED + LEFT_MOTOR_ADJUST;
  int rightSpeed = BASE_SPEED + RIGHT_MOTOR_ADJUST;

  // If right wall is too close → reduce LEFT motor speed
  if (rightDist < RIGHT_SAFE_DISTANCE) {
    int reduction = (RIGHT_SAFE_DISTANCE - rightDist) * 20;
    leftSpeed -= reduction;
    if (leftSpeed < 60) leftSpeed = 50;
    Serial.print("Right too close → reduce LEFT motor to ");
    Serial.println(leftSpeed);
  }

  // If left wall is too close → reduce RIGHT motor speed
  if (leftDist < LEFT_SAFE_DISTANCE) {
    int reduction = (LEFT_SAFE_DISTANCE - leftDist) * 20;
    rightSpeed -= reduction;
    if (rightSpeed < 60) rightSpeed = 50;
    Serial.print("Left too close → reduce RIGHT motor to ");
    Serial.println(rightSpeed);
  }

  // Apply forward motion with adjusted speeds
  analogWrite(LEFT_MOTOR_FORWARD, leftSpeed);
  analogWrite(LEFT_MOTOR_REVERSE, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, rightSpeed);
  analogWrite(RIGHT_MOTOR_REVERSE, 0);
}

// ---------------------------------------------------------------------------
// -------------------- Basic Motor Functions -------------------------------
void moveForward() {
  analogWrite(LEFT_MOTOR_FORWARD, BASE_SPEED + LEFT_MOTOR_ADJUST);
  analogWrite(LEFT_MOTOR_REVERSE, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, BASE_SPEED + RIGHT_MOTOR_ADJUST);
  analogWrite(RIGHT_MOTOR_REVERSE, 0);
}

void reverse() {
  analogWrite(LEFT_MOTOR_FORWARD, 0);
  analogWrite(LEFT_MOTOR_REVERSE, BASE_SPEED + LEFT_MOTOR_ADJUST);
  analogWrite(RIGHT_MOTOR_FORWARD, 0);
  analogWrite(RIGHT_MOTOR_REVERSE, BASE_SPEED + RIGHT_MOTOR_ADJUST);
}

void smoothTurnRight() {
  analogWrite(LEFT_MOTOR_FORWARD, TURN_SPEED + LEFT_MOTOR_ADJUST);
  analogWrite(LEFT_MOTOR_REVERSE, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, 0);
  analogWrite(RIGHT_MOTOR_REVERSE, TURN_SPEED + RIGHT_MOTOR_ADJUST);
}

void smoothTurnLeft() {
  analogWrite(RIGHT_MOTOR_FORWARD, TURN_SPEED + RIGHT_MOTOR_ADJUST);
  analogWrite(RIGHT_MOTOR_REVERSE, 0);
  analogWrite(LEFT_MOTOR_FORWARD, 0);
  analogWrite(LEFT_MOTOR_REVERSE, TURN_SPEED + LEFT_MOTOR_ADJUST);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_FORWARD, 0);
  analogWrite(LEFT_MOTOR_REVERSE, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, 0);
  analogWrite(RIGHT_MOTOR_REVERSE, 0);

  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_REVERSE, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_REVERSE, LOW);
}
