#include "../inc/Kinect.h"
#include "../inc/SkeletonData.h"
#include "../../../QtPrintFunctions.h"
#include <QSize>
#include <QPoint>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <iostream>
#include <QVector2D>

/*!
    \class Kinect
    \b Kinect is a wrapper for the Microsoft kinect sensor.
*/

/*!
   \fn Kinect::Kinect
   Constructs an uninitialized Kinect object.
 */
Kinect::Kinect()
    : m_initialized( false )
    , m_rgbStreamOpen( false )
    , m_deptStreamOpen( false )
    , m_a( 0 )
    , m_b( 0 )
    , m_c( 0 )
    , m_d( 0 )
    , mp_lastDepthPixelImage( nullptr )
{
}


/*!
   \fn Kinect::~Kinect
 */
Kinect::~Kinect()
{
    // Destory the sensor
}

/*!
    \fn HRESULT Kinect::initialize( const DWORD flag )
    Initializes the Kinect with \a flag.
    \param flag
    \return
 */
HRESULT Kinect::initialize( const DWORD flag )
{
    int numSensor;
    HRESULT res = NuiGetSensorCount( &numSensor );
    if ( numSensor < 0 )
    {
        return NO_SENSOR;
    }
    if ( res != S_OK )
    {
        return INTERNAL_ERROR;
    }
    res = NuiCreateSensorByIndex( 0, &mp_sensor );
    if ( res != S_OK )
    {
        return res;
    }
    res = mp_sensor->NuiInitialize( flag );
    if ( res != S_OK )
    {
        return res;
    }
    if ( ( flag & NUI_INITIALIZE_FLAG_USES_SKELETON ) == NUI_INITIALIZE_FLAG_USES_SKELETON )
    {
        res = mp_sensor->NuiSkeletonTrackingEnable( 0,
                                                    NUI_SKELETON_TRACKING_FLAG_SUPPRESS_NO_FRAME_DATA );
        if ( res != S_OK )
        {
            return res;
        }
    }
    m_initialized = true;
    return S_OK;
}

/*!
   \fn int Kinect::getSensorCount() const
    Returns how many kinect sensors are plugged in.
 */
int Kinect::getSensorCount() const
{
    int numSensors;
    HRESULT res = NuiGetSensorCount( &numSensors );
    if ( FAILED( res ) )
    {
        return 0;
    }
    return numSensors;
}


/*!
   \brief Kinect::openRGBStream
   Das ist ein Test und soll da bitte nicht erscheinen.
 */
HRESULT Kinect::openRGBStream( NUI_IMAGE_RESOLUTION resolution,
                               DWORD frameFlag,
                               DWORD frameLimit,
                               HANDLE nextFrame )
{
    if ( mp_sensor )
    {
        HRESULT res = mp_sensor->NuiImageStreamOpen( NUI_IMAGE_TYPE_COLOR,
                                                     resolution,
                                                     frameFlag,
                                                     frameLimit,
                                                     nextFrame,
                                                     &m_rgbHandle );
        if ( res == S_OK )
        {
            setSize( m_rgbStreamResolution, resolution );
            m_rgbStreamOpen = true;
        }
        return res;

    }
    else
    {
        return NO_SENSOR;
    }
}

/*!
   \fn Kinect::openDepthStream
   \param resolution
   \param frameFlag
   \param frameLimit
   \param nextFrame
   \return
 */
HRESULT Kinect::openDepthStream( NUI_IMAGE_RESOLUTION resolution,
                                 DWORD frameFlag,
                                 DWORD frameLimit,
                                 HANDLE nextFrame )
{
    if ( mp_sensor )
    {
        HRESULT res =  mp_sensor->NuiImageStreamOpen( NUI_IMAGE_TYPE_DEPTH,
                                                      resolution,
                                                      frameFlag,
                                                      frameLimit,
                                                      nextFrame,
                                                      &m_depthHandle );
        if ( res == S_OK )
        {
            m_deptStreamOpen = true;
            setSize( m_depthStreamResolution, resolution );
        }
        const int size = depthStreamResolution().width() * depthStreamResolution().height() ;
        mp_lastDepthPixelImage = new NUI_DEPTH_IMAGE_PIXEL[size];
        return res;

    }
    else
    {
        return NO_SENSOR;
    }
}


HRESULT Kinect::getRGBImage( QImage*& img )
{
    Q_ASSERT( m_initialized );
    Q_ASSERT( m_rgbStreamOpen );
    if ( !mp_sensor )
    {
        return NO_SENSOR;
    }
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_rgbHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {
        const BYTE* curr = ( const BYTE* ) LockedRect.pBits;
        const BYTE* dataEnd = curr + ( m_rgbStreamResolution.width() * m_rgbStreamResolution.height()) * 4;
        img = new QImage( m_rgbStreamResolution.width(), m_rgbStreamResolution.height(), QImage::Format_RGB32 );
        int i = 0;
        int j = 0;
        while ( curr < dataEnd )
        {
            // Kinect stores the color in BRGA format.
            BYTE blue      = curr[0];
            BYTE green     = curr[1];
            BYTE red       = curr[2];
            BYTE alpha     = curr[3];
            Q_UNUSED( alpha );
            img->setPixel( i, j, qRgb( red, green, blue ) );
            if ( i < m_rgbStreamResolution.width()-1 )
            {
                ++i;
            }
            else
            {
                i = 0;
                ++j;
            }
            curr += 4;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_rgbHandle, &imageFrame ); // Delete frame data

    return res;
}

/*!
   \brief Kinect::getDepthImage
   If a rgb image is available it will be copied to \a img in BGRA format and the function
   returns S_OK.
   Otherwise \a img will not be touched and an error will be returned.
 */
HRESULT Kinect::getRGBImage( uchar* img )
{
    Q_ASSERT( m_initialized );
    Q_ASSERT( m_rgbStreamOpen );
    if ( !mp_sensor )
    {
        return NO_SENSOR;
    }
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_rgbHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {
        // NOTE: Kinect stores the image in RGBA output will be in RGB.
        uchar* curr = ( uchar* ) LockedRect.pBits;
        uchar* end  =  curr + ( m_rgbStreamResolution.width()*m_rgbStreamResolution.height()*4);
        while ( curr < end )
        {
            *img++ = *curr++;
            *img++ = *curr++;
            *img++ = *curr++;
            curr++;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_rgbHandle, &imageFrame ); // Deletes the frame data
    return res;
}

HRESULT Kinect::getDepthImageAsGreyImage( QImage*& img )
{
    Q_ASSERT( m_initialized );
    Q_ASSERT( m_deptStreamOpen );
    if ( !mp_sensor )
    {
        return NO_SENSOR;
    }
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_depthHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {
        int width;
        int height;
        switch ( imageFrame.eResolution )
        {
            case NUI_IMAGE_RESOLUTION_80x60:
            {
                width = 80;
                height = 60;
                break;
            }
            case NUI_IMAGE_RESOLUTION_320x240:
            {
                width = 320;
                height = 240;
                break;
            }
            case NUI_IMAGE_RESOLUTION_640x480:
            {
                width = 640;
                height = 480;
                break;
            }
            case NUI_IMAGE_RESOLUTION_1280x960:
            {
                width = 1280;
                height = 960;
                break;
            }

        }
        const USHORT* curr = ( const USHORT* ) LockedRect.pBits;
        const USHORT* dataEnd = curr + ( width * height );
        img = new QImage( width, height, QImage::Format_RGB32 );
        int i = 0;
        int j = 0;
        while ( curr < dataEnd )
        {
            USHORT depth = NuiDepthPixelToDepth( *curr );
            // Kinect stores the color in BRGA format.
            BYTE intensity = depth == 0 || depth > 4095 ? 0 : 255 - (BYTE)(((float)depth / 4095.0f) * 255.0f);
            USHORT blue      = intensity;
            USHORT green     = intensity;
            USHORT red       = intensity;
            USHORT alpha     = 1;
            Q_UNUSED( alpha );
            img->setPixel( i, j, qRgb( red, green, blue ) );

            if ( i < width-1 )
            {
                ++i;
            }
            else
            {
                i = 0;
                ++j;
            }
            ++curr;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_depthHandle, &imageFrame );
    return res;
}

HRESULT Kinect::getDepthImageAsGreyImage( uchar* img )
{
    Q_ASSERT( m_initialized );
    Q_ASSERT( m_deptStreamOpen );
    if ( !mp_sensor )
    {
        return NO_SENSOR;
    }
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_depthHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {

        const USHORT* curr = ( const USHORT* ) LockedRect.pBits;
        const USHORT* dataEnd = curr + ( m_depthStreamResolution.width() * m_depthStreamResolution.height() );
        int i = -1;
        while ( curr < dataEnd )
        {
            USHORT depth = NuiDepthPixelToDepth( *curr );
            BYTE intensity = depth == 0 || depth > 4095 ? 0 : 255 - (BYTE)(((float)depth / 4095.0f) * 255.0f);
            img[++i] =  intensity;
            img[++i] =  intensity;
            img[++i] =  intensity;

            ++curr;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_depthHandle, &imageFrame );
    return res;
}

HRESULT Kinect::getDepthImage( std::vector<ushort>& depthData )
{
    delete [] mp_lastDepthPixelImage;
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_depthHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {
        int size = m_depthStreamResolution.width() * m_depthStreamResolution.height();
        if ( depthData.size() != size )
        {
            depthData.resize( size );
        }
        const USHORT* curr = ( const USHORT* ) LockedRect.pBits;
        const USHORT* dataEnd = curr + size;
        int i = -1;
        while ( curr < dataEnd )
        {
            USHORT depth = NuiDepthPixelToDepth( *curr );
            depthData[++i] = depth;
            ++curr;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_depthHandle, &imageFrame );
    return res;
}


HRESULT Kinect::getDepthImage( ushort* img )
{
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    HRESULT res;
    if ( res = mp_sensor->NuiImageStreamGetNextFrame( m_depthHandle, 0, &imageFrame ) < 0 )
    {
        return res;
    }
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);
    if ( LockedRect.Pitch != 0 )
    {
        const int size = m_depthStreamResolution.width() * m_depthStreamResolution.height();

        memcpy( mp_lastDepthPixelImage, LockedRect.pBits, size );
        const USHORT* curr = ( const USHORT* ) LockedRect.pBits;
        const USHORT* dataEnd = curr + ( size );
        int i = -1;
        while ( curr < dataEnd )
        {
            USHORT depth = NuiDepthPixelToDepth( *curr );
            img[++i] = depth ;
            ++curr;
        }
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_depthHandle, &imageFrame );
    return res;
}

/**
 * @brief Kinect::getSkeleton
 * @param skeletons
 * @return
 */
HRESULT Kinect::getSkeleton( QList<SkeletonDataPtr>& skeletons )
{
    NUI_SKELETON_FRAME skeletonFrame;
    if ( mp_sensor->NuiSkeletonGetNextFrame( 0, &skeletonFrame) != S_OK )
    {
        // WARNING: Information about error is lost this way.
        return 1;
    }
    // Smooth skeleton data
    mp_sensor->NuiTransformSmooth( &skeletonFrame, nullptr );

    m_a = skeletonFrame.vFloorClipPlane.x;
    m_b = skeletonFrame.vFloorClipPlane.y;
    m_c = skeletonFrame.vFloorClipPlane.z;
    m_d = skeletonFrame.vFloorClipPlane.w;

    for ( int i = 0; i < NUI_SKELETON_COUNT; ++i )
    {
        switch ( skeletonFrame.SkeletonData[i].eTrackingState )
        {
            case NUI_SKELETON_TRACKED:
            {
                skeletons.append( SkeletonDataPtr ( new SkeletonData( skeletonFrame.SkeletonData[i] ) ) );
            }
        }
    }
    return S_OK;
}

QSize Kinect::rgbStreamResolution() const
{
    return m_rgbStreamResolution;
}

QSize Kinect::depthStreamResolution() const
{
    return m_depthStreamResolution;
}

bool Kinect::isInitialized() const
{
    return m_initialized;
}

bool Kinect::isRGBStreamOpen() const
{
    return m_rgbStreamOpen;
}

bool Kinect::isDepthStreamOpen() const
{
    return m_deptStreamOpen;
}

QVector4D Kinect::planeCoefficients() const
{
    return QVector4D( m_a,
                      m_b,
                      m_c,
                      m_d );
}

/*!
   \brief Kinect::transformFromRGBToSkeleton
   Transforms the coordinates in the rgb image defined by \a rgbCoordinates into skeleton space
   and saves them into \a skeltenCoordinates.
 */
bool Kinect::transformFromRGBToSkeleton( const QPoint& rgbCoordinates, QVector3D& skeletonCoordinates )
{
    qDebug() << "RGB to Skeleton";
    if ( !mp_lastDepthPixelImage )
    {
        return false;
    }
    const int size = 640*480;
    INuiCoordinateMapper* mapper;
    if  ( mp_sensor->NuiGetCoordinateMapper( &mapper ) != S_OK )
    {
        return false;
    }
    Vector4* points = new Vector4[size];
    // http://msdn.microsoft.com/en-us/library/jj883689.aspx
    mapper->MapColorFrameToSkeletonFrame( NUI_IMAGE_TYPE_COLOR,         // color encoding scheme of color frame
                                          NUI_IMAGE_RESOLUTION_640x480, // resolution color image
                                          NUI_IMAGE_RESOLUTION_640x480, // resolution depth image
                                          size,                         // number of elements in the array of depth pixels
                                          mp_lastDepthPixelImage,       // depth frame pixel data
                                          size,                         // number of depth points
                                          points );                     // output: depth pixels
    int index = rgbCoordinates.y() * 640 + rgbCoordinates.x();
    Q_ASSERT( index < size );
    Vector4 vec = points[index];
    skeletonCoordinates.setX( vec.x );
    skeletonCoordinates.setY( vec.y );
    skeletonCoordinates.setZ( vec.z );
    mapper->Release();
    printVector3D( skeletonCoordinates, "Mapped head" );
    delete [] points;
    return true;
}

/*!
   \brief Kinect::transformFromRGBToSkeleton
   \overload inect::transformFromRGBToSkeleton( const QPoint& rgbCoordinates, QVector3D& skeletonCoordinates )
{
 */
bool Kinect::transformFromRGBToSkeleton( const int x,
                                         const int y,
                                         QVector3D& skeletonCoordinates )
{
    return transformFromRGBToSkeleton( QPoint( x , y ), skeletonCoordinates );
}

void Kinect::setSize(QSize& size, NUI_IMAGE_RESOLUTION resolution)
{
    switch ( resolution )
    {
        case NUI_IMAGE_RESOLUTION_INVALID:
        {
            break;
        }
        case NUI_IMAGE_RESOLUTION_80x60:
        {
            size.setWidth( 80 );
            size.setHeight( 60 );
            break;
        }
        case NUI_IMAGE_RESOLUTION_320x240:
        {
            size.setWidth( 320 );
            size.setHeight( 240 );
            break;
        }
        case NUI_IMAGE_RESOLUTION_640x480:
        {
            size.setWidth( 640 );
            size.setHeight( 480 );
            break;
        }
        case NUI_IMAGE_RESOLUTION_1280x960:
        {
            size.setWidth( 1280 );
            size.setHeight( 960 );
            break;
        }
    }
}

/*!
   \brief transformFromSkeltonToRGB
   \param coordinates
   \return
 */
QPoint transformFromSkeltonToRGB( const QVector3D& coordinates )
{
    Vector4 vec;
    vec.x = coordinates.x();
    vec.y = coordinates.y();
    vec.z = coordinates.z();
    LONG tmpX, tmpY;
    USHORT depth;
    NuiTransformSkeletonToDepthImage( vec, &tmpX, &tmpY, &depth );
    LONG x, y;
    NuiImageGetColorPixelCoordinatesFromDepthPixel( NUI_IMAGE_RESOLUTION_640x480,
                                                    nullptr,
                                                    tmpX,
                                                    tmpY,
                                                    depth,
                                                    &x,
                                                    &y );
    return QPoint( x, y );
}

