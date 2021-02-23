#ifndef VIEWPORTGRID_H
#define VIEWPORTGRID_H

#include "object3d.h"

class QOpenGLShaderProgram;

class ViewportGrid : public Object3D
{
public:
    ViewportGrid();

    void init();
    void createGrid(int size);
    void draw(QMatrix4x4 viewProjection);
    void draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection);

    int size;
    QVector<QVector3D> vertices;
    QVector<GLushort> indices;
    GLushort gridaxisindex[4];

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLBuffer indexBuffer2;
    QOpenGLVertexArrayObject vertexArrayObject;

    QOpenGLShaderProgram *shaderProgram;
    int u_modelViewProj;
    int u_color;

    QVector3D color = QVector3D(0.33f, 0.33f, 0.33f);
    QVector3D axisColor = QVector3D(0.11f, 0.11f, 0.11f);

    private:

};

#endif // VIEWPORTGRID_H
