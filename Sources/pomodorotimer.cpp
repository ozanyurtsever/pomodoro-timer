#include "pomodorotimer.h"
#include "ui_pomodorotimer.h"
#include "QTimer"
#include "QDebug"




PomodoroTimer::PomodoroTimer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PomodoroTimer)
{

    is_short_break = false;
    is_long_break = false;
    is_pomodoro = false;

    minutes = new QString("00");
    seconds = new QString ("00");
    seperator = new QString(":");

    sound.setSource(QUrl::fromLocalFile(":/sounds/alarm.wav"));
    sound.setLoopCount(3);
    lcdNumber = new QLCDNumber(this);
    lcdNumber->move(this->width()/2 - 150,this->height()/2 - 50);
    lcdNumber->resize(250,100);
    lcdNumber->autoFillBackground();
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),this,SLOT(updateTime())); // every 1 second, timer will gonna send a signal and it will be emitted by updateTime method

    auto time = *minutes + *seperator + *seconds;
    lcdNumber->display(time);

    setWindowTitle(tr("Pomodoro Timer"));


    ui->setupUi(this);

}

PomodoroTimer::~PomodoroTimer()
{
    delete ui;
    delete seconds;
    delete minutes;
    delete seperator;
    delete lcdNumber;
    delete timer;
}

void PomodoroTimer::shortBreakInitializer()
{
    *minutes = QVariant("05").toString();
    *seconds = QVariant("00").toString();
    auto time = *minutes + *seperator + *seconds;
    lcdNumber->display(time);

}

void PomodoroTimer::longBreakInitializer()
{
    *minutes = QVariant("30").toString();
    *seconds = QVariant("00").toString();
    auto time = *minutes + *seperator + *seconds;
    lcdNumber->display(time);

}

void PomodoroTimer::pomodoroInitializer()
{
    *minutes = QVariant("25").toString();
    *seconds = QVariant("00").toString();
    auto time = *minutes + *seperator + *seconds;
    lcdNumber->display(time);
}


void PomodoroTimer::updateTime()
{
    auto second = seconds->toInt();
    auto minute = minutes->toInt();
    if(second>0){
        second--;
    }else{
        second = 59;
        minute--;
    }

    *seconds = QVariant(second).toString().rightJustified(2, '0');
    *minutes = QVariant(minute).toString().rightJustified(2, '0');
    if(second % 2 != 0){
        *seperator = " ";
    }else{
        *seperator = ":";
    }
    auto time = *minutes + *seperator + *seconds;
    lcdNumber->display(time);

    if(minute == 0 && second == 0){
        timer->stop();
        sound.play();

    }
}

void PomodoroTimer::on_pomodoroButton_clicked()
{
    is_short_break = false;
    is_long_break = false;
    is_pomodoro = true;
    sound.stop();

    pomodoroInitializer();
}

void PomodoroTimer::on_shortBreakButton_clicked()
{
    is_short_break = true;
    is_long_break = false;
    is_pomodoro = false;
    sound.stop();

    shortBreakInitializer();
}

void PomodoroTimer::on_longBreakButton_clicked()
{

    is_short_break = false;
    is_long_break = true;
    is_pomodoro = false;
    sound.stop();

    longBreakInitializer();
}

void PomodoroTimer::on_startButton_clicked()
{
    if((is_short_break || is_long_break || is_pomodoro) && !(seconds->toInt() == 0 && minutes->toInt() == 0)){

        timer->start(1000);
    }
}

void PomodoroTimer::on_stopButton_clicked()
{
    timer->stop();
}

void PomodoroTimer::on_restartButton_clicked()
{
    timer->stop();
    sound.stop();

    if(is_short_break){

        shortBreakInitializer();

    }else if(is_long_break){

        longBreakInitializer();

    }else if(is_pomodoro){

        pomodoroInitializer();
    }

}
