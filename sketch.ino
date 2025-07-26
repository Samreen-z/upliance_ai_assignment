#include <DHT.h>

#define DHTPIN 21          // DHT22 data pin connected to GPIO 4
#define DHTTYPE DHT22

#define RELAY_PIN 26       // Relay module connected to GPIO 5
#define LED_PIN 2         // Onboard LED for visual feedback

// Temperature thresholds
#define IDLE_TEMP 25.0
#define HEATING_TEMP 30.0
#define STABILIZING_TEMP 35.0
#define TARGET_TEMP 38.0
#define OVERHEAT_TEMP 40.0

DHT dht(DHTPIN, DHTTYPE);

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = IDLE;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // Heater OFF initially
  digitalWrite(LED_PIN, LOW);   // LED OFF initially
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    delay(2000);
    return;
  }

  // State classification
  if (temperature < IDLE_TEMP) {
    currentState = IDLE;
    digitalWrite(RELAY_PIN, LOW);
  } else if (temperature >= IDLE_TEMP && temperature < HEATING_TEMP) {
    currentState = HEATING;
    digitalWrite(RELAY_PIN, HIGH);
  } else if (temperature >= HEATING_TEMP && temperature < STABILIZING_TEMP) {
    currentState = STABILIZING;
    digitalWrite(RELAY_PIN, HIGH);
  } else if (temperature >= STABILIZING_TEMP && temperature <= TARGET_TEMP) {
    currentState = TARGET_REACHED;
    digitalWrite(RELAY_PIN, LOW);
  } else if (temperature > OVERHEAT_TEMP) {
    currentState = OVERHEAT;
    digitalWrite(RELAY_PIN, LOW);
  }

  // LED feedback
  if (currentState == OVERHEAT) {
    digitalWrite(LED_PIN, HIGH); // Alert
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // Serial logging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tState: ");
  printState(currentState);

  delay(2000);
}

void printState(HeaterState state) {
  switch (state) {
    case IDLE:
      Serial.println("Idle");
      break;
    case HEATING:
      Serial.println("Heating");
      break;
    case STABILIZING:
      Serial.println("Stabilizing");
      break;
    case TARGET_REACHED:
      Serial.println("Target Reached");
      break;
    case OVERHEAT:
      Serial.println("Overheat!");
      break;
  }
}
