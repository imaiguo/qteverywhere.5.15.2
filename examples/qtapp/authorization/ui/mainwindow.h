#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


class DownloadManager;
class QPushButton;
class QTextEdit;
class QLineEdit;
class AuthHttpRequest;

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
    void onUpdate();
    bool checkSSl();

public slots:
    void onActivated(bool b);
    void onFileDownDone(bool res, QString savedPaths, QString errors);
    void onAuth(QString res);

private:
    QPushButton *m_btnAutoActivate;
    QPushButton *m_btnExportMachineId;
    QPushButton *m_btnImportKey;
    QPushButton *m_btnGetNewVersion;
    QPushButton *m_btnShowLog;
    QLineEdit * m_Url;

    QTextEdit *m_txtShow;

    DownloadManager *manager;
    AuthHttpRequest *auth;
};
#endif // MAINWINDOW_H
