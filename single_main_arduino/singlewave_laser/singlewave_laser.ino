#include <iomanip>
#include <sstream>
#include <iostream>
#include <ModbusRTU.h>
#include <string>
#include <algorithm>
#include <SoftwareSerial.h>


//Конфигурация пинов
#define pinD1 5
#define pinD2 4

// Конфигурация модуля RS-485
#define RS485_RX 13
#define RS485_TX 15

// Параметры подключения Modbus
#define MODBUS_SLAVE_ID 1
// Параметры регистров
#define READ_REGISTR 3
#define WRITE_REGISTR 6
#define FREQUENCY_REGISTR 1
#define PULSES_REGISTR 2
#define VOLTAGE_REGISTR 4
#define CURRENT_REGISTR 3
#define BLOCK_REGISTR 9
#define BLOCK_UP 2
#define BLOCK_DOWN 4
#define BLOCK_GENERATE 8
#define BLOCK_NOTGENERATE 10
#define BLOCK_INTERNAL_SYNC 20
#define BLOCK_EXTERNAL_SYNC 40


// Инициализация объектов
ModbusRTU mb;
EspSoftwareSerial::UART myPort;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
#ifdef ESP8266
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#elif ESP32
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#else
  Serial.print("Request result: 0x");
  Serial.print(event, HEX);
#endif
  return true;
}

const int numValues = 3;
uint16_t au16data[1] = {1};
uint16_t au16block[1];
float PulseDuration,Period,NumberOfPulses;
char buffer[28];
String flag = "";



using namespace std;
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  myPort.begin(9600, SWSERIAL_8N2, RS485_RX, RS485_TX, false);
  mb.begin(&myPort);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
  {
    flag = Serial.readString();
    
    if (flag == "upBlock"){
      upBlock();
    }
    else if (flag == "downBlock")
    {
      downBlock();
    }
  }

  //myPort.write(start, sizeof(start));
  //delay(5000);
  //myPort.write(stop, sizeof(stop));
  //delay(5000);
 


  
  
}

void readSerialData()
{
  if (Serial.available()>0)
  {
    bool digit;
    String data = Serial.readString(); // Чтение данных до символа новой строки
    for (int i = 0; i < data.length(); i++) {
          digit = isdigit(data[i]);
          if(digit){
            break;
          }
        }
    if (digit){
      data.toCharArray(buffer,28);
      Serial.write(buffer);
      PulseDuration=round(atoi(strtok(buffer," ")));
      Period=round(stof(strtok(NULL," "))*10);
      NumberOfPulses=atoi(strtok(NULL," "));
      Serial.write("Done!");
      Serial.println(PulseDuration);
      Serial.println(Period);
      Serial.println(NumberOfPulses);
    
    }
     
  }
}

void upBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_UP,cb);  
}
void downBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_DOWN,cb);
}

void generateBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_GENERATE,cb);
}

void notgenerateBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_NOTGENERATE,cb);  
}

std::string intToHex(int value) {
    std::stringstream stream;
    stream << std::hex << value;
    return stream.str();
}

void generation()
{
  digitalWrite(D1,HIGH);
  delayMicroseconds(100000000);
  digitalWrite(D1,LOW);
  delayMicroseconds(100000000);
}
