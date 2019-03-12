#include "configurator.hpp"
#include "ui_configurator.h"

#include <core/serializer.hpp>

#include <QFile>
#include <QFileDialog>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

cs::Configurator::Configurator(QWidget* parent):
    QWidget(parent),
    ui(new Ui::Configurator())
{
    setupUi();
    setupValidators();

    QObject::connect(ui->applyButton, &QPushButton::clicked, this, &Configurator::onApplyButtonClicked);
    QObject::connect(ui->boostrapTypeBox, &QComboBox::currentTextChanged, this, &Configurator::onBoostrapButtonClicked);
    QObject::connect(ui->saveListButton, &QPushButton::clicked, this, &Configurator::onSaveButtonClicked);
    QObject::connect(ui->browseListButton, &QPushButton::clicked, this, &Configurator::onBrowseButtonCliecked);
}

cs::Configurator::~Configurator()
{
    delete ui;
}

void cs::Configurator::setupUi()
{
    setObjectName("configurator");

    ui->setupUi(this);
    ui->listBox->setVisible(false);

    ui->boostrapTypeBox->addItems(cs::Literals::boostrapTypes);
    ui->nodeTypeComboBox->addItems(cs::Literals::nodeTypes);

    setWindowTitle(cs::Literals::configuratorTitle);
    setWindowIcon(QIcon(":/resources/cs.ico"));

    QFile file(":/resources/style.css");

    if (file.open(QIODevice::ReadOnly))
        setStyleSheet(file.readAll());

    cs::Serializer serializer(cs::Literals::configFileName);
    updateUi(serializer.readData());

    resize(minimumSize());
    onBoostrapButtonClicked(ui->boostrapTypeBox->currentText());
}

void cs::Configurator::setupValidators()
{
    ui->outputPortEdit->setValidator(createPortValidator());
    ui->inputPortEdit->setValidator(createPortValidator());

    ui->outputIpEdit->setValidator(createIpValidator());
}

void cs::Configurator::updateUi(const cs::Data& data)
{
    if (!data.nodeType.isEmpty())
        ui->nodeTypeComboBox->setCurrentText(data.nodeType);

    if (!data.boostrapType.isEmpty())
        ui->boostrapTypeBox->setCurrentText(data.boostrapType);

    ui->ipv6CheckBox->setChecked(data.isIpv6);

    if (!data.nodeIp.isEmpty())
        ui->outputIpEdit->setText(data.nodeIp);

    if (data.nodeOutputPort)
        ui->outputPortEdit->setText(QString::number(data.nodeOutputPort));

    if (data.nodeInputPort)
        ui->inputPortEdit->setText(QString::number(data.nodeInputPort));
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

void cs::Configurator::updateUi(const cs::Hosts& hosts)
{
    ui->listWidget->clear();

    for (const auto& host : hosts)
        ui->listWidget->addItem(cs::HostSerializer::combine(host));
}

cs::Hosts cs::Configurator::uiHosts() const
{
    cs::Hosts hosts;

    for (int i = 0; ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        std::optional<cs::Host> host = cs::HostSerializer::split(item->text());

        if (host)
            hosts.append(std::move(host).value());
    }

    return hosts;
}

QValidator* cs::Configurator::createPortValidator()
{
    constexpr static int minPort = 1024;
    constexpr static int maxPort = 65535;
    return new QIntValidator(minPort, maxPort, this);
}

QValidator* cs::Configurator::createIpValidator()
{
    QRegularExpression regexpr("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
    return new QRegularExpressionValidator(regexpr, this);
}

void cs::Configurator::onApplyButtonClicked()
{
    cs::Serializer seriazler(cs::Literals::configFileName);
    seriazler.writeData(uiData());
}

void cs::Configurator::onBoostrapButtonClicked(const QString& text)
{
    if (text == cs::Literals::signalServerType)
    {
        ui->listBox->setVisible(false);
        resize(minimumSize());
    }
    else
    {
        ui->listBox->setVisible(true);
        resize(maximumSize());
    }
}

void cs::Configurator::onSaveButtonClicked()
{
    QString path = ui->listEdit->text();

    if (path.isEmpty())
    {
        path = QFileDialog::getExistingDirectory(this, "Choose directory", QApplication::applicationDirPath());
        path += "/" + cs::Literals::hostsFileName;
    }

    cs::HostSerializer serializer(path);
    serializer << uiHosts();
}

void cs::Configurator::onBrowseButtonCliecked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open " + cs::Literals::hostsFileName, QApplication::applicationDirPath(), "*.txt");

    HostSerializer serializer(fileName);
    Hosts hosts;
    serializer >> hosts;

    ui->listEdit->setText(fileName);
    updateUi(hosts);
}
