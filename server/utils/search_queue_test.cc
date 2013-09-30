/*************************************************************************
     ** File Name: search_queue_test.cc
    ** Author: tsgsz
    ** Mail: cdtsgsz@gmail.com
    ** Created Time: Tue Sep 17 22:31:53 2013
    **Copyright [2013] <Copyright tsgsz>  [legal/copyright]
 ************************************************************************/
#include "owb/server/utils/search_queue.h"

#include "thirdparty/gtest/gtest.h"
//#include "thirdparty/boost/thread/thread.hpp"

namespace owb {
namespace server {
namespace utils{
class TestClass {
public:
    TestClass(){}
    ~TestClass(){}
    int Tid;
};

bool AssginTestClass(TestClass* t1, TestClass& t2) {
    if (t1 == NULL) return false;
    t1->Tid = t2.Tid;
    return true;
}

class TestSearchQueue : public testing::Test {
protected:
    SearchQueue<TestClass>* queue;
    boost::function<bool(TestClass*, TestClass&)> cb;
    virtual void SetUp() {
        queue = new SearchQueue<TestClass>(3);
        cb = &AssginTestClass;
    }
    virtual void TearDown() {
        delete queue;
    }
public:
    void Run() {
        for (int i = 0; i < 100; ++i) {
            //to do
        }
    }
};

TEST_F(TestSearchQueue, SingleThread) {
    TestClass test_1;
    test_1.Tid = 1;
    TestClass test_2;
    test_2.Tid = 2;
    ASSERT_TRUE(queue->Push(test_1, 1, cb));
    ASSERT_FALSE(queue->IsEmpty());
    ASSERT_TRUE(queue->Push(test_2, 2, cb));
    ASSERT_FALSE(queue->IsFull());
    std::vector<TestClass> r;
    ASSERT_TRUE(queue->GetItems(r, 0));
    ASSERT_EQ(r.size(), 2);
    ASSERT_EQ(r[0].Tid, 1);
    ASSERT_EQ(r[1].Tid, 2);
    r.clear();
    TestClass test_3;
    test_3.Tid = 3;
    TestClass test_4;
    test_4.Tid = 4;
    ASSERT_TRUE(queue->Push(test_3, 3, cb));
    ASSERT_TRUE(queue->IsFull());
    ASSERT_TRUE(queue->Push(test_4, 4, cb));
    ASSERT_FALSE(queue->GetItems(r, 0));
}

// todo
TEST_F(TestSearchQueue, MutilThreadGetItems) {
    //boost::thread* thread1 = new boost::thread(boost::bind(&TestSearchQueue::Run, this));
}


}  // utils
}  // server
}  // owb
