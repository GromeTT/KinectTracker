#ifndef INTERSECTION_H
#define INTERSECTION_H

bool pointInCube( const float x,
                  const float y,
                  const float z,
                  const float cubeX,
                  const float cubeY,
                  const float cubeZ,
                  const float width,
                  const float height,
                  const float depth );

bool pointInSphere( const float x,
                    const float y,
                    const float z,
                    const float originX,
                    const float originY,
                    const float originZ,
                    const float radius );

#endif // INTERSECTION_H
