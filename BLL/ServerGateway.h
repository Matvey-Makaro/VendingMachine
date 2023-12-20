#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QTcpServer>
#include <QVector>
#include <QJsonArray>
#include "Entities/StatisticItem.h"

class ServerGateway : public QObject
{
    Q_OBJECT
public:
    explicit ServerGateway(QObject *parent = nullptr);

signals:
    void SetItemSignal(QString item, int price, int slot);
    void SetItemPriceSignal(QString item, int price);
    void SetItemSlotSignal(QString item, int slot);
    void DeleteItemSignal(QString item);
    void BlockItemSignal(QString item);
    void UnblockItemSignal(QString item);
    void GetCurrBalanceSignal();
    void SetBalanceSignal(int balance);
    void GetStatisticSignal();
    void GetErrorSignal();

public slots:
    void Run();
    void SendStatistic(QVector<StatisticItem> statistics);
    void SendBalance(int balance);
    void SendError(int code);


private slots:
    void OnNewConnection();
    void OnReadyRead();

private:
    void ParseRequest(const QJsonObject& obj);
    void HandleSetItem(const QJsonObject& params);
    void HandleSetItemPrice(const QJsonObject& params);
    void HandleSetItemSlot(const QJsonObject& params);
    void HandleDeleteItem(const QJsonObject& params);
    void HandleBlockItem(const QJsonObject& params);
    void HandleUnblockItem(const QJsonObject& params);
    void HandleGetCurrBalance(const QJsonObject& params);
    void HandleSetBalance(const QJsonObject& params);
    void HandleGetStatistic(const QJsonObject& params);
    void HandleGetError(const QJsonObject& params);

    QJsonArray ToJson(const QVector<StatisticItem>& statisticItems) const;
    QJsonObject ToJson(const StatisticItem& statItem) const;

private:
    QTcpServer* _tcpServer;
    QTcpSocket* _socket;
};
using ServerGatewayShp = QSharedPointer<ServerGateway>;
