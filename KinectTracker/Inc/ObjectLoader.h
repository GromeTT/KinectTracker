#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <QVector>
#include <QString>
#include "Vertex.h"

class LoaderObject
{
public:
    LoaderObject();
    ~LoaderObject();

    void addVertex( const Vertex vertex );
    void addIndice( const unsigned int indice );

    const Vertices& getVertices() const;
    const QVector<unsigned int>& getIndices() const;
private:
    Vertices m_vertices;
    QVector<unsigned int> m_indices;
};

class ObjectLoader
{
public:
    ObjectLoader();
    ObjectLoader( const QString& filename );
    ~ObjectLoader();

    void setFilename( const QString& filename );
    LoaderObject* load();
    QString      getFilename( ) const;

private:
    QString m_filename;
};

#endif // OBJECTLOADER_H
