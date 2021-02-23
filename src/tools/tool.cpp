#include "tool.h"

#include <QMatrix4x4>
#include <QVector3D>

Tool::Tool(): QObject(), initialized(false)
{

}

//Tool::~Tool()
//{

//}

void Tool::draw(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4& viewProjection)
{

}


void Tool::drawSelection(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4& viewProjection)
{

}

void Tool::initialize()
{
    initialized = true;
}

void Tool::activate()
{

}

void Tool::deactivate()
{

}

void Tool::keyPressEvent(QKeyEvent *event)
{

}

void Tool::keyReleaseEvent(QKeyEvent *event)
{

}

void Tool::mousePressEvent(QMouseEvent *event)
{

}

void Tool::mouseReleaseEvent(QMouseEvent *event)
{

}

void Tool::mouseMoveEvent(QMouseEvent *event)
{

}

void Tool::wheelEvent(QWheelEvent *event)
{

}
