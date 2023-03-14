#include "FileParse.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

using namespace orga;

//  CmdFileParse
//
void CmdFileParse::Parse()
{
    ifstream in(file_.c_str());
    string line;

    while (getline(in, line))
    {
        if (!line.empty())
        {
            Tokenizer tok(line, boost::char_separator<char>("\t"));
            TokenizerIt it = tok.begin();

            wIQCmd cmd{};

            if (it != tok.end()) cmd.msisdn_ = *it++;
            if (it != tok.end()) cmd.imsi_   = *it++;
            if (it != tok.end()) cmd.target_ = *it++;
            if (it != tok.end()) cmd.op_     = *it++;
            if (it != tok.end()) cmd.result_ = *it;

            commands_.push_back(cmd);
        }
    }
}
