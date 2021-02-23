#include "scene.h"

Scene::Scene(): hierarchyModified(false)
{
    this->setParent(this);
    this->setObjectName("SceneRoot");
    //root->setParent(root);

//    root = new Object3D;
//    root->setParent(root);
    //    root->setObjectName("SceneRoot");
}

Scene::~Scene()
{
    qDebug() << "scene destructor";
}

std::vector<Object3D*>* Scene::getObjectList()
{
    if (hierarchyModified) {
        updateObjectList();
    }
    return &objectList;
}


void Scene::updateObjectList()
{
    objectList.clear();

    std::vector<Object3D*> stack;
    stack.push_back(this);

    while(stack.size() > 0) {
        Object3D* current = stack.back();
        stack.pop_back();
        for(Object3D* children : current->children) {
            stack.push_back(children);
            objectList.push_back(children);
        }
    }
}

