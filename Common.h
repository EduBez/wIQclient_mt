#ifndef Common_H
    #define Common_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/tokenizer.hpp>
#include <boost/utility.hpp>

#include "sockets/SimpleSocket.h"

namespace orga {

//  Forward declaration
//
struct wIQCmd;

//  Type aliases
//
typedef std::vector<wIQCmd>         VecCmd;

typedef std::vector<std::string>    VecStr;

typedef std::pair<std::string, int> PairStrInt;

typedef std::set<PairStrInt>        SetPair;

typedef std::vector<PairStrInt>     VecPair;

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
typedef Tokenizer::iterator         TokenizerIt;

typedef SocketClient<512>    SocketT;

typedef std::vector<SocketT> VecSocket;

typedef boost::function<bool (const std::string&, const std::string&)> Operation;
typedef std::map<std::string, Operation> MapOp;

} // Eof namespace orga

#endif
