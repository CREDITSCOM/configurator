#ifndef PORTVALIDATOR_HPP
#define PORTVALIDATOR_HPP

#include <QObject>
#include <QIntValidator>

namespace cs
{
    class PortValidator : public QIntValidator
    {
    public:
        explicit PortValidator(QObject* parent = nullptr);

    private:
        const static int min = 1024;
        const static int max = 65535;
    };
}

#endif // PORTVALIDATOR_HPP
