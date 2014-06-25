#include "../inc/FixedPropertyVector.h"
#include <QDebug>

FixedPropertyVector::FixedPropertyVector()
    : m_data ( std::vector<float>( 0 ) )
{
}

FixedPropertyVector::FixedPropertyVector( const int size )
    : m_data ( std::vector<float>( size ) )
{
}

FixedPropertyVector::FixedPropertyVector( const FixedPropertyVector& other )
{
    m_data.resize( other.size() );
    for ( int i = 0; i < other.size(); ++i )
    {
        m_data[i] = other.m_data.at( i );
    }
}

FixedPropertyVector::~FixedPropertyVector()
{

}

void FixedPropertyVector::setData( const int index,
                                   const float data )
{
    m_data[index] = data;
}

const std::vector<float>& FixedPropertyVector::data() const
{
    return m_data;
}

float FixedPropertyVector::at( const int index ) const
{
    return m_data.at( index );
}

float FixedPropertyVector::last() const
{
    return m_data.back();
}

int FixedPropertyVector::size() const
{
    return static_cast<int>( m_data.size() );
}

void FixedPropertyVector::operator =( const FixedPropertyVector& other )
{
    m_data.resize( other.size() );
    for ( int i = 0; i < other.size(); ++i )
    {
        m_data[i] = other.m_data.at( i );
    }
}

bool FixedPropertyVector::operator ==( const FixedPropertyVector& other )
{
    return m_data == other.m_data;
}

bool FixedPropertyVector::operator !=(const FixedPropertyVector& other)
{
    return m_data != other.m_data;
}
