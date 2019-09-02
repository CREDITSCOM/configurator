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

        inline static auto apiExecutorPortParameter = "apiexec_port";
        inline static auto executorPortParameter = "executor_port";
        inline static auto apiPortParameter = "port";
        inline static auto ajaxPortParameter = "ajax_port";
        inline static auto executorCommand = "executor_command";

        inline static auto ipParameter = "ip";
        inline static auto portParameter = "port";

        // settings.properties
        inline static auto apiNodeHost = "node.api.host";
        inline static auto apiNodePort = "node.api.port";
        inline static auto apiExecutorPort = "contract.executor.port";
        inline static auto apiExecutorNodePort = "contract.executor.node.api.port";
        inline static auto apiExecutorNodeHost = "contract.executor.node.api.host";
        inline static auto apiExecutorReadTimeout = "contract.executor.read.client.timeout";

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

    // defaults
    const QString defaultLocalHostIp = "127.0.0.1";
    const QString defaultSignalServerIp = "51.38.0.1";
    const QString defaultExecutorCommand = "java -Xmx768m -XX:MaxMetaspaceSize=256m -XX:+HeapDumpOnOutOfMemoryError -jar contract-executor.jar";

    const int defaultSignalServerPort = 6000;
    const int defaultHostInputPort = 6000;
    const int defaultApiExecutorPort = 9070;
    const int defaultApiPort = 9090;
    const int defaultAjaxPort = 8081;
    const int defautlExecutorPort = 9080;

    struct Cmds
    {
        inline static auto cmds = {
            "start java -jar contract-executor/target/contract-executor.jar",
            "start java -jar wallet-desktop/target/wallet-desktop.jar",
            "client",
        };
    };

    struct ApiData
    {
        int apiExecutorPort = 0;
        int executorPort = 0;
        int ajaxPort = 0;
        int apiPort = 0;
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

        ApiData api;
    };
}

#endif // COMMON_HPP
