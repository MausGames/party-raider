////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_GAME_H_
#define _PAR_GUARD_GAME_H_


// ****************************************************************
class cGame final
{
private:
    std::vector<cPlayer*> m_apPlayer;
    std::vector<cBullet*> m_apBullet;

    cInterface m_Interface;

    coreUint8 m_aiScore[PLAYERS];

    coreUint8 m_iNumIteration;
    coreUint8 m_iLastIteration;

    coreFlow m_fTime;
    coreBool m_bStarted;


public:
    cGame()noexcept;
    ~cGame();

    DISABLE_COPY(cGame)

    void Render();
    void Move();

    void StartIteration();
    void EndIteration();

    RETURN_RESTRICT cPlayer* CreatePlayer(const coreVector3& vColor, const coreUint8 iControl);
    void DeletePlayer(cPlayer* pPlayer);

    RETURN_RESTRICT cBullet* CreateBullet(cPlayer* pOwner, const coreVector2& vPosition, const coreVector2& vVelocity);
    void DeleteBullet(cBullet* pBullet);

    coreUint8 RetrievePlayerCount(const coreUintW iIndex)const;

    inline const coreUint8& GetScore(const coreUintW iIndex)const {ASSERT(iIndex < PLAYERS) return m_aiScore[iIndex];}
    inline const coreFloat& GetTime ()const {return m_fTime;}
};


#endif // _PAR_GUARD_GAME_H_