#ifndef Socket_H
    #define Socket_H

extern "C" {
    #include <arpa/inet.h>  // inet_ntoa
    #include <errno.h>
    #include <netdb.h>      // gethostbyname
    #include <sys/socket.h>
}

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/utility.hpp>

#include "SocketMsg.h"


//  SocketException
//
class SocketException : public std::exception
{
    const char* msg_;
    int error_;

public:
    // Ctor
    explicit SocketException(const char* Msg, int Error)
        : msg_(Msg), error_(Error) {}

    const char* what() const throw()
    {
        return boost::str(boost::format("Code {%1%}, Message {%2%}")
             % error_
             % msg_).c_str();
    }
};


//  SocketBase
//
template <int N>
class SocketBase
{
public:
    // Ctor
    SocketBase() : size_(N), socket_(0)
    {
        memset(data_, '\0', N);
        Initialize();
    }

    hostent* GetHostByName(const char* Host)
    {
        error_ = 0;
        hostent* entity;

        if ((entity = gethostbyname(Host)) == 0)
        {
            switch (h_errno)
            {
                case HOST_NOT_FOUND : error_ = 250; break;
                case NO_DATA        : error_ = 251; break;
                case NO_RECOVERY    : error_ = 252; break;
                case TRY_AGAIN      : error_ = 253; break;
            }

            switch (errno)
            {
                case EINVAL         : error_ = 254; break;
            }

            if (error_ != 0)
                throw SocketException(Error(), errno);
        }
        return entity;
    }

    inline int Handle() const
    {
        return socket_;
    }

    template <typename T>
    T Read()
    {
        return reinterpret_cast<T>(data_);
    }

    int Receive()
    {
        error_ = 0;
        const int options = 0;

        int bytes = recv(socket_, data_, size_, options);

        if (bytes == -1)
        {
            switch(errno)
            {
                case EACCES      : error_ = 285; break;
                case EBADF       : error_ = 286; break;
                case ECONNRESET  : error_ = 287; break;
                case EFAULT      : error_ = 288; break;
                case EINTR       : error_ = 289; break;
                case EINVAL      : error_ = 290; break;
                case EIO         : error_ = 291; break;
                case ENOBUFS     : error_ = 292; break;
                case ENOMEM      : error_ = 293; break;
                case ENOSR       : error_ = 294; break;
                case ENOTCONN    : error_ = 295; break;
                case ENOTSOCK    : error_ = 296; break;
                case EOPNOTSUPP  : error_ = 297; break;
                case ETIMEDOUT   : error_ = 298; break;
                case EWOULDBLOCK : error_ = 299; break;
            }

            if (error_ != 0)
                throw SocketException(Error(), errno);
        }
        return bytes;
    }

    void Send(const char* Data, int Size)
    {
        memcpy(&data_, Data, Size);

        error_ = 0;
        const int flags = 0;

        if (send(socket_, data_, Size, flags) == -1)
        {
            switch (errno)
            {
                case EACCES       : error_ = 285; break;
                case EBADF        : error_ = 286; break;
                case ECONNRESET   : error_ = 287; break;
                case EDESTADDRREQ : error_ = 300; break;
                case EFAULT       : error_ = 288; break;
                case EINTR        : error_ = 289; break;
                case EIO          : error_ = 291; break;
                case EMSGSIZE     : error_ = 301; break;
                case ENETDOWN     : error_ = 302; break;
                case ENETUNREACH  : error_ = 303; break;
                case ENOBUFS      : error_ = 292; break;
                case ENOMEM       : error_ = 293; break;
                case ENOSR        : error_ = 294; break;
                case ENOTCONN     : error_ = 295; break;
                case ENOTSOCK     : error_ = 296; break;
                case EOPNOTSUPP   : error_ = 297; break;
                case EPIPE        : error_ = 304; break;
                case EWOULDBLOCK  : error_ = 299; break;
            }

            if (error_ != 0)
                throw SocketException(Error(), errno);
        }
    }

protected:
    // Member functions
    inline const char* Error()
    {
        return errors_[error_].c_str();
    }

    void Open()
    {
        error_ = 0;
        socket_ = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_ == -1)
        {
            socket_ = 0;

            switch (errno)
            {
                case EACCES          : error_ = 200; break;
                case EAFNOSUPPORT    : error_ = 201; break;
                case EMFILE          : error_ = 202; break;
                case ENFILE          : error_ = 203; break;
                case ENOBUFS         : error_ = 204; break;
                case ENOMEM          : error_ = 205; break;
                case ENOSR           : error_ = 206; break;
                case EPERM           : error_ = 207; break;
                case EPROTONOSUPPORT : error_ = 208; break;
                case EPROTOTYPE      : error_ = 209; break;
            }

            if (error_ != 0)
                throw SocketException(Error(), errno);
        }
    }

    // Data members
    int error_;
    int size_;
    int socket_;

private:
    void Initialize()
    {
        errors_.insert(std::make_pair(0, NO_SOCKET_ERROR));

        errors_.insert(std::make_pair(200, ERR_MSG_200));
        errors_.insert(std::make_pair(201, ERR_MSG_201));
        errors_.insert(std::make_pair(202, ERR_MSG_202));
        errors_.insert(std::make_pair(203, ERR_MSG_203));
        errors_.insert(std::make_pair(204, ERR_MSG_204));
        errors_.insert(std::make_pair(205, ERR_MSG_205));
        errors_.insert(std::make_pair(206, ERR_MSG_206));
        errors_.insert(std::make_pair(207, ERR_MSG_207));
        errors_.insert(std::make_pair(208, ERR_MSG_208));
        errors_.insert(std::make_pair(209, ERR_MSG_209));
        errors_.insert(std::make_pair(210, ERR_MSG_210));
        errors_.insert(std::make_pair(211, ERR_MSG_211));
        errors_.insert(std::make_pair(212, ERR_MSG_212));
        errors_.insert(std::make_pair(213, ERR_MSG_213));
        errors_.insert(std::make_pair(214, ERR_MSG_214));
        errors_.insert(std::make_pair(215, ERR_MSG_215));
        errors_.insert(std::make_pair(216, ERR_MSG_216));
        errors_.insert(std::make_pair(217, ERR_MSG_217));
        errors_.insert(std::make_pair(218, ERR_MSG_218));
        errors_.insert(std::make_pair(219, ERR_MSG_219));
        errors_.insert(std::make_pair(220, ERR_MSG_220));
        errors_.insert(std::make_pair(221, ERR_MSG_221));
        errors_.insert(std::make_pair(222, ERR_MSG_222));
        errors_.insert(std::make_pair(223, ERR_MSG_223));
        errors_.insert(std::make_pair(224, ERR_MSG_224));
        errors_.insert(std::make_pair(225, ERR_MSG_225));
        errors_.insert(std::make_pair(226, ERR_MSG_226));
        errors_.insert(std::make_pair(227, ERR_MSG_227));
        errors_.insert(std::make_pair(228, ERR_MSG_228));
        errors_.insert(std::make_pair(229, ERR_MSG_229));
        errors_.insert(std::make_pair(230, ERR_MSG_230));
        errors_.insert(std::make_pair(231, ERR_MSG_231));
        errors_.insert(std::make_pair(232, ERR_MSG_232));
        errors_.insert(std::make_pair(233, ERR_MSG_233));
        errors_.insert(std::make_pair(234, ERR_MSG_234));
        errors_.insert(std::make_pair(235, ERR_MSG_235));
        errors_.insert(std::make_pair(236, ERR_MSG_236));
        errors_.insert(std::make_pair(237, ERR_MSG_237));
        errors_.insert(std::make_pair(238, ERR_MSG_238));
        errors_.insert(std::make_pair(239, ERR_MSG_239));
        errors_.insert(std::make_pair(240, ERR_MSG_240));
        errors_.insert(std::make_pair(241, ERR_MSG_241));
        errors_.insert(std::make_pair(242, ERR_MSG_242));
        errors_.insert(std::make_pair(243, ERR_MSG_243));
        errors_.insert(std::make_pair(244, ERR_MSG_244));
        errors_.insert(std::make_pair(245, ERR_MSG_245));
        errors_.insert(std::make_pair(246, ERR_MSG_246));
        errors_.insert(std::make_pair(247, ERR_MSG_247));
        errors_.insert(std::make_pair(248, ERR_MSG_248));
        errors_.insert(std::make_pair(249, ERR_MSG_249));
        errors_.insert(std::make_pair(250, ERR_MSG_250));
        errors_.insert(std::make_pair(251, ERR_MSG_251));
        errors_.insert(std::make_pair(252, ERR_MSG_252));
        errors_.insert(std::make_pair(253, ERR_MSG_253));
        errors_.insert(std::make_pair(254, ERR_MSG_254));
        errors_.insert(std::make_pair(255, ERR_MSG_255));
        errors_.insert(std::make_pair(257, ERR_MSG_257));
        errors_.insert(std::make_pair(258, ERR_MSG_258));
        errors_.insert(std::make_pair(259, ERR_MSG_259));
        errors_.insert(std::make_pair(260, ERR_MSG_260));
        errors_.insert(std::make_pair(261, ERR_MSG_261));
        errors_.insert(std::make_pair(262, ERR_MSG_262));
        errors_.insert(std::make_pair(263, ERR_MSG_263));
        errors_.insert(std::make_pair(264, ERR_MSG_264));
        errors_.insert(std::make_pair(265, ERR_MSG_265));
        errors_.insert(std::make_pair(266, ERR_MSG_266));
        errors_.insert(std::make_pair(267, ERR_MSG_267));
        errors_.insert(std::make_pair(268, ERR_MSG_268));
        errors_.insert(std::make_pair(269, ERR_MSG_269));
        errors_.insert(std::make_pair(270, ERR_MSG_270));
        errors_.insert(std::make_pair(271, ERR_MSG_271));
        errors_.insert(std::make_pair(272, ERR_MSG_272));
        errors_.insert(std::make_pair(273, ERR_MSG_273));
        errors_.insert(std::make_pair(274, ERR_MSG_274));
        errors_.insert(std::make_pair(275, ERR_MSG_275));
        errors_.insert(std::make_pair(276, ERR_MSG_276));
        errors_.insert(std::make_pair(277, ERR_MSG_277));
        errors_.insert(std::make_pair(278, ERR_MSG_278));
        errors_.insert(std::make_pair(279, ERR_MSG_279));
        errors_.insert(std::make_pair(280, ERR_MSG_280));
        errors_.insert(std::make_pair(281, ERR_MSG_281));
        errors_.insert(std::make_pair(282, ERR_MSG_282));
        errors_.insert(std::make_pair(283, ERR_MSG_283));
        errors_.insert(std::make_pair(284, ERR_MSG_284));
        errors_.insert(std::make_pair(285, ERR_MSG_285));
        errors_.insert(std::make_pair(286, ERR_MSG_286));
        errors_.insert(std::make_pair(287, ERR_MSG_287));
        errors_.insert(std::make_pair(288, ERR_MSG_288));
        errors_.insert(std::make_pair(289, ERR_MSG_289));
        errors_.insert(std::make_pair(290, ERR_MSG_290));
        errors_.insert(std::make_pair(291, ERR_MSG_291));
        errors_.insert(std::make_pair(292, ERR_MSG_292));
        errors_.insert(std::make_pair(293, ERR_MSG_293));
        errors_.insert(std::make_pair(294, ERR_MSG_294));
        errors_.insert(std::make_pair(295, ERR_MSG_295));
        errors_.insert(std::make_pair(296, ERR_MSG_296));
        errors_.insert(std::make_pair(297, ERR_MSG_297));
        errors_.insert(std::make_pair(298, ERR_MSG_298));
        errors_.insert(std::make_pair(299, ERR_MSG_299));
        errors_.insert(std::make_pair(300, ERR_MSG_300));
        errors_.insert(std::make_pair(301, ERR_MSG_301));
        errors_.insert(std::make_pair(302, ERR_MSG_302));
        errors_.insert(std::make_pair(303, ERR_MSG_303));
        errors_.insert(std::make_pair(304, ERR_MSG_304));
    }

    // Data members
    char data_[N];
    std::map<int, std::string> errors_;
};


//  SocketClient
//
template <int N>
class SocketClient : public SocketBase<N>
{
public:
    // Default Ctor
    SocketClient() : SocketBase<N>() { }

    // Ctor
    SocketClient(const char* Host, int Port)
        : host_(Host), port_(Port) { }

    void Connect()
        { Perform(); }

    void Connect(const char* Host, int Port)
        { host_ = Host; port_ = Port; Perform(); }

private:
    void Perform()
    {
        hostent* entity = SocketBase<N>::GetHostByName(host_);

        sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));

        addr.sin_family      = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_addr.s_addr = ((in_addr*) (entity->h_addr))->s_addr;
        addr.sin_port        = htons(port_);

        // Open socket
        SocketBase<N>::Open();

        int rslt = connect(SocketBase<N>::socket_, (sockaddr*) &addr, sizeof(addr));

        if (rslt == -1)
        {
            switch (errno)
            {
                case EACCES        : SocketBase<N>::error_ = 257; break;
                case EADDRINUSE    : SocketBase<N>::error_ = 258; break;
                case EADDRNOTAVAIL : SocketBase<N>::error_ = 259; break;
                case EAFNOSUPPORT  : SocketBase<N>::error_ = 260; break;
                case EALREADY      : SocketBase<N>::error_ = 261; break;
                case EBADF         : SocketBase<N>::error_ = 262; break;
                case ECONNREFUSED  : SocketBase<N>::error_ = 263; break;
                case ECONNRESET    : SocketBase<N>::error_ = 264; break;
                case EFAULT        : SocketBase<N>::error_ = 265; break;
                case EHOSTUNREACH  : SocketBase<N>::error_ = 266; break;
                case EINPROGRESS   : SocketBase<N>::error_ = 267; break;
                case EINTR         : SocketBase<N>::error_ = 268; break;
                case EINVAL        : SocketBase<N>::error_ = 269; break;
                case EIO           : SocketBase<N>::error_ = 270; break;
                case EISCONN       : SocketBase<N>::error_ = 271; break;
                case ELOOP         : SocketBase<N>::error_ = 272; break;
                case ENAMETOOLONG  : SocketBase<N>::error_ = 273; break;
                case ENETDOWN      : SocketBase<N>::error_ = 274; break;
                case ENETUNREACH   : SocketBase<N>::error_ = 275; break;
                case ENOBUFS       : SocketBase<N>::error_ = 276; break;
                case ENOENT        : SocketBase<N>::error_ = 277; break;
                case ENOSR         : SocketBase<N>::error_ = 278; break;
                case ENOTDIR       : SocketBase<N>::error_ = 279; break;
                case ENOTSOCK      : SocketBase<N>::error_ = 280; break;
                case EOPNOTSUPP    : SocketBase<N>::error_ = 281; break;
                case EPROTOTYPE    : SocketBase<N>::error_ = 282; break;
                case ETIMEDOUT     : SocketBase<N>::error_ = 283; break;
                case EWOULDBLOCK   : SocketBase<N>::error_ = 284; break;
            }

            if (SocketBase<N>::error_ != 0)
                throw SocketException(SocketBase<N>::Error(), errno);
        }
    }

    // Data members
    const char* host_;
    int port_;
};


//  SocketServer
//
template <int N>
class SocketServer : public SocketBase<N>
{
public:
    // Ctor
    SocketServer()
        // Mil
        : SocketBase<N>(), server_(0) { }

    void Accept()
    {
        SocketBase<N>::error_ = 0;
        int size = sizeof(sockaddr_in);

        do
        {
            SocketBase<N>::socket_ =
                accept(server_, (sockaddr*) &addr_, (socklen_t*) &size);
        }
        while ((SocketBase<N>::socket_ == -1) && (errno == EINTR));

        if (SocketBase<N>::socket_ == -1)
        {
            SocketBase<N>::socket_ = 0;

            switch (errno)
            {
                case EBADF        : SocketBase<N>::error_ = 237; break;
                case ECONNABORTED : SocketBase<N>::error_ = 238; break;
                case EFAULT       : SocketBase<N>::error_ = 239; break;
                case EINTR        : SocketBase<N>::error_ = 240; break;
                case EINVAL       : SocketBase<N>::error_ = 241; break;
                case EMFILE       : SocketBase<N>::error_ = 242; break;
                case ENFILE       : SocketBase<N>::error_ = 243; break;
                case ENOBUFS      : SocketBase<N>::error_ = 244; break;
                case ENOMEM       : SocketBase<N>::error_ = 245; break;
                case ENOSR        : SocketBase<N>::error_ = 246; break;
                case ENOTSOCK     : SocketBase<N>::error_ = 247; break;
                case EOPNOTSUPP   : SocketBase<N>::error_ = 248; break;
                case EPROTO       : SocketBase<N>::error_ = 249; break;
                case EWOULDBLOCK  : SocketBase<N>::error_ = 250; break;
            }

            if (SocketBase<N>::error_ != 0)
                throw SocketException(SocketBase<N>::Error(), errno);
        }

        hostent* entity = gethostbyaddr((char*) &addr_.sin_addr, sizeof(in_addr), AF_INET);

        if (!entity)
        {
            switch (h_errno)
            {
                case HOST_NOT_FOUND : SocketBase<N>::error_ = 250; break;
                case NO_DATA        : SocketBase<N>::error_ = 251; break;
                case NO_RECOVERY    : SocketBase<N>::error_ = 252; break;
                case TRY_AGAIN      : SocketBase<N>::error_ = 253; break;
            }

            switch (errno)
            {
                case EINVAL         : SocketBase<N>::error_ = 254; break;
            }

            if (SocketBase<N>::error_ != 0)
                throw SocketException(SocketBase<N>::Error(), errno);
        }

        std::cout << boost::format("<|> Socket (%1%) accept connection from <%2%>[%3%]")
                                   % SocketBase<N>::socket_
                                   % entity->h_name
                                   % inet_ntoa((in_addr) addr_.sin_addr)
                  << std::endl;
    }

    void Open(int Port)
    {
        // Open socket
        SocketBase<N>::Open();

        server_ = SocketBase<N>::socket_;

        addr_.sin_family      = AF_INET;
        addr_.sin_port        = htons(Port);
        addr_.sin_addr.s_addr = htonl(INADDR_ANY);

        memset(&(addr_.sin_zero), 0, 8);

        int rslt = bind(server_, (sockaddr*) &addr_, sizeof(sockaddr));

        if (rslt == -1)
        {
            switch (errno)
            {
                case EACCES        : SocketBase<N>::error_ = 210; break;
                case EADDRINUSE    : SocketBase<N>::error_ = 211; break;
                case EADDRNOTAVAIL : SocketBase<N>::error_ = 212; break;
                case EAFNOSUPPORT  : SocketBase<N>::error_ = 213; break;
                case EBADF         : SocketBase<N>::error_ = 214; break;
                case EDESTADDRREQ  : SocketBase<N>::error_ = 215; break;
                case EFAULT        : SocketBase<N>::error_ = 216; break;
                case EINVAL        : SocketBase<N>::error_ = 217; break;
                case EIO           : SocketBase<N>::error_ = 218; break;
                case EISCONN       : SocketBase<N>::error_ = 219; break;
                case EISDIR        : SocketBase<N>::error_ = 220; break;
                case ELOOP         : SocketBase<N>::error_ = 221; break;
                case ENAMETOOLONG  : SocketBase<N>::error_ = 222; break;
                case ENOBUFS       : SocketBase<N>::error_ = 223; break;
                case ENOENT        : SocketBase<N>::error_ = 224; break;
                case ENOSR         : SocketBase<N>::error_ = 225; break;
                case ENOTDIR       : SocketBase<N>::error_ = 226; break;
                case ENOTSOCK      : SocketBase<N>::error_ = 227; break;
                case EOPNOTSUPP    : SocketBase<N>::error_ = 228; break;
                case EROFS         : SocketBase<N>::error_ = 229; break;
            }

            if (SocketBase<N>::error_ != 0)
                throw SocketException(SocketBase<N>::Error(), errno);
        }

        rslt = listen(server_, 10);

        if (rslt == -1)
        {
            switch (errno)
            {
                case EACCES       : SocketBase<N>::error_ = 230; break;
                case EBADF        : SocketBase<N>::error_ = 231; break;
                case EDESTADDRREQ : SocketBase<N>::error_ = 232; break;
                case EINVAL       : SocketBase<N>::error_ = 233; break;
                case ENOBUFS      : SocketBase<N>::error_ = 234; break;
                case ENOTSOCK     : SocketBase<N>::error_ = 235; break;
                case EOPNOTSUPP   : SocketBase<N>::error_ = 236; break;
            }

            if (SocketBase<N>::error_ != 0)
                throw SocketException(SocketBase<N>::Error(), errno);
        }
    }

private:
    // Data members
    int server_;
    sockaddr_in addr_;
};

#endif

