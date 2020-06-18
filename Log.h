#ifndef Log_H
    #define Log_H

#include "Common.h"

namespace orga {

//  Logger
//
class Logger : private boost::noncopyable
{
public:
    static void Flush(std::stringstream& Stream)
    {
        boost::mutex::scoped_lock lock(mutex_);

        std::cout << Stream.str();
        log_ << Stream.str();

        // Clear string stream
        Stream.rdbuf()->str("");
    }

    static void Open(const std::string& File)
    {
        log_.open(File.c_str()/*, std::ios::app*/);

        if (!log_.is_open())
        {
            throw std::runtime_error(boost::str(boost::format
                ("Error opening log file: \"%1%\"") % File));
        }
    }

    template <typename T>
    static void Write(T Arg)
    {
        boost::mutex::scoped_lock lock(mutex_);

        std::cout << Arg << std::endl;
        log_      << Arg << std::endl;
    }

    template <typename T1, typename T2>
    static void Write(T1 Arg1, T2 Arg2)
    {
        boost::mutex::scoped_lock lock(mutex_);

        std::cout << Arg1 << Arg2 << std::endl;
        log_      << Arg1 << Arg2 << std::endl;
    }

    template <typename T>
    static void WriteStream(std::stringstream& Stream, T Arg)
    {
        boost::mutex::scoped_lock lock(mutex_);
        Stream << Arg << std::endl;
    }

    template <typename T1, typename T2>
    static void WriteStream(std::stringstream& Stream, T1 Arg1, T2 Arg2)
    {
        boost::mutex::scoped_lock lock(mutex_);
        Stream << Arg1 << Arg2 << std::endl;
    }

    template <typename T1, typename T2, typename T3>
    static void WriteStream(std::stringstream& Stream, T1 Arg1, T2 Arg2, T3 Arg3)
    {
        boost::mutex::scoped_lock lock(mutex_);
        Stream << Arg1 << Arg2 << Arg3 << std::endl;
    }

private:
    // Data members
    static boost::mutex mutex_;
    static std::ofstream log_;
};

} // Eof namespace orga

#endif
