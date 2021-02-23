#ifndef UVVIEWPORT_H
#define UVVIEWPORT_H

#include <qopenglfunctions.h>
#include <qopenglwidget.h>

#include <QOpenGLBuffer>

class Mesh;
class Camera;
class QOpenGLShaderProgram;
//class QOpenGLBuffer;
class QOpenGLTexture;

class UVViewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit UVViewport(QWidget *parent = nullptr);

    Mesh *current_mesh;
    Camera *camera;
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLBuffer vertex_buffer; // normal display
    QOpenGLTexture *texture;

   // bool active = false;

signals:

public slots:
   // void update();

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // UVVIEWPORT_H
