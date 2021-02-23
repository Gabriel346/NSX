#ifndef TRANSLATECOMMAND_H
#define TRANSLATECOMMAND_H

#include "command.h"
#include "../object3d.h"

#include <QVector3D>

class TranslateCommand : public Command
{
public:
    TranslateCommand();
    ~TranslateCommand();

    void execute(std::vector<QVariant>);
    void undo();

    bool undoable() {return true;}
    QString commandName() {return "Translate";}

private:
    //std::vector<QVector3D> translations;
    std::vector<Object3D*> ref;
    std::vector<QVector3D> old_translation;
};

#endif // SETPROPERTYCOMMAND_H
