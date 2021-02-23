#include "setpropertycommand.h"
#include <qdebug.h>

SetPropertyCommand::SetPropertyCommand()
{

}

SetPropertyCommand::~SetPropertyCommand()
{

}


void SetPropertyCommand::execute(std::vector<QVariant> args)
{
    target = qvariant_cast<QObject*>(args[0]);
    property_name = qvariant_cast<QString>(args[1]);
    old_value = target->property(property_name.toUtf8());
    target->setProperty(property_name.toUtf8(), args[2]);
}

void SetPropertyCommand::undo()
{
    target->setProperty(property_name.toUtf8(), old_value);
}
