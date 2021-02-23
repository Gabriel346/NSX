#ifndef MANIPULATORTOOL_H
#define MANIPULATORTOOL_H

#include "tool.h"

class NavigationTool: public Tool
{
    //Q_OBJECT

public:

    explicit NavigationTool();

    void draw(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4 &viewProjection);

    void activate();
    void deactivate();

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

};

//Q_DECLARE_METATYPE(NavigationTool*)

#endif // MANIPULATORTOOL_H
