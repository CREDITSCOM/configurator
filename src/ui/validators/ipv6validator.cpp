#include "ipv6validator.hpp"

#include <QRegularExpression>

cs::Ipv6Validator::Ipv6Validator(QObject* parent):
    QRegularExpressionValidator(parent)
{
    QRegularExpression ipv6Regexpr("");
    setRegularExpression(ipv6Regexpr);
}
