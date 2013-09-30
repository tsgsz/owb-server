// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "server/services/manager.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::owb;

class managerHandler : virtual public managerIf {
 public:
  managerHandler() {
    // Your initialization goes here
  }

  bool Login(const  ::owb::OwbUser& user) {
    // Your implementation goes here
    printf("Login\n");
  }

  void JoinMeeting( ::owb::OwbServerInfo& _return, const std::string& uname, const std::string& passwd, const std::string& mid) {
    // Your implementation goes here
    printf("JoinMeeting\n");
  }

  void CreateMeeting(std::string& _return, const std::string& uname) {
    // Your implementation goes here
    printf("CreateMeeting\n");
  }

  bool HeartBeatWithMonitor(const  ::owb::OwbServerHbPack& pack) {
    // Your implementation goes here
    printf("HeartBeatWithMonitor\n");
  }

  bool MeetingOver(const std::string& mid) {
    // Your implementation goes here
    printf("MeetingOver\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<managerHandler> handler(new managerHandler());
  shared_ptr<TProcessor> processor(new managerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

