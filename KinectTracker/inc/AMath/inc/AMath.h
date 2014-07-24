#ifndef MATH_H
#define MATH_H

#include <QVector3D>

namespace AMath
{
    const float PI = 3.14159265359f;
    const float factorRadianToDegree = 180/PI;

    float radToDegF( const float rad );
    double radToDegD( const double rad );
    void anglesFromSphericalCoordinates( float& phi, float& theta, const QVector3D& direction );

    /**************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************/

    class Circle2D
    {
    public:
        Circle2D();
        Circle2D( const float x,
                  const float y,
                  const float r );
        ~Circle2D();

        float x() const;
        float y() const;
        float radius() const;

        void setX( const float x );
        void setY( const float y );
        void setRadius( const float radius );

    private:
        float m_x;
        float m_y;
        float m_radius;
    };

    /**************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************
     **************************************************************************************************************************/

    class Rectangle3D
    {
    public:
        Rectangle3D();
        Rectangle3D( const float x,
                     const float y,
                     const float z );
        Rectangle3D( const float x,
                     const float y,
                     const float z,
                     const float width,
                     const float height );
        ~Rectangle3D();

        void setByTopLeftAndBottomRight( const QVector3D& topLeftCorner,
                                         const QVector3D& bottomRightCorner );
        void move( const float x,
                   const float y,
                   const float z );
        void setWidth( const float width );
        void setHeight( const float height );
        void resize( const float width,
                     const float height );

        float width() const;
        float height() const;
        QVector3D center() const;
        QVector3D topLeftCorner() const;
        QVector3D bottomRightCorner() const;

    private:
        float m_x;
        float m_y;
        float m_z;
        float m_width;
        float m_height;
    };
}

#endif // MATH_H
