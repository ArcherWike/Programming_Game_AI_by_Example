#pragma once

#include <string>

enum message_type
{
    Msg_StrangerComing,
    Msg_PotatoReady,
    Msg_DogoIsDangerous,
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
    case 0:

        return "Stranger is Coming...";

    case 1:

        return "Potatoes are cooked";

    case 2:
        return "Dogo is dangerous";

    default:

        return "Not recognized!";
    }
}