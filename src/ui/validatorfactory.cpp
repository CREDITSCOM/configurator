#include "validatorfactory.hpp"

#include <QValidator>

#include <ui/validators/portvalidator.hpp>
#include <ui/validators/ipv4validator.hpp>
#include <ui/validators/ipv6validator.hpp>

QValidator* cs::ValidatorFactory::create(cs::ValidatorFactory::Type type, QObject* parent) noexcept
{
    switch (type) {
        case Type::Port: {
            return new PortValidator(parent);
        }

        case Type::Ipv4: {
            return new Ipv4Validator(parent);
        }

        case Type::Ipv6: {
            return new Ipv6Validator(parent);
        }
    }

    return nullptr;
}
