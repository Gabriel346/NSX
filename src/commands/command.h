#ifndef COMMAND_H
#define COMMAND_H

#include <qvariant.h>
#include <vector>

class Command
{
public:
    Command();
    virtual ~Command() {}

    virtual void execute(std::vector<QVariant>) = 0;
    virtual void undo() {}

    virtual QString commandName() = 0;
    virtual bool undoable() {return false;}

private:

};

#endif // COMMAND_H
