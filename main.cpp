#include <QApplication>
#include <ui/configurator.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cs::Configurator configurator;
    configurator.show();

    return a.exec();
}
