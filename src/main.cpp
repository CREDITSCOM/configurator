#include <QApplication>

#include <ui/ave.h>
#include <ui/configurator.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cs::Ave* ave = new cs::Ave();
    ave->show();

    cs::Configurator configurator;
    ave->setContinuation(&configurator);

    return a.exec();
}
