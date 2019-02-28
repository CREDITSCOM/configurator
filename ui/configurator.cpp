#include "configurator.hpp"
#include "ui_configurator.h"

#include <core/common.hpp>

cs::Configurator::Configurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configurator)
{
    ui->setupUi(this);
    setWindowTitle(cs::Literals::configuratorTitle);
}

cs::Configurator::~Configurator()
{
    delete ui;
}
