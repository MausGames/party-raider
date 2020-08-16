////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_BULLET_H_
#define _PAR_GUARD_BULLET_H_


// ****************************************************************
class cBullet final : public coreObject3D
{
private:
    cPlayer* m_pOwner;

    coreVector2 m_vOldPos;
    coreVector2 m_vVelocity;
    coreVector2 m_vFlyRotation;

    coreObject3D m_Straw;
    coreObject3D m_Glass;


public:
    cBullet()noexcept;

    ENABLE_COPY(cBullet)

    void Render()final;
    void Move  ()final;

    inline void RenderStraw() {m_Straw.Render();}
    inline void RenderGlass() {m_Glass.Render();}

    inline void SetOwner   (cPlayer*           pOwner)    {m_pOwner    = pOwner;}
    inline void SetVelocity(const coreVector2& vVelocity) {m_vVelocity = vVelocity;}

    inline cPlayer*           GetOwner   ()const {return m_pOwner;}
    inline const coreVector2& GetOldPos  ()const {return m_vOldPos;}
    inline const coreVector2& GetVelocity()const {return m_vVelocity;}
};


#endif // _PAR_GUARD_BULLET_H_