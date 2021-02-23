#ifndef SCENETREEMODEL_H
#define SCENETREEMODEL_H

#include "scene.h"

#include <QAbstractItemModel>

class Scene;

class SceneTreeModel: public QAbstractItemModel
{
public:
    SceneTreeModel(Scene* scene, QObject* parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const {return 1;}
    QVariant data(const QModelIndex &index, int role) const;

private:
    Object3D* fake_root;
    Scene* scene;
};

#endif // SCENETREEMODEL_H
