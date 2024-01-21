
#include <CAN.h>
#include <OBD2.h>
#include <SPI.h>



const bool use_StandardAddressing = true; 
const int PIDS[]={
ENGINE_COOLANT_TEMPERATURE,
VEHICLE_SPEED,RUN_TIME_SINCE_ENGINE_START,ENGINE_RPM,DISTANCE_TRAVELED_WITH_MIL_ON,FUEL_SYSTEM_STATUS,CALCULATED_ENGINE_LOAD} ;

const int NUM_PIDS = sizeof(PIDS) / sizeof(PIDS[0]);

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial 115200 is begin");
//SPI.begin(18, 19, 23, 5); // SCK, MISO, MOSI, SS
//Serial.println("Spi begin");
while(!Serial);
Serial.println(F("OBD2 Real-Time Data")); 

 if (OBD2.begin()) { // initialize OBD-II communication
    Serial.println("OBD-II initialized");
  } else {
    Serial.println("OBD-II initialization failed");
  }
while(1)
{
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
{
  for(int i =0 ; i!=NUM_PIDS;i++)
  {
    int pid= PIDS[i];
      printPID(pid);
       delay (200);
  }

  Serial.println();
  delay(1000);
}

void printPID(int pid)
{
  Serial.print (OBD2.pidName(pid)); 
Serial.print(F("="));


float pid_Value = OBD2.pidRead(pid);

if (isnan (pid_Value))
Serial.print("error");
 else
 {
Serial.print(pid_Value); 
Serial.print(F(""));
Serial.print(OBD2.pidUnits(pid));
Serial.println();
 }
}
//VSPI  GPIO 23 GPIO 19 GPIO 18 GPIO 5
//MOSI Pin: 23
//MISO Pin: 19
//SCK Pin: 18
//SS Pin: 5


//int const spiCSPin =5 ;
//#define CAN_500KBPS_8MHZ 1 // add this line
//#define MCP_8MHz 8 // add this line
//#define CS_PIN 5
//#define INT_PIN 16

//  SPI.begin(18, 19, 23, 5); // SCK, MISO, MOSI, SS
//  mcP2515.reset();
//  mcP2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
//  mcP2515.setNormalMode();
//  pinMode(INT_PIN, INPUT);
//  Serial.println("MCP2515 ready");

//MCP2515 mcp2515(CS_PIN);
//  MCP2515  mcP2515(GPIO5); // use uppercase MCP2515
//to know the spi in ESP_32
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//  Serial.print("MOSI Pin: ");
//  Serial.println(MOSI);
//  Serial.print("MISO Pin: ");
//  Serial.println(MISO);
//  Serial.print("SCK Pin: ");
//  Serial.println(SCK);
//  Serial.print("SS Pin: ");
//  Serial.println(SS);  
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//}
