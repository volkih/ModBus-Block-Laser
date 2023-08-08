#include <Arduino.h>

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
#define pinD5 14 

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
#define BLOCK_VOLTAGE 100
#define BLOCK_CURRENT 100

// Настройка параметров
#define MaxPumpPassport (130.0)
#define correctionFactor (0.8)
#define phaseDuration (30)
#define nominalFrequency (20.0)
#define preparatoryPulseDuration (70)
#define ratedPumpingDuration (90)

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
float Duration,Period,NumberOfWarmPulses, generationFrequency;
char buffer[28];
char flagdata[50];
bool toggleflag = 0;
char commandChar[1];
String flag = "";
// put function declarations here:
void readSerialData();
void upBlock();
void downBlock();
void upBlock();
void generateBlock();
void notgenerateBlock();
void setCurrent();
void setVoltage();
void Parameter_calculation(float, float, float, float, float, float, float &, float &, float &);


using namespace std;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  myPort.begin(9600, SWSERIAL_8N2, RS485_RX, RS485_TX, false);
  mb.begin(&myPort);
  pinMode(pinD5, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
 }

void loop() {
  // put your main code here, to run repeatedly:
  //readSerialData();
  if (Serial.available()>0)
  {
    digitalWrite(pinD5, HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
    flag = Serial.readString();
    flag.toCharArray(flagdata, flag.length() + 1);
    switch (flagdata[0])
    {
    case 'F':
      memmove(&flagdata[0],&flagdata[1],49);
      generationFrequency = atof(flagdata) / 10;
      Parameter_calculation(ratedPumpingDuration, correctionFactor, phaseDuration,
                            nominalFrequency, generationFrequency, preparatoryPulseDuration, 
                            Duration, Period, NumberOfWarmPulses);
      break;
    case 'V':
      setVoltage();
      break;
    case 'I':
      setCurrent();
      break;
    case 'u':
      upBlock();
      break;
    case 'd':
      downBlock();
      break;
    default:
      break;
    }
    digitalWrite(pinD5, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

// put function definitions here:

void Parameter_calculation(float t_n, float k, float t_fr, float F_n, float F_p, float t_prep, float &t_ef_temp, float &T_temp, float &N)
{
      float P_n;
      float P_p;
      float t_p;
      float t_ef;
      float t_diod;
      float t_temp;

      P_n = (t_n + k * t_fr) * F_n;
      t_p = (P_n/F_p) - k * t_fr;
      if (t_p < MaxPumpPassport)
      {
        t_diod = t_p + t_fr;
        flag = true;
        t_ef_temp = t_diod;
        T_temp = 1 / F_p;
      }
      else
      {
        P_p = (t_n + k * t_fr) * F_p;
        t_ef = (P_n - P_p) / F_p;
        N = ceil(t_ef / (t_prep + k * t_fr));
        t_temp = t_ef / N - k * t_fr;
        t_ef_temp = t_temp + t_fr;
        T_temp = 1 / (F_p * (N + 1));
        flag = false;
      }
}


/*void readSerialData()
{
  bool digit;
  String data = Serial.readString(); // Чтение данных до символа новой строки
  for (int i = 0; i < data.length(); i++)
  {
    digit = isdigit(data[i]);
    if (digit)
    {
      break;
    }
  }
  if (digit)
  {
    data.toCharArray(buffer, 28);
    Serial.write(buffer);
    PulseDuration = round(atoi(strtok(buffer, " ")));
    Period = round(stof(strtok(NULL, " ")) * 10);
    NumberOfPulses = atoi(strtok(NULL, " "));
    Serial.write("Done!");
    Serial.println(PulseDuration);
    Serial.println(Period);
    Serial.println(NumberOfPulses);
  }
}
*/
void upBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_UP,cb);  
}
void downBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_DOWN,cb);
}

void setCurrent()
{
  mb.writeHreg(MODBUS_SLAVE_ID, CURRENT_REGISTR, BLOCK_CURRENT, cb);
}

void setVoltage()
{
mb.writeHreg(MODBUS_SLAVE_ID, VOLTAGE_REGISTR, BLOCK_VOLTAGE, cb);
}

void generateBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_GENERATE,cb);
}

void notgenerateBlock()
{
  mb.writeHreg(MODBUS_SLAVE_ID,BLOCK_REGISTR,BLOCK_NOTGENERATE,cb);  
}

void generation()
{
  digitalWrite(D1,HIGH);
  delayMicroseconds(100000000);
  digitalWrite(D1,LOW);
  delayMicroseconds(100000000);
}
