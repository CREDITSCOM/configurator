#include "tree.hpp"
#include <cstring>

void cs::Tree::clear()
{
    data.clear();
    last = QVector<MappedType>::iterator{};
}

bool cs::Tree::isEmpty() const
{
    return data.isEmpty();
}

bool cs::Tree::addSection(const QString& section)
{
    if (!containsSection(section)) {
        QString checked = section;
        checked.remove("\r").remove("[").remove("]");

        auto iter = std::lower_bound(data.begin(), data.end(), checked, [](const MappedType& type, const QString& value) {
            return type.first.toLower() < value.toLower();
        });

        last = data.insert(iter, MappedType { checked, {} });
        return true;
    }

    return false;
}

bool cs::Tree::addKeyValue(const QString& section, const QString& keyValue)
{
    KeyValueVector& vector = keyValueVector(section);
    KeyValuePair pair = split(keyValue);

    if (!containsKey(section, keyValue)) {
        vector.push_back(pair);
        return true;
    }

    return false;
}

bool cs::Tree::appendKeyValue(const QString& keyValue)
{
    if (data.isEmpty()) {
        return false;
    }

    return addKeyValue(last->first, keyValue);
}

bool cs::Tree::isSection(const QString& str)
{
    return str.contains("[") && str.contains("]") && !str.contains("=");
}

bool cs::Tree::isKeyValuePair(const QString& str)
{
    return str.contains("=");
}

bool cs::Tree::isEmpty(const QString& str)
{
    auto string = str.toStdString();
    auto result = !std::strcmp(string.data(), "\n");

    return str.contains("\r") || str.isEmpty() || result;
}

cs::KeyValuePair cs::Tree::split(const QString& str)
{
    auto index = str.indexOf("=");

    QString key = str.mid(0, index);
    QString value = str.mid(index + 1);

    return std::make_pair(key.trimmed(), value.remove("\r").trimmed());
}

std::pair<QString, QString> cs::Tree::separatePrefix(const QString& str)
{
    if (str.contains("/")) {
        QStringList list = str.split("/");
        return std::make_pair(list.front(), list.back());
    }
    else if (!str.isEmpty()) {
        return std::make_pair(str, QString());
    }

    return std::make_pair(QString(), QString());
}

QString cs::Tree::combine(const QString& section, const QString& key)
{
    return section + QString("/") + key;
}

bool cs::Tree::containsSection(const QString& section) const
{
    auto iter = std::find_if(data.begin(), data.end(), [&](const cs::MappedType& e) {
        return e.first == section;
    });

    return iter != data.end();
}

bool cs::Tree::containsKey(const QString& section, const QString& key) const
{
    const KeyValueVector& vector = keyValueVector(section);
    auto iter = std::find_if(vector.begin(), vector.end(), [&](const KeyValuePair& pair) {
        return pair.first == key;
    });

    return iter != vector.end();
}

bool cs::Tree::contains(const QString& str)
{
    const auto& [section, key] = Tree::separatePrefix(str);

    if (section.isEmpty() && key.isEmpty()) {
        return false;
    }
    else if (!section.isEmpty()) {
        return containsSection(section);
    }

    return containsKey(section, key);
}

cs::KeyValueVector& cs::Tree::keyValueVector(const QString& section)
{
    auto iter = std::find_if(data.begin(), data.end(), [&](const MappedType& type) {
        return type.first == section;
    });

    return iter->second;
}

cs::KeyValuePair& cs::Tree::keyValue(const QString& section, const QString& key)
{
    KeyValueVector& vector = keyValueVector(section);
    auto iter = std::find_if(vector.begin(), vector.end(), [&](const KeyValuePair& pair) {
        return pair.first == key;
    });

    return (*iter);
}

const cs::KeyValueVector& cs::Tree::keyValueVector(const QString& section) const
{
    return const_cast<Tree*>(this)->keyValueVector(section);
}

const cs::KeyValuePair& cs::Tree::keyValue(const QString& section, const QString& key) const
{
    return const_cast<Tree*>(this)->keyValue(section, key);
}

QVariant& cs::Tree::value(const QString& section, const QString& key)
{
    return keyValue(section, key).second;
}

bool cs::Tree::remove(const QString& section, const QString& key)
{
    if (!containsSection(section)) {
        return false;
    }

    KeyValueVector& vector = keyValueVector(section);
    auto iter = std::find_if(vector.begin(), vector.end(), [&](const KeyValuePair& pair) {
        return pair.first == key;
    });

    if (iter != vector.end()) {
        vector.erase(iter);
        return true;
    }

    return false;
}

bool cs::Tree::remove(const QString& section)
{
    auto iter = std::find_if(data.begin(), data.end(), [&](const MappedType& type) {
        return type.first == section;
    });

    if (iter != data.end()) {
        data.erase(iter);
        return true;
    }

    return false;
}

const QVector<cs::MappedType>& cs::Tree::raw() const
{
    return data;
}
