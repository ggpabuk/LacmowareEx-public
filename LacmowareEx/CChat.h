#pragma once
#include "CFeature.h"

class CChat :
    public CFeature
{
private:
    struct Message
    {
        int pid;
        std::string pname;
        std::string text;
    };

    std::deque<Message> m_lastMessages;
    std::mutex m_mutex;
    int m_maxMessages;
    bool m_ignorePing;

    void sendMessage(const char *text);
public:
    CChat();

    void fnDraw(unsigned int &uElementId) override;

};
