#pragma once

#include <QLabel>
#include <QPainter>

class CRoundExLabel : public QLabel
{
    Q_OBJECT
public:
    CRoundExLabel(QWidget *parent = 0);
    ~CRoundExLabel();
    void SetString(QString& str);
    
protected:
    void painEvent(QPaintEvent* e);

private:
    QString strName;
};

