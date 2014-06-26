#include "../inc/RectangleHistogram.h"

/*!
   \brief RectangleHistogram::RectangleHistogram
   Constructs an Rectangle with center (0, 0),
   a width = 0  and a height = 0.
 */
RectangleHistogram::RectangleHistogram()
    : m_x( 0 )
    , m_y( 0 )
    , m_width( 0 )
    , m_height( 0 )
{
}

/*!
   \brief RectangleHistogram::RectangleHistogram
   Constructs a rectangle with center (x, y).
   The dimensions are define by \a width and \a height.
 */
RectangleHistogram::RectangleHistogram( const int x,
                                        const int y,
                                        const int width,
                                        const int height )
    : m_x( x - width/2 )
    , m_y( y - height/ 2)
    , m_width( width )
    , m_height( height )
{
}

RectangleHistogram::~RectangleHistogram()
{

}
