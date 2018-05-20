#ifndef MYCAM_H
#define MYCAM_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent*);

private:
    Ui::MyCam *ui;
    QGraphicsScene *scene;
    int m_dx, m_dy;
    bool m_judge;
    void mousePosJudge(QMouseEvent*);
};

#endif // MYCAM_H
