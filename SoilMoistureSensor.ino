int moisture = 0;
int pumpPin = 7; // Pump 
int dryThreshold = 600;   // Initial guess for dry soil
int wetThreshold = 400;   // Initial guess for wet soil

// Self-learning memory variables
long totalMoisture = 0;
int sampleCount = 0;

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(pumpPin, OUTPUT); // Pump control pin
  digitalWrite(pumpPin, LOW); 
}

void loop()
{
  digitalWrite(A0, HIGH);
  delay(10); 
  moisture = analogRead(A1);
  digitalWrite(A0, LOW); // Turn off the sensor to reduce corrosion

  Serial.print("Moisture: ");
  Serial.println(moisture);

  // LEDS
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  if (moisture < 200) {
    digitalWrite(12, HIGH);
  } else {
    if (moisture < 400) {
      digitalWrite(11, HIGH);
    } else {
      if (moisture < 600) {
        digitalWrite(10, HIGH);
      } else {
        if (moisture < 800) {
          digitalWrite(9, HIGH);
        } else {
          digitalWrite(8, HIGH);
        }
      }
    }
  }

  //Pump Control (self-learning)
  // Update learning averages
  totalMoisture += moisture;
  sampleCount++;

  if (sampleCount >= 100) { // After 100 samples (~10 sec if delay=100ms)
    int avgMoisture = totalMoisture / sampleCount;

    // Adjust thresholds dynamically
    if (avgMoisture < wetThreshold) {
      wetThreshold = avgMoisture; // soil is wetter than expected
    }
    if (avgMoisture > dryThreshold) {
      dryThreshold = avgMoisture; // soil is drier than expected
    }

    Serial.print("Updated Wet Threshold: ");
    Serial.println(wetThreshold);
    Serial.print("Updated Dry Threshold: ");
    Serial.println(dryThreshold);

    totalMoisture = 0;
    sampleCount = 0;
  }

  // Pump logic
  if (moisture > dryThreshold) {
    digitalWrite(pumpPin, LOW); // Turn pump ON IF soil too dry
    Serial.println("Pump ON");
  } 
  else if (moisture < wetThreshold) {
    digitalWrite(pumpPin, HIGH); // Turn pump OFF if soil wet enough
    Serial.println("Pump OFF");
  }

  delay(100); 
}
