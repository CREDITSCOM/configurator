#include "scanner.hpp"
#include <string>
#include <cstring>

#include <QFile>
#include <QList>
#include <QDebug>

void cs::Tree::clear()
{
    data.clear();
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

        data.insert(iter, MappedType { checked, {} });
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

    return addKeyValue(data.back().first, keyValue);
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

    return qMakePair(key, value.remove("\r"));
}

QPair<QString, QString> cs::Tree::separatePrefix(const QString& str)
{
    if (str.contains("/")) {
        QStringList list = str.split("/");
        return qMakePair(list.front(), list.back());
    }
    else if (!str.isEmpty()) {
        return qMakePair(str, QString());
    }

    return qMakePair(QString(), QString());
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

// scanner
cs::Scanner::Scanner(const QString& fileName, QObject* parent):
    QObject(parent),
    name(fileName),
    state(Status::NoError)
{
    if (QFile::exists(name)) {
        if (!read()) {
            qDebug() << name << ", file format error";
            state = Status::ParseError;
        }
    }
}

cs::Scanner::~Scanner()
{
    sync();
}

void cs::Scanner::sync()
{
    if (!data.isEmpty()) {
        write();
    }
}

void cs::Scanner::clear()
{
    data.clear();
}

cs::Scanner::Status cs::Scanner::status()
{
    return state;
}

QString cs::Scanner::toString() const
{
    QString str;
    const auto& raw = data.raw();

    for (int i = 0; i < raw.size(); ++i) {
        const auto& [key, keyValueVector] = raw[i];

        QString checkedKey = checkKey(key);
        str.append(checkedKey).append("\n");

        for (const auto& [value, result] : keyValueVector) {
            str.append(value).append("=").append(result.value<QString>()).append("\n");
        }

        if (i != (raw.size() - 1)) {
            str.append("\n");
        }
    }

    return str;
}

void cs::Scanner::beginGroup(const QString& prefix)
{
    section = prefix;
}

void cs::Scanner::endGroup()
{
    section = QString();
}

QVariant cs::Scanner::value(const QString& str)
{
    const auto& [section, key] = Tree::separatePrefix(checkSection(str));

    if (section.isEmpty() || key.isEmpty()) {
        return QVariant();
    }

    return data.value(section, key);
}

bool cs::Scanner::contains(const QString& str)
{
    return data.contains(checkSection(str));
}

void cs::Scanner::setValue(const QString& str, const QVariant& value)
{
    const auto& [section, key] = Tree::separatePrefix(checkSection(str));

    if (section.isEmpty()) {
        return;
    }

    if (key.isEmpty()) {
        data.addSection(section);
    }
    else {
        data.addSection(section);

        if (!data.containsKey(section, key)) {
            data.addKeyValue(section, key + QString("=") + value.value<QString>());
        }
        else {
            data.value(section, key) = value;
        }
    }
}

void cs::Scanner::remove(const QString& str)
{
    const auto& [section, key] = Tree::separatePrefix(checkSection(str));

    if (section.isEmpty()) {
        return;
    }

    if (key.isEmpty()) {
        data.remove(section);
    }
    else {
        data.remove(section, key);
    }
}

QString cs::Scanner::fileName() const
{
    return name;
}

QString cs::Scanner::checkSection(const QString& str) const
{
    // it's section or section/key
    if (section.isEmpty()) {
        return str;
    }

    // make section + key
    return section + QString("/") + str;
}

QString cs::Scanner::checkKey(const QString& key) const
{
    if (!key.contains("[") && !key.contains("]")) {
        return QString("[") + key + QString("]");
    }

    return key;
}

bool cs::Scanner::fromString(const QString& str)
{
    data.clear();
    QStringList entity = str.split("\n");

    for (const auto& str : entity) {
        if (Tree::isSection(str)) {
            if (!data.addSection(str)) {
                return failed();
            }
        }
        else if (Tree::isKeyValuePair(str)) {
            if (!data.appendKeyValue(str)) {
                return failed();
            }
        }
        else if (!Tree::isEmpty(str)) {
            return failed();
        }
    }

    return true;
}

void cs::Scanner::write()
{
    if (QFile::exists(name)) {
        QFile::remove(name);
    }

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        state = Status::FileAccessError;
        return;
    }

    QTextStream stream(&file);
    stream << toString();
}

bool cs::Scanner::read()
{
    QFile file(name);

    if (!file.open(QIODevice::ReadOnly)) {
        state = Status::FileAccessError;
        return false;
    }

    QByteArray rawData = file.readAll();
    QString str = std::move(rawData);

    return fromString(str);
}

bool cs::Scanner::failed()
{
    data.clear();
    return false;
}
