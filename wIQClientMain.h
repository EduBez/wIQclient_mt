#ifndef wIQClientMain_H
    #define wIQClientMain_H

#include <csignal>
#include <unistd.h>

#include <memory>

#include "ClientMt.h"
#include "Log.h"

namespace orga {

//  Condition
//
class Condition : private boost::noncopyable
{
public:
    static bool& Control()
        { return control_; }

private:
    // Data members
    static bool control_;
};

//  Timer
//
class Timer : private boost::noncopyable
{
public:
    // Ctor
    explicit Timer(int Seconds)
    {
        signal(SIGALRM, &Timer::Handler);
        alarm(Seconds);
    }

    // Dtor
    ~Timer()
        { alarm(0); }

    // Alarm signal handler
    static void Handler(int SigNum)
        { Condition::Control() = false; }
};

//  TemplateMethodBase
//
class TemplateMethodBase
{
public:
    virtual void Run(Dispatch& D) = 0;

    void SetCycle(int Cycles)
        { cycles_ = Cycles; }

protected:
    int cycles_{};
};

//  TemplateMethodIteration
//
struct TemplateMethodIteration : public TemplateMethodBase
{
    void Run(Dispatch& D) override
    {
        Logger::Write("{|} Processing mode is: <iteration>");

        for (int i=0; i < cycles_; ++i)
        {
            Logger::Write("<|> Iteration number: ", i);
            D.Run();
        }
    }
};

//  TemplateMethodTimed
//
struct TemplateMethodTimed : public TemplateMethodBase
{
    void Run(Dispatch& D) override
    {
        Logger::Write("{|} Processing mode is: <timed>");

        Timer timer(cycles_);

        while (Condition::Control()) {
            D.Run();
        }
        Logger::Write("<|> Reached elapsed time");
    }
};

//  Factory
//
struct Factory : private boost::noncopyable
{
    static std::unique_ptr<TemplateMethodBase> Create(int NoOfTimes, int Seconds)
    {
        std::unique_ptr<TemplateMethodBase> p;

        if (NoOfTimes)
        {
            p = std::unique_ptr<TemplateMethodBase>(new TemplateMethodIteration());
            p->SetCycle(NoOfTimes);
        }
        else if (Seconds)
        {
            p = std::unique_ptr<TemplateMethodBase>(new TemplateMethodTimed());
            p->SetCycle(Seconds);
        }

        return p;
    }
};

} // Eof namespace orga

#endif
