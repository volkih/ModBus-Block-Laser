#include "widget.h"


bool flag;
bool generated;
QString portName = "COM4";
QSerialPort serialPort;
using namespace std;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Объявление объектов
    generationLabel = new QLabel("Частота генерации, Гц:");
    generationEdit = new QLineEdit;

    ratedPumpingDurationLabel = new QLabel("Длительность накачки, мкс:");
    ratedPumpingDurationEdit = new QLineEdit;

    phaseDurationLabel = new QLabel("Длительность накачки фазы, мкс:");
    phaseDurationEdit = new QLineEdit;

    maxPumpingDurationLabel = new QLabel("Максимальная длительность накачки:");
    maxPumpingDurationEdit = new QLineEdit;
    maxPumpingDurationEdit->setReadOnly(true);
    maxPumpingDurationEdit->setText(QString::number(MaxPumpPassport));

    correctionFactorLabel = new QLabel("Поправочный коэффицент:");
    correctionFactorEdit = new QLineEdit;

    preparatoryPulseDurationLabel = new QLabel("Длительность подготовительных импульсов, мкс:");
    preparatoryPulseDurationEdit = new QLineEdit;

    pumpingCurrentLabel = new QLabel("Ток накачки, А:");
    pumpingCurrentEdit = new QLineEdit;
    pumpingCurrentEdit->setReadOnly(true);
    pumpingCurrentEdit->setText(QString::number(Current));

    startBlockButton = new QPushButton("Включение блока");
    generationBlockButton = new QPushButton("Начать генерацию");
    SyncBlockButton = new QPushButton("Внутренняя синхронизация");
    //openPortButton = new QPushButton("Открыть порт");
    //closePortButton = new QPushButton("Закрыть порт");
    setParametersButton = new QPushButton("Записать параметры");

    Logger = new QTextEdit;

    //Объявление свойств объектов

    startBlockButton->setStyleSheet("background-color: #f2190a");
    generationBlockButton->setStyleSheet("background-color: #f2190a");

    Logger->setReadOnly(true);

    // Объявление слоев

    layout_main = new QHBoxLayout;
    layout = new QVBoxLayout;
    layout_H = new QHBoxLayout;
    //layoutPort = new QHBoxLayout;


    layout->addWidget(generationLabel);
    layout->addWidget(generationEdit);
    layout->addWidget(ratedPumpingDurationLabel);
    layout->addWidget(ratedPumpingDurationEdit);
    layout->addWidget(phaseDurationLabel);
    layout->addWidget(phaseDurationEdit);
    layout->addWidget(maxPumpingDurationLabel);
    layout->addWidget(maxPumpingDurationEdit);
    layout->addWidget(correctionFactorLabel);
    layout->addWidget(correctionFactorEdit);
    layout->addWidget(preparatoryPulseDurationLabel);
    layout->addWidget(preparatoryPulseDurationEdit);
    layout->addWidget(pumpingCurrentLabel);
    layout->addWidget(pumpingCurrentEdit);



    layout_H->addWidget(generationBlockButton);
    layout_H->addWidget(SyncBlockButton);

    layout->addLayout(layout_H);

    layout->addWidget(startBlockButton);

    layout_main->addLayout(layout);
    layout_main->addWidget(Logger);
    layout_main->addWidget(setParametersButton);

    //layoutPort->addWidget(openPortButton);
    //layoutPort->addWidget(closePortButton);

    //layout_main->addLayout(layoutPort);
    setLayout(layout_main);



    // Ограничения на ввод
    floatValidator = new QDoubleValidator(this);

    floatValidator->setRange(MinFrequency, MaxFrequency, demicalPlaces);
    generationEdit->setValidator(floatValidator);

    floatValidator->setRange(MinPumpDuration, MaxPumpDuration, demicalPlaces);
    ratedPumpingDurationEdit->setValidator(floatValidator);

    floatValidator->setRange(MinBorder, MaxPumpDuration, demicalPlaces);
    phaseDurationEdit->setValidator(floatValidator);

    floatValidator->setRange(MinBorder, MaxPumpDuration, demicalPlaces);
    maxPumpingDurationEdit->setValidator(floatValidator);

    floatValidator->setRange(MinCorrectionFactor, MaxCorrectionFactor, demicalPlaces);
    correctionFactorEdit->setValidator(floatValidator);

    floatValidator->setRange(MinBorder, MaxPumpDuration, demicalPlaces);
    preparatoryPulseDurationEdit->setValidator(floatValidator);

    // Объявление последовательного порта

    // Создание нажатия кнопок
    connect(startBlockButton, &QPushButton::clicked, this, &Widget::clickedStartBlock);
    connect(generationBlockButton, &QPushButton::clicked, this, &Widget::clickedGenerateBlock);
    connect(setParametersButton, &QPushButton::clicked, this, &Widget::setParameters);

    serialPort = new QSerialPort;
    // Создает и настраивает объект QSerialPort
    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadWrite);
}

Widget::~Widget()
{
    delete generationLabel;
    delete generationEdit;
    delete ratedPumpingDurationLabel;
    delete ratedPumpingDurationEdit;
    delete phaseDurationLabel;
    delete phaseDurationEdit;
    delete maxPumpingDurationLabel;
    delete maxPumpingDurationEdit;
    delete correctionFactorLabel;
    delete correctionFactorEdit;
    delete preparatoryPulseDurationLabel;
    delete preparatoryPulseDurationEdit;
    delete pumpingCurrentLabel;
    delete pumpingCurrentEdit;
    delete startBlockButton;
    delete generationBlockButton;
    delete SyncBlockButton;
    delete setParametersButton;
    delete layout;
    delete layout_H;
    delete layout_main;
    delete Logger;
    delete floatValidator;
    serialPort->close();
    delete serialPort;

}



void Widget::clickedStartBlock()
{
    if(serialPort->isOpen()){
        if (startBlockButton->text() == "Включение блока"){
            startBlockButton->setStyleSheet("background-color: #0af20a");
            startBlockButton->setText("Выключение блока");

            //Включаем блок
            serialPort->write("upBlock");
            serialPort->waitForBytesWritten(-1);
            readSerialData();
        }
        else{
            startBlockButton->setStyleSheet("background-color: #f2190a");
            startBlockButton->setText("Включение блока");

            // Выключаем блок
            serialPort->write("downBlock");
            serialPort->waitForBytesWritten(-1);
            readSerialData();
        }
    }else{
        QMessageBox::warning(this,"Error","Port is not open!");
    }
}


void Widget::clickedGenerateBlock()
{
    float Duration;
    float Period;
    float NumberOfWarmPulses;

    if(serialPort->isOpen()){
        if(generationBlockButton->text() == "Начать генерацию")
        {
            generationBlockButton->setStyleSheet("background-color: #0af20a");
            generationBlockButton->setText("Закончить генерацию");

            serialPort->write("startGenerate");
            serialPort->waitForBytesWritten(-1);
            readSerialData();
        }
        else
        {
            generationBlockButton->setStyleSheet("background-color: #f2190a");
            generationBlockButton->setText("Начать генерацию");

            serialPort->write("stopGenerate");
            serialPort->waitForBytesWritten(-1);

            readSerialData();
        }
    }
    else{
        QMessageBox::warning(this,"Error","Port is not open!");
    }
}


void Widget::Parameter_calculation(float t_n, float k, float t_fr, float F_n, float F_p, float t_prep, float &t_ef_temp, float &T_temp, float &N)
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

void Widget::DataPort(float FinalDuration, float FinalPeriod, float NumberOfPulses)
{

      if(serialPort->isOpen()){

        string message1 = to_string(FinalDuration);
        string message2 =to_string(FinalPeriod * 1000);
        string message3 =to_string(NumberOfPulses);
        string finalmessage = message1 + " " + message2 + " " + message3;
        // Записывем числа в QByteArray
        char chars[finalmessage.size()];
        finalmessage.copy(chars, finalmessage.size());
        slice(chars,0,26);
        // cout << chars << endl;
        // Отправляем данные через последовательный порт
        serialPort->write(chars);
        serialPort->waitForBytesWritten(-1);
      }
      else{
        QMessageBox::warning(this,"Error","Port is not open!");
      }

}



void Widget::readSerialData()
{
      QString data = "";

      if(serialPort->isOpen()){
        // Получаем данные через последовательный порт
        data = serialPort->readAll();
        Logger->append(data);
      }
      else{
        QMessageBox::warning(this,"Error","Port is not open!");
      }
}

void Widget::setParameters()
{
    float Duration;
    float Period;
    float NumberOfWarmPulses;

    try {
        // Проверка и получение значений параметров из полей ввода
        float generationFrequency = validateInput<float>(generationEdit);
        float ratedPumpingDuration = validateInput<float>(ratedPumpingDurationEdit);
        float phaseDuration = validateInput<float>(phaseDurationEdit);
        // float maxPumpingDuration = validateInput<float>(maxPumpingDurationEdit);
        float correctionFactor = validateInput<float>(correctionFactorEdit);
        float preparatoryPulseDuration = validateInput<float>(preparatoryPulseDurationEdit);
        // float pumpingCurrent = validateInput<float>(pumpingCurrentEdit);


        // Perform any necessary actions with the parameters

        Parameter_calculation(ratedPumpingDuration, correctionFactor, phaseDuration, NominalFrequency, generationFrequency, preparatoryPulseDuration, Duration, Period, NumberOfWarmPulses);

        DataPort(Duration,Period,NumberOfWarmPulses);

    } catch (const exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
      }

}

