#include "configurator.hpp"
#include "ui_configurator.h"

#include <ui/validatorfactory.hpp>
#include <core/serializer.hpp>
#include <core/propertyserializer.hpp>
#include <core/utils.hpp>

#include <map>
#include <thread>

#include <QDebug>
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
    QObject::connect(ui->extendingCheckBox, &QCheckBox::clicked, this, &Configurator::onExtendSettings);
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

#if __linux__
    ui->runButton->setVisible(false);
#endif

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

    cs::PropertySerializer property(cs::Literals::propertySettingsFileName);
    property.write(uiApiData());

    changeSize();
    move(Utils::desktopCenter(this));

    onBoostrapButtonClicked(ui->boostrapTypeBox->currentText());
    onExtendSettings(ui->extendingCheckBox->isChecked());
}

void cs::Configurator::setupValidators()
{
    ui->outputPortEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Port, this));
    ui->inputPortEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Port, this));

    ui->serverIpEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Ip, this));
    ui->serverPortEdit->setValidator(ValidatorFactory::create(ValidatorFactory::Type::Port, this));

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
    ui->nodeTypeComboBox->setCurrentText(data.nodeType);
    ui->boostrapTypeBox->setCurrentText(data.boostrapType);
    ui->ipv6CheckBox->setChecked(data.isIpv6);
    ui->outputIpEdit->setText(data.nodeIp);
    ui->serverIpEdit->setText(data.signalServerIp);

    if (data.nodeOutputPort) {
        ui->outputPortEdit->setText(QString::number(data.nodeOutputPort));
    }

    if (data.nodeInputPort) {
        ui->inputPortEdit->setText(QString::number(data.nodeInputPort));
    }

    if (data.signalServerPort) {
        ui->serverPortEdit->setText(QString::number(data.signalServerPort));
    }

    if (data.api.apiExecutorPort) {
        ui->apiExecutorPortEdit->setText(QString::number(data.api.apiExecutorPort));
    }

    if (data.api.executorPort) {
        ui->executorPortEdit->setText(QString::number(data.api.executorPort));
    }

    if (data.api.apiPort) {
        ui->apiPortEdit->setText(QString::number(data.api.apiPort));
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

    if (!ui->serverIpEdit->text().isEmpty()) {
        data.signalServerIp = ui->serverIpEdit->text();
    }

    if (!ui->serverPortEdit->text().isEmpty()) {
        data.signalServerPort = ui->serverPortEdit->text().toInt();
    }

    if (!ui->apiExecutorPortEdit->text().isEmpty()) {
        data.api.apiExecutorPort = ui->apiExecutorPortEdit->text().toInt();
    }

    if (!ui->executorPortEdit->text().isEmpty()) {
        data.api.executorPort = ui->executorPortEdit->text().toInt();
    }

    if (!ui->apiPortEdit->text().isEmpty()) {
        data.api.apiPort = ui->apiPortEdit->text().toInt();
    }

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

cs::ApiData cs::Configurator::uiApiData() const
{
    ApiData data;
    data.apiPort = ui->apiPortEdit->text().toInt();
    data.executorPort = ui->executorPortEdit->text().toInt();
    data.apiExecutorPort = ui->apiExecutorPortEdit->text().toInt();

    return data;
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

void cs::Configurator::changeSize(QSize size)
{
    setFixedSize(size);
    resize(size);
}

void cs::Configurator::changeSize(int w, int h)
{
    changeSize(QSize(w, h));
}

void cs::Configurator::changeSize()
{
    const static int delta = 40;

    if (ui->listBox->isVisible() && ui->extendingCheckBox->isChecked()) {
        changeSize(fixedWidth, fixedMaxHeight);
    }
    else if (ui->listBox->isVisible() && !ui->extendingCheckBox->isChecked()) {
        changeSize(fixedWidth, fixedMaxHeight - delta);
    }
    else if (!ui->listBox->isVisible() && ui->extendingCheckBox->isChecked()){
        changeSize(fixedWidth, fixedMinHeight);
    }
    else {
        changeSize(fixedWidth, fixedMinHeight - delta);
    }
}

void cs::Configurator::onApplyButtonClicked()
{
    if (!ui->outputIpEdit->text().isEmpty()) {
        if (ui->outputPortEdit->text().isEmpty()) {
            ui->outputIpEdit->clear();
            ui->outputPortEdit->clear();
        }
    }

    if (ui->serverIpEdit->text().isEmpty() || ui->serverPortEdit->text().isEmpty()) {
        ui->serverIpEdit->clear();
        ui->serverPortEdit->clear();
    }

    cs::Serializer seriazler(cs::Literals::configFileName);
    seriazler.writeData(uiData());

    cs::PropertySerializer property(cs::Literals::propertySettingsFileName);
    property.write(uiApiData());
}

void cs::Configurator::onBoostrapButtonClicked(const QString& text)
{
    if (text == cs::Literals::signalServerType) {
        ui->listBox->setVisible(false);
    }
    else {
        ui->listBox->setVisible(true);
    }

    changeSize();
}

void cs::Configurator::onSaveButtonClicked()
{
    QString path = ui->listEdit->text();

    if (path.isEmpty()) {
        path = QFileDialog::getExistingDirectory(this, "Choose directory", QApplication::applicationDirPath());
        path += QString("/") + cs::Literals::hostsFileName;

        ui->listEdit->setText(path);
    }

    cs::HostSerializer serializer(path);
    serializer << uiHosts();
}

void cs::Configurator::onBrowseButtonCliecked()
{
    static const QString title = QString("Open ") + cs::Literals::hostsFileName;
    QString fileName = QFileDialog::getOpenFileName(this, title, QApplication::applicationDirPath(), "*.txt");

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
    constexpr auto timeout = 2000;
    std::map<const char *, std::thread> spawners;

    for (auto cmd : Cmds::cmds) {
        spawners.emplace(cmd, [cmd]() {
            if (std::system(cmd)) {
                qDebug() << "cmd error for " << cmd;
            }
        });

        spawners[cmd].detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }

    onApplyButtonClicked();
    QApplication::exit();
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

void cs::Configurator::onExtendSettings(bool state)
{
    ui->outputIpEdit->setVisible(state);
    ui->outputPortEdit->setVisible(state);

    ui->outputIpLabel->setVisible(state);
    ui->outputPortLabel->setVisible(state);

    ui->executorPortEdit->setVisible(state);
    ui->executorPortLabel->setVisible(state);

    ui->apiPortEdit->setVisible(state);
    ui->apiPortLabel->setVisible(state);

    changeSize();
}
