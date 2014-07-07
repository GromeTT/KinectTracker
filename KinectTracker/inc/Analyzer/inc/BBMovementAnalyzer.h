#ifndef BBMOVEMENTANALYZER_H
#define BBMOVEMENTANALYZER_H

#include "MovementAnalyzer.h"

class BBMovementAnalyzer : public MovementAnalyzer
{
    Q_OBJECT

public:
    BBMovementAnalyzer( QObject* parent = nullptr );
    virtual ~BBMovementAnalyzer();

    void setDeltaX( const float deltaX );
    void setDeltaY( const float deltaY );
    void setDeltaZ( const float deltaZ );

    float deltaX() const;
    float deltaY() const;
    float deltaZ() const;

signals:
    void deltaXChanged();
    void deltaYChanged();
    void deltaZChanged();

private:
    virtual void anaylzeV( const SkeletonDataPtr skeleton,
                           const unsigned int timestamp );
    virtual void resetV();

    float               m_deltaX;
    float               m_deltaY;
    float               m_deltaZ;

private:

    Q_PROPERTY( float deltaX MEMBER m_deltaX
                READ deltaX
                WRITE setDeltaX
                NOTIFY deltaXChanged )

    Q_PROPERTY( float deltaY MEMBER m_deltaY
                READ deltaY
                WRITE setDeltaY
                NOTIFY deltaYChanged )

    Q_PROPERTY( float deltaZ MEMBER m_deltaZ
                READ deltaZ
                WRITE setDeltaZ
                NOTIFY deltaZChanged )
};

typedef QSharedPointer<BBMovementAnalyzer> BBMovementAnalyzerPtr;

#endif // BBMOVEMENTANALYZER_H
