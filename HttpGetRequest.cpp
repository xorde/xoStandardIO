#include "HttpGetRequest.h"
#include <QNetworkReply>
#include <QNetworkRequest>


HttpGetRequest::HttpGetRequest(QObject *parent) : ComponentBase ("HttpGetRequest", "HttpGetRequest", parent)
{

    createInput("url", m_url);
    createOutput("response", m_response);
}

void HttpGetRequest::objectReceiveEvent(QString name)
{
    if(name == "url")
    {
        QNetworkRequest request;
        request.setUrl(QUrl(m_url));

        manager->get(request);
    }
}

void HttpGetRequest::onCreate()
{
    manager = new QNetworkAccessManager();
    connections << connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply)
    {
        if(reply->error()) { qDebug() << "HttpGetRequest::ERROR" << reply->errorString(); return; }

        m_response = reply->readAll();
    });
}

void HttpGetRequest::onDestroy()
{
        for(auto& connection : connections) disconnect(connection);

    delete manager;
    manager = nullptr;
}
