#include "CommandLine.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

using namespace orga;
using namespace po;

//  ProgramOptions
//
void ProgramOptions::ParseCmdLine(int argc, char* argv[])
{
    store(parse_command_line(argc, argv, desc_), vm_);
    notify(vm_);

    // -- help
    if (vm_.count("help"))
    {
        cout << desc_ << "\n";
        throw CmdLineException();
    }

    // -- version
    if (vm_.count("version"))
        throw CmdLineException("wIQclient_mt -- version 1.0.\n");

    // -- file
    if (vm_.count("file"))
    {
        file_ = vm_["file"].as<string>();

        if (!ifstream(file_.c_str()))
            throw CmdLineException("Command file not found.\n");
    }
    else
        throw CmdLineException("Command file missing.\n");

    // -- server
    if (vm_.count("server"))
        servers_ = vm_["server"].as<VecStr>();
    else
        throw CmdLineException("List of server(s) missing.\n");

    // -- iteration Or timed
    if (!vm_.count("iteration") && !vm_.count("timed"))
        throw CmdLineException
            ("Must inform the repetition pattern: \"iteration, i\" or \"timed, t\".\n");

    if (vm_.count("iteration") && vm_.count("timed"))
        throw CmdLineException
            ("Must choose the repetition pattern: \"iteration, i\" or \"timed, t\".\n");

    if (vm_.count("iteration") && !vm_.count("timed"))
        iterate_ = vm_["iteration"].as<int>();

    else
    {
        if (vm_.count("timed") && !vm_.count("iteration"))
            seconds_ = vm_["timed"].as<int>();

        else
            throw CmdLineException
                ("Must inform the repetition pattern: \"iteration, i\" or \"timed, t\".\n");
    }
}

void ProgramOptions::SetupCmdLine()
{
    desc_.add_options()
        ("version,v" , "Display the version number")
        ("help,h"    , "SyncOut help message")

        ("iteration,i" , value<int>() , "Repeat processing <num> number of times")
        ("timed,t"     , value<int>() , "Repeat processing <sec> number of seconds")

        ("file,f"    , value<string>()          , "File containing commands to execute")
        ("server,s"  , value<vector<string> >() , "List of servers. Ex: -s localhost:8080 -s 127.0.0.1:5043")

        ("log,l"     , value<string>(&outlog_)->default_value("wIQclient_mtLog"), "Name of the output log file. Default is \"wIQclient_mtLog\"")
    ;
}
