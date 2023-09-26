#pragma once

#include <string>

enum message_type
{
    Msg_StrangerComing,
    Msg_PotatoReady,
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
    case 0:

        return "Stranger is Coming...";

    case 1:

        return "Potatoes are cooked";

    default:

        return "Not recognized!";
    }
}