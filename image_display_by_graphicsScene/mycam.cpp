#include "mycam.h"
#include "ui_mycam.h"

MyCam::MyCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyCam)
{
    ui->setupUi(this);
    ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
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

bool MyCam::mousePosJudge(QMouseEvent* evt)
{
    m_dx = evt->windowPos().x() - ui->graphicsView->pos().x();
    m_dy = evt->windowPos().y() - ui->graphicsView->pos().y();
    return m_dx > 0 && m_dx < ui->graphicsView->width() &&
           m_dy > 0 && m_dy < ui->graphicsView->height();
}

void MyCam::mousePressEvent(QMouseEvent* evt)
{
    if (evt->buttons() & Qt::LeftButton && mousePosJudge(evt))
    {
        offset = QPointF(m_dx, m_dy);
        qDebug() << offset;
    }
}

void MyCam::mouseMoveEvent(QMouseEvent* evt)
{
    if (evt->buttons() & Qt::LeftButton && mousePosJudge(evt))
    {
        mousePos = QPointF(m_dx, m_dy);
        qDebug() << mousePos;
    }
}

void MyCam::mouseReleaseEvent(QMouseEvent* evt)
{
    mouseBox.setTopLeft(offset);
    mouseBox.setBottomRight(mousePos);
    scene->addRect(mouseBox, QPen(Qt::red), QBrush());
}
