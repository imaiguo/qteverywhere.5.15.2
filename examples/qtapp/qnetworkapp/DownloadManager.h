#pragma once

#include <QtCore>
#include <QtNetwork>

#include <cstdio>

QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

using namespace std;

class DownloadManager: public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QVector<QNetworkReply *> currentDownloads;

public:
    DownloadManager();
    void doDownload(const QUrl &url);
    static QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);
    static bool isHttpRedirect(QNetworkReply *reply);
    static void setPath(const QString dir);
    static const QString getPath();

public slots:
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);

public:
    static QString m_path;
};
