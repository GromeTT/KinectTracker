#ifndef PROCESSINGCOMPONENT_H
#define PROCESSINGCOMPONENT_H

#include <QObject>
#include <QVector>

class ProcessingComponent : public QObject
{
public:
    ProcessingComponent( QObject* parent = nullptr );
    virtual ~ProcessingComponent();

    void addComponent( ProcessingComponent* compnent );
    const QVector<ProcessingComponent*>& getComponents() const;
    ProcessingComponent* getProcessingComponent( const int index ) const;

private:
    QVector<ProcessingComponent*> m_components;

};

#endif // PROCESSINGCOMPONENT_H
