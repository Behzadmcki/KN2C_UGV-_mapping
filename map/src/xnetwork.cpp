#include "xnetwork.h"

XNetwork::XNetwork(QObject *parent) : QObject(parent)
{
    _socket=new QUdpSocket(this);
    connect(_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}



void XNetwork::Send(QByteArray data)
{
    _socket->flush();
    _socket->writeDatagram(data,bot_hostaddess,bot_port);


}



void XNetwork::Set_clientIP(QString MY_IP, long port)
{
    bot_hostaddess.setAddress(MY_IP);
    bot_port=port;
}



void XNetwork::Set_serverIP(QString MY_IP, long port)
{
    server_hostaddess.setAddress(MY_IP);
    server_port=port;
    _socket->bind(server_hostaddess,server_port);

}



QByteArray XNetwork::Get_data()
{
    return resive_data_reg;
}



int XNetwork::Get_data_size()
{
    return resive_data_reg.size();
}

bool XNetwork::net_is_connect()
{
    return _socket->isOpen();
}


void XNetwork::readyRead()
{
    resive_data_reg.resize(_socket->pendingDatagramSize());
    _socket->readDatagram(resive_data_reg.data(),_socket->pendingDatagramSize());
    _socket->flush();
   emit reseived_data();

}
