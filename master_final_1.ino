#include <Wire.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>  // Library for MQ series gas sensors

// Define I2C address for the slave device
const int SLAVE_ADDRESS = 0x08;

// Define DHT Sensors
#define DHTTYPE DHT22
#define DHTPIN1 4  // DHT22 data pin connected to GPIO4
#define DHTPIN2 5  // DHT22 data pin connected to GPIO5
#define DHTPIN3 18  // DHT22 data pin connected to GPIO18
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);

// Define MQ-7 Sensors for CO
#define MQ_PIN1 35
#define MQ_PIN2 32
#define MQ_PIN3 33
#define MQ_TYPE "MQ-7"
#define VOLTAGE 3.3
#define ADC_BITS 12
MQUnifiedsensor mq1(MQ_TYPE, VOLTAGE, ADC_BITS, MQ_PIN1);
MQUnifiedsensor mq2(MQ_TYPE, VOLTAGE, ADC_BITS, MQ_PIN2);
MQUnifiedsensor mq3(MQ_TYPE, VOLTAGE, ADC_BITS, MQ_PIN3);

// Define Noise Sensors
#define NOISE_SENSOR_PIN1 34  // Example pin for noise sensor (adjust if needed)
#define NOISE_SENSOR_PIN2 25
#define NOISE_SENSOR_PIN3 26

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  Wire.begin();

  // Initialize MQ sensors
  mq1.init();
  mq2.init();
  mq3.init();
}

void loop() {
  // Reading DHT sensors
  float temperature1 = dht1.readTemperature();
  float humidity1 = dht1.readHumidity();
  float temperature2 = dht2.readTemperature();
  float humidity2 = dht2.readHumidity();
  float temperature3 = dht3.readTemperature();
  float humidity3 = dht3.readHumidity();

  // If temperature3 or humidity3 is NaN, replace them with temperature2 or humidity2
  if (isnan(temperature3)) {
    temperature3 = temperature2;
  }
  if (isnan(humidity3)) {
    humidity3 = humidity2;
  }

  // Reading MQ-7 sensors for CO
  mq1.update();
  float co1 = mq1.readSensor();
  mq2.update();
  float co2 = mq2.readSensor();
  mq3.update();
  float co3 = mq3.readSensor();

  // Reading noise levels from the noise sensors
  int noiseLevel1 = analogRead(NOISE_SENSOR_PIN1);
  int noiseLevel2 = analogRead(NOISE_SENSOR_PIN2);
  int noiseLevel3 = analogRead(NOISE_SENSOR_PIN3);

  // Check for valid readings
  if (isnan(temperature1) || isnan(humidity1) || isnan(co1) ||
      isnan(temperature2) || isnan(humidity2) || isnan(co2) ||
      isnan(co3)) {
    Serial.println("Failed to read from one or more sensors!");
    return;
  }

  // Display all sensor readings on the serial monitor
  Serial.print("T1: "); Serial.print(temperature1); Serial.print(" °C, ");
  Serial.print("H1: "); Serial.print(humidity1); Serial.print(" %, ");
  Serial.print("CO1: "); Serial.print(co1); Serial.print(" ppm, ");
  Serial.print("Noise1: "); Serial.print(noiseLevel1); Serial.println();

  Serial.print("T2: "); Serial.print(temperature2); Serial.print(" °C, ");
  Serial.print("H2: "); Serial.print(humidity2); Serial.print(" %, ");
  Serial.print("CO2: "); Serial.print(co2); Serial.print(" ppm, ");
  Serial.print("Noise2: "); Serial.print(noiseLevel2); Serial.println();

  Serial.print("T3: "); Serial.print(temperature3); Serial.print(" °C, ");
  Serial.print("H3: "); Serial.print(humidity3); Serial.print(" %, ");
  Serial.print("CO3: "); Serial.print(co3); Serial.print(" ppm, ");
  Serial.print("Noise3: "); Serial.print(noiseLevel3); Serial.println();

  // Convert the data to a string
  String dataString = String(temperature1) + "," + String(humidity1) + "," + String(co1) + "," + String(noiseLevel1) + "," +
                      String(temperature2) + "," + String(humidity2) + "," + String(co2) + "," + String(noiseLevel2) + "," +
                      String(temperature3) + "," + String(humidity3) + "," + String(co3) + "," + String(noiseLevel3);

  // Send data to the slave device
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write((const uint8_t*)dataString.c_str(), dataString.length());
  Wire.endTransmission();

  // Delay before the next reading
  delay(2000);
}
