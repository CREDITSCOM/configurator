/********************************************************************************
** Form generated from reading UI file 'configurator.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATOR_H
#define UI_CONFIGURATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configurator
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;

    void setupUi(QWidget *Configurator)
    {
        if (Configurator->objectName().isEmpty())
            Configurator->setObjectName(QString::fromUtf8("Configurator"));
        Configurator->resize(400, 300);
        verticalLayoutWidget = new QWidget(Configurator);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 2, 2));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(Configurator);

        QMetaObject::connectSlotsByName(Configurator);
    } // setupUi

    void retranslateUi(QWidget *Configurator)
    {
        Configurator->setWindowTitle(QApplication::translate("Configurator", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Configurator: public Ui_Configurator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATOR_H
