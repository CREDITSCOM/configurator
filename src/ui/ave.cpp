#include "ave.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>

#include <mutex>

constexpr int timeOut = 2000;
static std::once_flag done;

cs::Ave::Ave(QWidget* parent):
    QFrame(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(this);

    layout->addWidget(label);

    setLayout(layout);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen);

    label->setAutoFillBackground(true);
    label->setPixmap(QPixmap::fromImage(QImage(":/resources/credits_bg.jpg")));

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    int w = static_cast<int>(center.x() - width() * 0.5);
    int h = static_cast<int>(center.y() - height() * 0.5);

    move(w, h);
}

void cs::Ave::setNext(QWidget* widget)
{
    next = widget;
}

void cs::Ave::showEvent(QShowEvent* event)
{
    QFrame::showEvent(event);
    std::call_once(done, std::bind(&Ave::doOnce, this));
}

void cs::Ave::doOnce()
{
    QTimer::singleShot(timeOut, Qt::TimerType::PreciseTimer, [this] {
        if (next)
        {
            next->show();
            next->setFocus();
        }

        delete this;
    });
}
