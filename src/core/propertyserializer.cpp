#include "propertyserializer.hpp"

#include <QFile>

cs::PropertySerializer::PropertySerializer(const QString& fileName, QObject* parent):
    QObject(parent)
{
    bool exists = QFile::exists(fileName);
    settings = std::make_unique<Scanner>(fileName);

    if (!exists) {
        writeDefaultData();
    }
}

cs::ApiData cs::PropertySerializer::read() const
{
    ApiData data;

    settings->beginGroup(cs::Literals::apiKey);

    if (settings->contains(cs::Literals::apiNodePort)) {
        data.apiPort = settings->value(cs::Literals::apiNodePort).value<int>();
    }

    if (settings->contains(cs::Literals::apiExecutorPort)) {
        data.executorPort = settings->value(cs::Literals::apiExecutorPort).value<int>();
    }

    if (settings->contains(cs::Literals::apiExecutorNodePort)) {
        data.executorPort = settings->value(cs::Literals::apiExecutorNodePort).value<int>();
    }

    settings->endGroup();

    return data;
}

void cs::PropertySerializer::write(const cs::ApiData& data)
{
    clear();

    settings->beginGroup(cs::Literals::apiKey);

    if (data.apiPort != 0) {
        settings->setValue(cs::Literals::apiNodePort, data.apiPort);
    }

    if (data.executorPort != 0) {
        settings->setValue(cs::Literals::apiExecutorPort, data.executorPort);
    }

    if (data.apiExecutorPort != 0) {
        settings->setValue(cs::Literals::apiExecutorNodePort, data.apiExecutorPort);
    }

    settings->endGroup();
}

void cs::PropertySerializer::writeDefaultData()
{
    ApiData data;
    data.apiExecutorPort = cs::defaultApiExecutorPort;
    data.executorPort = cs::defautlExecutorPort;
    data.apiPort = cs::defaultApiPort;
    data.ajaxPort = cs::defaultAjaxPort;

    write(data);

    settings->beginGroup(cs::Literals::apiKey);

    settings->setValue(cs::Literals::apiNodeHost, cs::defaultLocalHostIp);
    settings->setValue(cs::Literals::apiExecutorNodeHost, cs::defaultLocalHostIp);
    settings->setValue(cs::Literals::apiExecutorReadTimeout, 0);

    settings->endGroup();
}

void cs::PropertySerializer::clear()
{
    settings->remove(cs::Tree::combine(cs::Literals::apiKey, cs::Literals::apiNodePort));
    settings->remove(cs::Tree::combine(cs::Literals::apiKey, cs::Literals::apiExecutorPort));
    settings->remove(cs::Tree::combine(cs::Literals::apiKey, cs::Literals::apiExecutorNodePort));
}

cs::PropertySerializer::~PropertySerializer() = default;
