#include "propertyserializer.hpp"

#include <QFile>
#include <QTextStream>

static const char* defaultText = "node.api.host=127.0.0.1\n"
                                 "node.api.port=9090\n"
                                 "contract.executor.port=9080\n"
                                 "contract.executor.node.api.port=%1";

cs::PropertySerializer::PropertySerializer(const QString& fileName, QObject* parent):
    QObject(parent),
    name(fileName)
{
}

int cs::PropertySerializer::readPort() const
{
    QFile file(name);
    int port = 0;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray data = file.readAll();
        QString str = data;

        int start = str.lastIndexOf("=") + 1;
        int length = str.length() - start;

        port = str.mid(start, length).toInt();

        file.close();
    }

    return port;
}

void cs::PropertySerializer::writePort(int port)
{
    if (QFile::exists(name)) {
        QFile::remove(name);
    }

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream stream(&file);
    QString str(defaultText);
    stream << str.arg(port);

    file.close();
}
