
#include "DownloadManager.h"

QString DownloadManager::m_path;

DownloadManager::DownloadManager(){
    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::setPath(const QString dir){
    m_path = dir;
}

const QString DownloadManager::getPath(){
    return m_path;
}

void DownloadManager::doDownload(const QUrl &url){
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#if QT_CONFIG(ssl)
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url){
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if(getPath().isEmpty()){
        setPath(QDir::currentPath());
        qDebug()<<"file save path is ["<<getPath()<<"].";
    }

    basename = getPath() + "/" + basename;

    return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();
    return true;
}

bool DownloadManager::isHttpRedirect(QNetworkReply *reply){
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void DownloadManager::sslErrors(const QList<QSslError> &sslErrors){
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply *reply){
    qDebug()<<"------downloadFinished------";
    QUrl url = reply->url();
    QString errors,path = url.toEncoded().constData();
    if (reply->error()) {
        
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));

        errors = qPrintable(reply->errorString());
        emit fileDownDone(false,path,errors);
    } else {
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);

            emit fileDownDone(false,path,u8"地址重定向");
        } else {
            QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)) {
                printf("Download of %s succeeded (saved to %s)\n",
                       url.toEncoded().constData(), qPrintable(filename));
                emit fileDownDone(true,filename,errors);
            }else{
                emit fileDownDone(false,path,u8"保存文件失败");
            }
        }
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
        // all downloads finished
        // QCoreApplication::instance()->quit();
        qDebug()<<u8"所有文件都已下载完成";
    }
}
