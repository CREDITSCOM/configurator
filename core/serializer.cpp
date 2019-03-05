#include "serializer.hpp"
#include <QFile>
#include <QSettings>

struct cs::Serializer::Data
{
    QString nodeType;
    QString boostrapType;
    bool isIpv6;

    QString signalServerIp;
    int signalServerPort;

    QString nodeIp;
    int nodeOutputPort;
    int nodeInputPort;
};

cs::Serializer::Serializer(const QString& fileName, QObject* parent):
    QObject(parent)
{
    bool readSettings = QFile::exists(fileName);

    settings = std::make_unique<QSettings>(fileName, QSettings::Format::IniFormat);
    data = std::make_unique<Serializer::Data>();
}
