#ifndef QTPRINTFUNCTIONS_H
#define QTPRINTFUNCTIONS_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QDebug>

void printMatrix( QMatrix4x4& matrix , const QString text = "" )
{
    qDebug() << QString ( "Matrix %1" ).arg( text );
    for ( int i = 0; i <  4; ++i )
    {
        qDebug() << QString( "%1 %2 %3 %4" ).arg( matrix( i, 0 ) )
                                            .arg( matrix( i, 1 ) )
                                            .arg( matrix( i, 2 ) )
                                            .arg( matrix( i, 3 ) );
    }
}

void printMatrixInOneLine( QMatrix4x4& matrix )
{
    qDebug() << "Matrix";
    QString res;
    for ( int i = 0; i < 16; ++i )
    {
        res.append( QString::number( matrix.data()[i] ) );
        res.append( " " );
    }
    qDebug() << res;
}

void printVector3D( const QVector3D& vector, const QString& text = "" )
{
    qDebug() << QString( "%1: %2 %3 %4" ).arg( text )
                                         .arg( vector.x() )
                                         .arg( vector.y() )
                                         .arg( vector.z() );
}

void printVector4D( const QVector4D& vector, const QString& text = "" )
{
    qDebug() << QString( "%1: %2 %3 %4 %5" ).arg( text )
                                            .arg( vector.x() )
                                            .arg( vector.y() )
                                            .arg( vector.z() )
                                            .arg( vector.w() );
}

void printScalar( const float scalar, const QString& text = "" )
{
    qDebug() << QString( "%1: %2" ).arg( text )
                                 .arg( scalar );
}

#endif // QTPRINTFUNCTIONS_H
