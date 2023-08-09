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

    VoltageLabel = new QLabel("Напряжение:");
    VoltageEdit = new QLineEdit;
    VoltageEdit->setReadOnly(true);
    VoltageEdit->setText(QString::number(Voltage));

    pumpingCurrentLabel = new QLabel("Ток накачки, А:");
    pumpingCurrentEdit = new QLineEdit;
    pumpingCurrentEdit->setReadOnly(true);
    pumpingCurrentEdit->setText(QString::number(Current));

    startBlockButton = new QPushButton("Включение блока");
    generationBlockButton = new QPushButton("Начать генерацию");
    SyncBlockButton = new QPushButton("Внутренняя синхронизация");

    setFrequencyButton = new QPushButton("Выставить");
    setVoltageButton = new QPushButton("Выставить");
    setCurrentButton = new QPushButton("Выставить");

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
    layout->addWidget(setFrequencyButton);

    layout->addWidget(VoltageLabel);
    layout->addWidget(VoltageEdit);
    layout->addWidget(setVoltageButton);

    layout->addWidget(pumpingCurrentLabel);
    layout->addWidget(pumpingCurrentEdit);
    layout->addWidget(setCurrentButton);


    layout_H->addWidget(generationBlockButton);
    layout_H->addWidget(SyncBlockButton);

    layout->addLayout(layout_H);

    layout->addWidget(startBlockButton);

    layout_main->addLayout(layout);
    layout_main->addWidget(Logger);

    //layoutPort->addWidget(openPortButton);
    //layoutPort->addWidget(closePortButton);

    //layout_main->addLayout(layoutPort);
    setLayout(layout_main);



    // Ограничения на ввод
    floatValidator = new QDoubleValidator(this);

    floatValidator->setRange(MinFrequency, MaxFrequency, demicalPlaces);
    generationEdit->setValidator(floatValidator);



    // Создание нажатия кнопок
    connect(startBlockButton, &QPushButton::clicked, this, &Widget::clickedStartBlock);
    connect(generationBlockButton, &QPushButton::clicked, this, &Widget::clickedGenerateBlock);

    connect(setFrequencyButton, &QPushButton::clicked, this, &Widget::setFrequency);
    connect(setVoltageButton, &QPushButton::clicked, this, &Widget::setVoltage);
    connect(setCurrentButton, &QPushButton::clicked, this, &Widget::setCurrent);

    // Объявление последовательного порта
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
    delete VoltageLabel;
    delete VoltageEdit;
    delete pumpingCurrentLabel;
    delete pumpingCurrentEdit;
    delete startBlockButton;
    delete generationBlockButton;
    delete SyncBlockButton;
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

            //Включаем блок
            serialPort->write("upBlock");
            serialPort->waitForBytesWritten(-1);

            startBlockButton->setStyleSheet("background-color: #0af20a");
            startBlockButton->setText("Выключение блока");

            //readSerialData();
        }
        else{

            // Выключаем блок
            serialPort->write("downBlock");
            serialPort->waitForBytesWritten(-1);

            startBlockButton->setStyleSheet("background-color: #f2190a");
            startBlockButton->setText("Включение блока");

            //readSerialData();
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
    QString time;

    if(serialPort->isOpen()){
        if(generationBlockButton->text() == "Начать генерацию")
        {
            generationBlockButton->setStyleSheet("background-color: #0af20a");
            generationBlockButton->setText("Закончить генерацию");

            serialPort->write("startGenerate");
            setTime(time);
            serialPort->waitForBytesWritten(-1);
            readSerialData(time);
        }
        else
        {
            generationBlockButton->setStyleSheet("background-color: #f2190a");
            generationBlockButton->setText("Начать генерацию");

            serialPort->write("stopGenerate");
            serialPort->waitForBytesWritten(-1);

            readSerialData(time);
        }
    }
    else{
        QMessageBox::warning(this,"Error","Port is not open!");
    }
}





void Widget::readSerialData(QString time)
{
    if(serialPort->isOpen()){
        // Получаем данные через последовательный порт
        if (serialPort->waitForReadyRead(-1))
        {
            QByteArray data = serialPort->readAll();
            Logger->append(time + " " + data);
        }
      }
      else{
        QMessageBox::warning(this,"Error","Port is not open!");
      }
}

void Widget::setTime(QString &formattedDateTime)
{
      currentDateTime = QDateTime::currentDateTime();
      formattedDateTime = currentDateTime.toString("hh:mm:ss");
}


void Widget::setFrequency()
{
      QString time;
      try{
        float generationFrequency = validateInput<float>(generationEdit);
      }
      catch (const exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
      }

      string fmess = "F";

      if (generationEdit->text() == "")
      {
        QMessageBox::critical(this,"Ошибка","Нет введеного значения");
      }
      else {
        float gen = generationEdit->text().toFloat() * 10;
        int genInt = (int)gen;
        qDebug() << genInt;
        string mess = to_string(genInt);
        fmess.append(mess);

        char chars[fmess.size()];
        fmess.copy(chars,fmess.size());

        qDebug() << chars;

        serialPort->write(chars);
        setTime(time);
        serialPort->waitForBytesWritten(-1);
        readSerialData(time);
      }
}


void Widget::setVoltage()
{
      try{
        float voltageInput = validateInput<float>(VoltageEdit);
      }
      catch (const exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
      }
      string fmess = "V";

      if (VoltageEdit->text() == "")
      {
        QMessageBox::critical(this,"Ошибка","Нет введеного значения");
      }
      else {
        string mess = VoltageEdit->text().toStdString();
        fmess.append(mess);

        char chars[fmess.size()];
        fmess.copy(chars,fmess.size());

        qDebug() << chars;

        serialPort->write(chars);
        serialPort->waitForBytesWritten(-1);

      }
}

void Widget::setCurrent()
{
      string fmess = "I";

      if (pumpingCurrentEdit->text() == "")
      {
        QMessageBox::critical(this,"Ошибка","Нет введеного значения");
      }
      else {
        string mess = pumpingCurrentEdit->text().toStdString();

        fmess.append(mess);

        char chars[fmess.size()];
        fmess.copy(chars,fmess.size());

        qDebug() << chars;

        serialPort->write(chars);
        serialPort->waitForBytesWritten(-1);

      }
}

