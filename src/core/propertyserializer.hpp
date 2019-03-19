#ifndef PROPERTYSERIALIZER_HPP
#define PROPERTYSERIALIZER_HPP

#include <QObject>

namespace cs
{
    class PropertySerializer : public QObject
    {
        Q_OBJECT

    public:
        explicit PropertySerializer(const QString& fileName, QObject* parent = nullptr);

        int readPort() const;
        void writePort(int port);

    private:
        QString name;
    };
}

#endif // PROPERTYSERIALIZER_HPP
