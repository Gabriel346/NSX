#include "polygontool.h"
#include "viewport.h"
#include "mainwindow.h"

#include <QAction>
#include "qmenubar.h"
#include <application.h>

PolygonTool::PolygonTool()
{
    Application &application = Application::instance();
    QAction *action = new QAction(application.tr("&PolygonTool"));
    application.mainWindow->menuBar()->findChild<QMenu*>("modeling")->addAction(action);
    connect(action, &QAction::triggered,
            this, [this](){Application::instance().activateTool(this);
    });
}


void PolygonTool::draw(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4 &viewProjection)
{
  //  if (dragging) {
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        //glMultMatrixf((viewProjection * object->local_transform.toMatrix()).data());
        glMultMatrixf(viewProjection.data());
        glPointSize(6.0);
        glBegin(GL_POINTS);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(new_point.x(), new_point.y(), new_point.z());
            for(auto &p: points) {
                glVertex3f(p.x(), p.y(), p.z());
            }
        glEnd();
        glPopMatrix();
        glEnable(GL_DEPTH_TEST);
  //  }
}

void PolygonTool::initialize()
{
}

void PolygonTool::activate()
{
}

void PolygonTool::deactivate()
{
    points.clear();
}

void PolygonTool::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        dragging = true;
//        Viewport *viewport = Viewport::getActiveViewport();
//        QVector3D ray_origin = viewport->camera.view.column(3).toVector3D();
//        QVector3D ray_direction = viewport->unprojectClick(event->pos());
//        new_point =  ray_origin - ray_direction * 10;
    }
}

void PolygonTool::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (dragging) {
            dragging = false;
            points.push_back(new_point);
        }

        if (points.size() == 3) {
            Mesh *mesh = Viewport::getActiveViewport()->edit_mode_object;
            if (mesh != nullptr) {
                int face_id = mesh->geometry->addFace(points);
                mesh->geometry_dirty = true;
                points.clear();
            }
        }
    }
}

void PolygonTool::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging) {
        Viewport *viewport = Viewport::getActiveViewport();
        Camera camera = viewport->camera;
        QVector3D camera_position = camera.view.column(3).toVector3D();
        QVector3D ray_origin = camera_position - viewport->unprojectClick(event->pos());
        QVector3D ray_direction = (camera_position - ray_origin).normalized();
        QVector3D camera_direction = (camera_position - camera.translation).normalized(); // plane
        float distance = QVector3D::dotProduct(camera_direction, (camera.translation - ray_origin))
                / QVector3D::dotProduct(ray_direction, camera_direction);
        new_point = camera_position + ray_direction * distance;
    }

//    float dist1 = QVector3D::dotProduct(s1-v1, normal);
//    float dist2 = QVector3D::dotProduct(s2-v1, normal);
//    if ((dist1*dist2)>= 0.0f)
//        return QVector3D();
//    if (dist1==dist2)        //ray parallel to triangle plane
//        return QVector3D();
//    //intersection between ray and triangle
//    return s1+(s2-s1)*(-dist1/(dist2-dist1));

}

void PolygonTool::registerAction()
{
}
