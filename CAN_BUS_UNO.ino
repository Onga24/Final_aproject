#include <CAN.h>
#include <OBD2.h>
#include <SPI.h>

//using PIDS from OBD2 library
const bool use_StandardAddressing = true; 
// making an array contain the defined IDS in the library
const int PIDS[]={
ENGINE_COOLANT_TEMPERATURE,
VEHICLE_SPEED,RUN_TIME_SINCE_ENGINE_START,ENGINE_RPM,DISTANCE_TRAVELED_WITH_MIL_ON,FUEL_SYSTEM_STATUS,CALCULATED_ENGINE_LOAD} ;
//getting the size of one elment of the array
const int NUM_PIDS = sizeof(PIDS) / sizeof(PIDS[0]);
//SPI pins
//SCK, MISO, MOSI, SS
//[18, 19, 23, 5] 
void setup()
{
   Serial.println("Serial begin at Baud Rate 115200 ");
  Serial.begin(115200);
 

// the serial must be true to leave the while loop
while(!Serial);
Serial.println(F("OBD2 Real-Time Data")); 
// the obd2 is true inside the if will be printed other inside the else will be printed 
 if (OBD2.begin()) { // initialize OBD-II communication
    Serial.println("OBD-II initialized");
  } else {
    Serial.println("OBD-II initialization failed");
  }
while(1)
{// trying to connect to obd2 
  Serial.print(F("Attempting to connect to OBD2 CAN bus...")); 
if (!OBD2.begin()){
Serial.println(F("failed!")); 
delay(1000);
}
else{
  Serial.println(F("success"));
}

break;
}
Serial.println();

}
void loop()
{ // print each and every elment of the array uisng PrintPID
  for(int i =0 ; i!=NUM_PIDS;i++)
  {
    int pid= PIDS[i];
      PrintPID(pid);
       delay (200);
  }

  Serial.println();
  delay(1000);
}

void PrintPID(int pid)
{
  Serial.print (OBD2.pidName(pid)); 
Serial.print(F("="));


float pid_Value = OBD2.pidRead(pid);
// if there is no value to pid , Error will be printed
if (isnan (pid_Value))
Serial.print("Error");
 else   // else the pid name and value will be printed 
 {
Serial.print(pid_Value); 
Serial.print(F(""));
Serial.print(OBD2.pidUnits(pid));
Serial.println();
 }
}

