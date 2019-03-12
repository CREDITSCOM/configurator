#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

#include <core/common.hpp>
#include <core/hostserializer.hpp>

class QValidator;

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
        void setupValidators();

        void updateUi(const Data& data);
        Data uiData() const;

        void updateUi(const Hosts& hosts);
        Hosts uiHosts() const;

        QValidator* createPortValidator();
        QValidator* createIpValidator();

    private slots:
        void onApplyButtonClicked();
        void onBoostrapButtonClicked(const QString& text);
        void onSaveButtonClicked();
        void onBrowseButtonCliecked();
    };
}

#endif // CONFIGURATOR_HPP
