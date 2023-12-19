#include <QThread>
#include <QTimer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include "ServerGateway.h"
#include "ServerCommunication/Requests.h"


ServerGateway::ServerGateway(QObject* parent) :
    QObject(parent)
{}

void ServerGateway::Run()
{
    QTimer::singleShot(1000, this, [this]()
    {
        emit BlockItemSignal("Hello world");
        QThread::sleep(2);
        emit BlockItemSignal("End");
    });

    _tcpServer = new QTcpServer(this);
    if(!_tcpServer->listen(QHostAddress::Any, 9000))
    {
        qDebug() << "ServerGateway::Run()" << !_tcpServer->listen();
    }

    connect(_tcpServer, &QTcpServer::newConnection, this, &ServerGateway::OnNewConnection);
}

void ServerGateway::OnNewConnection()
{
    qDebug() << "ServerGateway::OnNewConnection()";
    _socket = _tcpServer->nextPendingConnection();
    connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
    connect(_socket, &QTcpSocket::readyRead, this, &ServerGateway::OnReadyRead);
}

void ServerGateway::OnReadyRead()
{
    QByteArray byteArray = _socket->readAll();
    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(byteArray, &err);
    if(err.error != QJsonParseError::NoError)
        return;
    auto obj = doc.object();
    ParseRequest(obj);
    qDebug() << "Byte array:" << byteArray;
}

void ServerGateway::ParseRequest(const QJsonObject& obj)
{
    Request request;
    if (const QJsonValue v = obj["instructionType"]; v.isDouble())
        request = static_cast<Request>(v.toInt());
    else
        return;

    QJsonObject params = obj["params"].toObject();

    if(request == Request::SetItem)
        HandleSetItem(params);
    else if (request == Request::SetItemPrice)
        HandleSetItemPrice(params);
    else if (request == Request::SetItemSlot)
        HandleSetItemSlot(params);
    else if (request == Request::DeleteItem)
        HandleDeleteItem(params);
    else if (request == Request::BlockItem)
        HandleBlockItem(params);
    else if (request == Request::UnblockItem)
        HandleUnblockItem(params);
    else if (request == Request::GetCurrBalance)
        HandleGetCurrBalance(params);
    else if (request == Request::SetBalance)
        HandleSetBalance(params);
    else if (request == Request::GetStatistic)
        HandleGetStatistic(params);
    else if (request == Request::GetError)
        HandleGetError(params);
    else Q_ASSERT(false && "Unreachable");

}

void ServerGateway::HandleSetItem(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else return;

    int price;
    if (const QJsonValue v = params["price"]; v.isDouble())
        price = v.toInt();
    else return;

    int slot;
    if (const QJsonValue v = params["slot"]; v.isDouble())
        slot = v.toInt();
    else
        return;

    emit SetItemSignal(item, price, slot);
}

void ServerGateway::HandleSetItemPrice(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else return;

    int price;
    if (const QJsonValue v = params["price"]; v.isDouble())
        price = v.toInt();
    else
        return;
    emit SetItemPriceSignal(item, price);
}

void ServerGateway::HandleSetItemSlot(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else return;

    int slot;
    if (const QJsonValue v = params["slot"]; v.isDouble())
        slot = v.toInt();
    else
        return;
    emit SetItemSlotSignal(item, slot);
}

void ServerGateway::HandleDeleteItem(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else
        return;
    emit DeleteItemSignal(item);
}

void ServerGateway::HandleBlockItem(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else
        return;
    emit BlockItemSignal(item);
}

void ServerGateway::HandleUnblockItem(const QJsonObject& params)
{
    QString item;
    if (const QJsonValue v = params["item"]; v.isString())
        item = v.toString();
    else
        return;
    emit UnblockItemSignal(item);
}

void ServerGateway::HandleGetCurrBalance(const QJsonObject& params)
{
    emit GetCurrBalanceSignal();
}

void ServerGateway::HandleSetBalance(const QJsonObject& params)
{
    int balance;
    if (const QJsonValue v = params["balance"]; v.isDouble())
        balance = v.toInt();
    else
        return;
    emit SetBalanceSignal(balance);
}

void ServerGateway::HandleGetStatistic(const QJsonObject& params)
{
    emit GetStatisticSignal();
}

void ServerGateway::HandleGetError(const QJsonObject& params)
{
    emit GetErrorSignal();
}
