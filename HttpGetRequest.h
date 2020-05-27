#ifndef HTTPGETREQUEST_H
#define HTTPGETREQUEST_H

#include "ComponentBase.h"
#include <QNetworkAccessManager>

class HttpGetRequest : public ComponentBase
{
public:
    HttpGetRequest(QObject* parent = nullptr);

private:
    xoString m_url;
    xoString m_response;

protected:
    virtual void objectReceiveEvent(QString name) override;
    virtual void onCreate() override;
    virtual void onDestroy() override;

private:
    QNetworkAccessManager* manager = nullptr;

    QList<QMetaObject::Connection> connections;

};

#endif // HTTPGETREQUEST_H
