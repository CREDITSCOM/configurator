#include "serializer.hpp"
#include "converter.hpp"

#include <QDebug>
#include <QFile>
#include <QSettings>

cs::Serializer::Serializer(const QString& fileName, QObject* parent):
    QObject(parent)
{
    bool exists = QFile::exists(fileName);
    settings = std::make_unique<QSettings>(fileName, QSettings::Format::IniFormat);

    if (!exists)
        writeDefaultData();
}

cs::Data cs::Serializer::readData() const
{
    cs::Data data;

    settings->beginGroup(cs::Literals::paramsKey);

    if (settings->contains(cs::Literals::nodeTypeParameter))
        data.nodeType = settings->value(cs::Literals::nodeTypeParameter).value<QString>();

    if (settings->contains(cs::Literals::boostrapTypeParameter))
        data.boostrapType = settings->value(cs::Literals::boostrapTypeParameter).value<QString>();

    if (settings->contains(cs::Literals::ipv6TypeParameter))
        data.isIpv6 = settings->value(cs::Literals::ipv6TypeParameter).value<bool>();

    settings->endGroup();

    settings->beginGroup(cs::Literals::signalServerKey);

    if (settings->contains(cs::Literals::ipParameter))
        data.signalServerIp = settings->value(cs::Literals::ipParameter).value<QString>();

    if (settings->contains(cs::Literals::portParameter))
        data.signalServerPort = settings->value(cs::Literals::portParameter).value<int>();

    settings->endGroup();

    settings->beginGroup(cs::Literals::hostInputKey);

    if (settings->contains(cs::Literals::portParameter))
        data.nodeInputPort = settings->value(cs::Literals::portParameter).value<int>();

    settings->endGroup();

    settings->beginGroup(cs::Literals::hostOutputKey);

    if (settings->contains(cs::Literals::ipParameter))
        data.nodeIp = settings->value(cs::Literals::ipParameter).value<QString>();

    if (settings->contains(cs::Literals::portParameter))
        data.nodeOutputPort = settings->value(cs::Literals::portParameter).value<int>();

    return data;
}

void cs::Serializer::writeData(const Data& data)
{
    // params
    settings->beginGroup(cs::Literals::paramsKey);

    if (!data.nodeType.isEmpty())
        settings->setValue(cs::Literals::nodeTypeParameter, data.nodeType);

    if (!data.boostrapType.isEmpty())
        settings->setValue(cs::Literals::boostrapTypeParameter, data.boostrapType);

    settings->setValue(cs::Literals::ipv6TypeParameter, data.isIpv6);
    settings->endGroup();

    // signal_server
    settings->beginGroup(cs::Literals::signalServerKey);

    if (!data.signalServerIp.isEmpty())
        settings->setValue(cs::Literals::ipParameter, data.signalServerIp);

    if (data.signalServerPort)
        settings->setValue(cs::Literals::portParameter, data.signalServerPort);

    settings->endGroup();

    // host_input
    const QString hostInputKey = cs::Literals::hostInputKey + "/" + cs::Literals::portParameter;
    const int hostInputPort = data.nodeInputPort ? data.nodeInputPort : cs::defaultHostInputPort;
    settings->setValue(hostInputKey, hostInputPort);

    // host_output
    settings->beginGroup(cs::Literals::hostOutputKey);

    if (!data.nodeIp.isEmpty() && data.nodeOutputPort)
    {
        settings->setValue(cs::Literals::ipParameter, data.nodeIp);
        settings->setValue(cs::Literals::portParameter, data.nodeOutputPort);
    }
    else
    {
        settings->endGroup();
        settings->remove(cs::Literals::hostOutputKey);
    }

    if (!settings->group().isEmpty())
        settings->endGroup();

    emit writeCompleted();
}

void cs::Serializer::writeDefaultData()
{
    cs::Data data;
    data.nodeType = cs::Literals::routerType;
    data.boostrapType = cs::Literals::signalServerType;
    data.isIpv6 = false;
    data.nodeInputPort = cs::defaultHostInputPort;
    data.signalServerIp = cs::defaultSignalServerIp;
    data.signalServerPort = cs::defaultSignalServerPort;
    data.nodeOutputPort = 0;

    writeData(data);

    // sinks.default
    settings->beginGroup(cs::Literals::sinksDefaultKey);

    settings->setValue("Destination", R"("Console")");
    settings->setValue("Filter", "%Severity% >= info");
    settings->setValue("Format", R"("[%TimeStamp%] %Message%")");

    settings->endGroup();

    // sinks.file
    settings->beginGroup(cs::Literals::sinksFileKey);

    settings->setValue("Destination", "TextFile");
    settings->setValue("Filter", "%Severity% >= debug");
    settings->setValue("Format", R"("[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%")");
    settings->setValue("AutoFlush", true);
    settings->setValue("Target", "log");
    settings->setValue("FileName", R"("log/log%N_%Y_%m_%d.txt")");
    settings->setValue("RotationSize", 52428800);
    settings->setValue("MaxFiles", 4);

    settings->endGroup();

    convert();
}

void cs::Serializer::convert()
{
    QString fileName;

    if (settings)
    {
        fileName = settings->fileName();
        settings.reset();
    }

    fileName = fileName.isEmpty() ? cs::Literals::configFileName : fileName;

    if (!cs::Converter::convert(fileName))
        qDebug() << "Convert error occured";

    settings = std::make_unique<QSettings>(fileName, QSettings::IniFormat);
}

cs::Serializer::~Serializer() = default;
