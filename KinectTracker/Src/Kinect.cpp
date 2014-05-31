#include "../Inc/Kinect.h"
#include "../Inc/Skeleton.h"
#include <QSize>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <iostream>

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
   \param resolution
   \param frameFlag
   \param frameLimit
   \param nextFrame
   \return
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
    res = mp_sensor->NuiImageStreamReleaseFrame( m_rgbHandle, &imageFrame ); // Deletes the frame data

    return res;
}

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
        uchar* curr = ( uchar* ) LockedRect.pBits;
        uchar* end   =  curr + ( m_rgbStreamResolution.width()*m_rgbStreamResolution.height()*4 );
        while ( curr < end )
        {
//            *curr++;
            *img++ = *curr++;
            *img++ = *curr++;
            *img++ = *curr++;
            curr++;

        }
//        std::copy( curr, end, img ); // Fastes method
    }
    texture->UnlockRect( 0 );
    res = mp_sensor->NuiImageStreamReleaseFrame( m_rgbHandle, &imageFrame ); // Deletes the frame data
    return res;
}

HRESULT Kinect::getDepthImage(QImage*& img)
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

HRESULT Kinect::getDepthImage(uchar* img)
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

/**
 * @brief Kinect::getSkeleton
 * @param skeletons
 * @return
 */
HRESULT Kinect::getSkeleton( QList<Skeleton*>& skeletons )
{
    // Resize vector for storing skeletons
    qDeleteAll( skeletons );

    NUI_SKELETON_FRAME skeletonFrame;
    if ( mp_sensor->NuiSkeletonGetNextFrame( 0, &skeletonFrame) != S_OK )
    {
        // WARNING: Information about error is lost this way.
        return 1;
    }
    // Smooth skeleton data
    mp_sensor->NuiTransformSmooth( &skeletonFrame, nullptr );

    for ( int i = 0; i < NUI_SKELETON_COUNT; ++i )
    {
        switch ( skeletonFrame.SkeletonData[i].eTrackingState )
        {
            case NUI_SKELETON_TRACKED:
            {
                Skeleton* skeleton = new Skeleton( skeletonFrame.SkeletonData[i] );
                skeletons.append( skeleton );
            }
        }
    }
    return S_OK;
}

QSize Kinect::getRGBStreamResoultion() const
{
    return m_rgbStreamResolution;
}

QSize Kinect::getDepthStreamResolution() const
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
