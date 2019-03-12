#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

#include <core/common.hpp>
#include <core/hostserializer.hpp>

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

        void setupUi();

        void updateUi(const Data& data);
        Data uiData() const;

        void updateUi(const Hosts& hosts);
        Hosts uiHosts() const;

    private slots:
        void onApplyButtonClicked();
        void onBoostrapButtonClicked(const QString& text);
        void onSaveButtonClicked();
        void onBrowseButtonCliecked();
    };
}

#endif // CONFIGURATOR_HPP
