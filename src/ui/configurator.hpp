#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>
#include <core/common.hpp>

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

        void updateUi(const Data& data);
        Data uiData() const;

    private slots:
        void onApplyButtonClicked();
    };
}

#endif // CONFIGURATOR_HPP
