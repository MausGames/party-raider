////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_INTERFACE_H_
#define _PAR_GUARD_INTERFACE_H_


// ****************************************************************
class CInterface final
{
private:
    coreLabel m_aScore[PLAYERS];

    coreLabel m_Title;
    coreLabel m_Time;
    coreLabel m_Countdown;


public:
    CInterface()noexcept;

    DISABLE_COPY(CInterface)

    void Render();
    void Move();
};


#endif // _PAR_GUARD_INTERFACE_H_