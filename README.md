This project is a combination of two systems that work together to monitor and diagnose a car. The first system is a car tracking system that uses an ESP32 microcontroller and an A9G Pudding Board to get the location of the car using GPS and GSM modules. The second system is a car diagnosis system that uses an Arduino Uno microcontroller, an OBD2 connector, an MCP2515 CAN bus controller, and a car to read and display the car’s diagnostic data such as engine temperature, fuel level, RPM, etc.

The data from both systems is sent to a website that is created using the WiFi.h library and can be accessed using an IP address.

The Final_Code file code not work without using the CAN_BUS_UNO file and upload the file to Arduino UNO 
