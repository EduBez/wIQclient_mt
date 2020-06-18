#ifndef FileParse_H
    #define FileParse_H

#include "Common.h"

namespace orga {

//  wIQCmd
//
struct wIQCmd
{
    std::string msisdn_;
    std::string imsi_;
    std::string target_;
    std::string op_;
    std::string result_;
};

template <typename S>
inline S& operator<< (S& s, const wIQCmd& Cmd)
{
    s << "msisdn "   << Cmd.msisdn_
      << ": imsi "   << Cmd.imsi_
      << ": target " << Cmd.target_
      << ": op "     << Cmd.op_
      << ": result " << Cmd.result_;

    return s;
}

//  CmdFileParse
//
class CmdFileParse : private boost::noncopyable
{
    std::string file_;
    VecCmd commands_;

public:
    // Ctor
    explicit CmdFileParse(std::string CmdFile)
        : file_(std::move(CmdFile)) {}

    inline VecCmd GetCommands()
        { return commands_; }

    void Parse();
};

} // Eof namespace orga

#endif
