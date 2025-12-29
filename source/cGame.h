////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_GAME_H_
#define _PAR_GUARD_GAME_H_


// ****************************************************************
class CGame final
{
private:
    coreList<CPlayer*> m_apPlayer;
    coreList<CBullet*> m_apBullet;

    CInterface m_Interface;

    coreUint8 m_aiScore[PLAYERS];

    coreUint8 m_iNumIteration;
    coreUint8 m_iLastIteration;

    coreFlow m_fTime;
    coreBool m_bStarted;


public:
    CGame()noexcept;
    ~CGame();

    DISABLE_COPY(CGame)

    void Render();
    void Move();

    void StartIteration();
    void EndIteration();

    RETURN_RESTRICT CPlayer* CreatePlayer(const coreVector3 vColor, const coreUint8 iControl);
    void DeletePlayer(CPlayer* pPlayer);

    RETURN_RESTRICT CBullet* CreateBullet(CPlayer* pOwner, const coreVector2 vPosition, const coreVector2 vVelocity);
    void DeleteBullet(CBullet* pBullet);

    coreUint8 RetrievePlayerCount(const coreUintW iIndex)const;

    inline const coreUint8& GetScore(const coreUintW iIndex)const {ASSERT(iIndex < PLAYERS) return m_aiScore[iIndex];}
    inline const coreFloat& GetTime ()const {return m_fTime;}
};


#endif // _PAR_GUARD_GAME_H_