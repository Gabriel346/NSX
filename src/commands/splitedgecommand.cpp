#include "splitedgecommand.h"
#include "../application.h"
#include "../mainwindow.h"

SplitEdgeCommand::SplitEdgeCommand()
{

}


void SplitEdgeCommand::execute(std::vector<QVariant>)
{
    Application &app = Application::instance();
    if (!app.selection.empty()) {
        app.selection[0];
        // TODO
    }
}

//void SplitEdgeCommand::undo()
//{
//}
