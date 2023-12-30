# DHT-sensor-with-Blynk
This is another project about DHT sensor but this time it runs on Wokwi Simulator via PlatformIO 
# Installation
Download the following extension on Visual Studio Code: Wokwi Simulator, PlatformIO IDE
# Setup a Blynk project on Blynk Cloud website
- Create "New device"
- Select a template and give your device a name> Create
- After you create your new device, there will be Template ID, Template Name, and AuthToken on the top right, copy paste them into the code
- Now set up Virtual Pins for the code to push data on Blynk:  
On Blynk.Console, select Developer Zone > Select your project > Datastreams > New Datastream then create 3 Virtual Pins as follows:
- V0 is for temperature, Data Type = Double; Unit = Celsius, °C; Min = 0, Max = 100; Decimals = #,##; Default Value = None
- V1 is for humidity, Data Type = Double; Unit = Percentage, %; Min = 0, Max = 100; Decimals = #,##; Default Value = None
- V2 is for alert LED, Data Type = Integer, Unit = None; Min = 0, Max = 1; Default Value = 0
# How to use
On VSC, select wokwi.toml file and click "Build", if the terminal displays "Success" then you are ready to run the code  
press F1 and select "Wokwi: Start Simulator"
