#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>


#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSerialPort>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTextEdit>
#include <QTimer>
#include <QMessageBox>
#include <QSettings>
#include <QDateTime>

#include <iostream>
#include <stdexcept>


#define MaxFrequency (25.0)
#define MinFrequency (0.0)

#define Voltage (10.0)
#define Current (10.0)
#define demicalPlaces (1)
#define MinBorder (0)


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    template <typename T>
    T validateInput(QLineEdit* edit) {
        bool ok;
        T value = edit->text().toFloat(&ok);
        if (!ok) {
            throw std::runtime_error("Ошибка! Неправильно введены значения");
        }
        return value;
    }
    QLineEdit *generationEdit;
    QLineEdit *VoltageEdit;
    QLineEdit *pumpingCurrentEdit;

    QPushButton *startBlockButton;
    QPushButton *generationBlockButton;
    QPushButton *SyncBlockButton;

    QPushButton *setFrequencyButton;
    QPushButton *setVoltageButton;
    QPushButton *setCurrentButton;

    QLabel *generationLabel;
    QLabel *VoltageLabel;
    QLabel *pumpingCurrentLabel;

    QDateTime currentDateTime;

    QVBoxLayout *layout;
    QHBoxLayout *layout_H;
    QHBoxLayout *layout_main;
    QHBoxLayout *layoutPort;

    QDoubleValidator *floatValidator;

    QTextEdit *Logger;

    QSerialPort *serialPort;

private slots:
    void clickedStartBlock();
    void clickedGenerateBlock();
    char* slice(char*s, int from, int to)
    {
        /*
          Эта функция обрезает строку, где:
          первый аргумент - массив char'ов
          второй - с какой позиции обрезать
          третий - по какую позицию
        */
        int j = 0;
        for(int i = from; i <= to; ++i)
            s[j++] = s[i];
        s[j] = 0;
        return s;
    }
    void setFrequency();
    void setVoltage();
    void setCurrent();
    void readSerialData(QString t);
    void setTime(QString &t);
};
#endif // WIDGET_H
