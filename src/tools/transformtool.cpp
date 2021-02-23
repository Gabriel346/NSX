#include "../camera.h"
#include "transformtool.h"
#include "selectiontool.h"
#include "../viewport.h"
#include "../mesh.h"
#include "../transform3d.h"
#include "../application.h"


static const QVector3D arrowPoints[5] = {
    QVector3D(-1, 0, -1),
    QVector3D(-1, 0, 1),
    QVector3D(1, 0, -1),
    QVector3D(1, 0, 1),
    QVector3D(0, 1, 0),
};

static const GLushort arrowIndex[18] = {
    0, 1, 2,
    1, 2, 3,
    0, 1, 4,
    0, 4, 2,
    1, 3, 4,
    3, 2, 4
};


static const float selectionIDs[7] = {
    0,
    1/255.0f,
    2/255.0f,
    3/255.0f,
    4/255.0f,
    5/255.0f,
    6/255.0f
};

TransformTool::TransformTool(): Tool()
{
    selectedColor = QVector3D(1, 1, 0);
}


// Build vertex buffers TODO: static const vertex buffers
void TransformTool::initialize()
{
    QMatrix4x4 m;
    QVector3D arrowScale = QVector3D(0.025f, 0.18f, 0.025f);

    m.setToIdentity();
    m.translate(1, 0, 0);
    m.rotate(-90, QVector3D(0, 0, 1));
    m.scale(arrowScale);
    for (int i = 0; i < 5; i++) {
        vertices.push_back(m * arrowPoints[i]);
    }
    for (int i = 0; i < 18; i++) {
        indices.push_back(arrowIndex[i]);
    }

    m.setToIdentity();
    m.translate(0, 1, 0);
    m.scale(arrowScale);
    for (int i = 0; i < 5; i++) {
        vertices.push_back(m * arrowPoints[i]);
    }
    for (int i = 0; i < 18; i++) {
        indices.push_back(arrowIndex[i] + 5);
    }


    m.setToIdentity();
    m.translate(0, 0, 1);
    m.rotate(90, QVector3D(1, 0, 0));
    m.scale(arrowScale);
    for (int i = 0; i < 5; i++) {
        vertices.push_back(m * arrowPoints[i]);
    }
    for (int i = 0; i < 18; i++) {
        indices.push_back(arrowIndex[i] + 10);
    }

    //make lines
    int k = vertices.size();
    vertices.push_back(QVector3D(0, 0, 0));
    vertices.push_back(QVector3D(1, 0, 0));
    vertices.push_back(QVector3D(0, 1, 0));
    vertices.push_back(QVector3D(0, 0, 1));

    indices.push_back(k);  indices.push_back(k+1);
    indices.push_back(k);  indices.push_back(k+2);
    indices.push_back(k);  indices.push_back(k+3);

    //in between triangles
    indices.push_back(k); indices.push_back(k + 1); indices.push_back(k + 2);
    indices.push_back(k); indices.push_back(k + 2); indices.push_back(k + 3);
    indices.push_back(k); indices.push_back(k + 1); indices.push_back(k + 3);

    //TODO refactor boilerplate
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/position.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/only_color.frag");
    shaderProgram->link();
    shaderProgram->bind();
    u_modelViewProj = shaderProgram->uniformLocation("modelViewProj");
    u_color = shaderProgram->uniformLocation("color");
    u_point_size = shaderProgram->uniformLocation("point_size");

    vertexArrayObject.create();
    vertexArrayObject.bind();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(&vertices[0], vertices.size()*sizeof(QVector3D));
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 12);
    vertexBuffer.release();

    vertexArrayObject.release();

    selectTool = new SelectionTool(); // TODO prednere da tool reg
}


//TODO refactor: abbiamo una parte dove comincia la manipolazione e salva i dati, una che aggiorna, una che finisce.
//1 dovrebbe salvare oggetti e transform. Per i vertex potrebbe modificare direttamente il buffer, e dopo salvare?
void TransformTool::update(Viewport *viewport) {
    Camera camera = viewport->camera;

     if (translating) {
        QVector3D cameraPlanePoint = currentTransform.toMatrix().column(3).toVector3D(); // gizmo poition
        QVector3D cameraPlaneNormal = (camera.view.column(3).toVector3D() - camera.translation).normalized();  // camera direction

        QVector3D camera_ray_start = viewport->getMouseWorldPosition();

        //camera ray
        QVector3D cameraPosition =  camera.view.column(3).toVector3D();
        QVector3D camera_ray = (cameraPosition - camera_ray_start).normalized();

        //ray plane intersection
        float distance = QVector3D::dotProduct(cameraPlaneNormal, (cameraPlanePoint - camera_ray_start)) / QVector3D::dotProduct(camera_ray, cameraPlaneNormal);
        QVector3D rayPlanePoint = camera_ray_start + distance * camera_ray;

        QVector3D global_translation = rayPlanePoint - start_global_position; //global translation
        currentTransform.setTranslation(global_translation);

        local_translation = rayPlanePoint - start_local_position;

        if (!currentObjects.empty()) {
            // object mode
            for(int i = 0; i < currentObjects.size(); i ++) {
                currentObjects[i]->local_transform.setTranslation(currentTransforms[i].translation() + local_translation);
            }

        } else {
            // component mode

            Mesh* m = Viewport::getActiveViewport()->edit_mode_object;

            for(auto &v: currentVertices) { //from selection
                m->geometry->vertices[v.header.id]->position = v.position + local_translation;
            }
            m->geometry_dirty = true;
        }

    } else {
        if (!has_selection) return;

        startTranslation();

        QVector3D cameraPlanePoint = currentTransform.toMatrix().column(3).toVector3D(); //TODO refactor
        QVector3D cameraPlaneNormal = (camera.view.column(3).toVector3D() - camera.translation).normalized();//TODO refactor

        QVector3D camera_ray_start = viewport->getMouseWorldPosition();

        //camera ray
        QVector3D cameraPosition =  camera.view.column(3).toVector3D();
        QVector3D camera_ray = (cameraPosition - camera_ray_start).normalized();

        //ray plane intersection
        float distance = QVector3D::dotProduct(cameraPlaneNormal, (cameraPlanePoint - camera_ray_start)) / QVector3D::dotProduct(camera_ray, cameraPlaneNormal);
        QVector3D rayPlanePoint = camera_ray_start + distance * camera_ray;

        //start position in global and object local space
        start_global_position = rayPlanePoint - currentTransform.translation(); //global_space

        if (Viewport::getActiveViewport()->edit_mode_object == nullptr) {
            currentObjects.clear();
            currentTransforms.clear();

            std::vector<QVariant> &selection = Application::instance().selection;
            for(QVariant &variant: selection) { //from selection
                Object3D* o = qvariant_cast<Object3D*>(variant);
                Q_ASSERT(o != nullptr);
                if (o->parent()->selected) continue; // modifica solo il piu alto della gerarchia
                currentObjects.push_back(o);
                currentTransforms.push_back(o->localTransform());
            }
            start_local_position = rayPlanePoint;
        } else {
            currentVertices.clear();

            Mesh* m = Viewport::getActiveViewport()->edit_mode_object;
            for(auto &i: m->selected_component_array) { //from selection
                currentVertices.push_back(*m->geometry->vertices[i]); // copy
            }
            start_local_position = rayPlanePoint;
        }

    }
}

void makeArrow()
{

}

void TransformTool::updateSize(QMatrix4x4 cameraView)
{
    QVector4D cp = cameraView.column(3); //cameraView.column(3).toVector3D();
   // float distance = (currentTransform.translation() - QVector3D(cp.x(), cp.y(), cp.z())).length();
    float distance = (currentTransform.translation() - cameraView.column(3).toVector3D()).length();
    currentTransform.setScale(distance*0.13);
}


void TransformTool::showGizmo()
{

}


void TransformTool::startTranslation()
{
    translating = true;
    //startTransform = currentTransform;
}


void TransformTool::updateTranslation(QPoint mouseDelta)
{

}


void TransformTool::endTranslation()
{
    translating = false;

    if (!currentObjects.empty()) {
        // object mode
        for(int i = 0; i < currentObjects.size(); i ++) {
            currentObjects[i]->local_transform.setTranslation(currentTransforms[i].translation());
        }

        std::vector<QVariant> args;
        //args.push_back(QVariant::fromValue(currentObjects));
        args.push_back(QVariant::fromValue(local_translation));

        Application::instance().executeCommand("Translate", args);

    } else {
        // component mode

//        Mesh* m = Viewport::getActiveViewport()->edit_mode_object;

//        for(auto &v: currentVertices) { //from selection
//            m->geometry->vertices[v.header.id]->position = v.position;
//        }
//        m->geometry_dirty = true;
    }
}



void TransformTool::draw(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4& viewProjection)
{
    if (!has_selection) return;

    float distance = (currentTransform.translation() - cameraPosition).length();
    currentTransform.setScale(distance*0.13f);

    shaderProgram->bind();
    shaderProgram->setUniformValue(u_modelViewProj, viewProjection * currentTransform.toMatrix());
    vertexArrayObject.bind();
    //X
    if (this->componentSelected & X_AXIS_SELECTED) { //manage highlight
        shaderProgram->setUniformValue(u_color, selectedColor);
    } else {
        shaderProgram->setUniformValue(u_color, QVector3D(1, 0, 0));
    }
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[54]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[0]);

    //Y
    if (this->componentSelected & Y_AXIS_SELECTED) {
        shaderProgram->setUniformValue(u_color, selectedColor);
    } else {
        shaderProgram->setUniformValue(u_color, QVector3D(0, 1, 0));
    }
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[56]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[18]);

    //Z
    if (this->componentSelected & Z_AXIS_SELECTED) {
        shaderProgram->setUniformValue(u_color, selectedColor);
    } else {
        shaderProgram->setUniformValue(u_color, QVector3D(0, 0, 1));
    }
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[58]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[36]);

    vertexArrayObject.release();
    shaderProgram->release();
}


void TransformTool::drawSelection(QOpenGLFunctions *f, QVector3D cameraPosition, QMatrix4x4& viewProjection)
{
    if (!has_selection) return;

    float distance = (currentTransform.translation() - cameraPosition).length();
    currentTransform.setScale(distance*0.13f);

    shaderProgram->bind();
    shaderProgram->setUniformValue(u_modelViewProj, viewProjection * currentTransform.toMatrix());
    vertexArrayObject.bind();

//AXIS TRIANGLES
    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[4], 0, 0)); //xy
    f->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices[60]);

    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[5], 0, 0)); //yz
    f->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices[63]);

    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[6], 0, 0)); //zx
    f->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices[66]);

    glClear(GL_DEPTH_BUFFER_BIT);

//AXIS
    glLineWidth(35.0f);

    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[0], 0, 0));
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[54]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[0]);

    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[1], 0, 0));
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[56]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[18]);

    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[2], 0, 0));
    f->glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, &indices[58]);
    f->glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, &indices[36]);

    glLineWidth(1.0f);


//CENTER
    f->glDisable(GL_DEPTH_TEST);
    shaderProgram->setUniformValue(u_color, QVector3D(selectionIDs[3], 0, 0));
    shaderProgram->setUniformValue(u_point_size, 20.0f);
    f->glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, &indices[58]);
    f->glEnable(GL_DEPTH_TEST);


    vertexArrayObject.release();
    shaderProgram->release();

}

//set highlight
void TransformTool::setSelection(int id) {

}


void TransformTool::activate() {
    active = true;
    has_selection = false;
    currentObjects.clear();

    if (Viewport::getActiveViewport()->edit_mode_object != nullptr) { //TODO selection vertex array
        Mesh* m = Viewport::getActiveViewport()->edit_mode_object;
        if (m->selected_component_array.size() == 0) return;

        QVector3D center; //Transform
        for(auto &i: m->selected_component_array) { //from selection
            center += m->geometry->vertices[i]->position;
        }
        center /= m->selected_component_array.size();
        //currentObject = nullptr;
        currentTransform = (m->global_transform);
        currentTransform.translate(center);

        has_selection = true;
    } else {
        std::vector<QVariant> &selection = Application::instance().selection;
        if(!selection.empty()) {
            QVector3D center;
            for(QVariant &variant: selection) { //from selection
                Object3D* o = qvariant_cast<Object3D*>(variant);
                if (o) {
                    center += o->global_transform.translation();
                }
            }
            center /= selection.size();
            currentTransform = Transform3D();
            currentTransform.setTranslation(center);
           // Object3D* o = qvariant_cast<Object3D*>(selection->at(0));
            //if (o) {
           //     currentObject = o;
             //   currentTransform = o->global_transform;
            has_selection = true;
          //  }
        }
    }
}

//TODO setCurrentObject

void TransformTool::deactivate() {
    active = false;
    has_selection = false;
}




void TransformTool::keyPressEvent(QKeyEvent *event)
{
    //get selections
    if (event->key() == Qt::Key_V) {
        //translation
    }
}

void TransformTool::keyReleaseEvent(QKeyEvent *event)
{
    //TODO if selection engaged reset
    //TODO snaps
}


void TransformTool::mousePressEvent(QMouseEvent *event)
{
    if (this->componentSelected == NO_SELECTION || !has_selection) {
        qDebug() << "adsasdads";
        selectTool->mousePressEvent(event);
        return;
    }
    //startTranslation()
    update(Viewport::getActiveViewport());
}

void TransformTool::mouseReleaseEvent(QMouseEvent *event)
{
    if (translating) {
        endTranslation();
    } else {
        selectTool->mouseReleaseEvent(event);
    }
}

void TransformTool::mouseMoveEvent(QMouseEvent *event)
{
    if (translating) {
        update(Viewport::getActiveViewport());
    } else {
        int id = Viewport::getActiveViewport()->getToolPickBufferID();
        switch (id) {
         case 0:
            this->componentSelected = X_AXIS_SELECTED;
            break;
         case 1:
            this->componentSelected = Y_AXIS_SELECTED;
            break;
         case 2:
            this->componentSelected = Z_AXIS_SELECTED;
            break;
        case 3:
           this->componentSelected = ALL_AXIS_SELECTED;
           break;
        case 4:
           this->componentSelected = XY_AXIS_SELECTED;
           break;
        case 5:
           this->componentSelected = YZ_AXIS_SELECTED;
           break;
        case 6:
           this->componentSelected = ZX_AXIS_SELECTED;
           break;
        default:
            this->componentSelected = NO_SELECTION;
        }
    }
}
