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

    cs::HostSerializer serializer(fileName);
    cs::Hosts deserializedList;
    serializer >> deserializedList;

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

    cs::HostSerializer serializer(fileName);
    serializer << expectedList;

    cs::Hosts list;
    serializer >> list;

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    QCOMPARE(list, expectedList);
}

void cstests::Test_HostSerializer::split()
{
    QString data = "192.168.0.1:6000";
    std::optional<cs::Host> result = cs::HostSerializer::split(data);

    QCOMPARE(result.has_value(), true);
    QCOMPARE(result.value().ip, "192.168.0.1");
    QCOMPARE(result.value().port, 6000);

    QString ipv6Data = "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:9010";
    std::optional<cs::Host> ipv6Result = cs::HostSerializer::split(ipv6Data);

    QCOMPARE(ipv6Result.has_value(), true);
    QCOMPARE(ipv6Result.value().ip, "2001:db8:85a3:8d3:1319:8a2e:370:7348");
    QCOMPARE(ipv6Result.value().port, 9010);
}
