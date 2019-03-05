#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <QObject>
#include <memory>

class QSettings;

namespace cs
{
    class Serializer : public QObject
    {
        Q_OBJECT

    public:
        explicit Serializer(const QString& fileName = "", QObject* parent = nullptr);

    private:
        struct Data;
        std::unique_ptr<Data> data;
        std::unique_ptr<QSettings> settings;
    };
}

#endif // SERIALIZER_HPP
