#ifndef MYCAM_H
#define MYCAM_H

#include <QMainWindow>
#include <QGraphicsScene>
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
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    Ui::MyCam *ui;
    QGraphicsScene *scene;
    int m_dx;
    int m_dy;
    QPointF offset, mousePos;
    QRectF mouseBox;
    bool mousePosJudge(QMouseEvent*);
};

#endif // MYCAM_H
