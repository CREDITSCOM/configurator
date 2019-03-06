#include "converter.hpp"
#include <QFile>
#include <QByteArray>

bool cs::Converter::convert(const QString& fileName)
{
    QByteArray data;

    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            return false;
        }

        data = file.readAll();
    }

    if (!data.contains(R"(\")")) {
        return true;
    }

    data.replace(R"(\")", R"(")");

    QFile::remove(fileName);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    if (!file.write(data)) {
        return false;
    }

    return true;
}
