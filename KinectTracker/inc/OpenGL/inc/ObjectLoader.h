#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include "Vertex.h"
#include "RenderObject.h"
#include <vector>
#include <string>

class LoaderObject
{
public:
    LoaderObject();
    ~LoaderObject();

    void addVertex( const Vertex vertex );
    void addIndice( const unsigned int indice );

    const Vertices&              getVertices() const;
    const QVector<unsigned int>& getIndices() const;

private:
    Vertices              m_vertices;
    QVector<unsigned int> m_indices;
};

typedef QSharedPointer<LoaderObject> LoaderObjectPtr;


/**************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************/

class ObjectLoader
{
public:
    enum class Format
        {
            VerticesOnly
        };

public:
    ObjectLoader();
    ObjectLoader( const QString& filename );
    ~ObjectLoader();

    void setFilename( const QString& filename );

    LoaderObjectPtr load();
    void            write( std::string& outputfile,
                           std::vector<Vertex> vertices );
    QString         getFilename( ) const;

private:
    QString m_filename;
};

#endif // OBJECTLOADER_H
