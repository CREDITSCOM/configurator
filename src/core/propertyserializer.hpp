#ifndef PROPERTYSERIALIZER_HPP
#define PROPERTYSERIALIZER_HPP

#include <QObject>
#include <core/common.hpp>

namespace cs
{
    class PropertySerializer : public QObject
    {
        Q_OBJECT

    public:
        explicit PropertySerializer(const QString& fileName, QObject* parent = nullptr);

        int readPort() const;
        void write(const ApiData& data);

    private:
        QString name;
    };
}

#endif // PROPERTYSERIALIZER_HPP
