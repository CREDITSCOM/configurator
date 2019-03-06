#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <QObject>
#include <memory>

#include <core/common.hpp>

class QSettings;

namespace cs
{
    class Serializer : public QObject
    {
        Q_OBJECT

    public:
        explicit Serializer(const QString& fileName = "", QObject* parent = nullptr);
        ~Serializer();

        Data readData() const;
        void writeData(const Data& data);

    private:
        std::unique_ptr<QSettings> settings;

        void writeDefaultData();
        void convert();

    signals:
        void readCompleted(const Data&);
        void writeCompleted();
    };
}

#endif // SERIALIZER_HPP
