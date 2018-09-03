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
	> **Arduino Uno** | **ESP8266**<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp; 0 (RX)  &nbsp; &nbsp; | &nbsp; &nbsp; RX<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp; 1 (TX)  &nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; TX<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp; GND &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; GND<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp; GND &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; GPIO 0<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp;  3.3 V &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; Vcc<br/>
	      &nbsp; &nbsp; &nbsp; &nbsp;  3.3 V &nbsp;&nbsp;&nbsp; &nbsp;| &nbsp; &nbsp; CH_PD<br/>
- Plug Arduino USB to your PC.
- Open "ESP FLASH DOWNLOAD TOOL V2.3" and make configuration as follows:
	- [insert image]
- Then , choose the right "COM PORT".
- Disconnect the GND of ESP8266 and then connect again.
- Press "START" button.
- The upload is finished when you see "FINISHED" on the left of the "START" button.
	
## Testing ESP8266 via Arduino Uno
- To program ESP8266 as standalone, Arduino Uno must be bypassed. This is done by connecting the "RESET" PIN of Arduino to the GND.
Now ESP8266 can be programmed through Arduino hardware. All of the connections are remaining as the same.
- Open Arduino IDE and **File --> Examples --> ESP8266WiFi --> WiFiScan**.
-  Make sure board configuration is correct as written in **Setting up Arduino IDE** section.
- Then compile and upload the code.
- The LED on ESP8266 must be blinking continuosly during the upload.
- Once the upload is done, open the serial monitor. You should see the available WiFi SSIDs on the monitor.
