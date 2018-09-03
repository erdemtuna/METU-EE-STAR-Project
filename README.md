# starProject
Steps to develop this project is summarized in the following sections.

## Required Hardwares
- ESP8266 (01), wireless module
- DHT11, temperature and humidity sensor
- USB Flasher (I used Arduino)
- Jumper cables (f-f, m-f, m-m)

## Setting up Arduino IDE

 1. Arduino IDE can be downloaded from [here, officially](https://www.arduino.cc/en/Main/Software).
 2.  To support ESP8266, in Arduino IDE, find **File --> Preferences --> Additional Boards Manager URLs**. 
 3.  Paste "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to given space.
 4.  Then, find **Tools --> Board --> Board Manager** and install ESP8266 boards.
 5. After installing ESP boards, choose the board as **Tools --> Board --> Generic ESP8266 Module**.
 6. Set board settings as follows:
	 [insert image]


## ESP8266 Firmware update

ESP8266 firmware and built-in features can be updated with some tools provided by the manufacterer. They can be found in [here](https://yadi.sk/d/MDdDTMgE3aoV4A). I used Arduino Uno to upload those updates to ESP8266. 
- PIN connections between Arduino and ESP8266 are as follows
	> **Arduino Uno** | **ESP8266**
	      &nbsp; &nbsp; &nbsp; &nbsp; 0 (RX)  &nbsp; &nbsp; | &nbsp; &nbsp; RX
	      &nbsp; &nbsp; &nbsp; &nbsp; 1 (TX)  &nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; TX
	      &nbsp; &nbsp; &nbsp; &nbsp; GND &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; GND
	      &nbsp; &nbsp; &nbsp; &nbsp; GND &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; GPIO 0
