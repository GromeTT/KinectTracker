#ifndef PROCESSINGCOMPONENT_H
#define PROCESSINGCOMPONENT_H

#include <QObject>
#include <QVector>

class ProcessingComponent : public QObject
{
public:
    ProcessingComponent();
    virtual ~ProcessingComponent();

    void addComponent( ProcessingComponent* compnent );
    QVector<ProcessingComponent*>& getComponents();

private:
    QVector<ProcessingComponent*> m_components;

};

#endif // PROCESSINGCOMPONENT_H
