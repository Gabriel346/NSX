#ifndef SETPROPERTYCOMMAND_H
#define SETPROPERTYCOMMAND_H

#include "command.h"

class SetPropertyCommand : public Command
{
public:
    SetPropertyCommand();
    ~SetPropertyCommand();

    void execute(std::vector<QVariant>);
    void undo();

    bool undoable() {return true;}
    QString commandName() {return "SetProperty";}

private:
    QObject *target;
    QString property_name;
    QVariant old_value;
};

#endif // SETPROPERTYCOMMAND_H
