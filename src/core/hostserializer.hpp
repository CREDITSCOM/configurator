#ifndef HOSTSERIALIZER_HPP
#define HOSTSERIALIZER_HPP

#include <QObject>
#include <QList>

namespace cs
{
    struct Host
    {
        QString ip;
        int port;
    };

    using Hosts = QList<Host>;

    class HostSerializer : public QObject
    {
        Q_OBJECT

    public:
        explicit HostSerializer(QObject* parent = nullptr);

        // try to get host list from file
        Hosts deserialize(const QString& fileName);
        void serialize(const Hosts& hosts, const QString& fileName);
    };

    bool operator==(const Host& lhs, const Host& rhs);
    bool operator!=(const Host& lhs, const Host& rhs);
}

#endif // HOSTSERIALIZER_HPP
