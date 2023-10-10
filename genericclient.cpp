#include "genericclient.h"

GenericClient::GenericClient(QObject *parent,const QString &host,quint16 port) : QObject(parent)
{

    connected = false;
    myTcpSocket = new QTcpSocket(this);
    myTcpSocket->connectToHost(host,port);
    connect(myTcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(myTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),parent,
            SLOT(slotServerError(QAbstractSocket::SocketError)));
    //connect(myTcpSocket,SIGNAL(disconnected()),parent,SLOT(slotDisconnected()));
    connect(myTcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    connect(myTcpSocket,SIGNAL(readyRead()),this,SLOT(slotReadLine()));

}


void GenericClient::slotConnected()
{
    connected = true;
}


void GenericClient::slotDisconnected()
{
    connected = false;
}


void GenericClient::slotReadLine()
{

    while(myTcpSocket->canReadLine())
    {
        myTcpSocket->readLine(line,300);
    }
    lineQstring.clear();
    lineQstring.append(line);
    emit newLine(lineQstring);

}


bool GenericClient::slotConnectStatus()
{
    return(connected);
}


void GenericClient::sendText(QString stemp)
{
    myTcpSocket->write(stemp.toLatin1());
    //qDebug() << stemp;
    myTcpSocket->flush();
}
