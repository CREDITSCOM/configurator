#include "ipv4validator.hpp"

#include <QRegularExpression>

cs::Ipv4Validator::Ipv4Validator(QObject* parent):
    QRegularExpressionValidator(parent)
{
    QRegularExpression ipv4Regexpr(R"RX(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)RX");
    setRegularExpression(ipv4Regexpr);
}
