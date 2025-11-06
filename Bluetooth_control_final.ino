// Pin definitions for motor control
#define in1 6     // Motor A Forward
#define in2 7     // Motor A Backward
#define in3 8     // Motor B Forward
#define in4 9     // Motor B Backward

void setup() {
  // Initialize motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize Bluetooth communication using Serial1 (TX1/RX1) for Arduino Mega
  Serial.begin(9600);     // For debugging via Serial Monitor
  Serial1.begin(9600);    // For communication with HC-05 module
}

void loop() {
  // Check if any data is received from the Bluetooth module
  if (Serial1.available()) {
    char command = Serial1.read();   // Read the Bluetooth command

    // Debug: Print the command to the serial monitor
    Serial.print("Command received: ");
    Serial.println(command);
    
    // Call function to control the car based on the command
    controlCar(command);
  }
}

// Function to control the car's movement based on Bluetooth commands
void controlCar(char command) {
  switch (command) {
    case 'F':   // Move Forward
      forward();
      break;

    case 'B':   // Move Backward
      backward();
      break;

    case 'L':   // Move Left
      turnLeft();
      break;

    case 'R':   // Move Right
      turnRight();
      break;

    case 'S':   // Stop
      Stop();
      break;

    default:
      Stop();  // Stop the car if an unknown command is received
      break;
  }
}

// Function to move the car forward
void forward() {
digitalWrite(in1, HIGH);   // Motor A forward
  digitalWrite(in2, LOW);    // Motor A not backward
  digitalWrite(in3, LOW);    // Motor B not forward
  digitalWrite(in4, HIGH);   // Motor B backward
}

// Function to move the car backward
void backward() {
  digitalWrite(in1, LOW);    // Motor A not forward
  digitalWrite(in2, HIGH);   // Motor A backward
  digitalWrite(in3, HIGH);   // Motor B forward
  digitalWrite(in4, LOW);    // Motor B not backward
}

// Function to turn the car left
void turnLeft() {
  digitalWrite(in1, LOW);   // Motor A forward
  digitalWrite(in2, HIGH);    // Motor A not backward
  digitalWrite(in3, LOW);    // Motor B not forward
  digitalWrite(in4, HIGH);   // Motor B backward
}

// Function to turn the car right
void turnRight() {
  digitalWrite(in1, HIGH);    // Motor A not forward
  digitalWrite(in2, LOW);   // Motor A backward
  digitalWrite(in3, HIGH);   // Motor B forward
  digitalWrite(in4, LOW);    // Motor B not backward
}

// Function to stop the car
void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
