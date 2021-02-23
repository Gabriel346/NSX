#include "scenetreemodel.h"

SceneTreeModel::SceneTreeModel(Scene* scene, QObject* parent):
    QAbstractItemModel(parent), scene(scene)
{
  qDebug() << "a";
}


QModelIndex SceneTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Object3D *parentObject;
    if( !parent.isValid() ) {
        parentObject = scene->root();
        qDebug() << parentObject;
    } else {
        parentObject = static_cast<Object3D*>( parent.internalPointer() );
        qDebug() << parentObject;
    }

    if( row >= 0 && row < parentObject->children.size() )
        return createIndex( row, column, parentObject->children.at( row ) );
    else
        return QModelIndex();
}


QModelIndex SceneTreeModel::parent(const QModelIndex &index) const
{
    qDebug() << index;
    if( !index.isValid() )
        return QModelIndex();
    Object3D *indexObject = static_cast<Object3D*>( index.internalPointer() );
    Object3D *parentObject = indexObject->parent();
    if( parentObject == scene->root() )
        return QModelIndex();
    return createIndex( parentObject->parent()->children.indexOf( parentObject ),
        0, parentObject );
}


int SceneTreeModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "1";
    Object3D *parentObject;
    if( !parent.isValid() ) {
        qDebug() << "2";
        parentObject = scene->root();
    } else {
        qDebug() << "3";
        parentObject = static_cast<Object3D*>( parent.internalPointer() );
    }
    return parentObject->children.count();
}


QVariant SceneTreeModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data";
    if( !index.isValid() )
        return QVariant();
    if( role == Qt::DisplayRole ) {
        return static_cast<QObject*>(index.internalPointer())->objectName();
    }
    return QVariant();
}
