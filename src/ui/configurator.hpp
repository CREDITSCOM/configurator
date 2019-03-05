#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

namespace Ui
{
    class Configurator;
}

namespace cs
{
    class Configurator : public QWidget
    {
        Q_OBJECT

    public:
        explicit Configurator(QWidget* parent = nullptr);
        ~Configurator();

    private:
        Ui::Configurator* ui;
    };
}

#endif // CONFIGURATOR_HPP
