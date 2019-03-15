#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

namespace cs
{
    struct Utils
    {
        static QStringList searchExpression(const QRegularExpression& expression, const QString& source)
        {
            QRegularExpressionMatchIterator iter = expression.globalMatch(source);
            QStringList result;

            while (iter.hasNext()) {
                QRegularExpressionMatch match = iter.next();

                if (match.hasMatch()) {
                    result.append(match.captured());
                }
            }

            return result;
        }
    };
}

#endif // UTILS_HPP
