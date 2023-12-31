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
    segindx = 0;

    // Read the saved settings
    mwwidth = 480;
    mwheight = 480;
    readSettings();
    //qDebug() << "waypoint file name" << lastwayfilename;
    //qDebug() << "segment file name" << lastsegfilename;

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

    lab21 = new QLabel("From WP");
    labfwp = new QLabel;
    labfwp->setFont(QFont("Helvetica",14,QFont::Bold));
    labfwp->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    lab22 = new QLabel("To WP");
    labtwp = new QLabel;
    labtwp->setFont(QFont("Helvetica",14,QFont::Bold));
    labtwp->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    prevseg = new QPushButton("Prev seg");
    connect(prevseg,SIGNAL(clicked()),this,SLOT(slotPrevSeg()));
    prevseg->setEnabled(false);
    nextseg = new QPushButton("Next seg");
    connect(nextseg,SIGNAL(clicked()),this,SLOT(slotNextSeg()));
    nextseg->setEnabled(false);
    revseg = new QPushButton("Reverse seg");
    connect(revseg,SIGNAL(clicked()),this,SLOT(slotRevSeg()));
    revseg->setEnabled(false);

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
    maingroup->addWidget(lab21,15,0);
    maingroup->addWidget(lab22,15,1);
    maingroup->addWidget(labfwp,16,0);
    maingroup->addWidget(labtwp,16,1);
    maingroup->addWidget(prevseg,17,0);
    maingroup->addWidget(nextseg,17,1);
    maingroup->addWidget(revseg,17,2);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(maingroup);

    // Finalize the GUI
    window->setLayout(layout);
    setCentralWidget(window);

    // Build the network client
    client = new GenericClient(this,host,port);
    connect(client,SIGNAL(newLine(QString)),this,SLOT(slotNewData(QString)));

    // Load waypoint and segment files if specified
    if (!lastwayfilename.isEmpty()&&!lastwayfilename.isNull())
    {
        wayfilename = lastwayfilename;
        loadWaypoints();
        if (validwayfile&&!lastsegfilename.isEmpty()&&!lastsegfilename.isNull())
        {
            segfilename = lastsegfilename;
            loadSegments();
        }
    }
    if (validsegfile)
    {
        prevseg->setEnabled(true);
        nextseg->setEnabled(true);
        if (segments[segindx].reversible) revseg->setEnabled(true);
        else revseg->setEnabled(false);
        labfwp->setText(segments[segindx].name1);
        labtwp->setText(segments[segindx].name2);
    }
    if (!validsegfile)
    {
        segindx = 0;
        labfwp->setText("----");
        labtwp->setText("----");
    }

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
    lastwayfilename = settings.value("wayfilename","").toString();
    lastsegfilename = settings.value("segfilename","").toString();
    segindx = settings.value("segindx",0).toInt();

}

void MainWindow::writeSettings()
{

    QSettings settings("nasa","navdemo");
    settings.setValue("host",host);
    settings.setValue("port",port);
    settings.setValue("mwwidth",width());
    settings.setValue("mwheight",height());
    if (validwayfile) settings.setValue("wayfilename",wayfilename);
    else settings.setValue("wayfilename","");
    if (validsegfile) settings.setValue("segfilename",segfilename);
    else settings.setValue("segfilename","");
    settings.setValue("segindx",segindx);

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
    closeSegAct = new QAction("Close segment file",this);
    connect(closeSegAct,SIGNAL(triggered()),this,SLOT(slotCloseSegments()));
    closeSegAct->setEnabled(false);
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

void MainWindow::slotCloseSegments()
{

    segments.clear();
    validsegfile = false;
    fileMenu->removeAction(closeSegAct);
    closeSegAct->setEnabled(false);
    stemp = "Open segment file";
    openSegAct->setText(stemp);
    fileMenu->insertAction(exitAct,openSegAct);
    openSegAct->setEnabled(true);
    closeWayAct->setEnabled(true);
    prevseg->setEnabled(false);
    nextseg->setEnabled(false);
    revseg->setEnabled(false);
    labfwp->setText("----");
    labtwp->setText("----");

}

void MainWindow::slotGetWaypoints()
{

    // Prompt user for the desired waypoint filename
    wayfilename = QFileDialog::getOpenFileName(this,"Select a waypoint file",
                                              ".",
                                              "Waypoint files (*.way)");
    if (wayfilename.isNull()||wayfilename.isEmpty()) return;
    loadWaypoints();

}


void MainWindow::loadWaypoints()
{

    // Ingest the contents of the waypoint file
    int iwpflag = ingestWaypoints();

    // Cannot open the waypoint file
    if (iwpflag==1)
    {
        validwayfile = false;
        waypoints.clear();
        QMessageBox msgBox;
        stemp = "Cannot open specified waypoint file\n";
        stemp.append(wayfilename);
        msgBox.setText(stemp);
        msgBox.exec();
    }

    // Waypoint file has fewer than two waypoints
    else if (iwpflag==2)
    {
        validwayfile = false;
        waypoints.clear();
        QMessageBox msgBox;
        stemp = "Specified waypoint file\n";
        stemp.append(wayfilename);
        stemp.append("\nis invalid because it contains fewer than two waypoints.");
        msgBox.setText(stemp);
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
            stemp = "Specified waypoint file\n";
            stemp.append(wayfilename);
            stemp.append("\nis invalid because one or more latitudes is out of bounds.");
            msgBox.setText(stemp);
            msgBox.exec();
        }
        else if (ivalwpflag==2)
        {
            validwayfile = false;
            waypoints.clear();
            QMessageBox msgBox;
            stemp = "Specified waypoint file\n";
            stemp.append(wayfilename);
            stemp.append("\nis invalid because one or more longitudes is out of bounds.");
            msgBox.setText(stemp);
            msgBox.exec();
        }
        else if (ivalwpflag==3)
        {
            validwayfile = false;
            waypoints.clear();
            QMessageBox msgBox;
            stemp = "Specified waypoint file\n";
            stemp.append(wayfilename);
            stemp.append("\nis invalid because one or more waypoint names is repeated.");
            msgBox.setText(stemp);
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

    // Prompt user for the desired segment filename
    segfilename = QFileDialog::getOpenFileName(this,"Select a segment file",
                                              ".",
                                              "Segment files (*.seg)");
    if (segfilename.isNull()||segfilename.isEmpty()) return;
    loadSegments();

}


void MainWindow::loadSegments()
{

    // Ingest the contents of the segment file
    int isegflag = ingestSegments();

    // Segment file cannot be opened
    if (isegflag==1)
    {
        validsegfile = false;
        segments.clear();
        QMessageBox msgBox;
        msgBox.setText("Selected segment file cannot be opened");
        msgBox.exec();
    }

    // Segment file does not contain a valid segment
    else if (isegflag==2)
    {
        validsegfile = false;
        segments.clear();
        QMessageBox msgBox;
        msgBox.setText("Selected segment file is invalid\n"
                       "Contains no valid segments");
        msgBox.exec();
    }

    // Segment file has a record containing fewer than three words
    else if (isegflag==3)
    {
        validsegfile = false;
        segments.clear();
        QMessageBox msgBox;
        msgBox.setText("Selected segment file is invalid\n"
                       "One or more lines contains fewer than three words");
        msgBox.exec();
    }

    // Validate the segments
    else
    {

        int ivalsegflag = validateSegments();
        if (ivalsegflag==1)
        {
            validsegfile = false;
            segments.clear();
            QMessageBox msgBox;
            msgBox.setText("Selected segment file is invalid\n"
                           "One or more waypoint names does not match waypoint data");
            msgBox.exec();
        }
        else if (ivalsegflag==2)
        {
            validsegfile = false;
            segments.clear();
            QMessageBox msgBox;
            msgBox.setText("Selected segment file is invalid\n"
                           "One or more nav techniques is undefined");
            msgBox.exec();
        }
        else
        {
            validsegfile = true;
            segreversed = false;
            closeWayAct->setEnabled(false);
            fileMenu->removeAction(openSegAct);
            openSegAct->setEnabled(false);
            stemp = "Close segment file ";
            stemp.append(segfilename);
            closeSegAct->setText(stemp);
            fileMenu->insertAction(exitAct,closeSegAct);
            closeSegAct->setEnabled(true);
            prevseg->setEnabled(true);
            nextseg->setEnabled(true);
            revseg->setEnabled(true);
            labtwp->setText(segments[segindx].name1);
            labfwp->setText(segments[segindx].name2);
            latfrom = segments[segindx].lat1;
            lonfrom = segments[segindx].lon1;
            latto = segments[segindx].lat2;
            lonto = segments[segindx].lon2;
        }
    }

}


// Returns 0 if segments ingested normally
// Returns 1 if segment file could not be opened
// Returns 2 if segment contains fewer than one segment
// Returns 3 if any segment lines has fewer than four words
int MainWindow::ingestSegments()
{
    seg newsegment;
    QString stemp2,stemp3;
    QFile *segfile;

    // Clear (reset) the segment list
    segments.clear();

    // Open the waypoint file
    segfile = new QFile(segfilename);
    if (!(segfile->open(QIODevice::ReadOnly)))
            return(1);

    // Read the contents of the segment file
    bool notenoughfields = false;
    QTextStream instream(segfile);
    while(!instream.atEnd())
    {
        stemp = instream.readLine();
        stemp2 = stemp.section(' ',0,0);
        if (stemp2.length() == 0) notenoughfields = true;
        else newsegment.name1 = stemp2;
        stemp2 = stemp.section(' ',1,1);
        if (stemp2.length() == 0) notenoughfields = true;
        else newsegment.name2 = stemp2;
        stemp2 = stemp.section(' ',2,2);
        if (stemp2.length() == 0) notenoughfields = true;
        else newsegment.alt = (stemp2.toDouble())*FT2M;
        stemp2 = stemp.section(' ',3,3);
        if (stemp2.length() == 0) notenoughfields = true;
        else
        {
            stemp3 = stemp2.left(1);
            int cmpflag = QString::compare(stemp3,"y",Qt::CaseInsensitive);
            if (!cmpflag) newsegment.reversible = true;
            else newsegment.reversible = false;
        }
        stemp2 = stemp.section(' ',4,4);
        stemp3 = stemp2.left(4);
        if (stemp2.length()==0)  newsegment.nt = geodesic;
        else if (QString::compare(stemp3,"geod",Qt::CaseInsensitive) == 0)
            newsegment.nt = geodesic;
        else if (QString::compare(stemp3,"grea",Qt::CaseInsensitive) == 0)
            newsegment.nt = greatcircle;
        else if (QString::compare(stemp3,"loxo",Qt::CaseInsensitive) == 0)
            newsegment.nt = loxodrome;
        else
            newsegment.nt = undefined;
        segments.append(newsegment);
    }

    // Close the waypoint file
    segfile->close();

    // Segments with too few fields
    if (notenoughfields) return(3);

    // File has fewer than one segment
    else if (segments.size()<1) return(2);

    // Normal operation
    else return(0);

}


// Returns 0 if segments validated normally
// Returns 1 if one or more waypoint names could not be matched to the waypoint file
// Returns 2 if one or more segments has an undefined nav technique
int MainWindow::validateSegments()
{
    bool match1, match2;
    int i,j;

    // Match segment names with waypoints
    for (i=0;i<segments.size();i++)
    {
        match1 = false;
        match2 = false;
        for (j=0;j<waypoints.size();j++)
        {
            if (QString::compare(segments[i].name1,waypoints[j].name,Qt::CaseInsensitive) == 0)
            {
                segments[i].lat1 = waypoints[j].lat;
                segments[i].lon1 = waypoints[j].lon;
                match1 = true;
            }
            if (QString::compare(segments[i].name2,waypoints[j].name,Qt::CaseInsensitive) == 0)
            {
                segments[i].lat2 = waypoints[j].lat;
                segments[i].lon2 = waypoints[j].lon;
                match2 = true;
            }
        }
        if (!match1||!match2) return(1);
    }

    // Search for undefined nav technique
    for (i=0;i<segments.size();i++)
    {
        if (segments[i].nt == undefined) return(2);
    }

    // Return normal
    return(0);

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
    //qDebug() << segreversed;

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

    niter = 0;
    gettimeofday(&tmag1,NULL);
    if (validsegfile)
    {
        double xtd = xtdgeodesic(latfrom/DEG2RAD,lonfrom/DEG2RAD,latto/DEG2RAD,lonto/DEG2RAD,
                                 lat/DEG2RAD,lon/DEG2RAD,&niter);
        stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
        labgextd->setText(stemp);
    }
    else
    {
        labgextd->setText("----");
    }
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

    if (validsegfile)
    {
        double xtd = xtdgreatcircle(latfrom/DEG2RAD,lonfrom/DEG2RAD,latto/DEG2RAD,lonto/DEG2RAD,
                                    lat/DEG2RAD,lon/DEG2RAD);
        stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
        labgcxtd->setText(stemp);
    }
    else
    {
        labgcxtd->setText("----");
    }
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

    niter = 0;
    gettimeofday(&tmag1,NULL);

    if (validsegfile)
    {
        double xtd = xtdloxodrome(latfrom/DEG2RAD,lonfrom/DEG2RAD,latto/DEG2RAD,lonto/DEG2RAD,
                                  lat/DEG2RAD,lon/DEG2RAD,&niter);
        stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
        lablxxtd->setText(stemp);
    }
    else
    {
        lablxxtd->setText("----");
    }
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

    niter = 0;
    gettimeofday(&tmag1,NULL);

    if (validsegfile)
    {
        double xtd = xtdloxodrome2(latfrom/DEG2RAD,lonfrom/DEG2RAD,latto/DEG2RAD,lonto/DEG2RAD,
                                   lat/DEG2RAD,lon/DEG2RAD,&niter);
        stemp = QString("%1").arg(xtd*M2FT,6,'f',0);
        lablx2xtd->setText(stemp);
    }
    else
    {
        lablx2xtd->setText("----");
    }
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


void MainWindow::slotPrevSeg()
{
    if (segindx>0) segindx--;
    latfrom = segments[segindx].lat1;
    lonfrom = segments[segindx].lon1;
    latto = segments[segindx].lat2;
    lonto = segments[segindx].lon2;
    labfwp->setText(segments[segindx].name1);
    labtwp->setText(segments[segindx].name2);
    if (segments[segindx].reversible) revseg->setEnabled(true);
    else revseg->setEnabled(false);
    segreversed = false;
}


void MainWindow::slotNextSeg()
{
    if (segindx<(segments.size()-1)) segindx++;
    latfrom = segments[segindx].lat1;
    lonfrom = segments[segindx].lon1;
    latto = segments[segindx].lat2;
    lonto = segments[segindx].lon2;
    labfwp->setText(segments[segindx].name1);
    labtwp->setText(segments[segindx].name2);
    if (segments[segindx].reversible) revseg->setEnabled(true);
    else revseg->setEnabled(false);
    segreversed = false;
}


void MainWindow::slotRevSeg()
{
    segreversed = !segreversed;
    if (!segreversed)
    {
        latfrom = segments[segindx].lat1;
        lonfrom = segments[segindx].lon1;
        latto = segments[segindx].lat2;
        lonto = segments[segindx].lon2;
        labfwp->setText(segments[segindx].name1);
        labtwp->setText(segments[segindx].name2);
    }
    else
    {
        latfrom = segments[segindx].lat2;
        lonfrom = segments[segindx].lon2;
        latto = segments[segindx].lat1;
        lonto = segments[segindx].lon1;
        labfwp->setText(segments[segindx].name2);
        labtwp->setText(segments[segindx].name1);
    }
    //qDebug() << segreversed;
}

