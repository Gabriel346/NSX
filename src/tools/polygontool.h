#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include "tool.h"

#include <QVector3D>

class Face;

class PolygonTool: Tool
{
    Q_OBJECT

public:
    PolygonTool();


    enum state {
      NONE,
      NEW_POLYGON
    };


    std::vector<QVector3D> points;
    QVector3D new_point;
    Face *face;

    bool dragging;

    void draw(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4 &viewProjection);
    void initialize();
    void activate();
    void deactivate();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void registerAction();
};

#endif // POLYGONTOOL_H
