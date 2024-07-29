# Garden project
 A project with sensor to measure soil moisture, ambient temperature and humidity.
# Required hardware:
* ESP32
* DHT-22
* 5 capacitive soil sensors (make sure it works correctly, common issues to lookout for: https://youtu.be/IGP38bz-K48?si=StQyUPtB-B0cJPUu&t=228 (not my video))
* 5V power supply
# Setup:
 Because the ESP32 wifi module disables the ability to read analog values from all ADC02 pins we can only connect the capasitive soil sensors on ADC01 pins (there are 6 of those on the esp32). <br>
 The pins I configured to read from the soil sensors are: 36, 39, 34, 35, 32 to find which pins those are search google for "esp32 devkit v1 pinout". <br>
 Connect the DHT-22 data line to pin 33. <br>
 Upload the arduino project to the ESP32 <br>
	(if you want to make it more secure in case you fear your neightbors might sniff the packets, add a password on line 98, for example: `WiFi.softAP("sernsor_server","password!");`) <br>
 Connect to the WIFI network it created and fill out your home's WIFI credentials and connect. <br>
	Open Index.html which is located in the src folder, enter the IP of the ESP32, and that's it!
# Comments:
 The index.html and output.css can be sent to any device and opened locally as is, or served from dedicated server.<br>
 The tags and ESP32 IP are saved in localStorage.<br>
 The decision behind having the whole frontend not on the ESP32 is to make it easier to edit the front end ( an api on ESP32 for uploading files to its local storage is an option, but I prefer additional flexability and security)<br>
 
