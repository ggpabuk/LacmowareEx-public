#pragma once
#include "CFeature.h"

class CChat :
    public CFeature
{
private:
    struct Message
    {
        int pid;
        std::string text;
    };

    static std::deque<Message> m_lastMessages;
    static std::mutex m_mutex;
    static int m_maxMessages;
public:
    CChat();

    void fnDraw(unsigned int &uElementId) override;

};
