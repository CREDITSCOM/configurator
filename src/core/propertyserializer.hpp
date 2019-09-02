#ifndef PROPERTYSERIALIZER_HPP
#define PROPERTYSERIALIZER_HPP

#include <QObject>

#include <core/common.hpp>
#include <core/scanner.hpp>

#include <memory>

namespace cs
{
    class PropertySerializer : public QObject
    {
        Q_OBJECT

    public:
        explicit PropertySerializer(const QString& fileName, QObject* parent = nullptr);
        ~PropertySerializer();

        ApiData read() const;
        void write(const ApiData& data);

    private:
        std::unique_ptr<Scanner> settings;

        void writeDefaultData();
        void clear();
    };
}

#endif // PROPERTYSERIALIZER_HPP
