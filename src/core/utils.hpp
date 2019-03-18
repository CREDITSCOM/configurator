#ifndef UTILS_HPP
#define UTILS_HPP

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QDesktopWidget>
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

        static QPoint desktopCenter(QWidget* widget) {
            QRect desktopRect = QApplication::desktop()->availableGeometry(widget);
            QPoint center = desktopRect.center();

            int w = static_cast<int>(center.x() - widget->width() * 0.5);
            int h = static_cast<int>(center.y() - widget->height() * 0.5);

            return QPoint(w, h);
        }
    };
}

#endif // UTILS_HPP
