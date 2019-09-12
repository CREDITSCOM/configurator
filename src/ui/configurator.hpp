#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

#include <core/common.hpp>
#include <core/hostserializer.hpp>

class QValidator;
class QListWidgetItem;

namespace Ui {
    class Configurator;
}

namespace cs
{
    class Configurator : public QWidget
    {
        Q_OBJECT

    public:
        explicit Configurator(QWidget* parent = nullptr);
        virtual ~Configurator() override;

    private:
        Ui::Configurator* ui;

        void setupUi();
        void setupValidators();
        void setupHostList();

        void updateUi(const Data& data);
        Data uiData() const;

        void updateUi(const Hosts& hosts);
        Hosts uiHosts() const;

        ApiData uiApiData() const;

        void addHostListEmptyObject();
        bool validateItemText(QListWidgetItem* item);
        bool isEmptyItemExists();

    private slots:
        void onApplyButtonClicked();
        void onBoostrapButtonClicked(const QString& text);
        void onSaveButtonClicked();
        void onBrowseButtonCliecked();
        void onRunButtonPressed();
        void onHostListItemChanged(QListWidgetItem* item);
        void onExtendSettings(bool state);
    };
}

#endif // CONFIGURATOR_HPP
