#include "../inc/ProcessingComponent.h"


ProcessingComponent::ProcessingComponent()
{

}

ProcessingComponent::~ProcessingComponent()
{

}

void ProcessingComponent::addComponent( ProcessingComponent* compnent )
{
    m_components.append( compnent );
}

QVector<ProcessingComponent*>& ProcessingComponent::getComponents()
{
    return m_components;
}
