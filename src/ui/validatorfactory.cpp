#include "validatorfactory.hpp"

#include <QValidator>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

QValidator* cs::ValidatorFactory::create(cs::ValidatorFactory::Type type, QObject* parent) noexcept
{
    constexpr static int minPort = 1024;
    constexpr static int maxPort = 65535;

    switch (type)
    {
        case Type::Port:
        {
            return new QIntValidator(minPort, maxPort, parent);
        }

        case Type::Ip:
        {
            QRegularExpression regexpr("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
            return new QRegularExpressionValidator(regexpr, parent);
        }
    }

    return nullptr;
}
