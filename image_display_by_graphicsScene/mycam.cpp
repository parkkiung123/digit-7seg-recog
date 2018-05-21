#include "mycam.h"
#include "ui_mycam.h"
#include <opencv2/opencv.hpp>

MyCam::MyCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyCam)
{
    ui->setupUi(this);

    // QGraphicsSceneによる画像表示
    scene = new QGraphicsScene(this);
    // マウスイベントをGraphicsViewが親(Wdiget)に通す
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->graphicsView->setScene(scene);
    // Opencvカメラセット
    cv::VideoCapture cap(0);
    ui->graphicsView->resize(cap.get(cv::CAP_PROP_FRAME_WIDTH),
                             cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // マウスselectionボックス
    selection = scene->addRect(QRectF(0, 0, 0, 0), qpen, QBrush());
    qpen = QPen(Qt::green);
    qpen.setWidth(3);
    selection->setPen(qpen);

    // カメラ用画像のセット
    frame = scene->addPixmap(image);
    // カメラから画像取得
    if(!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
    {
        qDebug() << "Cannot detect camera";
    }

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(this, SIGNAL(sigDrawFrame()), this, SLOT(slotDrawFrame()));

    while(1)//無限ループ
    {
        cv::Mat cvframe;
        cap >> cvframe;
        QImage qimage( cvframe.data, cvframe.cols, cvframe.rows,
                       static_cast<int>(cvframe.step),
                       QImage::Format_RGB888 );
        image = QPixmap::fromImage(qimage);
        emit sigDrawFrame();
        cv::waitKey(1);
    }
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

void MyCam::slotDrawFrame()
{
    qDebug() << "aaa";
    frame->setPixmap(image);
}
