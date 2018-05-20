#include "mycam.h"
#include "ui_mycam.h"

MyCam::MyCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyCam)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap input("C:\\Users\\parkk\\Pictures\\lena.png");
    ui->graphicsView->resize(input.width(), input.height());
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->addPixmap(input);
}

MyCam::~MyCam()
{
    delete ui;
}

void MyCam::mousePosJudge(QMouseEvent* evt)
{
    QPointF clickedPoint = evt->windowPos();
    int dx = clickedPoint.x() - ui->graphicsView->pos().x();
    int dy = clickedPoint.y() - ui->graphicsView->pos().y();
    m_dx = dx;
    m_dy = dy;
    m_judge = dx > 0 && dx < ui->graphicsView->width() &&
              dy > 0 && dy < ui->graphicsView->height();
}

void MyCam::mousePressEvent(QMouseEvent* evt)
{
    mousePosJudge(evt);
    if (m_judge)
    {
        scene->addEllipse(m_dx, m_dy, 10, 10, QPen(Qt::green), QBrush(Qt::green));
    }
}
