namespace cpp owb
namespace java owb
namespace cocoa owb

exception OwbMissingMeeting {
1: required string descripe;
}

exception OwbDeadMeeting {
1: required string descripe;
}

struct OwbServerInfo {
1: required string ip;
2: required i32 master_port;
3: required i32 updator_port;
4: required i32 provider_port;
}

enum OwbUserIdentity {
    HOST = 0,
    CANDIDATE = 1,
    PARTICIPANTS = 2
}

struct OwbUser {
1: required string uname;
2: required string passwd;
3: optional OwbUserIdentity identity;
}

struct OwbHbSPack {
1: required string uname;
2: required string mid;
}

struct OwbHbRPack {
1: required OwbUserIdentity identity;
}
