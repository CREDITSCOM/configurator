#ifndef TEST_SCANNER_HPP
#define TEST_SCANNER_HPP

#include <QObject>

namespace cstests
{
    class Test_Scanner : public QObject
    {
        Q_OBJECT

    public:
        explicit Test_Scanner(QObject *parent = nullptr);

    private:
        void generate();
        void clean();

    private slots:
        void read();
        void write();
        void cleanupTestCase();
    };
}

#endif // TEST_SCANNER_HPP
