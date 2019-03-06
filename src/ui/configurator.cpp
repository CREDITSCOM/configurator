#include "configurator.hpp"
#include "ui_configurator.h"

#include <core/serializer.hpp>
#include <QFile>

cs::Configurator::Configurator(QWidget* parent):
    QWidget(parent),
    ui(new Ui::Configurator())
{
    ui->setupUi(this);
    ui->listBox->setVisible(false);

    ui->boostrapTypeBox->addItems(cs::Literals::boostrapTypes);
    ui->nodeTypeComboBox->addItems(cs::Literals::nodeTypes);

    setWindowTitle(cs::Literals::configuratorTitle);
    setWindowIcon(QIcon(":/resources/cs.ico"));

    QFile file(":/resources/style");

    if (file.open(QIODevice::ReadOnly)) {
        setStyleSheet(file.readAll());
    }

    cs::Serializer serializer(cs::Literals::configFileName);
    updateUi(serializer.readData());

    QObject::connect(ui->applyButton, &QPushButton::clicked, this, &Configurator::onApplyButtonClicked);
}

cs::Configurator::~Configurator()
{
    delete ui;
}

void cs::Configurator::updateUi(const cs::Data& data)
{
    if (!data.nodeType.isEmpty()) {
        ui->nodeTypeComboBox->setCurrentText(data.nodeType);
    }

    if (!data.boostrapType.isEmpty()) {
        ui->boostrapTypeBox->setCurrentText(data.boostrapType);
    }

    ui->ipv6CheckBox->setChecked(data.isIpv6);

    if (!data.nodeIp.isEmpty()) {
        ui->outputIpEdit->setText(data.nodeIp);
    }

    if (data.nodeOutputPort) {
        ui->outputPortEdit->setText(QString::number(data.nodeOutputPort));
    }

    if (data.nodeInputPort) {
        ui->inputPortEdit->setText(QString::number(data.nodeInputPort));
    }
}

cs::Data cs::Configurator::uiData() const
{
    cs::Data data;
    data.nodeType = ui->nodeTypeComboBox->currentText();
    data.boostrapType = ui->boostrapTypeBox->currentText();
    data.isIpv6 = ui->ipv6CheckBox->isChecked();

    data.nodeIp = ui->outputIpEdit->text();
    data.nodeOutputPort = ui->outputPortEdit->text().toInt();
    data.nodeInputPort = ui->inputPortEdit->text().toInt();

    return data;
}

void cs::Configurator::onApplyButtonClicked()
{
    cs::Serializer seriazler(cs::Literals::configFileName);
    seriazler.writeData(uiData());
}
