#include "mycam.h"
#include "ui_mycam.h"

MyCam::MyCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyCam)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->graphicsView->setScene(scene);
    image = QPixmap("C:\\Users\\parkk\\Pictures\\lena.png");
    ui->graphicsView->resize(image.width(), image.height());
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->addPixmap(image);

    selection = scene->addRect(QRectF(0, 0, 0, 0), qpen, QBrush());
    qpen = QPen(Qt::green);
    qpen.setWidth(3);
    selection->setPen(qpen);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(saveImage()));
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
    }
}

void MyCam::mouseMoveEvent(QMouseEvent* evt)
{
    if (evt->buttons() & Qt::LeftButton && mousePosJudge(evt))
    {
        mouseBox.setTopLeft(offset);
        mouseBox.setBottomRight(QPointF(m_dx-3, m_dy-3));
        selection->setRect(mouseBox);
    }
}

void MyCam::saveImage()
{
    if (mouseBox.width() > 0 && mouseBox.height() > 0)
    {
        QPixmap ROI = image.copy(mouseBox.toRect());
        qDebug() << ROI.save("tmp.jpg");
    } else
    {
        qDebug() << "set ROI";
    }
}
