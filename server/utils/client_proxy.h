// Copyright 2013, Baidu Inc.
// Author: Chenjun You <youchenjun@baidu.com>

#ifndef OWB_SERVER_UTILS_CLIENT_PROXY_H_
#define OWB_SERVER_UTILS_CLIENT_PROXY_H_

#include <exception>
#include <string>

#include "common/base/singleton.h"
#include "thirdparty/boost/shared_ptr.hpp"
#include "thirdparty/gflags/gflags.h"
#include "thirdparty/thrift/transport/TTransport.h"
#include "thirdparty/thrift/transport/TSocket.h"
#include "thirdparty/thrift/transport/TBufferTransports.h"
#include "thirdparty/thrift/protocol/TProtocol.h"
#include "thirdparty/thrift/protocol/TBinaryProtocol.h"

#include "owb/server/common/common.h"

namespace owb {
namespace server {
namespace utils {

class NotInitException : public std::exception {
};

template<typename T>
class ClientProxy : public common::SingletonBase< ClientProxy<T> > {
public:
    void Init(std::string ip, int port);
    void Open();
    void Close();
    T* operator->();
private:
    friend class common::SingletonBase< ClientProxy<T> >;
    ClientProxy();
    ~ClientProxy();
    T* client_;
    bool isInited_;
    bool isOpened_;
    ::boost::shared_ptr< ::apache::thrift::transport::TTransport> transport_;
};

using ::apache::thrift::transport::TTransport;
using ::apache::thrift::transport::TSocket;
using ::apache::thrift::transport::TBufferedTransport;
using ::apache::thrift::protocol::TProtocol;
using ::apache::thrift::protocol::TBinaryProtocol;
using ::boost::shared_ptr;

template<typename T>
ClientProxy<T>::ClientProxy() {
}

template<typename T>
ClientProxy<T>::~ClientProxy() {
    if (!isInited_) return;
    Close();
    if (NULL != transport_) delete transport_;
    if (NULL != client_) delete client_;
}

template<typename T>
void ClientProxy<T>::Init(std::string ip, int port) {
    if (isInited_) return;
    ::boost::shared_ptr<TTransport> socket(new TSocket(ip, port));
    transport_ = shared_ptr<TTransport>(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport_));
    client_ = new T(protocol);
    isInited_ = true;
}

template<typename T>
void ClientProxy<T>::Open() {
    if (isOpened_) return;
    transport_->open();
    isOpened_ = true;
}

template<typename T>
void ClientProxy<T>::Close() {
    if (!isInited_) throw NotInitException("Client has not be inited");
    if (!isOpened_) return;
    transport_->close();
    isOpened_ = false;
}

template<typename T>
T* ClientProxy<T>::operator->() {
    if (!isInited_) throw NotInitException("Client has not be inited");
    Open();
    return client_;
}

}  // utils
}  // server
}  // owb
#endif  // OWB_SERVER_UTILS_CLIENT_PROXY_H_
