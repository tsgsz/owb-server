cc_library (
    name = 'search_queue',
    srcs = 'search_queue.cc',
    deps = [
        '//thirdparty/boost:boost',
        '//thirdparty/glog:glog'
    ],
)
    
cc_test (
    name = 'search_queue_test',
    srcs = 'search_queue_test.cc',
    deps = ':search_queue',
)

cc_test (
    name = 'client_proxy_test',
    srcs = 'client_proxy_test.cc',
    deps = '//thirdparty/gflags:gflags',
)
