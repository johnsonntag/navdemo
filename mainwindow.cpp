#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize variables
    validwayfile = false;
    validsegfile = false;

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

    labwayvalid = new QLabel();
    labwayvalid->setFont(QFont("Helvetica",10,QFont::Bold));
    labwayvalid->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    labsegvalid = new QLabel();
    labsegvalid->setFont(QFont("Helvetica",10,QFont::Bold));
    labsegvalid->setFrameStyle(QFrame::Panel|QFrame::Sunken);

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
    maingroup->addWidget(labwayvalid,14,0);
    maingroup->addWidget(labsegvalid,14,1);
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

    openWayAct = new QAction("Open waypoint file",this);
    connect(openWayAct,SIGNAL(triggered()),this,SLOT(slotGetWaypoints()));
    openWayAct->setEnabled(true);
    closeWayAct = new QAction("Close waypoint file",this);
    connect(closeWayAct,SIGNAL(triggered()),this,SLOT(slotCloseWaypoints()));
    closeWayAct->setEnabled(false);
    openSegAct = new QAction("Open segment file",this);
    connect(openSegAct,SIGNAL(triggered()),this,SLOT(slotGetSegments()));
    openSegAct->setEnabled(false);
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
    fileMenu->addAction(openWayAct);
    fileMenu->addAction(openSegAct);
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(maginfoAct);
    helpMenu->addAction(aboutAct);

}

void MainWindow::slotCloseWaypoints()
{

    waypoints.clear();
    validwayfile = false;
    fileMenu->removeAction(closeWayAct);
    closeWayAct->setEnabled(false);
    stemp = "Open waypoint file";
    stemp.append(wayfilename);
    openWayAct->setText(stemp);
    fileMenu->insertAction(openSegAct,openWayAct);
    openWayAct->setEnabled(true);
    openSegAct->setEnabled(false);

}

void MainWindow::slotGetWaypoints()
{

    // Prompt user for the desired waypoint filename
    wayfilename = QFileDialog::getOpenFileName(this,"Select a waypoint file",
                                              ".",
                                              "Waypoint files (*.way)");

    // Ingest the contents of the waypoint file
    int iwpflag = ingestWaypoints();
    //qDebug() << iwpflag << waypoints.size();
    //int i;
    //for (i=0;i<waypoints.size();i++)
    //{
    //    qDebug() << i << waypoints[i].name << waypoints[i].lat/DEG2RAD << waypoints[i].lon/DEG2RAD;
    //}

    // Cannot open the waypoint file
    if (iwpflag==1)
    {
        validwayfile = false;
        waypoints.clear();
        QMessageBox msgBox;
        msgBox.setText("Cannot open selected waypoint file");
        msgBox.exec();
    }

    // Waypoint file has fewer than two waypoints
    else if (iwpflag==2)
    {
        validwayfile = false;
        waypoints.clear();
        QMessageBox msgBox;
        msgBox.setText("Selected waypoint file is invalid\n"
                       "Contains fewer than two waypoints");
        msgBox.exec();
    }

    // Validate the newly ingested waypoints
    else
    {

        int ivalwpflag = validateWaypoints();
        if (ivalwpflag==1)
        {
            validwayfile = false;
            waypoints.clear();
            QMessageBox msgBox;
            msgBox.setText("Selected waypoint file is invalid\n"
                           "One or more latitudes is out of bounds");
            msgBox.exec();
        }
        else if (ivalwpflag==2)
        {
            validwayfile = false;
            waypoints.clear();
            QMessageBox msgBox;
            msgBox.setText("Selected waypoint file is invalid\n"
                           "One or more longitudes is out of bounds");
            msgBox.exec();
        }
        else if (ivalwpflag==3)
        {
            validwayfile = false;
            waypoints.clear();
            QMessageBox msgBox;
            msgBox.setText("Selected waypoint file is invalid\n"
                           "One or more waypoint names is repeated");
            msgBox.exec();
        }
        else
        {
            validwayfile = true;
            fileMenu->removeAction(openWayAct);
            openWayAct->setEnabled(false);
            stemp = "Close waypoint file ";
            stemp.append(wayfilename);
            closeWayAct->setText(stemp);
            fileMenu->insertAction(openSegAct,closeWayAct);
            closeWayAct->setEnabled(true);
            openSegAct->setEnabled(true);
        }
    }

}


// Returns 0 if waypoints ingested normally
// Returns 1 if waypoint file could not be opened
// Returns 2 if waypoint file contains fewer than two waypoints
int MainWindow::ingestWaypoints()
{
    wp newwaypoint;
    QString stemp2;
    QFile *wpfile;

    // Clear (reset) the waypoint list
    waypoints.clear();

    // Open the waypoint file
    wpfile = new QFile(wayfilename);
    if (!(wpfile->open(QIODevice::ReadOnly)))
            return(1);

    // Read the contents of the waypoint file
    QTextStream instream(wpfile);
    while(!instream.atEnd())
    {
        stemp = instream.readLine();
        newwaypoint.name = stemp.section(' ',0,0,QString::SectionSkipEmpty);
        stemp2 = stemp.section(' ',1,1,QString::SectionSkipEmpty);
        newwaypoint.lat = (stemp2.toDouble())*DEG2RAD;
        stemp2 = stemp.section(' ',2,2,QString::SectionSkipEmpty);
        newwaypoint.lon = (stemp2.toDouble())*DEG2RAD;
        waypoints.append(newwaypoint);
        //qDebug() << stemp;
    }

    // Close the waypoint file
    wpfile->close();

    // Fewer than two waypoints
    if (waypoints.size()<2)
        return(2);

    //Normal operation
    return(0);

}


// Returns 0 if waypoints are good
// Returns 1 if one or more latitudes are out of bounds
// Returns 2 if one or more longitudes are out of bounds
// Returns 3 if a waypoint name is used more than once
int MainWindow::validateWaypoints()
{
    int i,j,cmpflag;

    // Search for out-of-bounds lats and lons
    bool latoob = false;
    bool lonoob = false;
    for (i=0;i<waypoints.size();i++)
    {
        if (waypoints[i].lat>(PI/2.0)||waypoints[i].lat<(-PI>2.0)) latoob = true;
        if (waypoints[i].lon>=(2.0*PI)||waypoints[i].lon<(-PI)) lonoob = true;
    }

    // Search for repeated waypoint names
    bool wprepeat = false;
    for (i=0;i<(waypoints.size()-1);i++)
    {
        for (j=(i+1);j<waypoints.size();j++)
        {
            cmpflag = QString::compare(waypoints[i].name,waypoints[j].name,Qt::CaseInsensitive);
            if (!cmpflag) wprepeat = true;
        }
    }

    // Select return value
    if (latoob) return(1);  // one or more latitudes out of bounds
    else if (lonoob) return(2);  // one or more longitudes out of bounds
    else if (wprepeat) return(3);  // repeated waypoint (case insensitive)
    else return(0);

}


void MainWindow::slotGetSegments()
{

    qDebug() << "in slotGetSegments\n";

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
    updateWaySeg();

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

void MainWindow::updateWaySeg()
{

    // Set valid waypoint label
    if (validwayfile)
        labwayvalid->setText("Valid waypoint file");
    else
        labwayvalid->setText("No waypoint file");

    // Set valid segment label
    if (validsegfile)
        labsegvalid->setText("Valid segment file");
    else
        labsegvalid->setText("No segment file");

}
