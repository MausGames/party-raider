////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_INTERFACE_H_
#define _PAR_GUARD_INTERFACE_H_


// ****************************************************************
class cInterface final
{
private:
    coreLabel m_aScore[PLAYERS];

    coreLabel m_Title;
    coreLabel m_Time;
    coreLabel m_Countdown;


public:
    cInterface()noexcept;

    DISABLE_COPY(cInterface)

    void Render();
    void Move();
};


#endif // _PAR_GUARD_INTERFACE_H_