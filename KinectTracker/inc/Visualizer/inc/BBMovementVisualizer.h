#ifndef BBMOVEMENTVISUALIZER_H
#define BBMOVEMENTVISUALIZER_H

#include "Visualizer.h"
#include "../../Analyzer/inc/BBMovementAnalyzer.h"

class RenderObject;

class BBMovementVisualizer : public Visualizer
{
public:
    BBMovementVisualizer( BBMovementAnalyzerPtr& movementAnalyzer,
                          OpenGLWindow* window );
    virtual ~BBMovementVisualizer();

private:
    virtual void renderV();

    RenderObject*         mp_boundingBoxLowerBody;
    BBMovementAnalyzerPtr m_movementAnalyzer;
};


#endif // BBMOVEMENTVISUALIZER_H
