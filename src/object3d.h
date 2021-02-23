#ifndef M3DOBJECT_H
#define M3DOBJECT_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QUuid>

#include "transform3d.h"
#include "selection.h"

class Viewport;

class Object3D : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Transform3D local_transform READ localTransform WRITE setLocalTransform)

public:
    explicit Object3D(QObject *parent = nullptr);

    QUuid id;

    Transform3D local_transform;
    Transform3D global_transform;
    virtual void draw(QOpenGLFunctions *f);
    virtual void draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection,  Viewport *viewport);
    virtual void drawSelection(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, SelectionType selection_type, int id);

    Object3D *parent();
    void setParent(Object3D*);

    QVector<Object3D*> children;
    void addObject3D(Object3D*);

    void updateTransform();
    bool selected;

    float bb_distance;
    virtual void updateBBox() {}

    Transform3D localTransform() { return local_transform; }
    void setLocalTransform(Transform3D t) { local_transform = t; }

private:
    Object3D *_parent;

};


Q_DECLARE_METATYPE(Object3D*)

#endif // M3DOBJECT_H
