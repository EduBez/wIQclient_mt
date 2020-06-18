#ifndef CommandLine_H
    #define CommandLine_H

#include "Common.h"

// Namespace Alias
namespace po = boost::program_options;

namespace orga {

//  CmdLineException
//
class CmdLineException : public std::exception
{
    const char* msg_;

public:
    // Ctor
    explicit CmdLineException(const char* Msg=nullptr)
        : msg_(Msg) {}

    [[nodiscard]]
    const char* what() const noexcept override 
        { return msg_; }
};


//  ProgramOptions
//
class ProgramOptions : private boost::noncopyable
{
public:
    // Ctor
    ProgramOptions()
        // Member initialization list
        : pdesc_(new po::options_description
        		("wIQclient_mt - Simulation of a mobile station"))

        , desc_(*(pdesc_.get()))

        , iterate_(0)
        , seconds_(0)

        { SetupCmdLine(); }

    inline std::string GetCmdFile()
        { return file_; }

    inline int GetIteration()
        { return iterate_; }

    inline std::string GetLogFile()
        { return outlog_; }

    inline int GetSeconds()
        { return seconds_; }

    inline VecStr GetServers()
        { return servers_; }

    void ParseCmdLine(int argc, char* argv[]);

private:
    // Member function
    void SetupCmdLine();

    // Data members
    boost::shared_ptr<po::options_description> pdesc_;

	po::options_description& desc_;
    po::variables_map vm_;

    std::string file_;
    std::string outlog_;

    VecStr servers_;

    int iterate_;
    int seconds_;
};

} // Eof namespace orga

#endif
