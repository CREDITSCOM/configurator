#include "ipv4validator.hpp"

#include <QRegularExpression>

cs::Ipv4Validator::Ipv4Validator(QObject* parent):
    QRegularExpressionValidator(parent)
{
    QRegularExpression ipv4Regexpr("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
    setRegularExpression(ipv4Regexpr);
}
