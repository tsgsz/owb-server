// Copyright 2013, Baidu Inc.
// Author: Chenjun You <youchenjun@baidu.com>

#ifndef OWB_SERVER_MANAGER_MANAGER_DB_HANDLER_H_
#define OWB_SERVER_MANAGER_MANAGER_DB_HANDLER_H_
#include <string>

namespace owb {
namespace server {
namespace manager {
class ManagerDbHandler {
public:
    ManagerDbHandler();
    int AddMeeting(const std::strubf& uname);
    bool SetMeetingId(const std::string& mid, int id);
    bool SetMeetingOver(const std::string& mid);
    bool UpdateMachineState();
    bool UpdateMachineHbTime(const std::string mid);
    bool AliasMeetingAndMachine(const std::string& mid,
                                const std::string& mname);
    bool GetMachineIp(const std::string& mid);
};
}
}
}
#endif  // OWB_SERVER_MANAGER_MANAGER_DB_HANDLER_H_
