#ifndef ClientMT_H
    #define ClientMT_H

#include <utility>

#include "Common.h"
#include "Log.h"
#include "FileParse.h"

namespace orga {

//  Dispatch
//
class Dispatch : private boost::noncopyable
{
public:
    // Ctor
    Dispatch(const VecStr& Servers, VecCmd  Commands);

    void Run();

private:
    // Member function
    void Create(VecPair Coll);
    static VecPair Extract(const VecStr& Servers);

    // Member variables
    VecCmd commands_ ;

    // Holds valid wIQ connections
    VecSocket sockets_;
};

//  ThreadAction
//
class ThreadAction : private boost::noncopyable
{
public:
    // Ctor
    ThreadAction(SocketT Socket, wIQCmd Command)
        // Mil
        : socket_(std::move(Socket)), command_(std::move(Command))
    {
        // Output grouping purposes
        id_ = rand();

        // Bind delegate
        func_ = boost::bind(&ThreadAction::Perform, this);

        // Initialize map of operations
        operations_.insert(std::make_pair("==",
            boost::bind(std::equal_to<std::string>(), _1, _2)));

        operations_.insert(std::make_pair("!=",
            boost::bind(std::not_equal_to<std::string>(), _1, _2)));

        operations_.insert(std::make_pair(">",
            boost::bind(std::greater<std::string>(), _1, _2)));

        operations_.insert(std::make_pair("<",
            boost::bind(std::less<std::string>(), _1, _2)));

        operations_.insert(std::make_pair(">=",
            boost::bind(std::greater_equal<std::string>(), _1, _2)));

        operations_.insert(std::make_pair("<=",
            boost::bind(std::less_equal<std::string>(), _1, _2)));

        operations_.insert(std::make_pair("regexp",
            boost::bind(&ThreadAction::OpRegExp  , this, _1, _2)));
    }

    inline void Start() const
    {
        boost::thread thrd(func_);
        thrd.join();
    }

private:
    // Member functions
    inline std::string GetId()
        { return boost::str(boost::format("thread {%1%} : ") % id_); }

    void Perform();
    void Send(std::string& Data);

    // Operations
    inline bool OpRegExp(const std::string& lhs, const std::string& rhs)
    {
        Logger::WriteStream(stream_, GetId(), "Operation error: OpRegEx not implemented");
        return false;
    }

     // Member variables
    SocketT socket_;
    wIQCmd command_;

    int id_;
    std::stringstream stream_;

    // Operations as High-Order functions
    MapOp operations_;

    // Thread delegate
    boost::function<void ()> func_;
};

} // Eof namespace orga

#endif
