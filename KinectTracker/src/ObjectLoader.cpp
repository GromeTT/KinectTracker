#include "../inc/ObjectLoader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


LoaderObject::LoaderObject()
{

}

LoaderObject::~LoaderObject()
{
}

void LoaderObject::addVertex( const Vertex vertex )
{
    m_vertices.append( vertex );
}

void LoaderObject::addIndice( const unsigned int indice )
{
    m_indices.append( indice );
}

const Vertices& LoaderObject::getVertices() const
{
    return m_vertices;
}

const QVector<unsigned int>& LoaderObject::getIndices() const
{
    return m_indices;
}



/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/


ObjectLoader::ObjectLoader()
    :m_filename( "" )
{

}

ObjectLoader::ObjectLoader( const QString& filename )
    : m_filename( filename )
{

}

ObjectLoader::~ObjectLoader()
{

}

void ObjectLoader::setFilename( const QString& filename )
{
    m_filename = filename;
}

LoaderObjectPtr ObjectLoader::load()
{
    QFile file ( m_filename );
    if ( !file.open( QFile::ReadOnly ) )
    {
        qWarning() << QString("Could not open file : %1").arg( m_filename );
        return LoaderObjectPtr();
    }
    QTextStream streamer( &file );
    LoaderObjectPtr obj ( new LoaderObject() );
    while ( !streamer.atEnd() )
    {
        QString line = streamer.readLine();
        if ( line.startsWith( "v" ) )
        {
            QStringList res = line.split( " " );
            Q_ASSERT( res.count() == 4 );
            obj->addVertex( Vertex( res.at( 1 ).toFloat(), res.at( 2 ).toFloat(), res.at( 3 ).toFloat() ) );
        }
        else if ( line.startsWith( "f" ) )
        {
            QStringList res = line.split( " " );
            for ( int i = 1; i < res.count(); ++i )
            {
                obj->addIndice( res.at( i ).toUInt()-1 );
            }
        }
    }
    file.close();
    return obj;
}

QString ObjectLoader::getFilename() const
{
    return m_filename;
}
