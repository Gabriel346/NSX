#include "viewportaxis.h"

#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector3D>

//using //namespace NSX;

#define ARROW_L 0.6f
#define ARROW_W 0.1f

#define r QVector3D(1, 0, 0)
#define g QVector3D(0, 1, 0)
#define b QVector3D(0, 0, 1)

const QVector3D ViewportAxis::vertices[] = {
    QVector3D(0, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0), QVector3D(0, 0, 1),             // 0-5
    QVector3D(ARROW_L, ARROW_W, 0), QVector3D(ARROW_L, -ARROW_W, 0), QVector3D(ARROW_L, 0, ARROW_W), QVector3D(ARROW_L, 0, -ARROW_W), //x  6-9
    QVector3D(ARROW_W, ARROW_L, 0), QVector3D(-ARROW_W, ARROW_L, 0), QVector3D(0, ARROW_L, ARROW_W), QVector3D(0, ARROW_L, -ARROW_W), //y 10-13
    QVector3D(ARROW_W, 0, ARROW_L), QVector3D(-ARROW_W, 0, ARROW_L), QVector3D(0, -ARROW_W, ARROW_L), QVector3D(0, ARROW_W, ARROW_L)  //z 14-17
};

const QVector3D ViewportAxis::colors[] = {
    r, r, g, g, b, b,             // 0-5
    r, r, r, r, //x  6-9
    g, g, g, g, //y 10-13
    b, b, b, b  //z 14-17
};

const GLushort ViewportAxis::indices[] = {
    0, 1, 2, 3, 4, 5,
    1, 6, 7, 1, 8, 9,
    3, 10, 11, 3, 12, 13,
    5, 14, 15, 5, 16, 17
};

#undef ARROW_L
#undef ARROW_W

#undef r
#undef g
#undef b

ViewportAxis::ViewportAxis()
{
}


void ViewportAxis::init() {
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/color.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/vertex_color.frag");
    shaderProgram->link();
    shaderProgram->bind();
    u_modelViewProj = shaderProgram->uniformLocation("modelViewProj");
    u_color = shaderProgram->uniformLocation("color");


    vertexArrayObject.create();
    vertexArrayObject.bind();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(&vertices[0], 18*sizeof(QVector3D));
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 12);
    vertexBuffer.release();

    colorBuffer.create();
    colorBuffer.bind();
    colorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    colorBuffer.allocate(&colors[0], 18*sizeof(QVector3D));
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, 0, 3, 12);
    colorBuffer.release();

//    indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBuffer.create();
//    indexBuffer.bind();
//    indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    indexBuffer.allocate(&indices[0], 24*sizeof(GLushort));

//    indexBuffer2 = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBuffer2.create();
//    indexBuffer2.bind();
//    indexBuffer2.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    indexBuffer2.allocate(&indices2[0], indices2.size()*sizeof(GLushort));
    vertexArrayObject.release();
 //   indexBuffer.release();
    shaderProgram->release();

}


void ViewportAxis::draw(QOpenGLFunctions *f, QQuaternion camera)
{
    identity.setToIdentity();
    identity.rotate(camera);
    identity.scale(1, 1, -1); // ??
    shaderProgram->bind();
    shaderProgram->setUniformValue(u_modelViewProj, identity.inverted());
    vertexArrayObject.bind();
   // indexBuffer.bind();
    f->glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, indices+6);
   // indexBuffer.release();
    vertexArrayObject.release();
    shaderProgram->release();
}





