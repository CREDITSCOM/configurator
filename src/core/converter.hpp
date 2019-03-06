#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <QObject>

namespace cs
{
    // converts QSetting .ini file to file with correct quoted symbols
    class Converter : public QObject
    {
        Q_OBJECT

        Converter() = delete;
        Converter(QObject* parent = nullptr) = delete;

    public:
        static bool convert(const QString& fileName);
    };
}

#endif // CONVERTER_HPP
