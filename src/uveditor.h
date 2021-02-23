#ifndef UVEDITOR_H
#define UVEDITOR_H

#include <QDockWidget>

class Mesh;
class UVViewport;

class UVEditor : public QWidget
{
    Q_OBJECT
public:
    explicit UVEditor(QWidget *parent = nullptr);

    UVViewport* viewport;

signals:

public slots:
   // void updateSelectedMesh();
};

#endif // UVEDITOR_H
