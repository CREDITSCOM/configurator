#ifndef COMMON_HPP
#define COMMON_HPP

#include <QStringList>

namespace cs
{
    struct Literals
    {
        inline const static QString configuratorTitle = QString("CS Node Configurator");
        inline const static QString boostrap = QString("Boostrap");
        inline const static QString routerType = QString("router");
        inline const static QString listType = QString("list");
        inline const static QString signalServerType = QString("signal_server");
        inline const static QString configFileName = QString("config.ini");
        inline const static QString hostsFileName = QString("hosts.txt");

        // keys
        inline const static QString paramsKey = QString("params");
        inline const static QString signalServerKey = QString("signal_server");
        inline const static QString hostInputKey = QString("host_input");
        inline const static QString hostOutputKey = QString("host_output");

        inline const static QString sinksDefaultKey = QString("Sinks.Default");
        inline const static QString sinksFileKey = QString("Sinks.File");

        // params
        inline const static QString nodeTypeParameter = QString("node_type");
        inline const static QString boostrapTypeParameter = QString("bootstrap_type");
        inline const static QString ipv6TypeParameter = QString("ipv6");

        inline const static QString ipParameter = QString("ip");
        inline const static QString portParameter = QString("port");

        // ui lists
        inline const static QStringList boostrapTypes = {
            signalServerType,
            listType
        };

        inline const static QStringList nodeTypes = {
            routerType
        };
    };

    const QString defaultSignalServerIp = "192.168.0.28";
    const int defaultSignalServerPort = 6000;
    const int defaultHostInputPort = 9000;

    struct Data
    {
        QString nodeType;
        QString boostrapType;
        bool isIpv6 = false;

        QString signalServerIp;
        int signalServerPort = 0;

        QString nodeIp;
        int nodeOutputPort = 0;
        int nodeInputPort = 0;
    };
}

#endif // COMMON_HPP
