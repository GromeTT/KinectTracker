#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>

class TestObject : public QObject
{
    Q_OBJECT

public:
    TestObject( QObject* parent );
    ~TestObject();

    void setA( const float a );
    float a() const;

signals:
    void aChanged();

private:
    float m_a;

private:
    Q_PROPERTY( float a MEMBER m_a
                READ a
                WRITE setA
                NOTIFY aChanged )

};

#endif // TESTOBJECT_H



