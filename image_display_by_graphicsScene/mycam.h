#ifndef MYCAM_H
#define MYCAM_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class MyCam;
}

class MyCam : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyCam(QWidget *parent = 0);
    ~MyCam();

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

private:
    Ui::MyCam *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *frame;
    QGraphicsRectItem *selection;
    QPixmap image;
    QPointF offset;
    QRectF mouseBox;
    QPen qpen;
    int m_dx;
    int m_dy;
    bool mousePosJudge(QMouseEvent*);

private slots:
    void saveImage();
    void slotDrawFrame();

signals:
    void sigDrawFrame();
};

#endif // MYCAM_H
