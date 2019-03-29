#include "scanner.hpp"

#include <QFile>
#include <QList>
#include <QDebug>

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

void cs::Scanner::process(QStringList& list)
{
    for (auto iterator = list.begin(); iterator != list.end();) {
        iterator->remove("\r");

        if (iterator->isEmpty()) {
            iterator = list.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}

bool cs::Scanner::fromString(const QString& str)
{
    data.clear();

    QStringList entity = str.split("\n");
    process(entity);

    for (auto& str : entity) {
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
