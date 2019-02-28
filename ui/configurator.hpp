#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

namespace cs
{
    class Configurator : public QWidget
    {
        Q_OBJECT

    public:
        explicit Configurator(QWidget* parent = nullptr);
    };
}

#endif // CONFIGURATOR_HPP
