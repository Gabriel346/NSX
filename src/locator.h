#ifndef LOCATOR_H
#define LOCATOR_H

#include "object3d.h"

class Locator : public Object3D
{
    Q_OBJECT

public:
    Locator();

    // Object3D interface
public:
    void draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, Viewport *viewport);
    void drawSelection(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, SelectionType, int);
    void updateBBox();
};

#endif // LOCATOR_H
