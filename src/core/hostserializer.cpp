#include "hostserializer.hpp"
#include <QDebug>
#include <core/utils.hpp>

cs::HostSerializer::HostSerializer(const QString& fileName, QObject* parent):
    QObject(parent),
    name(fileName)
{
}

cs::Hosts cs::HostSerializer::deserialize()
{
    QFile file(name);
    cs::Hosts hosts;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Deserialization of hosts failed, can not access file " << name;
        return hosts;
    }

    QByteArray data = file.readAll();
    QString source = std::move(data);

    QRegularExpression ipRegExpr("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
    QRegularExpression portRegExpr(":[0-9]{2,5}");

    QStringList ipList = Utils::searchExpression(ipRegExpr, source);
    QStringList portList = Utils::searchExpression(portRegExpr, source);

    if (ipList.size() != portList.size()) {
        return hosts;
    }

    for (int i = 0; i < ipList.size(); ++i) {
        if (portList[i].contains(":")) {
            portList[i].remove(":");
        }

        hosts.append(cs::Host { ipList[i], portList[i].toInt() });
    }

    return hosts;
}

void cs::HostSerializer::serialize(const cs::Hosts& hosts)
{
    if (QFile::exists(name)) {
        QFile::remove(name);
        return;
    }

    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);

    for (const auto& host : hosts) {
        stream << host.ip << ':' << host.port << endl;
    }

    file.close();
}

std::optional<cs::Host> cs::HostSerializer::split(const QString& str)
{
    if (!str.contains(":")) {
        return std::nullopt;
    }

    QRegularExpression ipv4RegExpr("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
    QRegularExpression portRegExpr(":[0-9]{2,5}");

    QRegularExpressionMatch ipMatch = ipv4RegExpr.match(str);
    QRegularExpressionMatch portMatch = portRegExpr.match(str);

    if (!ipMatch.hasMatch() || !portMatch.hasMatch()) {
        return std::nullopt;
    }

    cs::Host host {
        ipMatch.captured(),
        portMatch.captured().remove(":").toInt()
    };

    return std::make_optional(std::move(host));
}

QString cs::HostSerializer::combine(const cs::Host& host)
{
    return host.ip + ":" + QString::number(host.port);
}

bool cs::operator==(const cs::Host& lhs, const cs::Host& rhs)
{
    return (lhs.ip == rhs.ip) && (lhs.port == rhs.port);
}

bool cs::operator!=(const cs::Host& lhs, const cs::Host& rhs)
{
    return !(lhs == rhs);
}

cs::HostSerializer& cs::operator<<(cs::HostSerializer& serializer, const cs::Hosts& hosts)
{
    serializer.serialize(hosts);
    return serializer;
}

cs::HostSerializer& cs::operator>>(cs::HostSerializer& serializer, cs::Hosts& hosts)
{
    hosts = serializer.deserialize();
    return serializer;
}
