#include "test_hostserializer.hpp"
#include <core/hostserializer.hpp>

#include <QDebug>
#include <QFile>
#include <QTest>
#include <QList>

cstests::Test_HostSerializer::Test_HostSerializer(QObject* parent):
    QObject(parent)
{
}

void cstests::Test_HostSerializer::deserialize()
{
    QString data = "192.168.0.1:6000\n"
                   "192.168.0.2:5555\n"
                   "1.7.33.222:65555\n"
                   "23.13.15.555:8080";

    cs::Hosts expectedList;
    expectedList.append(cs::Host {"192.168.0.1", 6000});
    expectedList.append(cs::Host {"192.168.0.2", 5555});
    expectedList.append(cs::Host {"1.7.33.222", 65555});
    expectedList.append(cs::Host {"23.13.15.555", 8080});

    const QString fileName = "test.txt";

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    {
        QFile file(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Text);

        QTextStream stream(&file);
        stream << data;

        file.close();
    }

    cs::HostSerializer serializer;
    cs::Hosts deserializedList = serializer.deserialize(fileName);

    QFile::remove(fileName);
    QCOMPARE(expectedList, deserializedList);
}

void cstests::Test_HostSerializer::serialize()
{
    cs::Hosts expectedList;
    expectedList.append(cs::Host {"192.168.0.1", 6000});
    expectedList.append(cs::Host {"192.168.0.2", 5555});
    expectedList.append(cs::Host {"1.7.33.222", 65555});
    expectedList.append(cs::Host {"23.13.15.555", 8080});

    const QString fileName = "test.txt";

    cs::HostSerializer serializer;
    serializer.serialize(expectedList, fileName);

    auto list = serializer.deserialize(fileName);

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    QCOMPARE(list, expectedList);
}
