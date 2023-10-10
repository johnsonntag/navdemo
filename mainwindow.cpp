#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Read the saved settings
    mwwidth = 480;
    mwheight = 480;
    readSettings();

    // Get starting info from user
    setupGui *setup = new setupGui(&host,&port);
    while (setup->exec() == QDialog::Rejected)
    {
         QMessageBox msgBox;
         msgBox.setText("Invalid input");
         msgBox.exec();
    }

     // Build the menu bar
    createActions();
    createMenus();

    // Window management
    setWindowTitle("Nav Demo");
    setMinimumSize(240,120);
    resize(mwwidth,mwheight);
    QWidget *window = new QWidget(this);

    // Build the GUI elemeents
    lab0 = new QLabel("UTC date:");
    labdate = new QLabel();
    labdate->setFont(QFont("Helvetica",14,QFont::Bold));
    labdate->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab1 = new QLabel("UTC time:");
    labtime = new QLabel();
    labtime->setFont(QFont("Helvetica",14,QFont::Bold));
    labtime->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab2 = new QLabel("Latitude (deg):");
    lablat = new QLabel();
    lablat->setFont(QFont("Helvetica",14,QFont::Bold));
    lablat->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab3 = new QLabel("Longitude (deg):");
    lablon = new QLabel();
    lablon->setFont(QFont("Helvetica",14,QFont::Bold));
    lablon->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab4 = new QLabel("WGS-84 altitude (m):");
    labhgps = new QLabel();
    labhgps->setFont(QFont("Helvetica",14,QFont::Bold));
    labhgps->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab5 = new QLabel("True track (deg):");
    labttrack = new QLabel();
    labttrack->setFont(QFont("Helvetica",14,QFont::Bold));
    labttrack->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab6 = new QLabel("Mag declination (deg):");
    labvar = new QLabel();
    labvar->setFont(QFont("Helvetica",14,QFont::Bold));
    labvar->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab7 = new QLabel("Mag track (deg):");
    labmtrack = new QLabel();
    labmtrack->setFont(QFont("Helvetica",14,QFont::Bold));
    labmtrack->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab8 = new QLabel("Mag calc time (msec):");
    labmcalc = new QLabel();
    labmcalc->setFont(QFont("Helvetica",14,QFont::Bold));
    labmcalc->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab9 = new QLabel("Geodesic XTD (ft):");
    labgextd = new QLabel();
    labgextd->setFont(QFont("Helvetica",14,QFont::Bold));
    labgextd->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab10 = new QLabel("Calc time (msec):");
    labgecalc = new QLabel();
    labgecalc->setFont(QFont("Helvetica",14,QFont::Bold));
    labgecalc->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab11 = new QLabel("Iterations:");
    labgeniter = new QLabel();
    labgeniter->setFont(QFont("Helvetica",14,QFont::Bold));
    labgeniter->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab12 = new QLabel("Great circle XTD (ft):");
    labgcxtd = new QLabel();
    labgcxtd->setFont(QFont("Helvetica",14,QFont::Bold));
    labgcxtd->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab13 = new QLabel("Calc time (msec):");
    labgccalc = new QLabel();
    labgccalc->setFont(QFont("Helvetica",14,QFont::Bold));
    labgccalc->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab14 = new QLabel("Iterations:");
    labgcniter = new QLabel();
    labgcniter->setFont(QFont("Helvetica",14,QFont::Bold));
    labgcniter->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab15 = new QLabel("Loxodrome XTD (ft):");
    lablxxtd = new QLabel();
    lablxxtd->setFont(QFont("Helvetica",14,QFont::Bold));
    lablxxtd->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab16 = new QLabel("Calc time (msec):");
    lablxcalc = new QLabel();
    lablxcalc->setFont(QFont("Helvetica",14,QFont::Bold));
    lablxcalc->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab17 = new QLabel("Iterations:");
    lablxniter = new QLabel();
    lablxniter->setFont(QFont("Helvetica",14,QFont::Bold));
    lablxniter->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    lab18 = new QLabel("Loxodrome2 XTD (ft):");
    lablx2xtd = new QLabel();
    lablx2xtd->setFont(QFont("Helvetica",14,QFont::Bold));
    lablx2xtd->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab19 = new QLabel("Calc time (msec):");
    lablx2calc = new QLabel();
    lablx2calc->setFont(QFont("Helvetica",14,QFont::Bold));
    lablx2calc->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab20 = new QLabel("Iterations:");
    lablx2niter = new QLabel();
    lablx2niter->setFont(QFont("Helvetica",14,QFont::Bold));
    lablx2niter->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    // Organize the GUI elements
    QGridLayout *maingroup = new QGridLayout;
    maingroup->addWidget(lab0,0,0);
    maingroup->addWidget(lab1,0,1);
    maingroup->addWidget(labdate,1,0);
    maingroup->addWidget(labtime,1,1);
    maingroup->addWidget(lab2,2,0);
    maingroup->addWidget(lab3,2,1);
    maingroup->addWidget(lab4,2,2);
    maingroup->addWidget(lablat,3,0);
    maingroup->addWidget(lablon,3,1);
    maingroup->addWidget(labhgps,3,2);
    maingroup->addWidget(lab5,4,0);
    maingroup->addWidget(lab6,4,1);
    maingroup->addWidget(lab7,4,2);
    maingroup->addWidget(lab8,4,3);
    maingroup->addWidget(labttrack,5,0);
    maingroup->addWidget(labvar,5,1);
    maingroup->addWidget(labmtrack,5,2);
    maingroup->addWidget(labmcalc,5,3);
    maingroup->addWidget(lab9,6,0);
    maingroup->addWidget(lab10,6,1);
    maingroup->addWidget(lab11,6,2);
    maingroup->addWidget(labgextd,7,0);
    maingroup->addWidget(labgecalc,7,1);
    maingroup->addWidget(labgeniter,7,2);
    maingroup->addWidget(lab12,8,0);
    maingroup->addWidget(lab13,8,1);
    maingroup->addWidget(lab14,8,2);
    maingroup->addWidget(labgcxtd,9,0);
    maingroup->addWidget(labgccalc,9,1);
    maingroup->addWidget(labgcniter,9,2);
    maingroup->addWidget(lab15,10,0);
    maingroup->addWidget(lab16,10,1);
    maingroup->addWidget(lab17,10,2);
    maingroup->addWidget(lablxxtd,11,0);
    maingroup->addWidget(lablxcalc,11,1);
    maingroup->addWidget(lablxniter,11,2);
    maingroup->addWidget(lab18,12,0);
    maingroup->addWidget(lab19,12,1);
    maingroup->addWidget(lab20,12,2);
    maingroup->addWidget(lablx2xtd,13,0);
    maingroup->addWidget(lablx2calc,13,1);
    maingroup->addWidget(lablx2niter,13,2);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(maingroup);

    // Finalize the GUI
    window->setLayout(layout);
    setCentralWidget(window);

    // Build the network client
    client = new GenericClient(this,host,port);
    connect(client,SIGNAL(newLine(QString)),this,SLOT(slotNewData(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    // Write the current user settings
    writeSettings();

}

void MainWindow::readSettings()
{

    QSettings settings("nasa","navdemo");
    host = settings.value("host","localhost").toString();
    port = settings.value("port",4063).toInt();
    mwwidth = settings.value("mwwidth",200).toInt();
    mwheight = settings.value("mwheight",200).toInt();

}

void MainWindow::writeSettings()
{

    QSettings settings("nasa","navdemo");
    settings.setValue("host",host);
    settings.setValue("port",port);
    settings.setValue("mwwidth",width());
    settings.setValue("mwheight",height());

}

void MainWindow::createActions()
{

    exitAct = new QAction("Exit",this);
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

    maginfoAct = new QAction("Geomagnetic model info",this);
    connect(maginfoAct,SIGNAL(triggered()),this,SLOT(slotMaginfo()));
    aboutAct = new QAction("About",this);
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(slotAbout()));

}

void MainWindow::createMenus()
{

    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(maginfoAct);
    helpMenu->addAction(aboutAct);

}

void MainWindow::slotMaginfo()
{
     QMessageBox msgBox;
     const std::string magdesc = mag.Description();
     const GeographicLib::Math::real magmintime = mag.MinTime();
     const GeographicLib::Math::real magmaxtime = mag.MaxTime();
     double magmaxtdiff = magmaxtime - dyear;
     double magmintdiff = magmintime - dyear;
     stemp = QString("Geomagnetic model: %1\nModel valid from: %2\nModel valid to: %3\n")
             .arg(QString::fromStdString(magdesc))
             .arg(magmintime,6,'f',1)
             .arg(magmaxtime,6,'f',1);
     if (magmintdiff>0.0) stemp.append("Current time is prior to model valid time, use caution");
     else if (magmaxtdiff<0.0) stemp.append("Current time is after model valid time, use caution");
     else stemp.append("Current time is within model valid time");
     msgBox.setText(stemp);
     msgBox.exec();

}

void MainWindow::slotAbout()
{
    QMessageBox msgBox;
    msgBox.setText("Qt5-based navigation demo\n"
                   "Utilizing GeographicLib functionality\n"
                   "Released: 22 June 2023");
    msgBox.exec();

}

void MainWindow::slotNewData(QString newgps)
{

    stemp = newgps.section(',',0,0);
    if (stemp=="11")
    {
      stemp = newgps.section(',',1,1);
      ymd = stemp.toInt();
      parseymd(ymd,&year,&month,&day);
      stemp = newgps.section(',',2,2);
      hms = stemp.toDouble();
      parsehms(hms,&hour,&min,&sec);
      timesecs = double(hour)*3600.0+double(min)*60.0+sec;
      sod = timesecs;
      stemp = newgps.section(',',3,3);
      lat = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',4,4);
      lon = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',5,5);
      hgps = stemp.toDouble()*FT2M;
      stemp = newgps.section(',',6,6);
      track = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',7,7);
      gs = stemp.toDouble()*6080.0/3600.0*FT2M;
      stemp = newgps.section(',',8,8);
      roc = stemp.toDouble()*FT2M/60.0;
    }
    else if (stemp=="10")
    {
      stemp = newgps.section(',',1,1);
      timesecs = stemp.toDouble();
      stemp = newgps.section(',',2,2);
      lat = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',3,3);
      lon = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',4,4);
      hgps = stemp.toDouble()*FT2M;
      stemp = newgps.section(',',5,5);
      track = stemp.toDouble()*DEG2RAD;
      stemp = newgps.section(',',6,6);
      gs = stemp.toDouble()*6080.0/3600.0*FT2M;
      stemp = newgps.section(',',7,7);
      roc = stemp.toDouble()*FT2M/60.0;
      n = 0;
      sod = timesecs;
      while (sod>86400.0)
      {
          sod -= 86400.0;
          ++n;
      }
      hour = int(sod/3600.0);
      min = int((sod-double(hour)*3600.0)/60.0);
      sec = sod-double(hour)*3600.0-double(min)*60.0;
    }
    else
    {
      qDebug() << "Unrecognized network message type\n";
    }

    updateTime();
    updateDate();
    updateLat();
    updateLon();
    updateHgps();
    updateTtrack();
    updateDec();
    updateMtrack();
    updateGeodesic();
    updateGreatcircle();
    updateLoxodrome();
    updateLoxodrome2();

}

void MainWindow::slotServerError(QAbstractSocket::SocketError socketError)
{

    QMessageBox netMsgBox;

    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        netMsgBox.setText("Connection to GNSS server closed by the server");
        netMsgBox.exec();
        break;
    case QAbstractSocket::HostNotFoundError:
        netMsgBox.setText("GNSS server not found");
        netMsgBox.exec();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        netMsgBox.setText("Connection refused by GNSS server");
        netMsgBox.exec();
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        netMsgBox.setText("Socket not available on GNSS server");
        netMsgBox.exec();
        break;
    default:
        netMsgBox.setText("Network error occurred");
        netMsgBox.exec();
    }
    close();

}

void MainWindow::updateTime()
{
    stemp = QString("%1:%2:%3").arg(hour,2,10,leadingZero).arg(min,2,10,leadingZero).arg(sec,4,'f',1,leadingZero);
    labtime->setText(stemp);
}

void MainWindow::updateDate()
{
    stemp = QString("%1-%2-%3").arg(year,4,10,leadingZero).arg(month,2,10,leadingZero).arg(day,2,10,leadingZero);
    labdate->setText(stemp);
}

void MainWindow::updateLat()
{
    if (lat>=0.0)
        stemp = QString("%1 N").arg(lat/DEG2RAD,9,'f',6,leadingZero);
    else
        stemp = QString("%1 S").arg(lat/DEG2RAD,9,'f',6,leadingZero);
    lablat->setText(stemp);
}

void MainWindow::updateLon()
{
    newlon = lon/DEG2RAD;
    while (newlon>180.0) newlon-=360.0;
    while (newlon<-180.0) newlon+=360.0;
    if (newlon>=0.0)
        stemp = QString("%1 E").arg(newlon,10,'f',6,leadingZero);
    else
        stemp = QString("%1 W").arg(newlon,10,'f',6,leadingZero);
    lablon->setText(stemp);
}

void MainWindow::updateHgps()
{
    stemp = QString("%1").arg(hgps,7,'f',1);
    labhgps->setText(stemp);
}

void MainWindow::updateTtrack()
{
    stemp = QString("%1").arg(track/DEG2RAD,6,'f',2);
    labttrack->setText(stemp);
}

void MainWindow::updateDec()
{
    char *ymd;
    std::string stemp1;
    double bx,by,bz,magh,magf,magi;

    // Evaluate the magnetic model at current time and location
    gettimeofday(&tmag1,NULL);
    asprintf(&ymd,"%04d-%02d-%02d",year,month,day);
    stemp1 = ymd;
    dyear = GeographicLib::Utility::fractionalyear<double>(stemp1);
    mag(dyear,lat/DEG2RAD,lon/DEG2RAD,hgps,bx,by,bz);
    GeographicLib::MagneticModel::FieldComponents(bx,by,bz,magh,magf,magd,magi);
    gettimeofday(&tmag2,NULL);
    double tmagcalcms = 1.0e3*(tmag2.tv_sec-tmag1.tv_sec)
            + (double)(tmag2.tv_usec-tmag1.tv_usec)/1.0e3;
    //qDebug() << tmagcalcms << "ms\n";

    // Display the result
    stemp = QString("%1").arg(magd,6,'f',2);
    labvar->setText(stemp);
    stemp = QString("%1").arg(tmagcalcms,6,'f',3);
    labmcalc->setText(stemp);

}

void MainWindow::updateMtrack()
{
    double mtrack = (track/DEG2RAD)-magd;
    while(mtrack>=360.0) mtrack-=360.0;
    while (mtrack<0) mtrack+=360.0;
    stemp = QString("%1").arg(mtrack,6,'f',2);
    labmtrack->setText(stemp);
}

void MainWindow::updateGeodesic()
{
    int niter;

    gettimeofday(&tmag1,NULL);
    double xtd = xtdgeodesic(lata1,lona1,lata2,lona2,lat/DEG2RAD,lon/DEG2RAD,&niter);
    stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
    labgextd->setText(stemp);
    gettimeofday(&tmag2,NULL);
    double tmagcalcms = 1.0e3*(tmag2.tv_sec-tmag1.tv_sec)
            + (double)(tmag2.tv_usec-tmag1.tv_usec)/1.0e3;
    stemp = QString("%1").arg(tmagcalcms,6,'f',3);
    labgecalc->setText(stemp);
    stemp = QString("%1").arg(niter,2);
    labgeniter->setText(stemp);

}

void MainWindow::updateGreatcircle()
{

    gettimeofday(&tmag1,NULL);
    double xtd = xtdgreatcircle(lata1,lona1,lata2,lona2,lat/DEG2RAD,lon/DEG2RAD);
    stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
    labgcxtd->setText(stemp);
    gettimeofday(&tmag2,NULL);
    double tmagcalcms = 1.0e3*(tmag2.tv_sec-tmag1.tv_sec)
            + (double)(tmag2.tv_usec-tmag1.tv_usec)/1.0e3;
    stemp = QString("%1").arg(tmagcalcms,6,'f',3);
    labgccalc->setText(stemp);
    labgcniter->setText("0");

}

void MainWindow::updateLoxodrome()
{
    int niter;

    gettimeofday(&tmag1,NULL);
    double xtd = xtdloxodrome(lata1,lona1,lata2,lona2,lat/DEG2RAD,lon/DEG2RAD,&niter);
    stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
    lablxxtd->setText(stemp);
    gettimeofday(&tmag2,NULL);
    double tmagcalcms = 1.0e3*(tmag2.tv_sec-tmag1.tv_sec)
            + (double)(tmag2.tv_usec-tmag1.tv_usec)/1.0e3;
    stemp = QString("%1").arg(tmagcalcms,6,'f',3);
    lablxcalc->setText(stemp);
    stemp = QString("%1").arg(niter,2);
    lablxniter->setText(stemp);

}

void MainWindow::updateLoxodrome2()
{
    int niter;

    gettimeofday(&tmag1,NULL);
    double xtd = xtdloxodrome2(lata1,lona1,lata2,lona2,lat/DEG2RAD,lon/DEG2RAD,&niter);
    stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
    lablx2xtd->setText(stemp);
    gettimeofday(&tmag2,NULL);
    double tmagcalcms = 1.0e3*(tmag2.tv_sec-tmag1.tv_sec)
            + (double)(tmag2.tv_usec-tmag1.tv_usec)/1.0e3;
    stemp = QString("%1").arg(tmagcalcms,6,'f',3);
    lablx2calc->setText(stemp);
    stemp = QString("%1").arg(niter,2);
    lablx2niter->setText(stemp);

}
