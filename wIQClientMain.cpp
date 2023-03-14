#include <iostream>
using namespace std;

#include "wIQClientMain.h"

#include "CommandLine.h"
#include "FileParse.h"

using namespace orga;

//  Condition
//
bool Condition::control_ = true;// Statics definition


//  Entry point
//
int main(int argc, char* argv[])
{
    // Ex: wIQclient_mt -s localhost:5384 -s 192.168.190.15:5384 -f wIQcommands -i 10

    try
    {
        // Retrieve program options
        ProgramOptions po;
        po.ParseCmdLine(argc, argv);

        // Parse wIQ command file
        CmdFileParse cf(po.GetCmdFile());
        cf.Parse();

        // Open global log
        Logger::Open(po.GetLogFile());

        // Create dispatcher
        Dispatch disp(po.GetServers(), cf.GetCommands());

        // Create application instance
        auto app(Factory::Create(po.GetIteration(), po.GetSeconds()));

        // Run application
        app->Run(disp);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}
