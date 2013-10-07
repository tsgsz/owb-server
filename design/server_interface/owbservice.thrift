namespace cpp owb
namespace java owb
namespace cocoa owb

include "owbop.thrift"
include "owbsys.thrift"

service data_provider {
    list<owbop.OwbOp> GetOps(1:string mid, 2:i32 opid);
    list<owbop.OwbOp> Restore(1:string mid);
}

service data_updater {
    i32 SendOp(1:owbop.OwbOp op);
}

service master {
    bool TransferAuth(1:string hname, 2:string mid);
    list<owbsys.OwbUser> GetUserList(1:string mid);
    owbsys.OwbHbRPack HeartBeat(1:owbsys.OwbHbSPack pack);
}

service monitor {
	owbsys.OwbServerInfo StartMeetingHandler(1:string mid);
}

service manager {
    bool Login(1:owbsys.OwbUser user);
    owbsys.OwbServerInfo JoinMeeting(1:string uname, 2:string mid) throws (1:owbsys.OwbMissingMeeting mmiss, 2:owbsys.OwbDeadMeeting mdead);
    string CreateMeeting(1:string uname);
    bool HeartBeatWithMonitor(1:owbsys.OwbServerHbPack pack);
    bool MeetingOver(1:string mid);
}
