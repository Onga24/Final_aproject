#include <HardwareSerial.h>
#include <math.h>
#include <WiFi.h>
// creates a server object and the port number is 80
WiFiServer server(80);
//Creating a Hardware serial
HardwareSerial A9G(2);
// Define the the baud rate
#define baudRate 115200
//varibles will be discussed in details 
int x=1,y=0,g=0;
String datad,googleMapsUrl;
const char* ssid     = "Onga 21";
const char* password = "01020304";
// Variable to store the previous time
unsigned long previousTime = 0;
String line1,line2,line3,line4,line5,line6,line7;
// Constant for the interval
const unsigned long interval = 10000; // 10 seconds
unsigned long currentTime;
void setup() {
  //sets up a serial communication
 Serial2.begin(115200,SERIAL_8N1, 16, 17);
  // Initialize the hardware serial and the software serial
  Serial.begin(baudRate);
   delay(10);
  Serial.println("Starting");
  A9G.begin(baudRate);
   delay(10);
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);//conect to wifi using the ssid and password
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("WiFi Not Connected");
        //loop start until the wifi is connected 
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    // print the locol ip address
    
    server.begin();
  // Set the AT Cmd
  A9G.println("AT");
  delay(2000);
  // Set the GPS 
  A9G.println("AT+GPS=1");
  delay(2000);

}

void loop() {
  // Get the current time
   currentTime = millis();
   if (currentTime - previousTime >= interval)
   {
    // Update the previous time
    previousTime = currentTime;
   }


      // used to statrt the while loop
      y=1;
    
Serial.println(currentTime);
    // Send the location to the WPS
   
    if(g) 
{ 
 // starting the loop 
    while(y==1)
    {
      // getting the output using the following cmd in NEMA
       datad=A9G.println("AT+GPSRD=1");            // enable the GPSRD cmd for 1 sec
       
       //Serial.println(datad); // if we need to print the NEMA MSG
       //delay 1.2 sec 
       delay(1200);
        
       datad=A9G.println("AT+GPSRD=0");// disable the GPSRD cmd
       y=0;        // ending the loop 

    }
  // we need to store location that begin in first line
    String data = A9G.readStringUntil('\n'); // read a line of data 
  
  if (data.startsWith("+GPSRD:$GNGGA"))  //check if we get +GPSRD:$GNGGA
  {     
      Serial.println(data); // print the sentence
      
      float lat, lon; // variables to store latitude and longitude
      
      char lat_dir, lon_dir; // variables to store latitude and longitude direction
      
      // code to remove the "+GPSRD:$GNGGA" to get the disrable line
      String result = data.substring(14); // start from index 14 and go to the end of the string
    
     // take the dirsered values 
      sscanf(result.c_str(), "%*f,%f,%c,%f,%c,%*d,%*d,%*f,%*f,%*c,%*f,%*c,%*f,%*c,*%*s", &lat, &lat_dir, &lon, &lon_dir);

      //uisng the function convert_to_decimal to convert from degrees and minutes to decimal
      lat = convert_to_decimal(lat, lat_dir); 
      lon = convert_to_decimal(lon, lon_dir);
      
      Serial.print("Latitude: ");
      Serial.println(lat, 6); // print latitude with 6 decimal places
      Serial.print("Longitude: ");
      Serial.println(lon, 6); // print longitude with 6 decimal places


      // googleMapsUrl is a variable to store the location into a HTTPS link
      googleMapsUrl = "https://www.google.com/maps/search/?api=1&query=";
      googleMapsUrl += String(lat, 6); // add the Latitude ro the link
      googleMapsUrl += ",";
      googleMapsUrl += String(lon, 6);// add the Longitude ro the link
      Serial.println(googleMapsUrl);// printing the link 

      //check if the serial2 is avalible 
      if(Serial2.available())
      {
        //read the 7 line of data comming from serial commuincattion 
   line1 = Serial2.readStringUntil('\n'); // read a line of data
   line2 = Serial2.readStringUntil('\n'); // read a line of data
   line3 = Serial2.readStringUntil('\n'); // read a line of data
   line4 = Serial2.readStringUntil('\n'); // read a line of data
   line5 = Serial2.readStringUntil('\n'); // read a line of data
   line6 = Serial2.readStringUntil('\n'); // read a line of data
   line7 = Serial2.readStringUntil('\n'); // read a line of data
   

    }
  }
}
  
  
  WiFiClient client = server.available();   // listen for incoming clients

if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // rea1d a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response is following
          client.println("To get the location of the vechile <a href='" + String(googleMapsUrl) + "'>Click here</a>");
          client.println();
          
     //check if the serial2 is available
  if(Serial2.available())
  {
    //print the saved lines
    client.println(line1);
     client.println();
   client.println(line2);
    client.println();
   client.println(line3);
    client.println();
   client.println(line4);
    client.println();
   client.println(line5);
    client.println();
   client.println(line6);
    client.println();
   client.println(line7);
    client.println();
  }
  //check if the serial2 is not available
else if (!Serial2.available())
{
  //print the default lines
         client.println("Engine coolant temperature=0°C");
         client.println();
         client.println("Vehicle speed=0.00km/h");
         client.println();
         client.println("Run time since engine start=0.00seconds");
         client.println();
         client.println("Engine RPM=0.0rpm");
         client.println();
         client.println("Distance traveled with malfunction indicator lamp (MIL) on=0.00km");
         client.println();
         client.println("Fuel system status=0.00");
         client.println();
         client.println("Calculated engine load=0.0% ");
         client.println();
}


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }  
  
  
  
// If there is data from the A9G module, print it to the hardware serial
  // to check if A9G is available
if(A9G.available()&& x==1) // used only to get the location for the first time
{ 
 
    while(x==1)
    {
       datad=A9G.println("AT+GPSRD=1");
       //Serial.println(datad);
      
       delay(1200);
       datad=A9G.println("AT+GPSRD=0");
       
       x=0;
    }
  
    String data = A9G.readStringUntil('\n'); // read a line of data
  if (data.startsWith("+GPSRD:$GNGGA"))
  {
   
      
      Serial.println(data); // print the sentence
      float lat, lon; // variables to store latitude and longitude
      char lat_dir, lon_dir; // variables to store latitude and longitude direction
      // code to remove the "+GPSRD:$GNGGA,"
      //String sentence = "+GPSRD:$GNGGA,012056.264,2959.6134,N,03231.1522,E,0,0,-68.1,M,16.2,M,*47";
      String result = data.substring(14); // start from index 13 and go to the end of the string
     // check if it is a GPGGA sentence
      sscanf(result.c_str(), "%*f,%f,%c,%f,%c,%*d,%*d,%*f,%*f,%*c,%*f,%*c,%*f,%*c,*%*s", &lat, &lat_dir, &lon, &lon_dir);
      lat = convert_to_decimal(lat, lat_dir); 
      lon = convert_to_decimal(lon, lon_dir);
      
      Serial.print("Latitude: ");
      Serial.println(lat, 6); // print latitude with 6 decimal places
      Serial.print("Longitude: ");
      Serial.println(lon, 6); // print longitude with 6 decimal places

      googleMapsUrl = "https://www.google.com/maps/search/?api=1&query=";
      googleMapsUrl += String(lat, 6);
      googleMapsUrl += ",";
      googleMapsUrl += String(lon, 6);
      Serial.println(googleMapsUrl);
  g=1;
    }
  }


 
}


float convert_to_decimal(const float value, const char dir) 
{
  int degrees = (int) value / 100; // get the degrees part
  float minutes = fmod(value, 100); // get the minutes part
  float result = degrees + minutes / 60; // convert to decimal degrees
  switch (dir) { // check the direction indicator
    case 'S':
    case 'W':
      result = -result; // multiply by -1 if south or west
      break;
    case 'N':
    case 'E':
      break; // do nothing if north or east
    default:
      return NAN; // return not-a-number if invalid input
  }
  return result;
}
