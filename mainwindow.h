#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/time.h>

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QLabel>
#include <QGridLayout>

#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Utility.hpp>
#include <GeographicLib/MagneticModel.hpp>

#include "genericclient.h"
#include "setupgui.h"
#include "constants.h"
#include "utility.h"
#include "navutility.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void closeEvent(QCloseEvent *event);
    void readSettings();
    void writeSettings();
    void updateDate();
    void updateTime();
    void updateLat();
    void updateLon();
    void updateHgps();
    void updateTtrack();
    void updateDec();
    void updateMtrack();
    void updateGeodesic();
    void updateGreatcircle();
    void updateLoxodrome();
    void updateLoxodrome2();
    QAction *exitAct;
    QAction *aboutAct;
    QAction *maginfoAct;
    QMenu *fileMenu;
    QMenu *helpMenu;
    GenericClient *client;
    QString host;
    quint16 port;
    QString stemp;
    double hms;
    double lat;
    double lon;
    double hgps;
    double timesecs;
    double sod;
    double track;
    double gs;
    double roc;
    int hour;
    int min;
    double sec;
    int n;
    QLabel *lab0;
    QLabel *lab1;
    QLabel *lab2;
    QLabel *lab3;
    QLabel *lab4;
    QLabel *lab5;
    QLabel *lab6;
    QLabel *lab7;
    QLabel *lab8;
    QLabel *lab9;
    QLabel *lab10;
    QLabel *lab11;
    QLabel *lab12;
    QLabel *lab13;
    QLabel *lab14;
    QLabel *lab15;
    QLabel *lab16;
    QLabel *lab17;
    QLabel *lab18;
    QLabel *lab19;
    QLabel *lab20;
    QLabel *labdate;
    QLabel *labtime;
    QLabel *lablat;
    QLabel *lablon;
    QLabel *labhgps;
    QLabel *labttrack;
    QLabel *labvar;
    QLabel *labmtrack;
    QLabel *labmcalc;
    QLabel *labgextd;
    QLabel *labgcxtd;
    QLabel *lablxxtd;
    QLabel *lablx2xtd;
    QLabel *labgecalc;
    QLabel *labgccalc;
    QLabel *lablxcalc;
    QLabel *lablx2calc;
    QLabel *labgeniter;
    QLabel *labgcniter;
    QLabel *lablxniter;
    QLabel *lablx2niter;
    int ymd;
    int year;
    int month;
    int day;
    int mwwidth;
    int mwheight;
    QChar leadingZero = QLatin1Char('0');
    double newlon;
    double a = GeographicLib::Constants::WGS84_a();
    double f = GeographicLib::Constants::WGS84_f();
    GeographicLib::MagneticModel mag{"wmm2020"}; // Note the curly brackets!!!
    double magd;
    double dyear;
    GeographicLib::Math::real magmaxtime;
    timeval tmag1;
    timeval tmag2;
    //KELPP north to south
    //double lata1 = 27.175667;
    //double lona1 = -91.949333;
    //double lata2 = 25.010333;
    //double lona2 = -91.949333;
    //KELPP south to south
    //double lata1 = 25.010333;
    //double lona1 = -91.949333;
    //double lata2 = 27.175667;
    //double lona2 = -91.949333;
    //PEGLG west to east
    //double lata1 = 26.804500;
    //double lona1 = -92.844500;
    //double lata2 = 26.694500;
    //double lona2 = -87.249833;
    //PEGLG east to west
    //double lata1 = 26.694500;
    //double lona1 = -87.249833;
    //double lata2 = 26.804500;
    //double lona2 = -92.844500;
    //PEGLG SOUTH west to east
    //double lata1 = -26.804500;
    //double lona1 = -92.844500;
    //double lata2 = -26.694500;
    //double lona2 = -87.249833;
    //PEGLG SOUTH east to west
    //double lata1 = -26.694500;
    //double lona1 = -87.249833;
    //double lata2 = -26.804500;
    //double lona2 = -92.844500;
    //KELPP south north to south
    //double lata1 = -25.010333;
    //double lona1 = -91.949333;
    //double lata2 = -27.175667;
    //double lona2 = -91.949333;
    //KELPP south south to north
    //double lata1 = -27.175667;
    //double lona1 = -91.949333;
    //double lata2 = -25.010333;
    //double lona2 = -91.949333;
    //DIAG SOUTH north to south
    //double lata1 = -26.804500;
    //double lona1 = -92.844500;
    //double lata2 = -29.269333;
    //double lona2 = -94.867667;
    //DIAG SOUTH south to north
    //double lata1 = -29.269333;
    //double lona1 = -94.867667;
    //double lata2 = -26.804500;
    //double lona2 = -92.844500;
    //N88 west to east
    //double lata1 = 88.0;
    //double lona1 = -90.0;
    //double lata2 = 88.0;
    //double lona2 = -45.0;
    //N88 east to west
    //double lata1 = 88.0;
    //double lona1 = -45.0;
    //double lata2 = 88.0;
    //double lona2 = -90.0;
    //S88 east to west
    //double lata1 = -88.0;
    //double lona1 = -45.0;
    //double lata2 = -88.0;
    //double lona2 = -90.0;
    //S88 west to east
    //double lata1 = -88.0;
    //double lona1 = -90.0;
    //double lata2 = -88.0;
    //double lona2 = -45.0;
    //Equator west to east
    //double lata1 = 0.0;
    //double lona1 = -45.0;
    //double lata2 = 0.0;
    //double lona2 = -35.0;
    //Equator east to west
    double lata1 = 0.0;
    double lona1 = -35.0;
    double lata2 = 0.0;
    double lona2 = -45.0;

private slots:
    void slotAbout();
    void slotMaginfo();
    void slotNewData(QString);
    void slotServerError(QAbstractSocket::SocketError socketError);

};
#endif // MAINWINDOW_H
