#ifndef HOSTSERIALIZER_TEST_H
#define HOSTSERIALIZER_TEST_H

#include <QObject>

namespace cstests
{
    class Test_HostSerializer : public QObject
    {
        Q_OBJECT

    public:
        explicit Test_HostSerializer(QObject* parent = nullptr);

    private slots:
        void deserialize();
    };
}

#endif // HOSTSERIALIZER_TEST_H
