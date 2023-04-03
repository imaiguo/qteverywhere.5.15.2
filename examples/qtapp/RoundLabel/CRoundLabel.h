#pragma once

#include <QLabel>
#include <QPainter>

class CRoundLabel : public QLabel
{
    Q_OBJECT
    
public:
    CRoundLabel(QWidget *parent = 0);
    ~QRoundLabel();
protected:
    void painEvent(QPaintEvent* e);
}