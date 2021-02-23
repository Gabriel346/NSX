#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Material;
class Command;
class Tool;
class MainWindow;


template< typename T > Command* t_createCommand() {
    return (Command*) new T();
}
typedef Command* (*t_createCommand_fp)();


class Application : public QApplication
{
    Q_OBJECT

    Application(int argc = 0, char *argv[] = nullptr);
public:
    static Application & instance();

    std::map<QString, Tool*> tools;
    //std::map<QString, Command*> commands;

    std::map<QString, t_createCommand_fp> commands_factory;

    std::map<QString, Material*> materials;

    std::map<Qt::Key, QVariant> hotkey_bindings; //Tools and commands

    std::vector<QVariant> selection;

    std::vector<Command*> undoStack;

    MainWindow *mainWindow;

    void init();

public slots:
    void registerPlugin(QString filename);
    void registerTool() {} // add Tool to tools, register command
    void registerCommand() {} //command -> (name, command)
    void registerHotkeys() {} // (key, command/tool name) -> (key, command/tool pointer)

    void activateTool(QString tool_name);
    void activateTool(Tool *tool);
    void executeCommand(QString command_name, std::vector<QVariant> args);

    void undo();

    //ActiveViewportor();
    //Scene;

   // std::vector<Command*>
};



#endif // APPLICATION_H
