#include "../inc/ProcessingComponent.h"


ProcessingComponent::ProcessingComponent( QObject* parent )
    : QObject( parent )
{

}

ProcessingComponent::~ProcessingComponent()
{

}

void ProcessingComponent::addComponent( ProcessingComponent* compnent )
{
    m_components.append( compnent );
}

const QVector<ProcessingComponent*>& ProcessingComponent::getComponents() const
{
    return m_components;
}

ProcessingComponent*ProcessingComponent::getProcessingComponent( const int index ) const
{
    return m_components.at( index );
}
