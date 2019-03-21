#ifndef COMMON_HPP
#define COMMON_HPP

#include <QStringList>

namespace cs
{
    struct Literals
    {
        // default program liters
        inline static auto configuratorTitle = "CS Node Configurator";
        inline static auto boostrap = "Boostrap";
        inline static auto routerType = "router";
        inline static auto clientType = "client";
        inline static auto listType = "list";
        inline static auto signalServerType = "signal_server";
        inline static auto configFileName = "config.ini";
        inline static auto hostsFileName = "hosts.txt";

        inline static auto cslauncherFileName = "cs-launcher.exe";
        inline static auto propertySettingsFileName = "settings.properties";

        // keys
        inline static auto paramsKey = "params";
        inline static auto signalServerKey = "signal_server";
        inline static auto hostInputKey = "host_input";
        inline static auto hostOutputKey = "host_address";
        inline static auto apiKey = "api";

        // sinks
        inline static auto sinksConsoleKey = "Sinks.Console";
        inline static auto sinksDefaultKey = "Sinks.Default";
        inline static auto sinksFileKey = "Sinks.File";

        // params
        inline static auto nodeTypeParameter = "node_type";
        inline static auto boostrapTypeParameter = "bootstrap_type";
        inline static auto ipv6TypeParameter = "ipv6";
        inline static auto executorPortParameter = "apiexec_port";

        inline static auto ipParameter = "ip";
        inline static auto portParameter = "port";

        // ui lists
        inline const static QStringList boostrapTypes = {
            signalServerType,
            listType
        };

        inline const static QStringList nodeTypes = {
            clientType,
            routerType
        };
    };

    const QString defaultSignalServerIp = "51.38.0.1";
    const int defaultSignalServerPort = 6000;
    const int defaultHostInputPort = 9000;
    const int defaultExecutorPort = 9070;

    struct Cmds
    {
        constexpr inline static auto cmds = {
            "start java -jar contract-executor/target/contract-executor.jar",
            "start java -jar wallet-desktop/target/wallet-desktop.jar",
            "client",
        };
    };

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

        int apiExecutorPort = 0;
    };
}

#endif // COMMON_HPP
