#ifndef VALIDATORFACTORY_HPP
#define VALIDATORFACTORY_HPP

#include <QObject>

class QValidator;
class QWidget;

namespace cs
{
    class ValidatorFactory : public QObject
    {
        Q_OBJECT

    public:
        enum class Type
        {
            Ip,
            Port
        };

        static QValidator* create(Type type, QObject* parent) noexcept;
    };
}

#endif // VALIDATORFACTORY_HPP
