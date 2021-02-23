#ifndef VIEWPORTAXIS_H
#define VIEWPORTAXIS_H

#include "object3d.h"

class QOpenGLShaderProgram;

class ViewportAxis: public Object3D
{
public:
    ViewportAxis();
    void init();
    void createGrid(int size);

    void draw(QOpenGLFunctions *f, QQuaternion camera);

    static const QVector3D vertices[18];
    static const QVector3D colors[18];
    static const GLushort indices[24]; //6 + 18

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer colorBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;

    QOpenGLShaderProgram *shaderProgram;
    int u_modelViewProj;
    int u_color;

    QVector3D color = QVector3D(0.33f, 0.33f, 0.33f);
    QVector3D red = QVector3D(1.0f, 0.0f, 0.0f);


private:
    QMatrix4x4 identity;

};

#endif // VIEWPORTAXIS_H
