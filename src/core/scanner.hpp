#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <QObject>
#include <QPair>
#include <QVariant>
#include <QVector>
#include <QMap>

namespace cs
{
    using KeyValuePair = QPair<QString, QVariant>;
    using KeyValueVector = QVector<KeyValuePair>;
    using MappedType = QPair<QString, KeyValueVector>;

    class Tree
    {
    public:
        void clear();
        bool isEmpty() const;

        bool addSection(const QString& section);
        bool addKeyValue(const QString& section, const QString& keyValue);

        // adds to last section
        bool appendKeyValue(const QString& keyValue);

        // utility
        static bool isSection(const QString& str);
        static bool isKeyValuePair(const QString& str);
        static bool isEmpty(const QString& str);
        static KeyValuePair split(const QString& str);
        static QPair<QString, QString> separatePrefix(const QString& str);

        bool containsSection(const QString& section) const;
        bool containsKey(const QString& section, const QString& key) const;
        bool contains(const QString& str);

        KeyValueVector& keyValueVector(const QString& section);
        KeyValuePair& keyValue(const QString& section, const QString& key);

        const KeyValueVector& keyValueVector(const QString& section) const;
        const KeyValuePair& keyValue(const QString& section, const QString& key) const;

        QVariant& value(const QString& section, const QString& key);

        bool remove(const QString& section, const QString& key);
        bool remove(const QString& section);

        // raw data access
        const QVector<MappedType>& raw() const;

    private:
        QVector<MappedType> data;
    };

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
