// Copyright 2013, Baidu Inc.
// Author: Chenjun You <youchenjun@baidu.com>

#ifndef OWB_SERVER_UTILS_SEARCHQUEUE_H_
#define OWB_SERVER_UTILS_SEARCHQUEUE_H_

#include <vector>

#include "common/base/uncopyable.h"
#include "boost/thread/mutex.hpp"
#include "boost/function.hpp"
#include "thirdparty/glog/logging.h"

#include "owb/server/common/common.h"


#define QUEUESIZE 128
#define ASSGINCLOURE ::boost::function<bool(T*, T&)>

namespace owb{
namespace server{
namespace utils{
template<typename T>
class SearchQueue : public common::Uncopyable {
public:
    explicit SearchQueue(int capacity = QUEUESIZE);
    virtual ~SearchQueue();
    bool GetItems(std::vector<T>& _return, int begin_index_);
    bool Push(T& item, int index, ASSGINCLOURE assgin_closure);
    bool IsEmpty() const;
    bool IsFull() const;
    void Clear();
private:
    int capacity_;
    int front_;
    int rear_;
    int front_index_;
    T** items_;
    boost::mutex queue_mutex_;
};

template<typename T>
SearchQueue<T>::SearchQueue(int capacity) {
    boost::mutex::scoped_lock lock(queue_mutex_);
    capacity_ = capacity;
    front_ = -1;
    rear_ = 0;
    front_index_ = 0;

    if (capacity_ <= 0) {
        LOG(ERROR) << "ERROR: capacity <= 0";
        exit(1);
    } else {
        try {
            items_ = new T*[capacity_];
            for (int i = 0; i < capacity_; ++i) {
                items_[i] = new T();
            }
        } catch (std::bad_alloc&) {
            LOG(ERROR) << "ERROR: can't create items_ set! ";
            exit(1);
        }
    }
}

template<typename T>
SearchQueue<T>::~SearchQueue() {
  boost::mutex::scoped_lock lock(queue_mutex_);
  if (items_ != NULL) {
    for (int i = 0; i < capacity_; ++i) {
        delete items_[i];
    }
    delete [] items_;
  }
}


template<typename T>
bool SearchQueue<T>::GetItems(std::vector<T>& _return, int begin_index) {
    boost::mutex::scoped_lock lock(queue_mutex_);
    if(begin_index < front_index_ - 1) {
        return false;
    }
    // find position of the begin_index in indexs_
    int begin_pos = front_ - (begin_index - front_index_ + 1);
    // if begin_pos < 0, then add a capacity_
    begin_pos = begin_pos < 0 ? begin_pos + capacity_ : begin_pos;
    //begin_pos ++;
    int pos = begin_pos;
    while(pos != rear_)
    {
        _return.push_back(*(items_[pos++]));
        pos = pos == capacity_ ? pos - capacity_ : pos;
    }
    return true;
}

template<typename T>
bool SearchQueue<T>::Push(T& item, int index, ASSGINCLOURE assgin_closure) {
    boost::mutex::scoped_lock lock(queue_mutex_);
    if (-1 == front_) {
        front_index_ = index;
        front_ = 0;
    }
    bool _return = assgin_closure(items_[rear_], item);
    ++ rear_;
    rear_ = rear_ == capacity_ ? rear_ - capacity_ : rear_;
    if (rear_ == front_) {
        front_ ++;
        front_ = front_ == capacity_ ? front_ - capacity_ : front_;
        front_index_ ++;
    }
    return _return;
}

template<typename T>
bool SearchQueue<T>::IsEmpty() const {
    return 0 == rear_ - front_;
}

template<typename T>
bool SearchQueue<T>::IsFull() const {
    return rear_ - front_ > 0 ? capacity_ == rear_ - front_ : 1 == front_ - rear_;
}

template<typename T>
void SearchQueue<T>::Clear() {
    boost::mutex::scoped_lock lock(queue_mutex_);
    rear_ = -1;
    front_index_ = 0;
    front_ = -1;
}

}  // utils
}  // server
}  // owb
#endif  // OWB_SERVER_UTILS_SEARCHQUEUE_H_
