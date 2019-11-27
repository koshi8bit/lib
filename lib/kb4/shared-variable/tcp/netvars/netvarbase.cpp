#include "netvarbase.h"
#include "initnvserver.h"
#include "initnvclient.h"




NetVarBase::NetVarBase(QString networkName) : QObject(nullptr)
{
    _value.clear();
    this->name = networkName.toUtf8();
    if(!InitNVServer::tcpserver && !InitNVClient::tcpclient){
        nvDebug << "Initialisation is required to use network variables. Try:";
        nvDebug << "InitNVServer s(port); or InitNVClient c(ip,port); in main() function.";
        nvDebug << networkName << "is invalid.";
        return;
    }
    if(VarsContainer::localVarsContains(this)){
         nvDebug << networkName << "is already exist.";
         nvDebug << networkName << "is invalid.";
         return;
    }
    VarsContainer::localVars.append(this);
}

NetVarBase::~NetVarBase()
{

}

bool NetVarBase::operator==(NetVarBase &other)
{
    return name == other.name;
}

void NetVarBase::updateNewValue(QVariant value)
{
    this->_value = value;
    emit valueChanged();
}

void NetVarBase::ask()
{
    if(InitNVServer::tcpserver){
        InitNVServer::askAll(name);
    }else if(InitNVClient::tcpclient){
        if(InitNVClient::tcpclient->state() == QAbstractSocket::ConnectedState){
            InitNVClient::ask(name);
        }else{
            nvDebug << "Could not ask. Client socket is not connected";
        }
    }else{
        //TODO:
    }
}

void NetVarBase::send()
{
    if(InitNVServer::tcpserver){
        InitNVServer::sendToAll(name,_value);
    }else if(InitNVClient::tcpclient){
        if(InitNVClient::tcpclient->state() == QAbstractSocket::ConnectedState){
            InitNVClient::sendValue(name,_value);
        }else{
            nvDebug << "Could not send. Client socket is not connected";
        }
    }else{
        //TODO:
    }
}
