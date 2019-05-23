#ifndef IPV4VALIDATOR_HPP
#define IPV4VALIDATOR_HPP

#include <QRegularExpressionValidator>

namespace cs
{
    class Ipv4Validator : public QRegularExpressionValidator
    {
    public:
        explicit Ipv4Validator(QObject* parent = nullptr);
    };
}

#endif // IPV4VALIDATOR_HPP
