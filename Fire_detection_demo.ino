// Pin assignments (adjust as per your setup)
#define FIRE_SENSOR_LEFT A0   // Left fire sensor
#define FIRE_SENSOR_MIDDLE A1 // Middle fire sensor
#define FIRE_SENSOR_RIGHT A2  // Right fire sensor
#define TRIG_PIN 3            // Trig pin of ultrasonic sensor
#define ECHO_PIN 2            // Echo pin of ultrasonic sensor

// Motor control pins
#define MOTOR_LEFT_PIN1 6    // L298 Motor driver pin for left motor
#define MOTOR_LEFT_PIN2 7    // L298 Motor driver pin for left motor
#define MOTOR_RIGHT_PIN1 8   // L298 Motor driver pin for right motor
#define MOTOR_RIGHT_PIN2 9   // L298 Motor driver pin for right motor

// Enable pins for controlling motor speed
#define EN_A 10              // Enable pin for left motor (PWM)
#define EN_B 5               // Enable pin for right motor (PWM)

// Threshold values
const int FIRE_DETECTED_THRESHOLD = 150;  // Fire detected when sensor value is below this
const int ULTRASONIC_THRESHOLD = 20;      // Distance in cm below which an obstacle is detected
const int MOTOR_SPEED = 160;              // Motor speed (0 - 255)

void setup() {
  // Initialize motor control pins
  pinMode(MOTOR_LEFT_PIN1, OUTPUT);
  pinMode(MOTOR_LEFT_PIN2, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN1, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN2, OUTPUT);

  // Initialize enable pins for speed control
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // Initialize fire sensors
  pinMode(FIRE_SENSOR_LEFT, INPUT);
  pinMode(FIRE_SENSOR_MIDDLE, INPUT);
  pinMode(FIRE_SENSOR_RIGHT, INPUT);

  // Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200); // Debugging via serial monitor
}

void loop() {
  // Read fire sensor values
  int fireLeft = analogRead(FIRE_SENSOR_LEFT);
  int fireMiddle = analogRead(FIRE_SENSOR_MIDDLE);
  int fireRight = analogRead(FIRE_SENSOR_RIGHT);

  // Get distance from ultrasonic sensor
  float distance = getUltrasonicDistance();

  // Print sensor values for debugging
  Serial.print("Left Fire Sensor: ");
  Serial.println(fireLeft);
  Serial.print("Middle Fire Sensor: ");
  Serial.println(fireMiddle);
  Serial.print("Right Fire Sensor: ");
  Serial.println(fireRight);
  Serial.print("Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check obstacle
  if (distance <= ULTRASONIC_THRESHOLD) {
    stopCar(); // Stop the car as an obstacle is detected
    Serial.println("Obstacle detected, stopping.");
    return;
  }

  // Fire detection logic
  if (fireMiddle < FIRE_DETECTED_THRESHOLD) {
    moveForward(); // Fire detected in front, move forward
    Serial.println("Fire detected in front, moving forward.");
  } 
  else if (fireLeft < FIRE_DETECTED_THRESHOLD) {
    turnLeft(); // Fire detected on the left, turn left
    Serial.println("Fire detected on the left, turning left.");
  } 
  else if (fireRight < FIRE_DETECTED_THRESHOLD) {
    turnRight(); // Fire detected on the right, turn right
    Serial.println("Fire detected on the right, turning right.");
  } 
  else {
    stopCar(); // No fire detected, stop the car
    Serial.println("No fire detected, car stopped.");
  }

  delay(2000); // Small delay for sensor stability
}

// Function to get distance from ultrasonic sensor
float getUltrasonicDistance() {
  long duration;  
  float distance;

  // Send a 10us pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm (speed of sound is 343 m/s)
  distance = duration * 0.034 / 2;

  return distance;
}

// Function to move the car forward
void moveForward() {
  analogWrite(EN_A, MOTOR_SPEED);  // Set speed for left motor
  analogWrite(EN_B, MOTOR_SPEED);  // Set speed for right motor

  digitalWrite(MOTOR_LEFT_PIN1, HIGH);  // Forward left motor
  digitalWrite(MOTOR_LEFT_PIN2, LOW);
  digitalWrite(MOTOR_RIGHT_PIN1, LOW);  // Forward right motor
  digitalWrite(MOTOR_RIGHT_PIN2, HIGH);
}

// Function to turn the car left
void turnLeft() {
  analogWrite(EN_A, MOTOR_SPEED);  // Set speed for left motor
  analogWrite(EN_B, MOTOR_SPEED);  // Set speed for right motor

  digitalWrite(MOTOR_LEFT_PIN1, LOW);   // Turn left motor off
  digitalWrite(MOTOR_LEFT_PIN2, HIGH);  // Reverse left motor
  digitalWrite(MOTOR_RIGHT_PIN1, LOW);  // Forward right motor
  digitalWrite(MOTOR_RIGHT_PIN2, HIGH);
}

// Function to turn the car right
void turnRight() {
  analogWrite(EN_A, MOTOR_SPEED);  // Set speed for left motor
  analogWrite(EN_B, MOTOR_SPEED);  // Set speed for right motor

  digitalWrite(MOTOR_LEFT_PIN1, HIGH);  // Forward left motor
  digitalWrite(MOTOR_LEFT_PIN2, LOW);
  digitalWrite(MOTOR_RIGHT_PIN1, HIGH); // Turn right motor off
  digitalWrite(MOTOR_RIGHT_PIN2, LOW);  // Reverse right motor
}

// Function to stop the car
void stopCar() {
  analogWrite(EN_A, 0);  // Stop left motor by setting speed to 0
  analogWrite(EN_B, 0);  // Stop right motor by setting speed to 0

  digitalWrite(MOTOR_LEFT_PIN1, LOW);  // Stop left motor
  digitalWrite(MOTOR_LEFT_PIN2, LOW);
  digitalWrite(MOTOR_RIGHT_PIN1, LOW); // Stop right motor
  digitalWrite(MOTOR_RIGHT_PIN2, LOW);
}
