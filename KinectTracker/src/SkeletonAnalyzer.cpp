#include "../inc/SkeletonAnalyzer.h"
#include "../inc/Skeleton.h"
#include <QVector3D>

SkeletonAnalyzer::SkeletonAnalyzer()
    : m_boxes( QVector<BoundingBoxWidthTimeStamp*>( 200 ) )
    , m_deltaX( 0.1f )
    , m_deltaY( 0.1f )
    , m_deltaZ( 0.1f )
{
}

SkeletonAnalyzer::~SkeletonAnalyzer()
{
    qDeleteAll( m_boxes );
}

void SkeletonAnalyzer::update( const Skeleton* skeleton,
                               const unsigned int timestamp )
{
    if ( m_boxes.first() )
    {
        if ( !m_boxes.first()->mp_box->arePointsInBoundingBox( skeleton->getJoints() ) )
        {
            BoundingBoxPtr bb ( new BoundingBox ( skeleton->getJoints(),
                                                  m_deltaX,
                                                  m_deltaY,
                                                  m_deltaZ ) );
            addBoundingBox( bb, timestamp );
        }
        else
        {
            // Update timestamp
            BoundingBoxPtr bb ( m_boxes.first()->mp_box );
            addBoundingBox( bb, timestamp );
        }
    }
    else
    {
        BoundingBoxPtr bb ( new BoundingBox ( skeleton->getJoints(),
                                              m_deltaX,
                                              m_deltaY,
                                              m_deltaZ ) );
        addBoundingBox( bb, timestamp );
    }
}

void SkeletonAnalyzer::setDeltaX( const float deltaX )
{
    m_deltaX = deltaX;
}

void SkeletonAnalyzer::setDeltaY(const float deltaY)
{
    m_deltaY = deltaY;
}

void SkeletonAnalyzer::setDeltaZ(const float deltaZ)
{
    m_deltaZ = deltaZ;
}

float SkeletonAnalyzer::deltaX() const
{
    return m_deltaX;
}

float SkeletonAnalyzer::deltaY() const
{
    return m_deltaY;
}

float SkeletonAnalyzer::deltaZ() const
{
    return m_deltaZ;
}

bool SkeletonAnalyzer::arePointsInLastBoundingBox(const Vertices& vertices)
{
    if ( !m_boxes.first() )
    {
        return false;
    }
    else
    {
        return m_boxes.first()->mp_box->arePointsInBoundingBox( vertices );
    }
}

QVector3D SkeletonAnalyzer::getVelocity( const unsigned int timestamp,
                                         const unsigned int ms )
{
    Q_ASSERT( timestamp > ms );
    unsigned int d = timestamp - ms;
    for ( int i = 0; i < 200; ++i )
    {
        if ( m_boxes.at( i ) &&
             m_boxes.at( i )->m_timestamp < d )
        {
            return QVector3D( m_boxes.first()->mp_box->getX() - m_boxes.at( i )->mp_box->getX(),
                              m_boxes.first()->mp_box->getY() - m_boxes.at( i )->mp_box->getY(),
                              m_boxes.first()->mp_box->getZ() - m_boxes.at( i )->mp_box->getZ() );
        }
    }
    return QVector3D();
}

const BoundingBox* SkeletonAnalyzer::getLastBoundingBox() const
{
    if ( !m_boxes.first() )
    {
        return nullptr;
    }
    else
    {
        return m_boxes.first()->mp_box.data();
    }
}

void SkeletonAnalyzer::addBoundingBox( BoundingBoxPtr& boundingBox,
                                       const unsigned int timestamp )
{
    m_boxes.prepend( new BoundingBoxWidthTimeStamp ( boundingBox, timestamp ) );
    if ( m_boxes.count( ) > 200 )
    {
        BoundingBoxWidthTimeStamp* bbw = m_boxes.takeLast();
        delete bbw;
        bbw = nullptr;
    }
}

SkeletonAnalyzer::BoundingBoxWidthTimeStamp::BoundingBoxWidthTimeStamp( BoundingBoxPtr& boudingBox,
                                                                        unsigned int timestamp )
    : mp_box( boudingBox )
    , m_timestamp( timestamp)
{

}
