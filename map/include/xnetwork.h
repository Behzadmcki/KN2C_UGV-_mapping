#ifndef XNETWORK_H
#define XNETWORK_H

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <linux/joystick.h>
#include <QDebug>

class XNetwork : public QObject
{

    Q_OBJECT
public:
    explicit XNetwork(QObject *parent = 0);
    void Send(QByteArray data);
    void Set_clientIP(QString MY_IP, long port);     //set xnet_socket IP & port
    void Set_serverIP(QString MY_IP, long port);     //set xnet_socket IP
    QByteArray Get_data();
    int Get_data_size();
    bool net_is_connect();

signals:
    void reseived_data();

public slots:
     void readyRead();

private:
    QUdpSocket* _socket;
    QByteArray resive_data_reg;

    QHostAddress server_hostaddess;
    long server_port;

    QHostAddress bot_hostaddess;
    long bot_port;

};

#endif // XNETWORK_H
