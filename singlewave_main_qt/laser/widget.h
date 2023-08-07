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

#include <iostream>
#include <stdexcept>


#define MaxFrequency (25.0)
#define MinFrequency (0.0)
#define MaxPumpDuration (200.0)
#define MinPumpDuration (20.0)
#define MaxCorrectionFactor (1.0)
#define MinCorrectionFactor (0.0)

#define MaxPumpPassport (130.0)
#define NominalFrequency (20.0f)

#define Current (41)
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
    QLineEdit *ratedPumpingDurationEdit;
    QLineEdit *phaseDurationEdit;
    QLineEdit *maxPumpingDurationEdit;
    QLineEdit *correctionFactorEdit;
    QLineEdit *preparatoryPulseDurationEdit;
    QLineEdit *pumpingCurrentEdit;

    QPushButton *startBlockButton;
    QPushButton *generationBlockButton;
    QPushButton *SyncBlockButton;
    QPushButton *setParametersButton;

    QPushButton *setFrequencyButton;
    QPushButton *setRatedPumpingButton;
    QPushButton *setPhaseButton;
    QPushButton *setMaxPumpingButton;
    QPushButton *setFactorButton;
    QPushButton *setWarmButton;
    QPushButton *setCurrentButton;

    QLabel *generationLabel;
    QLabel *ratedPumpingDurationLabel;
    QLabel *phaseDurationLabel;
    QLabel *maxPumpingDurationLabel;
    QLabel *correctionFactorLabel;
    QLabel *preparatoryPulseDurationLabel;
    QLabel *pumpingCurrentLabel;

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
    void Parameter_calculation(float t_n, float k, float t_fr, float F_n, float F_p, float t_prep, float& t_ef_temp, float& T_temp, float& N);
    void DataPort(float FinalDuration, float FinalPeriod, float NumberOfPulses = 0.0);
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
    void readSerialData();
    void setParameters();
    void setFrequency();
    void setRatedPumping();
    void setPhase();
    void setMaxPumping();
    void setFactor();
    void setWarm();
    void setCurrent();
};
#endif // WIDGET_H
