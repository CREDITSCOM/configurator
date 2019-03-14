#ifndef AVE_H
#define AVE_H

#include <QFrame>

namespace cs
{
    class Ave : public QFrame
    {
        Q_OBJECT

    public:
        explicit Ave(QWidget* parent = nullptr);
        void setNext(QWidget* widget);

    protected:
        virtual void showEvent(QShowEvent* event) override;
        void doOnce();

    private:
        QWidget* next = nullptr;
    };
}

#endif // AVE_H
