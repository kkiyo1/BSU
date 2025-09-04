#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <QObject>

class TestInput : public QObject
{
    Q_OBJECT
public:
    explicit TestInput(QObject *parent = 0);

private slots:
    void checkPositive();
    void checkString();
};

#endif
