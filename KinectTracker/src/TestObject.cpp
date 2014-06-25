#include "../inc/TestObject.h"

TestObject::TestObject(QObject* parent)
    : QObject( parent )
{

}

TestObject::~TestObject()
{

}

void TestObject::setA(const float a)
{
    m_a = a;
    emit aChanged();
}

float TestObject::a() const
{
    return m_a;
}
