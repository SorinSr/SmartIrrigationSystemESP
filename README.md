# SmartIrrigationSystemESP

I. Short Description
The purpose of this project is to create a smart irrigations system developed for home use, but scalable to industrial applications also. The whole idea started when I planted some hot peppers, but after some weeks I forgot to water them, so they died. The best way to deal with this problem was to develop to develop an automation for this process. The proposed system is continuously monitoring soil moisture, air humidity and temperature, and based on those inputs system decides whether to water the plants or to wait. These three measures are displayed on a small screen and also they are transmitted to a Blynk Cloud and from there they are displayed on the web dashboard and also in the mobile app. The water level from the tank is visible as well Blynk app, and also an on-tap watering function is available, to water the plants whenever needed.

II. Hardware Description
For this project I used multiple components, in order to monitor, control, display and trigger actions.

ESP-WROOM-32S: low-cost microcontroller very suitable for applications like this because it incorporates WI-FI, Bluetooth, GIPIO Pins with digital and analog I/Os, I2C and many more. Another thing that was very helpful, was the integration with Arduino IDE.

OLED Display SSD1306: a small 0.96 inch display with 128×64 pixels resolution that was used to display temperature, humidity and soil moisture. This device is using I2C communication protocol, so in order to communicate with it, was required to use the suitable pins for this: GPIO21 – SDA and GPIO22 SCL.

DHT11: this sensor is used to measure the temperature and humidity. It has a high precision and large measurement range: 0 to 50 Celsius degrees, for temperature, and 20 to 90% humidity.

Moisture sensor: this sensor has to parts, one that comes in contact with water, and the other one, that process and send data. One interesting thig about this sensor is the fact that it can have an analog output and also a digital one. It has adjustable sensitivity and an indicator LED to show when the maximum value is obtained.

Water level sensor: another sensor which stays in water. This sensor has an analog output and a LED to indicate it is functioning. SRD-50VDC-SL-C relay module: this relay was used to control the water pump. Low current signal triggers the relay in order to open or close the circuit. This type of relays support up to 250V and 10A.

Water pump: this pump is very useful because it can function under water without problems and it has an imput voltage between 3 and 6V.

Other components used: battery holder, to power the pump, jump wires and breadboard to make all the connections.



![system](https://user-images.githubusercontent.com/47916325/151583411-e2bace4a-4534-4933-b224-63ed6a988c26.jpeg)

The data read from the sensors is displayed in Blink dashboards and cand be accessed trough web interface or mobile app.


![blynk_web](https://user-images.githubusercontent.com/47916325/151585140-60012a9f-d8bc-4bc1-b0a1-222fc099be1e.JPG)
![blynk_mobile](https://user-images.githubusercontent.com/47916325/151585224-eb4526a2-ce83-4be2-b261-1ac6cbc7a077.jpg)
