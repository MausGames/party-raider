////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
CBullet::CBullet()noexcept
: coreObject3D   ()
, m_pOwner       (NULL)
, m_vOldPos      (coreVector2(FLT_MAX,FLT_MAX))
, m_vVelocity    (coreVector2(0.0f,0.0f))
, m_vFlyRotation (coreVector2::Rand())
, m_Straw        ()
, m_Glass        ()
{
    this  ->DefineProgram("drink_program");
    m_Straw.DefineProgram("drink_program");
    m_Glass.DefineProgram("glass_program");

    switch(Core::Rand->Uint(2u))
    {
    default: UNREACHABLE
    case 0u:
        {
            this->DefineModel  ("drink_sunrise.md5z");
            this->DefineTexture(0, "drink_sunrise.webp");
            this->SetSize      (coreVector3(1.0f,1.0f,1.0f));
            this->SetAlpha     (0.91f);

            m_Straw.DefineModel  ("drink_sunrise_straw.md5z");
            m_Straw.DefineTexture(0u, "default_black.webp");

            m_Glass.DefineModel  ("drink_sunrise.md5z");
            m_Glass.DefineTexture(0u, "drink_sunrise.webp");
        }
        break;

    case 1u:
        {
            this->DefineModel         ("drink_mojito.md5z");
            this->DefineTexture       (0u, "drink_mojito.webp");
            this->SetSize             (coreVector3(1.0f,1.0f,1.0f) * 1.08f);
            this->SetCollisionModifier(coreVector3(1.3f,1.3f,1.3f));
            this->SetAlpha            (0.85f);

            m_Straw.DefineModel  ("drink_mojito_straw.md5z");
            m_Straw.DefineTexture(0u, "default_black.webp");

            m_Glass.DefineModel  ("drink_mojito.md5z");
            m_Glass.DefineTexture(0u, "drink_mojito.webp");
        }
        break;

    case 2u:
        {
            this->DefineModel  ("drink_blue.md5z");
            this->DefineTexture(0u, "drink_blue.webp");
            this->SetSize      (coreVector3(1.0f,1.0f,1.0f) * 1.16f);
            this->SetAlpha     (0.87f);

            m_Straw.DefineModel  ("drink_blue_straw.md5z");
            m_Straw.DefineTexture(0u, "drink_citrus.webp");

            m_Glass.DefineModel  ("drink_blue_glass.md5z");
            m_Glass.DefineTexture(0u, "drink_blue.webp");
        }
        break;
    }

    this->ChangeType(TYPE_BULLET);
}


// ****************************************************************
void CBullet::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void CBullet::Move()
{
    m_vOldPos = this->GetPosition().xy();

    m_vVelocity += coreVector2(0.0f,-0.3f) * (PLAYER_SPEED * PLAYER_ACCELERATION * TIME);
    if(!m_vVelocity.IsNull())
    {
        m_vVelocity.x *= POW(1.0f - PLAYER_BRAKE.x * 0.03f * (1.0f/60.0f), TIME * 60.0f);
        m_vVelocity.y *= POW(1.0f - PLAYER_BRAKE.y * 0.1f  * (1.0f/60.0f), TIME * 60.0f);
    }

    const coreFloat   T    = TIME * (PI * 5.0f);
    const coreVector2 A    = coreVector2::Direction(T * m_vFlyRotation.y);
    const coreVector2 B    = coreVector2::Direction(T * m_vFlyRotation.x);
    const coreMatrix3 mRot = coreMatrix3( A.y,  A.x*B.x, -A.x*B.y,
                                         0.0f,      B.y,      B.x,
                                          A.x, -A.y*B.x,  A.y*B.y);

    this->SetPosition   (coreVector3(this->GetPosition().xy() + m_vVelocity * TIME, 0.0f));
    this->SetDirection  (this->GetDirection()   * mRot);
    this->SetOrientation(this->GetOrientation() * mRot);

    m_Straw.SetPosition   (this->GetPosition());
    m_Straw.SetSize       (this->GetSize());
    m_Straw.SetDirection  (this->GetDirection());
    m_Straw.SetOrientation(this->GetOrientation());
    m_Straw.Move();

    m_Glass.SetPosition   (this->GetPosition());
    m_Glass.SetSize       (this->GetSize());
    m_Glass.SetDirection  (this->GetDirection());
    m_Glass.SetOrientation(this->GetOrientation());
    m_Glass.Move();

    this->coreObject3D::Move();
}