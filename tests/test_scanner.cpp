#include "test_scanner.hpp"

#include <core/scanner.hpp>
#include <core/common.hpp>

#include <QDebug>
#include <QFile>
#include <QTest>

static const char* generatedData =  "[params]\n"
                                    "node_type=client\n"
                                    "bootstrap_type=signal_server\n"
                                    "ipv6=false\n"
                                    "hosts_filename=hosts.txt\n"
                                    "\r\n"
                                    "[signal_server]\n"
                                    "ip=51.38.0.1\n"
                                    "port=6000\n"
                                    "\r\n"
                                    "[host_input]\n"
                                    "port=9000\n"
                                    "\r\n"
                                    "[api]\n"
                                    "apiexec_port=9070\n"
                                    "executor_port=9080\n"
                                    "port=9090\n"
                                    "ajax_port=8081\n"
                                    "\r\n"
                                    "[Sinks.Default]\n"
                                    "Destination=\"Console\"\n"
                                    "Filter=\"%Severity% >= info\"\n"
                                    "Format=\"[%Severity%] %Message%\"";

cstests::Test_Scanner::Test_Scanner(QObject* parent):
    QObject(parent)
{
    generate();
}

void cstests::Test_Scanner::generate()
{
    if (QFile::exists(cs::Literals::configFileName)) {
        QFile::remove(cs::Literals::configFileName);
    }

    QFile file(cs::Literals::configFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);
    stream << generatedData;

    file.close();
}

void cstests::Test_Scanner::clean()
{
    if (QFile::exists(cs::Literals::configFileName)) {
        QFile::remove(cs::Literals::configFileName);

        qDebug() << cs::Literals::configFileName << " cleaned";
    }
}

void cstests::Test_Scanner::read()
{
    cs::Scanner scanner(cs::Literals::configFileName);
    cs::Scanner::Status status = scanner.status();

    QCOMPARE(status, cs::Scanner::Status::NoError);
}

void cstests::Test_Scanner::write()
{
    if (!QFile::exists(cs::Literals::configFileName)) {
        generate();
    }

    cs::Scanner scanner1(cs::Literals::configFileName);
    cs::Scanner::Status status1 = scanner1.status();

    QCOMPARE(status1, cs::Scanner::Status::NoError);

    cs::Scanner scanner2(cs::Literals::configFileName);
    cs::Scanner::Status status2 = scanner2.status();

    QCOMPARE(status2, cs::Scanner::Status::NoError);

    QString str1 = scanner1.toString();
    QString str2 = scanner2.toString();

    QCOMPARE(str1, str2);

    scanner1.sync();

    QString readedStr1;
    QString readedStr2;

    {
        QFile file(cs::Literals::configFileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        readedStr1 = file.readAll();
    }

    scanner2.sync();

    {
        QFile file(cs::Literals::configFileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        readedStr2 = file.readAll();
    }

    QCOMPARE(readedStr1, readedStr2);
}

void cstests::Test_Scanner::cleanupTestCase()
{
    clean();
}
