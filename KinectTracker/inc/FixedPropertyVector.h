#ifndef FIXEDPROPERTYVECTOR_H
#define FIXEDPROPERTYVECTOR_H

#include <QObject>
#include <vector>

class FixedPropertyVector
{

public:
    FixedPropertyVector();
    FixedPropertyVector( const int size );
    FixedPropertyVector( const FixedPropertyVector& other );
    ~FixedPropertyVector();

    void setData( const int index, const float data );

    const std::vector<float>& data() const;
    float at( const int index ) const;
    float last() const;
    int   size() const;

    void operator = ( const FixedPropertyVector& other );
    bool operator == ( const FixedPropertyVector& other );
    bool operator != ( const FixedPropertyVector& other );

private:
    std::vector<float> m_data;
};

#endif // FIXEDPROPERTYVECTOR_H
