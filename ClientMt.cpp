#include "sockets/SocketWait.h"
#include "ClientMt.h"

#include <utility>
#include "XMLProtocol.h"

using std::cout;
using std::endl;
using std::make_pair;
using std::runtime_error;
using std::sort;
using std::string;
using std::unique_copy;
using std::vector;

using namespace orga;

//  Dispatch
//

// Ctor
Dispatch::Dispatch(const VecStr& Servers, VecCmd Commands)
    // Mil
    : commands_(std::move(Commands))
{
    Create(Extract(Servers));
}

void Dispatch::Create(VecPair Coll)
{
    for (auto& it : Coll)
    {
        bool valid = true;

        SocketT socket;
        try
        {
            socket.Connect(it.first.c_str(), it.second);
        }
        catch (SocketException& e)
        {
            valid = false;

            string msg = boost::str(boost::format
                (" Host {%1%}, Port {%2%} ") % it.first % it.second);

            Logger::Write("Error opening connection:", msg);
        }

        if (valid)
            sockets_.emplace_back(socket);
    }

    if (sockets_.empty())
        throw runtime_error("No wIQ servers available");

}

VecPair Dispatch::Extract(const VecStr& Servers)
{
    VecPair coll, rslt;

    for (const auto& Server : Servers)
    {
        if (!Server.empty())
        {
            TokenizerIt tok
                = Tokenizer(Server, boost::char_separator<char>(":")).begin();

            string server = *tok;
            int port = boost::lexical_cast<int>(*(++tok));

            // Add to collection
            coll.push_back(make_pair(server, port));
        }
    }

    // Sort collection
    sort(coll.begin(), coll.end());
    // Remove duplicate servers during copy
    unique_copy(coll.begin(), coll.end(), back_inserter(rslt));

    return rslt;
}

void Dispatch::Run()
{
    unsigned i = 0;

    for (auto& command : commands_)
    {
        // Start communication thread with wIQ
        ThreadAction act(sockets_[i], command);
        act.Start();

        // Get next server
        if (++i >= sockets_.size())
            i = 0;
    }
}

//  ThreadAction
//
void ThreadAction::Perform()
{
    string data = boost::str(boost::format(XML_REQ_TYPE_1)
        % command_.msisdn_
        % command_.target_
        % command_.imsi_);
        
    size_t length = data.length() + 15;
    const int sessionId = 1; // Magic number ???

    data = boost::str(boost::format("1D%04X2O%06d%06d0%s")
       % length
       % sessionId
       % 0
       % data.c_str());
       
    Send(data);
    Operation op = operations_[command_.op_];

    if (op)
    {
        // Execute operation
        bool rslt = op(data, command_.result_);
        // Log result
        Logger::WriteStream(stream_, GetId(), "Op result: ", rslt ? "true" : "false");
    }
    else
        Logger::WriteStream(stream_, GetId(), "Operation error: Op not supported");

    Logger::Flush(stream_);
}

void ThreadAction::Send(string& Data)
{
    try
    {
        Logger::WriteStream(stream_, GetId(), "Send request: ", Data);

        // Send command
        socket_.Send(Data.c_str(), Data.size());
        // Wait for response
        SocketWait wt(socket_, POLLIN | POLLPRI);

        if (wt.Wait(5000, POLLIN | POLLPRI))
        {
            int bytes = socket_.Receive();
            Logger::WriteStream(stream_, GetId(), "Bytes read: ", bytes);

            Data = socket_.Read<char*>();
            Logger::WriteStream(stream_, GetId(), "wIQ Response: ", Data);
        }
    }
    catch (SocketException& e)
    {
        Logger::Write("SocketException: ", e.what());
    }
}
