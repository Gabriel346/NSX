#ifndef SPLITEDGECOMMAND_H
#define SPLITEDGECOMMAND_H

#include "command.h"

class SplitEdgeCommand: public Command
{
public:
    SplitEdgeCommand();

    bool undoable() {return true;}
    QString commandName() {return "SplitEdge";}

    // Command interface
public:
    void execute(std::vector<QVariant>);
    //void undo();
};

#endif // SPLITEDGECOMMAND_H
