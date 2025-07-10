#pragma once
#include <QtCore>
#include <QtNetwork>

class AuthHttpRequest : public QObject {
Q_OBJECT

public:
    AuthHttpRequest();
    void Auth(QString url);

private:
    QNetworkAccessManager m_manager;
    QNetworkReply * m_repy;

public slots:
    void replyFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);

private:
    void Init();


signals:
    void AuthResult(QString res);

};