
#include <QPainter>
#include <QFileDialog>
#include <QMutex>
#include <QMutexLocker>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDateTime>
#include <QMouseEvent>

#include "ScreenWidget.h"

#define STRDATETIME qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

ScreenWidget::ScreenWidget(QWidget *parent) : QWidget(parent){
    m_menu = new QMenu(this);
    m_menu->addAction("保存截图", this, &ScreenWidget::saveScreenCrop);
    m_menu->addAction("截图另存", this, &ScreenWidget::saveScreenCropToPath);
    m_menu->addAction("保存全屏", this, &ScreenWidget::saveFullScreen);
    m_menu->addAction("全屏另存", this, &ScreenWidget::saveFullToPath);
    m_menu->addAction("退出截图", this, &ScreenWidget::hide);

    //取得屏幕大小
    m_screen = new Screen(QApplication::desktop()->size());
    //保存全屏图像
    m_fullScreen = new QPixmap();
}

void ScreenWidget::paintEvent(QPaintEvent *){
    int x = m_screen->getLeftUp().x();
    int y = m_screen->getLeftUp().y();
    int w = m_screen->getRightDown().x() - x;
    int h = m_screen->getRightDown().y() - y;

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPixmap(0, 0, *m_bgScreen);

    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, m_fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawText(x + 2, y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )")
                     .arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));
}

void ScreenWidget::showEvent(QShowEvent *){
    QPoint point(-1, -1);
    m_screen->setStart(point);
    m_screen->setEnd(point);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    *m_fullScreen = m_fullScreen->grabWindow(QApplication::desktop()->winId(), 0, 0, m_screen->width(), m_screen->height());
#else
    QScreen *pscreen = QApplication::primaryScreen();
    *m_fullScreen = pscreen->grabWindow(QApplication::desktop()->winId(), 0, 0, m_screen->width(), m_screen->height());
#endif

    //设置透明度实现模糊背景
    QPixmap pix(m_screen->width(), m_screen->height());
    pix.fill((QColor(160, 160, 160, 200)));
    m_bgScreen = new QPixmap(*m_fullScreen);
    QPainter p(m_bgScreen);
    p.drawPixmap(0, 0, pix);
}

void ScreenWidget::saveScreenCrop(){
    int x = m_screen->getLeftUp().x();
    int y = m_screen->getLeftUp().y();
    int w = m_screen->getRightDown().x() - x;
    int h = m_screen->getRightDown().y() - y;

    QString fileName = QString("%1/screen_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    m_fullScreen->copy(x, y, w, h).save(fileName, "png");
    hide();
}

void ScreenWidget::saveFullScreen(){
    QString fileName = QString("%1/full_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    m_fullScreen->save(fileName, "png");
    hide();
}

void ScreenWidget::saveScreenCropToPath(){
    QString name = QString("%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        int x = m_screen->getLeftUp().x();
        int y = m_screen->getLeftUp().y();
        int w = m_screen->getRightDown().x() - x;
        int h = m_screen->getRightDown().y() - y;
        m_fullScreen->copy(x, y, w, h).save(fileName, "png");
        hide();
    }
}

void ScreenWidget::saveFullToPath(){
    QString name = QString("%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");
    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        m_fullScreen->save(fileName, "png");
        hide();
    }
}

void ScreenWidget::mouseMoveEvent(QMouseEvent *e){
    if (m_screen->getStatus() == Screen::SELECT) {
        m_screen->setEnd(e->pos());
    } else if (m_screen->getStatus() == Screen::MOV) {
        QPoint p(e->x() - m_movePos.x(), e->y() - m_movePos.y());
        m_screen->move(p);
        m_movePos = e->pos();
    }

    this->update();
}

void ScreenWidget::mousePressEvent(QMouseEvent *e){
    int m_status = m_screen->getStatus();

    if (m_status == Screen::SELECT) {
        m_screen->setStart(e->pos());
    } else if (m_status == Screen::MOV) {
        if (m_screen->isInArea(e->pos()) == false) {
            m_screen->setStart(e->pos());
            m_screen->setStatus(Screen::SELECT);
        } else {
            m_movePos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }

    this->update();
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent *){
    if (m_screen->getStatus() == Screen::SELECT) {
        m_screen->setStatus(Screen::MOV);
    } else if (m_screen->getStatus() == Screen::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}

void ScreenWidget::contextMenuEvent(QContextMenuEvent *){
    this->setCursor(Qt::ArrowCursor);
    m_menu->exec(cursor().pos());
}
