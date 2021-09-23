# ESP01 with Adafruit stemma capacitive soil sensor
This repo tries to show a walktrough, how to use the adafruit stemma capacitive soil sensor with ESP01

Hardware:
- Adafruit stemma soil sensor i2c capacitive moisture sensor
  data sheet: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor.pdf

- EPS01
  The ESP01 has I2C feature, see data sheet https://www.microchip.ua/wireless/esp01.pdf

GPIO2 is I2C_SDA 
IO014 is I2C_SLK


Adafruit library and sample code:
https://github.com/adafruit/Adafruit_Seesaw/blob/master/examples/soil_sensor/soilsensor_example/soilsensor_example.ino