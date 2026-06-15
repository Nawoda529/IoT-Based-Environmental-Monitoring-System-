# 🌍 IoT-Based Environmental Monitoring System

## Overview

The IoT-Based Environmental Monitoring System is a smart environmental sensing platform designed to monitor and analyze real-time environmental conditions using Internet of Things (IoT) technology and Machine Learning.

The system collects data from multiple environmental sensors, including temperature, humidity, air quality, and noise sensors, using ESP32 microcontrollers. The collected data is transmitted to the cloud through Firebase and analyzed using machine learning techniques to identify environmental patterns and predict environmental stress conditions.

A web-based dashboard provides users with real-time visualizations, environmental status updates, and predictive insights, enabling informed decision-making and increased awareness of environmental conditions.

---
## Final Project video


 https://drive.google.com/file/d/190HGrOw9sMJvpUwhaxPc7z1za-ShOz8t/view?usp=sharing

 
## Problem Statement

Environmental conditions such as air pollution, temperature fluctuations, humidity changes, and excessive noise can significantly affect human health and quality of life. Traditional environmental monitoring methods often require manual measurements and lack real-time accessibility.

This project addresses these challenges by providing an automated IoT-based monitoring solution capable of collecting environmental data continuously and delivering actionable insights through cloud-based analytics and visualization.

---

## Objectives

* Monitor environmental parameters in real time.
* Collect and store sensor data in the cloud.
* Analyze environmental conditions using machine learning algorithms.
* Predict environmental stress levels and trends.
* Provide an intuitive dashboard for data visualization.
* Improve environmental awareness through data-driven insights.

---

# System Architecture

```text
Environmental Sensors
        │
        ▼
   ESP32 Slave Node
        │
        ▼
   ESP32 Master Node
        │
        ▼
      Firebase
        │
        ▼
 Data Processing Layer
        │
        ▼
 Machine Learning Models
        │
        ▼
  Web Dashboard
        │
        ▼
       Users
```

---

## Features

### Real-Time Environmental Monitoring

The system continuously measures environmental parameters including:

* Temperature
* Humidity
* Air Quality
* Noise Levels

### Cloud-Based Data Storage

All sensor readings are transmitted to Firebase, allowing secure and centralized storage of environmental data.

### Machine Learning Analytics

The platform applies machine learning algorithms to:

* Analyze environmental conditions
* Detect abnormal patterns
* Predict environmental stress levels
* Generate environmental insights

### Interactive Dashboard

Users can access:

* Live sensor readings
* Historical environmental data
* Prediction results
* Visual charts and graphs
* Environmental condition summaries

---

## Hardware Components

### ESP32 Development Boards

The project uses a Master-Slave ESP32 architecture:

#### ESP32 Master

* Receives sensor data
* Processes incoming readings
* Sends data to Firebase

#### ESP32 Slave

* Reads sensor values
* Transfers environmental data to the master node

---

### Sensors Used

#### DHT22 Sensor

Measures:

* Temperature
* Relative Humidity

#### MQ-135 Gas Sensor

Measures:

* Air Quality
* Harmful Gas Concentration

#### Noise Sensor

Measures:

* Ambient Sound Levels
* Environmental Noise Pollution

---

## Software Technologies

### Embedded Systems

* Arduino IDE
* ESP32 Firmware
* C++

### Cloud Services

* Firebase Realtime Database

### Machine Learning

* Python
* Jupyter Notebook
* Pandas
* NumPy
* Scikit-Learn

### Web Technologies

* HTML
* CSS
* JavaScript

### Development Tools

* PyCharm
* GitHub

---

## Machine Learning Module

The machine learning component analyzes historical environmental sensor data to identify trends and generate predictions.

### Input Features

* Temperature
* Humidity
* Air Quality Index
* Noise Levels

### Processing

* Data Cleaning
* Feature Extraction
* Data Normalization
* Model Training

### Outputs

* Environmental Condition Classification
* Environmental Stress Prediction
* Trend Analysis

---

## Data Flow

1. Sensors collect environmental readings.
2. ESP32 Slave gathers sensor data.
3. Data is transmitted to ESP32 Master.
4. ESP32 Master uploads readings to Firebase.
5. Machine learning models process the collected data.
6. Results are displayed through the web dashboard.
7. Users access real-time monitoring and prediction insights.



## Applications

* Smart Cities
* Environmental Research
* Air Quality Monitoring
* Industrial Monitoring
* Educational Projects
* Environmental Awareness Programs

---

## Future Improvements

* Mobile Application Integration
* SMS and Email Alerts
* Advanced AI Predictions
* Weather Data Integration
* Multi-Location Monitoring
* Real-Time Notifications
* Predictive Environmental Risk Assessment

---

## Results

The developed system successfully:

* Monitored environmental conditions in real time.
* Collected sensor readings through IoT devices.
* Stored data securely in Firebase.
* Applied machine learning techniques for environmental analysis.
* Visualized environmental data through a web interface.
* Generated predictive insights for environmental monitoring.

---

## Contributors

### N. M. Hewage

Project Development and Implementation

GitHub: https://github.com/Nawoda529

---

## License

This project was developed for academic and research purposes.

---

⭐ If you found this project useful, consider giving the repository a star.
