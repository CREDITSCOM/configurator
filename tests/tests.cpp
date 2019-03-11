#include <QApplication>
#include <QTest>
#include <test_hostserializer.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new cstests::Test_HostSerializer(), argc, argv);
    return 0;
}
