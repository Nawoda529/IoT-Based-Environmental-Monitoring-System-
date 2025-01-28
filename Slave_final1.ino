#include <Wire.h>

const int SLAVE_ADDRESS = 0x08;  // Must match the master address

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);  // Initialize I2C communications as a slave
  Wire.onReceive(receiveData);  // Register event handler for receiving data
}

void loop() {
  // The main loop does nothing; data handling is done in the receiveData function
  delay(100);
}

// Function to handle received data
void receiveData(int numBytes) {
  String receivedData = "";
  
  while (Wire.available()) {
    char c = Wire.read();  // Read one character from I2C
    receivedData += c;    // Append character to the receivedData string
  }
  
  // Print received data to the Serial Monitor
  Serial.println("Data received: " + receivedData);

  // Split the received data based on comma and identify each value
  float temperatures[3];
  float humidities[3];
  float coLevels[3];
  int noiseLevels[3];

  int commaIndex = 0;
  int lastIndex = 0;

  // Extract and store temperature readings
  for (int i = 0; i < 3; i++) {
    commaIndex = receivedData.indexOf(',', lastIndex);
    temperatures[i] = receivedData.substring(lastIndex, commaIndex).toFloat();
    lastIndex = commaIndex + 1;
  }

  // Extract and store humidity readings
  for (int i = 0; i < 3; i++) {
    commaIndex = receivedData.indexOf(',', lastIndex);
    humidities[i] = receivedData.substring(lastIndex, commaIndex).toFloat();
    lastIndex = commaIndex + 1;
  }

  // Extract and store CO concentration readings
  for (int i = 0; i < 3; i++) {
    commaIndex = receivedData.indexOf(',', lastIndex);
    coLevels[i] = receivedData.substring(lastIndex, commaIndex).toFloat();
    lastIndex = commaIndex + 1;
  }

  // Extract and store noise level readings
  for (int i = 0; i < 3; i++) {
    if (i < 2) {
      commaIndex = receivedData.indexOf(',', lastIndex);
      noiseLevels[i] = receivedData.substring(lastIndex, commaIndex).toInt();
      lastIndex = commaIndex + 1;
    } else {
      noiseLevels[i] = receivedData.substring(lastIndex).toInt();
    }
  }

  // Calculate the midpoint of each sensor category
  float midTemperature = (temperatures[0] + temperatures[1] + temperatures[2]) / 3.0;
  float midHumidity = (humidities[0] + humidities[1] + humidities[2]) / 3.0;
  float midCO = (coLevels[0] + coLevels[1] + coLevels[2]) / 3.0;
  int midNoiseLevel = (noiseLevels[0] + noiseLevels[1] + noiseLevels[2]) / 3;

  // Print the midpoints
  Serial.println("Midpoint Temperature: " + String(midTemperature) + " °C");
  Serial.println("Midpoint Humidity: " + String(midHumidity) + " %");
  Serial.println("Midpoint CO Level: " + String(midCO) + " ppm");
  Serial.println("Midpoint Noise Level: " + String(midNoiseLevel));

  // Calculate and print the predictions using the midpoint values
  calculateAndPredict(midTemperature, midHumidity, midCO, midNoiseLevel);

  // Introduce a delay before the next processing
  delay(2000);  // Delay for 2 seconds, adjust this as needed
}

void calculateAndPredict(float temperature, float humidity, float co, int noiseLevel) {
  // Temperature-Humidity Index (THI) calculation
  float THI = temperature - ((0.55 - 0.0055 * humidity) * (temperature - 14.5));
  Serial.println("Temperature-Humidity Index (THI): " + String(THI));

  // Heat Index (HI) calculation
  float HI = -8.784695 + 1.61139411 * temperature + 2.338549 * humidity - 0.14611605 * temperature * temperature - 
             0.012308094 * humidity * humidity + 0.016424828 * temperature * humidity - 0.002211732 * temperature * temperature * humidity - 
             0.00072546 * temperature * humidity * humidity + 0.000003582 * temperature * temperature * humidity * humidity;
  Serial.println("Heat Index (HI): " + String(HI) + " °C");

  // Noise Level Analysis
  String noiseCategory = "";
  if (noiseLevel < 40) {
    noiseCategory = "Quiet";
  } else if (noiseLevel < 70) {
    noiseCategory = "Moderate";
  } else {
    noiseCategory = "Loud";
  }
  Serial.println("Noise Level Category: " + noiseCategory);

  // Air Quality Prediction based on CO levels
  String airQuality = "";
  if (co < 4.4) {
    airQuality = "Good";
  } else if (co < 9.4) {
    airQuality = "Moderate";
  } else if (co < 12.4) {
    airQuality = "Unhealthy for Sensitive Groups";
  } else if (co < 15.4) {
    airQuality = "Unhealthy";
  } else if (co < 30.4) {
    airQuality = "Very Unhealthy";
  } else {
    airQuality = "Hazardous";
  }
  Serial.println("Air Quality: " + airQuality);

  // Weather Prediction based on temperature and humidity
  String weatherPrediction = "";
  if (humidity > 80 && temperature < 25) {
    weatherPrediction = "Possible Rain";
  } else if (HI > 35) {
    weatherPrediction = "High Heat Risk";
  } else {
    weatherPrediction = "Normal Weather";
  }
  Serial.println("Weather Prediction: " + weatherPrediction);

  // Overall Environmental Stress Index (ESI)
  float ESI = 0.63 * temperature + 0.35 * humidity + 0.33 * THI - 0.35;
  Serial.println("Environmental Stress Index (ESI): " + String(ESI));
  String stressCategory = (ESI > 30) ? "High Stress" : "Normal";
  Serial.println("Environmental Stress Prediction: " + stressCategory);
}
