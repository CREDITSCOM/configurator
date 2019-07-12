#ifndef TREE_HPP
#define TREE_HPP

#include <QPair>
#include <QString>
#include <QVector>
#include <QVariant>

#include <utility>

namespace cs
{
    using KeyValuePair = std::pair<QString, QVariant>;
    using KeyValueVector = QVector<KeyValuePair>;
    using MappedType = std::pair<QString, KeyValueVector>;

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
        static std::pair<QString, QString> separatePrefix(const QString& str);
        static QString combine(const QString& section, const QString& key);

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
        QVector<MappedType>::iterator last;
    };
}

#endif // TREE_HPP
