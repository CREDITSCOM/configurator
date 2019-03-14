#include "configurator.hpp"
#include "ui_configurator.h"

#include <ui/validatorfactory.hpp>
#include <core/serializer.hpp>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
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
    setupHostList();

    addHostListEmptyObject();

    QObject::connect(ui->applyButton, &QPushButton::clicked, this, &Configurator::onApplyButtonClicked);
    QObject::connect(ui->runButton, &QPushButton::clicked, this, &Configurator::onRunButtonPressed);
    QObject::connect(ui->boostrapTypeBox, &QComboBox::currentTextChanged, this, &Configurator::onBoostrapButtonClicked);
    QObject::connect(ui->saveListButton, &QPushButton::clicked, this, &Configurator::onSaveButtonClicked);
    QObject::connect(ui->browseListButton, &QPushButton::clicked, this, &Configurator::onBrowseButtonCliecked);
    QObject::connect(ui->listWidget, &QListWidget::itemChanged, this, &Configurator::onHostListItemChanged);
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

    if (file.open(QIODevice::ReadOnly)) {
        setStyleSheet(file.readAll());
    }

    cs::Serializer serializer(cs::Literals::configFileName);
    updateUi(serializer.readData());

    resize(minimumSize());

    onBoostrapButtonClicked(ui->boostrapTypeBox->currentText());
}

void cs::Configurator::setupValidators()
{
    ui->outputPortEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Port, this));
    ui->inputPortEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Port, this));

    ui->outputIpEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Ip, this));
}

void cs::Configurator::setupHostList()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        Qt::ItemFlags flags = item->flags();

        item->setFlags(flags | Qt::ItemIsEditable);

        if (!item->text().isEmpty()) {
            if (item->icon().isNull()) {
                item->setIcon(QIcon(":/resources/host.jpg"));
            }
        }
    }
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

void cs::Configurator::updateUi(const cs::Hosts& hosts)
{
    ui->listWidget->clear();

    for (const auto& host : hosts) {
        ui->listWidget->addItem(cs::HostSerializer::combine(host));
    }

    setupHostList();
    addHostListEmptyObject();
}

cs::Hosts cs::Configurator::uiHosts() const
{
    cs::Hosts hosts;

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        std::optional<cs::Host> host = cs::HostSerializer::split(item->text());

        if (host) {
            hosts.append(std::move(host).value());
        }
    }

    return hosts;
}

void cs::Configurator::addHostListEmptyObject()
{
    QObject::disconnect(ui->listWidget, &QListWidget::itemChanged, this, &Configurator::onHostListItemChanged);

    ui->listWidget->addItem(QString(""));

    QListWidgetItem* item = ui->listWidget->item(ui->listWidget->count() - 1);
    Qt::ItemFlags flags = item->flags();

    item->setFlags(flags | flags | Qt::ItemIsEditable);

    QObject::connect(ui->listWidget, &QListWidget::itemChanged, this, &Configurator::onHostListItemChanged);
}

bool cs::Configurator::validateItemText(QListWidgetItem* item)
{
    std::optional<Host> host = HostSerializer::split(item->text());

    if (!host.has_value()) {
        item->setText("");
        return false;
    }

    return true;
}

bool cs::Configurator::isEmptyItemExists()
{
    for (int i = 0; i < (ui->listWidget->count() - 1); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);

        if (item->text().isEmpty()) {
            return true;
        }
    }

    return false;
}

void cs::Configurator::onApplyButtonClicked()
{
    cs::Serializer seriazler(cs::Literals::configFileName);
    seriazler.writeData(uiData());
}

void cs::Configurator::onBoostrapButtonClicked(const QString& text)
{
    if (text == cs::Literals::signalServerType) {
        ui->listBox->setVisible(false);
        resize(minimumSize());
    }
    else {
        ui->listBox->setVisible(true);
        resize(maximumSize());
    }
}

void cs::Configurator::onSaveButtonClicked()
{
    QString path = ui->listEdit->text();

    if (path.isEmpty()) {
        path = QFileDialog::getExistingDirectory(this, "Choose directory", QApplication::applicationDirPath());
        path += "/" + cs::Literals::hostsFileName;

        ui->listEdit->setText(path);
    }

    cs::HostSerializer serializer(path);
    serializer << uiHosts();
}

void cs::Configurator::onBrowseButtonCliecked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open " + cs::Literals::hostsFileName, QApplication::applicationDirPath(), "*.txt");

    if (fileName.isEmpty()) {
        return;
    }

    HostSerializer serializer(fileName);
    Hosts hosts;
    serializer >> hosts;

    ui->listEdit->setText(fileName);
    updateUi(hosts);
}

void cs::Configurator::onRunButtonPressed()
{
    if (!QFile::exists(cs::Literals::cslauncherFilename)) {
        QMessageBox box;
        box.setIcon(QMessageBox::Icon::Critical);
        box.setText("CS Node configurator");
        box.setInformativeText("cs-launcher.exe not found, can not run process");
        box.setStandardButtons(QMessageBox::Ok);
        box.setWindowIcon(QIcon(":/resources/cs.ico"));

        box.exec();
    }
    else {
        std::system(cs::Literals::cslauncherFilename.toLatin1().data());
    }
}

void cs::Configurator::onHostListItemChanged(QListWidgetItem* item)
{
    if (!item->text().isEmpty()) {
        if (validateItemText(item)) {
            if (item->icon().isNull()) {
                item->setIcon(QIcon(":/resources/host.jpg"));
            }
        }
    }

    if (isEmptyItemExists()) {
        QStringList items;

        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem* listItem = ui->listWidget->item(i);

            if (!listItem->text().isEmpty()) {
                items.append(listItem->text());
            }
        }

        QObject::disconnect(ui->listWidget, &QListWidget::itemChanged, this, &Configurator::onHostListItemChanged);

        ui->listWidget->clear();
        ui->listWidget->addItems(items);

        QObject::connect(ui->listWidget, &QListWidget::itemChanged, this, &Configurator::onHostListItemChanged);

        setupHostList();

        if (!ui->listWidget->count()) {
            addHostListEmptyObject();
        }
    }
    else {
        int lastIndex = ui->listWidget->count() - 1;

        if (!ui->listWidget->item(lastIndex)->text().isEmpty()) {
            addHostListEmptyObject();
        }
    }
}
