#ifndef SETUPGUI_H
#define SETUPGUI_H

#include <QDialog>
#include <QLineEdit>
#include <QIntValidator>
#include <QCheckBox>

class setupGui : public QDialog
{
    Q_OBJECT

public:
    //setupGui(QString *host,quint16 *port,QString *ilshost,quint16 *ilsport);
    setupGui(QString *host,quint16 *port);
    ~setupGui();

private:
    QLineEdit *hostedit;
    QLineEdit *portedit;
    QIntValidator *portval;
    QString *setuphost;
    quint16 *setupport;

private slots:
    void slotTestInputs();

};

#endif // SETUPGUI_H
