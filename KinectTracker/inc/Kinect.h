#ifndef KINECT_H
#define KINECT_H

#define NOMINMAX

#include "Windows.h"
#include "NuiApi.h"
#include "NuiImageCamera.h"
#include "SkeletonData.h"
#include <QVector>
#include <QSize>
#include <QSharedPointer>
#include <QOpenGLTexture>

class QImage;
class QVector2D;

class Kinect
{
public:
    enum Error
    {
        OK = S_OK, /*!< OK  <br> basdasa*/
        FAIL = E_FAIL, /*!< OK  */
        DEVICE_NOT_READY = E_NUI_DEVICE_NOT_READY, /*!< OK  */
        OUT_OF_MEMORY = E_OUTOFMEMORY,
        POINTER = E_POINTER,
        INVALIDARG = E_INVALIDARG,
        INVALID_OPERATION = ERROR_INVALID_OPERATION,
        NO_SENSOR,
        NO_FRAME_AVAILABLE,
        INTERNAL_ERROR,
        NO_INTERFACE = E_NOINTERFACE,
        WRONG_VECTOR_SIZE
    };

public:
    Kinect();
    ~Kinect();

    HRESULT initialize( const DWORD flag );
    int getSensorCount() const;
    HRESULT openRGBStream( NUI_IMAGE_RESOLUTION resolution,
                           DWORD frameFlag,
                           DWORD frameLimit,
                           HANDLE nextFrame );
    HRESULT openDepthStream( NUI_IMAGE_RESOLUTION resolution,
                             DWORD frameFlag,
                             DWORD frameLimit,
                             HANDLE nextFrame );
    HRESULT getRGBImage( QImage*& img );
    HRESULT getRGBImage( uchar* img );
    HRESULT getDepthImageAsGreyImage( QImage*& img );
    HRESULT getDepthImageAsGreyImage( uchar* img );
    HRESULT getDepthImage( std::vector<ushort>& depthData );
    HRESULT getDepthImage( ushort* img );
    HRESULT getSkeleton( QList<SkeletonDataPtr>& skeletons );
    QSize rgbStreamResolution() const;
    QSize depthStreamResolution() const;
    bool isInitialized() const;
    bool isRGBStreamOpen() const;
    bool isDepthStreamOpen() const;

private:
    void setSize( QSize& size, NUI_IMAGE_RESOLUTION resolution );

    INuiSensor* mp_sensor;
    HANDLE      m_depthHandle;
    HANDLE      m_rgbHandle;
    HANDLE      m_skeletonHandle;
    QSize       m_rgbStreamResolution;
    QSize       m_depthStreamResolution;
    bool        m_initialized;
    bool        m_rgbStreamOpen;
    bool        m_deptStreamOpen;
};

QVector2D transformFromSkeltonToRGB( const QVector3D& coordinates );

typedef QSharedPointer<Kinect> KinectPtr;

#endif // KINECT_H
