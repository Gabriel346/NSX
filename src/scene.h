#ifndef SCENE_H
#define SCENE_H

#include "object3d.h"

#include <QObject>

class Scene: public Object3D //TOOD usare un Object3D come root
{
public:
    Scene();
    ~Scene();

    bool hierarchyModified;

    std::map<QString, Object3D*> object_map;
    std::vector<Object3D*> objectList; // cache in ordine del scene tree
    std::vector<Object3D*>* getObjectList();
    void updateObjectList();

    Object3D* root() { return (Object3D*)this; }
};

#endif // SCENE_H
