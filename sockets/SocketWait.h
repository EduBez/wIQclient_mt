#ifndef SocketWait_H
    #define SocketWait_H

extern "C" {
    #include <poll.h>
}

#include <vector>


//  SocketWait
//
class SocketWait
{
    typedef std::vector<pollfd> VecPollFd;
    typedef VecPollFd::iterator VecPollFdIt;

    VecPollFd ufds_;

public:
    // Ctor
    template <typename T>
    SocketWait(T& Socket, int Events)
    {
        pollfd ufd;

        ufd.fd = Socket.Handle();
        ufd.events = Events;

        ufds_.push_back(ufd);
    }

    bool Wait(int MilliSecs, int Events)
    {
        int rslt;

        if ((rslt = poll((pollfd*) &ufds_[0], ufds_.size(), MilliSecs)) < 0)
            return false;

        else if (rslt > 0)
        {
            for (VecPollFdIt it = ufds_.begin(); it != ufds_.end(); ++it)
            {
                if ((*it).revents && Events)
                    return true;
            }
            return false;
        }
        return false;
    }
};

#endif

