#include "object3d.h"
#include "viewport.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

//using //namespace NSX;

Object3D::Object3D(QObject *parent) : QObject(parent), _parent(nullptr), selected(false)
{

}

//Object3D::~Object3D()
//{

//}

void Object3D::draw(QOpenGLFunctions *f)
{

}

void Object3D::draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection,  Viewport *viewport)
{

}

void Object3D::drawSelection(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, SelectionType selection_type, int id)
{

}

Object3D* Object3D::parent()
{
    return _parent;
}

void Object3D::setParent(Object3D *p)
{
    _parent = p;
}

void Object3D::addObject3D(Object3D *object)
{
    this->children.push_back(object);
    object->setParent(this);
}


