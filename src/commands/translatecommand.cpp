#include "translatecommand.h"
#include "../application.h"
#include "../viewport.h"
#include "../object3d.h"
#include "../transform3d.h"
#include <qdebug.h>

TranslateCommand::TranslateCommand()
{

}

TranslateCommand::~TranslateCommand()
{

}


void TranslateCommand::execute(std::vector<QVariant> args)
{
    Application &app = Application::instance();

    QVector3D translation = qvariant_cast<QVector3D>(args[0]);

    for(QVariant &variant: app.selection) { //from selection
        Object3D* o = qvariant_cast<Object3D*>(variant);
        if (o) {
            if (o->parent()->selected) continue;
            ref.push_back(o);
            old_translation.push_back(o->local_transform.translation());
            o->local_transform.translate(translation);
        }
    }

    //std::vector<Object3D*> o = qvariant_cast<std::vector<Object3D*>(args);
}

void TranslateCommand::undo()
{
  //  Viewport *v = Viewport::getActiveViewport();
    int i = 0;
    for(Object3D* &o: ref) { //from selection
        //Object3D* o = qvariant_cast<Object3D*>(variant);
       // if (o) {
            o->local_transform.setTranslation(old_translation.at(i++));
       // }
    }
}
