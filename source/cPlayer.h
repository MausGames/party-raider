////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_PLAYER_H_
#define _PAR_GUARD_PLAYER_H_


// ****************************************************************
class cPlayer final : public coreObject3D
{
private:
    coreUint8 m_iControl;

    coreVector2 m_vOldPos;
    coreVector2 m_vVelocity;
    coreVector2 m_vAim;
    coreFlow    m_fCooldown;

    coreInt8 m_iHealth;


public:
    cPlayer()noexcept;

    ENABLE_COPY(cPlayer)

    void Render()final;
    void Move  ()final;

    bool TakeDamage(const coreInt8 iDamage);

    inline void SetControl (const coreUint8   iControl)  {m_iControl  = iControl;}
    inline void SetVelocity(const coreVector2 vVelocity) {m_vVelocity = vVelocity;}
    inline void SetAim     (const coreVector2 vAim)      {m_vAim      = vAim;}

    inline const coreUint8&   GetControl ()const {return m_iControl;}
    inline const coreVector2& GetOldPos  ()const {return m_vOldPos;}
    inline const coreVector2& GetVelocity()const {return m_vVelocity;}
};


#endif // _PAR_GUARD_PLAYER_H_