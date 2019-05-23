#include "portvalidator.hpp"

cs::PortValidator::PortValidator(QObject* parent):
    QIntValidator(min, max, parent)
{
}
