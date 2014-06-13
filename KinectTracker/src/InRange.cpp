#include "../inc/InRange.h"



InRange::InRange()
{
    setObjectName( "InRange" );
}

InRange::~InRange()
{

}

//void InRange::inRange( cv::InputArray& src,
//                       cv::OutputArray& dst,
//                       const int channels )
//{
//    cv::inRange( src, m_lowerBoundary, m_upperBoundary, dst );
//}

//int InRange::lowerBoundary() const
//{
//    return m_lowerBoundary;
//}

//int InRange::upperBoundary() const
//{
//    return m_upperBoundary;
//}

//void InRange::setLowerBoundary(const int boundary)
//{
//    if ( m_lowerBoundary != boundary )
//    {
//        m_lowerBoundary = boundary;
//        emit lowerBoundaryChanged();
//    }
//}

//void InRange::setUpperBoundary(const int boundary)
//{
//    if ( m_upperBoundary != boundary )
//    {
//        m_upperBoundary = boundary;
//        emit upperBoundaryChanged();
//    }
//}
