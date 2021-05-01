////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cInterface::cInterface()noexcept
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        m_aScore[i].Construct  ("default.ttf", 50u, 2u);
        m_aScore[i].SetPosition(coreVector2((i ? 1.0f : -1.0f) * 0.4f, 0.192f));
    }

    m_Title.Construct  ("default.ttf", 100u, 2u);
    m_Title.SetPosition(coreVector2(0.0f,0.0f));
    m_Title.SetText    ("PARTY RAIDER");

    m_Time.Construct  ("default.ttf", 50u, 2u);
    m_Time.SetPosition(coreVector2(0.0f,0.0f));

    m_Countdown.Construct  ("default.ttf", 90u, 2u);
    m_Countdown.SetPosition(coreVector2(0.0f,0.095f));
}


// ****************************************************************
void cInterface::Render()
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
        m_aScore[i].Render();

    m_Time     .Render();
    m_Countdown.Render();
    m_Title    .Render();
}


// ****************************************************************
void cInterface::Move()
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        m_aScore[i].SetText(PRINT("%u", g_pGame->GetScore(i)));
        m_aScore[i].Move();
    }

    const coreFloat fTitle     = MAX(GAME_WAIT - (TIME - GAME_TIME - GAME_COUNTDOWN), 0.0f);
    const coreFloat fTime      = CEIL(MIN(TIME, GAME_TIME));
    const coreFloat fCountdown = CEIL(TIME - GAME_TIME);

         if(fCountdown >  3.0f) m_Countdown.SetText("");
    else if(fCountdown >  0.0f) m_Countdown.SetText(PRINT("%.0f", fCountdown));
    else if(fCountdown > -1.0f) m_Countdown.SetText("GO!");
    else if(fTime <= -GAME_DELAY)
    {
        coreUintW iWinIndex = 0u;
        coreUint8 iWinCount = g_pGame->GetScore(0u);
        coreUint8 iSame     = 1u;

        for(coreUintW i = 1u; i < PLAYERS; ++i)
        {
            const coreUint8 iNewCount = g_pGame->GetScore(i);
            if(iNewCount > iWinCount)
            {
                iWinIndex = i;
                iWinCount = iNewCount;
            }
            else if(iNewCount == iWinCount)
            {
                iSame += 1u;
            }
        }

        if(iSame == PLAYERS) m_Countdown.SetText("DRAW!");
                        else m_Countdown.SetText(PRINT("PLAYER %zu WINS!", iWinIndex + 1u));
    }
    else if(fTime <= 0.0f) m_Countdown.SetText("TIMES UP!");
    else if(fTime <= 3.0f) m_Countdown.SetText(PRINT("%.0f", fTime));
    else                   m_Countdown.SetText("");

    if(fTime > -GAME_DELAY) m_Time.SetText(PRINT("%.0f", MAX(fTime, 0.0f)));

    m_Title.SetPosition(coreVector2(m_Title.GetPosition().x, 0.095f - POW(fTitle * 2.0f, 2.0f)));

    m_Title    .Move();
    m_Time     .Move();
    m_Countdown.Move();
}