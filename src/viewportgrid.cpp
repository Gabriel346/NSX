#include "viewportgrid.h"

#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector3D>

//using //namespace NSX;

ViewportGrid::ViewportGrid()
{

}

void ViewportGrid::init() {
    //initializeOpenGLFunctions();

    createGrid(16);

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/position.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/only_color.frag");
    shaderProgram->link();
    shaderProgram->bind();
    u_modelViewProj = shaderProgram->uniformLocation("modelViewProj");
    u_color = shaderProgram->uniformLocation("color");

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(&vertices[0], vertices.size()*sizeof(QVector3D));

    indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    indexBuffer.allocate(&indices[0], indices.size()*sizeof(GLushort));

//    indexBuffer2 = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBuffer2.create();
//    indexBuffer2.bind();
//    indexBuffer2.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    indexBuffer2.allocate(&indices2[0], indices2.size()*sizeof(GLushort));

    vertexArrayObject.create();
    vertexArrayObject.bind();
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 12);
    vertexArrayObject.release();

    indexBuffer.release();
    vertexBuffer.release();
    shaderProgram->release();

}


void ViewportGrid::createGrid(int size) {
    vertices.clear();
    indices.clear();

    GLushort index = 0;
    for (int i = -size; i <= size; i++) {
         vertices.push_back(QVector3D(i, 0, size));
         vertices.push_back(QVector3D(i, 0, -size));

         indices.push_back(index);
         indices.push_back(++index);
         index++;

         vertices.push_back(QVector3D(-size, 0, i));
         vertices.push_back(QVector3D(size, 0, i));

         indices.push_back(index);
         indices.push_back(++index);
         index++;
    }

    int lines = (size * 2 + 1) * 4;
    gridaxisindex[0] = size*4;
    gridaxisindex[1] = size*4 + 1;
    gridaxisindex[2] = size*4 + 2;
    gridaxisindex[3] = size*4 + 3;

}


void ViewportGrid::draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection)
{
    shaderProgram->bind();
    shaderProgram->setUniformValue(u_modelViewProj, *viewProjection * local_transform.toMatrix());


    vertexArrayObject.bind();

    //grid axis
    shaderProgram->setUniformValue(u_color, axisColor);
    f->glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, gridaxisindex);


    //grid
    indexBuffer.bind();
    shaderProgram->setUniformValue(u_color, color);
    f->glDrawElements(GL_LINES, (16*2+1)*4, GL_UNSIGNED_SHORT, nullptr);
    indexBuffer.release();



    vertexArrayObject.release();
    shaderProgram->release();
}





