#ifndef CONFIGURATOR_HPP
#define CONFIGURATOR_HPP

#include <QWidget>

#include <core/common.hpp>
#include <core/hostserializer.hpp>

#include <mutex>

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
        ~Configurator();

    private:
        Ui::Configurator* ui;

        const int fixedWidth = 400;
        const int fixedMinHeight = 310;
        const int fixedMaxHeight = 565;

        void setupUi();
        void setupValidators();
        void setupHostList();

        void updateUi(const Data& data);
        Data uiData() const;

        void updateUi(const Hosts& hosts);
        Hosts uiHosts() const;

        void addHostListEmptyObject();
        bool validateItemText(QListWidgetItem* item);
        bool isEmptyItemExists();

        void changeSize(QSize size);
        void changeSize(int w, int h);
        void changeSize();

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
