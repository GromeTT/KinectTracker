#ifndef SPHEREMOVEMENTANALYZER_H
#define SPHEREMOVEMENTANALYZER_H

#include "Visualizer.h"
#include "../../Analyzer/inc/SphereMovementAnalyzer.h"

class SphereMovementVisualizer : public Visualizer
{
public:
    SphereMovementVisualizer( SphereMovementAnalyzerPtr& movementAnalyzer,
                              QOpenGLWindow* window );
    virtual ~SphereMovementVisualizer();

private:
    virtual void renderV();

    RenderObject*             mp_sphere;
    SphereMovementAnalyzerPtr m_sphereMovementAnalyzer;
};

#endif // SPHEREMOVEMENTANALYZER_H
