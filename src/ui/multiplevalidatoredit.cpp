#include "multiplevalidatoredit.hpp"
#include <QValidator>

cs::MultipleValidatorEdit::MultipleValidatorEdit(QWidget* parent):
    QLineEdit(parent)
{
    initialization();
}

cs::MultipleValidatorEdit::MultipleValidatorEdit(const QString& text, QWidget* parent):
    QLineEdit(text, parent)
{
    initialization();
}

void cs::MultipleValidatorEdit::addValidator(QValidator* validator)
{
    validator->setParent(this);
    m_validators.push_back(validator);
}

void cs::MultipleValidatorEdit::onTextChanged()
{
    if (m_validators.empty()) {
        return;
    }

    bool validation = false;
    QString string = text();
    int pos = 0;

    for (QValidator* validator : m_validators) {
        auto state = validator->validate(string, pos);

        if (state == QValidator::State::Acceptable) {
            validation = true;
        }
    }

    if (!validation) {
        undo();
    }
}

void cs::MultipleValidatorEdit::initialization()
{
    QObject::connect(this, &QLineEdit::textChanged, this, &MultipleValidatorEdit::onTextChanged);
}
