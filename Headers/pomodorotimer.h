#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <QMainWindow>
#include <QString>
#include "QLCDNumber"
#include "QTimer"
#include "QSoundEffect"

namespace Ui {
class PomodoroTimer;
}

class PomodoroTimer : public QMainWindow
{
    Q_OBJECT

public:
    explicit PomodoroTimer(QWidget *parent = 0);
    ~PomodoroTimer();

private:
    Ui::PomodoroTimer *ui;
    QString *minutes, *seconds, *seperator;
    QLCDNumber *lcdNumber;
    void shortBreakInitializer();
    void longBreakInitializer();
    void pomodoroInitializer();
    QTimer *timer;
    QSoundEffect sound;

    bool is_short_break, is_long_break, is_pomodoro;

private slots:
    void updateTime();
    void on_pomodoroButton_clicked();
    void on_shortBreakButton_clicked();
    void on_longBreakButton_clicked();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_restartButton_clicked();
};

#endif // POMODOROTIMER_H
