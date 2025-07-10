
#include <QtCore>
#include <QtNetwork>

#include <cstdio>

#include "DownloadManager.h"


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    DownloadManager manager;
    manager.setPath(QString("C:/QtProc/QGet"));

    QStringList urllist;
    urllist.append("https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png");
    urllist.append("http://www.zzbaike.com/w/images/c/cc/Http_img.jpg");

    for(QString url:urllist){
        QUrl fileurl = QUrl::fromEncoded(url.toLocal8Bit());
        manager.doDownload(fileurl);
    }

    app.exec();
}
