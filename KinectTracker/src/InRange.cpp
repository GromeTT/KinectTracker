#include "../inc/InRange.h"
#include <QDebug>

InRange::InRange( const int channelCount,
                  QObject* parent )
    : ProcessingComponent( parent )
    , m_lowerBounds( FixedPropertyVector( channelCount ) )
    , m_upperBounds( FixedPropertyVector( channelCount ) )
{
    setObjectName( "InRange" );
}

InRange::~InRange()
{

}

void InRange::process( cv::InputArray& input,
                       cv::OutputArray& output )
{
    cv::inRange( input,
                 m_lowerBounds.data(),
                 m_upperBounds.data(),
                 output );
}

void InRange::setLowerBounds( const FixedPropertyVector& lowerBounds )
{
    if ( m_lowerBounds != lowerBounds )
    {
        m_lowerBounds = lowerBounds;
        emit lowerBoundsChanged();
    }
}

void InRange::setUpperBounds( const FixedPropertyVector& upperBounds )
{
    if ( m_upperBounds != upperBounds )
    {
        m_upperBounds = upperBounds;
        emit upperBoundsChanged();
    }
}

const FixedPropertyVector& InRange::lowerBounds() const
{
    return m_lowerBounds;
}

const FixedPropertyVector& InRange::upperBounds() const
{
    return m_upperBounds;
}





