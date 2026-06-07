#include <src/ui/commands/archive-done-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/helpers/ui/printer.hpp>

std::string ArchiveDoneCommand::getName() const { return "archive"; }
std::string ArchiveDoneCommand::getDescription() const { return "Archives all done tasks to a text file"; }

void ArchiveDoneCommand::execute(UIContext& context)
{
    std::string filename;
    Input::inputString("Enter filename to archive done tasks: ", filename);

    context.getTaskService().archiveDone(filename);
    
    Printer::printSuccess("Tasks successfully archived to " + filename);
}
