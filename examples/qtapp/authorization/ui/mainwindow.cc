
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QLineEdit>

#include "mainwindow.h"
#include "machineid/GetCpuIndex.h"
#include "netservice/DownloadManager.h"
#include "netservice/AuthHttpRequest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    setFixedSize(800,400);

    manager =  new DownloadManager();
    manager->setPath(QString("D:/devtools/Qt/downfile"));

    setWindowIcon(QPixmap(":/image/favicon.png"));

    auth = new AuthHttpRequest();
}

MainWindow::~MainWindow(){

}


void MainWindow::initUI()
{
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
    

    m_txtShow = new QTextEdit(this);
    m_txtShow->move(200,70);
    m_txtShow->setReadOnly(true);
    m_txtShow->setFixedSize(500,300);
    m_txtShow->show();

    m_Url = new QLineEdit(this);
    m_Url->move(200,30);
    m_Url->setFixedSize(500,30);
    m_Url->show();
    m_Url->setText("http://127.0.0.1:3000/");

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
    connect(m_btnAutoActivate,&QAbstractButton::clicked,this,&MainWindow::onActivated);
    connect(m_btnGetNewVersion,&QAbstractButton::clicked,this,&MainWindow::onUpdate);
    connect(manager,&DownloadManager::fileDownDone,this,&MainWindow::onFileDownDone);
    connect(auth,&AuthHttpRequest::AuthResult,this,&MainWindow::onAuth);
}

void MainWindow::onActivated(bool b){
    m_txtShow->append(u8"获取到CPU序列号:" + QString(GWTools::GetCpuIndex().c_str()));

    qDebug()<<m_Url->text();
    auth->Auth(m_Url->text());
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

void MainWindow::onAuth(QString res){
    m_txtShow->append(u8"授权返回:" + res);
}