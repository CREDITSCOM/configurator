#ifndef IPV6VALIDATOR_HPP
#define IPV6VALIDATOR_HPP

#include <QRegularExpressionValidator>

namespace cs
{
    class Ipv6Validator : public QRegularExpressionValidator
    {
    public:
        explicit Ipv6Validator(QObject* parent);
    };
}

#endif // IPV6VALIDATOR_HPP
