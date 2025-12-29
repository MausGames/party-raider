////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_BULLET_H_
#define _PAR_GUARD_BULLET_H_


// ****************************************************************
class CBullet final : public coreObject3D
{
private:
    CPlayer* m_pOwner;

    coreVector2 m_vOldPos;
    coreVector2 m_vVelocity;
    coreVector2 m_vFlyRotation;

    coreObject3D m_Straw;
    coreObject3D m_Glass;


public:
    CBullet()noexcept;

    ENABLE_COPY(CBullet)

    void Render()final;
    void Move  ()final;

    inline void RenderStraw() {m_Straw.Render();}
    inline void RenderGlass() {m_Glass.Render();}

    inline void SetOwner   (CPlayer*          pOwner)    {m_pOwner    = pOwner;}
    inline void SetVelocity(const coreVector2 vVelocity) {m_vVelocity = vVelocity;}

    inline CPlayer*           GetOwner   ()const {return m_pOwner;}
    inline const coreVector2& GetOldPos  ()const {return m_vOldPos;}
    inline const coreVector2& GetVelocity()const {return m_vVelocity;}
};


#endif // _PAR_GUARD_BULLET_H_