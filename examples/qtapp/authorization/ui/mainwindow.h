#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QNetworkReply>

class DownloadManager;
class QPushButton;
class QTextEdit;
class QLineEdit;
class AuthHttpRequest;
class NetworkError;

/*
1 在线激活                         V
2 导出机器码
3 日志写入读取类
4 自动升级线程
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();

private:
    void addConnections();
    bool checkSSl();

public slots:
    void onActivated(bool b);
    void onFileDownDone(bool res, QString savedPaths, QString errors);
    void onAuth(QString res);
    void onVersionPush();
    void onUpdate();

    void onPushDone(QNetworkReply*);
    void onPushError(QNetworkReply::NetworkError);

    void sslErrors(const QList<QSslError> &errors);

private:
    QPushButton *m_btnAutoActivate;
    QPushButton *m_btnExportMachineId;
    QPushButton *m_btnImportKey;
    QPushButton *m_btnGetNewVersion;
    QPushButton *m_btnShowLog;
    QLineEdit * m_Url;
    QPushButton *m_btnVersionPush;

    QTextEdit *m_txtShow;

    DownloadManager *manager;
    AuthHttpRequest *auth;
    QNetworkAccessManager m_manager;
    QNetworkReply *m_currentPush;
};
#endif // MAINWINDOW_H
