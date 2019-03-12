#ifndef HOSTSERIALIZER_HPP
#define HOSTSERIALIZER_HPP

#include <QObject>
#include <QList>

#include <optional>

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
        explicit HostSerializer(const QString& fileName, QObject* parent = nullptr);

        // try to get host list from file
        Hosts deserialize();
        void serialize(const Hosts& hosts);

        static std::optional<Host> split(const QString& str);
        static QString combine(const Host& host);

    private:
        QString name;
    };

    bool operator==(const Host& lhs, const Host& rhs);
    bool operator!=(const Host& lhs, const Host& rhs);

    HostSerializer& operator<<(HostSerializer& serializer, const Hosts& hosts);
    HostSerializer& operator>>(HostSerializer& serializer, Hosts& hosts);
}

#endif // HOSTSERIALIZER_HPP
