#include <iomanip>
#include <sstream>
#include <iostream>
#include <ModbusRtu.h>
#include <string>
#include <algorithm>


//Конфигурация пинов
#define pinD1 5
#define pinD2 4

// Конфигурация модуля RS-485
#define RS485_RX 15
#define RS485_TX 13

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
//#define BLOCK_UP 2
//#define BLOCK_DOWN 4
//#define BLOCK_GENERATE 8
//#define BLOCK_NOTGENERATE 10
//#define BLOCK_INTERNAL_SYNC 20
//#define BLOCK_EXTERNAL_SYNC 40

// Инициализация объектов
Modbus master(MODBUS_SLAVE_ID,Serial,RS485_TX);
modbus_t telegram_freq,telegram_pulse,telegram_curr,telegram_volt,telegram_block;

const int numValues = 3;
uint16_t au16data[1];
uint16_t au16block[1];
float PulseDuration,Period,NumberOfPulses;
char buffer[28];

using namespace std;
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  

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
      Serial.println(data);
      data.toCharArray(buffer,28);
      Serial.println(buffer);
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

void MasterSetup()
{
  pinMode(RS485_RX, INPUT);
  pinMode(RS485_TX, OUTPUT);
  master.begin(9600);
}

void sendModbusCommand() 
{
  if (Serial.available()>0)
  {
    String flag = Serial.readString();
    if(flag == "start")
    {  
      telegram_freq.u8id = MODBUS_SLAVE_ID;
      telegram_freq.u8fct = WRITE_REGISTR;
      telegram_freq.u16RegAdd = FREQUENCY_REGISTR;
      telegram_freq.u16CoilsNo = 1;
      telegram_freq.au16reg = au16data;
      // Отправка команды через Modbus
      master.query(telegram_freq);
    }

  }
}

void SetBlock()
{
  if (Serial.available()>0)
  {
    
    String flag = Serial.readString();
    if(flag == "upBlock")
    {  
      Serial.write("Block is up!");
      au16block[0] = 2;
      telegram_block.u8id = MODBUS_SLAVE_ID;
      telegram_block.u8fct = WRITE_REGISTR;
      telegram_block.u16RegAdd = BLOCK_REGISTR;
      telegram_block.u16CoilsNo = 1;
      telegram_block.au16reg = au16block;
      // Отправка команды через Modbus
      master.query(telegram_block);
    }
    else if (flag = "downBlock")
    {
      au16block[0] = 4;
      telegram_block.u8id = MODBUS_SLAVE_ID;
      telegram_block.u8fct = WRITE_REGISTR;
      telegram_block.u16RegAdd = BLOCK_REGISTR;
      telegram_block.u16CoilsNo = 1;
      telegram_block.au16reg = au16block;
      // Отправка команды через Modbus
      master.query(telegram_block);
    }
  }
}
void startGenerationBlock()
{
    if (Serial.available()>0)
  {
    String flag = Serial.readString();
    if(flag == "startGenerate")
    {  
      au16block[0] = 8;
      telegram_block.u8id = MODBUS_SLAVE_ID;
      telegram_block.u8fct = WRITE_REGISTR;
      telegram_block.u16RegAdd = BLOCK_REGISTR;
      telegram_block.u16CoilsNo = 1;
      telegram_block.au16reg = au16block;
      // Отправка команды через Modbus
      master.query(telegram_block);
    }
    else if (flag = "stopGenerate")
    {
      au16block[0] = 10;
      telegram_block.u8id = MODBUS_SLAVE_ID;
      telegram_block.u8fct = WRITE_REGISTR;
      telegram_block.u16RegAdd = BLOCK_REGISTR;
      telegram_block.u16CoilsNo = 1;
      telegram_block.au16reg = au16block;
      // Отправка команды через Modbus
      master.query(telegram_block);
    }
  }
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
