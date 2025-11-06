// Pin definitions
#define gasSensorPin A4  // MQ-2 gas sensor analog pin
#define buzzerPin 9      // Active Buzzer pin

// Threshold for gas detection (adjust according to your needs)
const int gasThreshold = 300; // Adjust this value based on your gas sensitivity and calibration

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Initially turn off the buzzer
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  int gasValue = analogRead(gasSensorPin);

  // Print the gas value to the Serial Monitor
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // Check if gas value exceeds the threshold
  if (gasValue > gasThreshold) {
    // Activate the buzzer
    digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
    Serial.println("Gas detected! Buzzer ON.");
  } else {
    // Deactivate the buzzer
    digitalWrite(buzzerPin, LOW);   // Turn off buzzer
    Serial.println("No gas detected. Buzzer OFF.");
  }

  // Small delay for stability
  delay(1000); // Adjust delay as needed
}
