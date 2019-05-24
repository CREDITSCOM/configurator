#ifndef MULTIPLEVALIDATOREDIT_HPP
#define MULTIPLEVALIDATOREDIT_HPP

#include <vector>
#include <QLineEdit>

class QValidator;

namespace cs
{
    class MultipleValidatorEdit : public QLineEdit
    {
    public:
        explicit MultipleValidatorEdit(QWidget* parent = nullptr);
        explicit MultipleValidatorEdit(const QString& text, QWidget* parent = nullptr);

        void addValidator(QValidator* validator);

    protected:
        void onTextChanged(const QString& text);

    private:
        void initialization();

        std::vector<QValidator*> m_validators;
    };
}

#endif // MULTIPLEVALIDATOREDIT_HPP
