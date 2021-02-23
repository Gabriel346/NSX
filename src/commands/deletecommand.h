#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "command.h"

class DeleteCommand: Command
{
public:
    DeleteCommand();
    virtual ~DeleteCommand() {}

    void execute(std::vector<QVariant>) = 0;
    void undo();

    QString commandName() {return "DeleteCommand";}
    bool undoable() {return true;}

};

#endif // DELETECOMMAND_H
