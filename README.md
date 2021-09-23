# ESP01 with Adafruit stemma capacitive soil sensor
This repo tries to show a walktrough, how to use the adafruit stemma capacitive soil sensor with ESP01

Hardware:
- Adafruit stemma soil sensor i2c capacitive moisture sensor
  
  data sheet: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor.pdf

- ESP01
  
  The ESP01 has I2C feature, see data sheet https://www.microchip.ua/wireless/esp01.pdf
  
  ![esp01_board](https://github.com/frankyhun/esp01_with_adafruit_stemma_soil_sensor/blob/main/esp01_board.png "Logo Title Text 1")



Adafruit library and sample code:
https://github.com/adafruit/Adafruit_Seesaw/blob/master/examples/soil_sensor/soilsensor_example/soilsensor_example.ino

!!! the only line to get the example work with ESP-01 is, to add the following line to the beginning of the start() method:
```
Wire.begin(0, 2);
