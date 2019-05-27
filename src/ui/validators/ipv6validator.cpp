#include "ipv6validator.hpp"

#include <QRegularExpression>

cs::Ipv6Validator::Ipv6Validator(QObject* parent):
    QRegularExpressionValidator(parent)
{
    QRegularExpression ipv6Regexpr(
        R"RX(\b[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}:[0-9a-fA-f]{1,4}\b)RX");

    setRegularExpression(ipv6Regexpr);
}
