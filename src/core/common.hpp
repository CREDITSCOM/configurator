#ifndef COMMON_HPP
#define COMMON_HPP

#include <QStringList>

namespace cs
{
    struct Literals
    {
        inline const static QString configuratorTitle = QString("CS Node Configurator");
        inline const static QString boostrap = QString("Boostrap");
        inline const static QString routerType = QString("rounter");
        inline const static QString signalServerType = QString("signal_server");
        inline const static QString configFileName = QString("config.ini");

        inline const static QStringList boostrapTypes = {
            routerType,
            signalServerType
        };
    };
}

#endif // COMMON_HPP
