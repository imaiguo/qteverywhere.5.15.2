
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QLineEdit>
#include <QFile>

#include "MainWindow.h"
#include "DownloadManager.h"
#include "AuthHttpRequest.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setFixedSize(800,400);

    manager =  new DownloadManager();
    manager->setPath(QString("D:/devtools/Qt/downfile"));

    setWindowIcon(QPixmap(":/image/favicon.png"));

    auth = new AuthHttpRequest();
}

MainWindow::~MainWindow(){

}


void MainWindow::initUI(){
    int xpos=30, ypox=30;
    m_btnAutoActivate = new QPushButton(this);
    m_btnAutoActivate->move(xpos,ypox);
    m_btnAutoActivate->setText(u8"获取CPU序列号");
    m_btnAutoActivate->show();

    ypox+=40;
    m_btnExportMachineId = new QPushButton(this);
    m_btnExportMachineId->move(xpos,ypox);
    m_btnExportMachineId->setText(u8"导出机器码");
    m_btnExportMachineId->show();

    ypox+=40;
    m_btnImportKey = new QPushButton(this);
    m_btnImportKey->move(xpos,ypox);
    m_btnImportKey->setText(u8"导入激活码");
    m_btnImportKey->show();

    ypox+=40;
    m_btnShowLog = new QPushButton(this);
    m_btnShowLog->move(xpos,ypox);
    m_btnShowLog->setText(u8"日志管理");
    m_btnShowLog->show();

    ypox+=40;
    m_btnGetNewVersion = new QPushButton(this);
    m_btnGetNewVersion->move(xpos,ypox);
    m_btnGetNewVersion->setText(u8"检查升级");
    m_btnGetNewVersion->show();
    
    
    ypox+=40;
    m_btnVersionPush = new QPushButton(this);
    m_btnVersionPush->move(xpos,ypox);
    m_btnVersionPush->setText(u8"版本新增");
    m_btnVersionPush->show();

    m_txtShow = new QTextEdit(this);
    m_txtShow->move(200,70);
    m_txtShow->setReadOnly(true);
    m_txtShow->setFixedSize(500,300);
    m_txtShow->show();

    m_Url = new QLineEdit(this);
    m_Url->move(200,30);
    m_Url->setFixedSize(500,30);
    m_Url->show();
    m_Url->setText("https://shop.uniontech.tech:8000/main/v1/versionpush");
}

void MainWindow::init(){
    addConnections();
    checkSSl();
}

bool MainWindow::checkSSl(){
    QString sRes = u8"QSslSocket version: " + QSslSocket::sslLibraryBuildVersionString();
    m_txtShow->append(sRes);
    
    sRes = QSslSocket::supportsSsl() ? u8"可用" : u8"不可用";
    sRes = u8"OpenSSL功能使能情况:" + sRes;
    m_txtShow->append(sRes);
    return QSslSocket::supportsSsl();
}

void MainWindow::addConnections(){
    connect(m_btnAutoActivate, &QAbstractButton::clicked, this, &MainWindow::onActivated);
    connect(m_btnGetNewVersion, &QAbstractButton::clicked,this, &MainWindow::onUpdate);
    connect(manager, &DownloadManager::fileDownDone,this, &MainWindow::onFileDownDone);
    connect(auth, &AuthHttpRequest::AuthResult, this, &MainWindow::onAuth);
    connect(m_btnVersionPush, &QAbstractButton::clicked, this, &MainWindow::onVersionPush);
}

void MainWindow::onActivated(bool b){
    // m_txtShow->append(u8"获取到CPU序列号:" + QString(GWTools::GetCpuIndex().c_str()));

    qDebug()<<m_Url->text();
    auth->Auth(m_Url->text());
}


void MainWindow::onVersionPush(){
    QString url = m_Url->text();
    m_txtShow->append(u8"开始推送版本...");
    QString filePath = "abc.zip";

    if(!QFile::exists(filePath)){
        m_txtShow->append(u8"文件不存在");
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 普通文本部分
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"data\""));
    textPart.setBody(u8"qg+dwCsJAoNGx4zkBikxMDrya5CTvbLx2jn7CWX4QhDxxphZx3qWEoCDh/f4l4i47NHK3RUsabMkZLBQoAF01S1KdqaUO3xEZVW6XXAezgNg34ba2abfkRvCLnccJHeAvSly6pIR+W8dfcZXM3syKLhyFh8o0MthP62pEg1GWm0=S8jAp13NfiBa0ydpWPbRGjtKx69v9NkfVXpz/9+rg4kbNRghpbt/f+ciSslQdqBpf8aBCqtMDkAYXgIRLbLqPqnV5xRzduPMNM2f1xrfGQvB2CNKCxWjWfWwRUwqG4DkWQq1ngXHkl0Wmibvf/6T6LOg+4Usc8bqObop0BhySVk=xhUcBLLjHf+uOHNQcp98TxURYAGQ5n3aeUbLrnZOJgPvdfHLkTG/wQFn8SslsMVaSRZTMa8QbxbaAFdyZevQsMv8EVUyJmCzGt9L+rLEbhDSme8ub6qy4Z8Z+GD1JdUViwrFgHdvR3ldd0NTn+D267PnaN4fQU/Vp8vbTZfB0k0=qEqLjBawCZZRLEvtMnjpcJw5zgtbSUADR/FWp8+pQx/ekZzA9gEiTHQoxkUKTsRxxjvnwRieEcwktm7dYzWFxNpgSI8M2kamBfv5wrSNH4AtnUbgzybMePO00uyx82cKwg7AVl2hM3OqX7f2NY4iCFYufe/fWd7sBbP1uSrxEL0=");
    multiPart->append(textPart);

    // 文件部分
    QFile *file = new QFile(filePath);
    if(!file->open(QIODevice::ReadOnly)){
         m_txtShow->append(u8"文件不存在");
         return;
    }
    file->setParent(multiPart);

    QHttpPart filePart;
    filePart.setBodyDevice(file);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/zip"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(("form-data; name=\"newversion\"; filename=\"abc.zip\" ")));

    multiPart->append(filePart);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    m_currentPush = m_manager.post(request, multiPart);
    multiPart->setParent(m_currentPush);

    connect(&m_manager, &QNetworkAccessManager::finished, this, &MainWindow::onPushDone);

#if QT_CONFIG(ssl)
    connect(m_currentPush, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif
}


void MainWindow::sslErrors(const QList<QSslError> &sslErrors){
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors){
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
        m_txtShow->append(u8"ssl error");
    }
#else
    Q_UNUSED(sslErrors);
#endif
}

void MainWindow::onPushError(QNetworkReply::NetworkError error){

}

void MainWindow::onUpdate(){
    QString f1="https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png";
    QString f2="http://www.zzbaike.com/w/images/c/cc/Http_img.jpgg";
    m_txtShow->append(u8"开始下载文件[\n" + f1 + "\n" + f2 + "\n].");
    QStringList urllist;
    urllist.append(f1);
    urllist.append(f2);

    for(QString url:urllist){
        QUrl fileurl = QUrl::fromEncoded(url.toLocal8Bit());
        manager->doDownload(fileurl);
    }
}

void MainWindow::onFileDownDone(bool res, QString savedPaths, QString errors){
    QString str = u8"下载文件[";
    str += savedPaths;
    if(res){
        str += u8"]成功";
        m_txtShow->append(str);
    }else{
        str += u8"]失败";
        str += u8"errros:";
        str += errors;
        m_txtShow->append(str);
    }
}

void MainWindow::onPushDone(QNetworkReply *reply){
    QUrl url = reply->url();
    QString errors,path = url.toEncoded().constData();
    if (reply->error()) {
        m_txtShow->append(u8"报错:" + reply->errorString());
    }
    QString result = reply->readAll();

    m_txtShow->append(u8"接收返回:" + result);
}

void MainWindow::onAuth(QString res){
    m_txtShow->append(u8"授权返回:" + res);
}
