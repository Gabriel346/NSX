#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "camera.h"
#include "tools/transformtool.h"

#include "mesh.h"
#include "scene.h"
#include "tools/tool.h"
#include "viewportaxis.h"
#include "viewportgrid.h"
#include "selection.h"

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLFramebufferObject>

#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>

class QElapsedTimer;

// NSX
class Mesh;

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:

    explicit Viewport(QWidget *parent = nullptr);
    ~Viewport() override;

    static Viewport* getActiveViewport();

    Camera camera;
    ViewportGrid grid;
    ViewportAxis axis;
  //  TransformTool gizmoTransform;


// Select stuff data ------------------------------------------------
    QOpenGLFramebufferObject *selectBuffer;
    QOpenGLFramebufferObject *tool_selectBuffer = nullptr;
    static QOpenGLShaderProgram *getSelectShader(); //render element id color TODO mettere in shader manager?
    void drawSelectionBuffer(Mesh* object = nullptr, SelectionType selection_type = OBJECT);
    uint selectedObject; //object in edit mode
    int getPickBufferID();
    int getToolPickBufferID();

   // std::vector<int> getPickBufferIDs(const QRect &selection_rectangle);
    std::vector<int> getPickBufferIDs(SelectionType selection_type, bool single, QPoint top_left, QPoint bottom_right, Mesh *object3d = nullptr);

    void getRectangleSelectionBufferPixelID(QPoint, QPoint);
    GLuint select_texture;
    unsigned char* select_texture_reset;


    Tool* default_tool = nullptr;
    Tool* previousTool = nullptr;
    Tool* active_tool = nullptr;
    QElapsedTimer* tool_timer;

    int width;
    int height;

    QVector3D getMouseWorldPosition();
    QVector3D unprojectClick(QPoint click_point);


    Mesh* edit_mode_object = nullptr;

    void testGLSelect();
    void testOcclusionQuery();

    Scene scene;

  //  std::vector<QVariant> *selection;
  //  std::vector<Object3D*> sceneObjects;

    std::vector<Material*> materials;
    Material* material; //default material
    //std::map<QString, Texture> texture_catalog;


    std::map<Qt::Key, QVariant> *hotkey_bindings;

    QPoint prevPos; //TODO mouse delta as global, updated from viewport event


signals:

public slots:
    void AddObject3D(int type); //test add cube to scene
    void update();
    void setDefaultTool();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    void contextMenuEvent(QContextMenuEvent *event);
    bool event(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
};

#endif // VIEWPORT_H
