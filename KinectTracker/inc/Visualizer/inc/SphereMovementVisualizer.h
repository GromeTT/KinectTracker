#ifndef SPHEREMOVEMENTVISUALIZER_H
#define SPHEREMOVEMENTVISUALIZER_H

#include "Visualizer.h"
#include "../../Analyzer/inc/SphereMovementAnalyzer.h"

class RenderObject;

class SphereMovementVisualizer: public Visualizer
{
public:
    SphereMovementVisualizer( SphereMovementAnalyzerPtr& movementAnalyzer,
                              OpenGLWindow* window );
    virtual ~SphereMovementVisualizer();

private:
    virtual void renderV();

    RenderObject*             mp_sphere;
    SphereMovementAnalyzerPtr m_sphereMovementAnalyzer;
};

#endif // SPHEREMOVEMENTVISUALIZER_H
