#include "locator.h"
#include "transform3d.h"

Locator::Locator()
{

}

void Locator::draw(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, Viewport *viewport)
{
    global_transform = parent()->global_transform * local_transform;
    const QMatrix4x4 MVP = *viewProjection * global_transform.toMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(MVP.data());

    glBegin(GL_LINES);

    if (selected) {
         glColor3f(1.0, 1.0, 1.0);
    } else {
        glColor3f(0.0, 0.0, 0.5);
    }

    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glPopMatrix();

}

void Locator::drawSelection(QOpenGLFunctions *f, QMatrix4x4 *viewProjection, SelectionType selection_type, int id)
{
    global_transform = parent()->global_transform * local_transform;
    const QMatrix4x4 MVP = *viewProjection * global_transform.toMatrix();

    glLineWidth(5.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(MVP.data());


    glBegin(GL_LINES);
    glColor3f(id/255.0f, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glPopMatrix();
    glLineWidth(1.0f);
}

void Locator::updateBBox()
{
}
