#include "AuthHttpRequest.h"

AuthHttpRequest::AuthHttpRequest(){
    Init();
}

void AuthHttpRequest::Auth(QString url){
    m_manager.get(QNetworkRequest(QUrl(url)));
}

void AuthHttpRequest::sslErrors(const QList<QSslError> &sslErrors){
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void AuthHttpRequest::Init(){
    connect(&m_manager, &QNetworkAccessManager::finished,this, &AuthHttpRequest::replyFinished);
}

void AuthHttpRequest::replyFinished(QNetworkReply *reply){
    QUrl url = reply->url();
    if (reply->error()) {
        
        fprintf(stderr, "error: %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
        QString errors = qPrintable(reply->errorString());
        emit AuthResult(errors);
    } else {
        QString res = reply->readAll();
        emit AuthResult(res);
    }
    reply->deleteLater();
}
