#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <QObject>
#include <QPair>
#include <QVariant>
#include <QVector>

#include <structures/tree.hpp>

namespace cs
{
    // main alternative to qsettings
    class Scanner : public QObject
    {
        Q_OBJECT

    public:
        enum class Status {
            NoError,
            ParseError,
            FileAccessError
        };

        explicit Scanner(const QString& fileName, QObject* parent = nullptr);
        ~Scanner();

        // qsettings-like interface
        void sync();
        void clear();

        Status status();
        QString toString() const;

        void beginGroup(const QString& prefix);
        void endGroup();

        QVariant value(const QString& str);
        bool contains(const QString& str);

        void setValue(const QString& str, const QVariant& value);
        void remove(const QString& str);

        QString fileName() const;

    private:
        Tree data;

        QString name;
        Status state;

        // service
        QString section;
        QString checkSection(const QString& str) const;
        QString checkKey(const QString& key) const;

        // parse data from string
        bool fromString(const QString& str);

        // file methods
        void write();
        bool read();

        // data helpers
        bool failed();
    };
}

#endif // SCANNER_HPP
