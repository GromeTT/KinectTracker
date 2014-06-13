#ifndef DIALTE_H
#define DIALTE_H

#include <opencv2/opencv.hpp>
#include "ProcessingComponent.h"

class Dilate : public ProcessingComponent
{
    Q_OBJECT

public:
    Dilate( QObject* parent = nullptr );
    virtual ~Dilate();

    void dilate( cv::Mat& input );
    void dilate( cv::Mat& input, cv::Mat& output );

    float anchorPointX() const;
    float anchorPointY() const;
    int   iterations() const;
    int   kernelRowCount() const;
    int   kernelColumnCount() const;

    void setAnchorPointX( const float x );
    void setAnchorPointY( const float y );
    void setIterations( const float iterations );
    void setKernelRowCount( const int rowCount );
    void setKernelColumnCount ( const int columnCount );

signals:
    void anchorPointXChanged();
    void anchorPointYChanged();
    void iterationsChanged();
    void kernelRowCountChanged();
    void kernelColumnCountChanged();

private:
    float m_anchorPointX;
    float m_anchorPointY;
    int   m_iterations;
    int   m_kernelRowCount;
    int   m_kernelColumnCount;

    Q_PROPERTY( float anchorPointX MEMBER m_anchorPointX
                READ anchorPointX
                WRITE setAnchorPointX
                NOTIFY anchorPointXChanged )
    Q_PROPERTY( float anchorPointY MEMBER m_anchorPointY
                READ anchorPointY
                WRITE setAnchorPointY
                NOTIFY anchorPointYChanged )
    Q_PROPERTY( int iterations MEMBER m_iterations
                READ iterations
                WRITE setIterations
                NOTIFY iterationsChanged )
    Q_PROPERTY( int kernelRowCount MEMBER m_kernelRowCount
                READ kernelRowCount
                WRITE setKernelRowCount
                NOTIFY kernelRowCountChanged )
    Q_PROPERTY( int kernelColumnCount MEMBER m_kernelColumnCount
                READ kernelColumnCount
                WRITE setKernelColumnCount
                NOTIFY kernelColumnCountChanged )
};

typedef QSharedPointer<Dilate> DilatePtr;
#endif // DIALTE_H
