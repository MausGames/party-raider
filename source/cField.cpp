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
cField::cField()noexcept
{
    this->DefineProgram("field_program");
    this->SetSize(coreVector2(1.0f,1.0f));

    for(coreUintW i = 0u; i < FIELD_GROUNDS; ++i)
    {
        m_aGround[i].DefineModel  ("default_cube.md3");
        m_aGround[i].DefineTexture(0u, "default_white.webp");
        m_aGround[i].DefineProgram("object_program");
        m_aGround[i].SetDirection (coreVector3(0.0f,1.0f,0.0f));

        m_aGround[i].ChangeType(TYPE_GROUND);
    }

    m_aGround[0].SetPosition(coreVector3(FIELD_SIZE.x * -(1.0f/3.0f), FIELD_SIZE.y *  0.5f,  0.0f));
    m_aGround[1].SetPosition(coreVector3(FIELD_SIZE.x *  (1.0f/3.0f), FIELD_SIZE.y *  0.5f,  0.0f));
    m_aGround[2].SetPosition(coreVector3(0.0f,                        FIELD_SIZE.y *  0.25f, 0.0f));
    m_aGround[3].SetPosition(coreVector3(FIELD_SIZE.x * -(1.0f/3.0f), 0.0f,                  0.0f));
    m_aGround[4].SetPosition(coreVector3(FIELD_SIZE.x *  (1.0f/3.0f), 0.0f,                  0.0f));
    m_aGround[5].SetPosition(coreVector3(0.0f,                        FIELD_SIZE.y * -0.25f, 0.0f));
    m_aGround[6].SetPosition(coreVector3(FIELD_SIZE.x * -(1.0f/3.0f), FIELD_SIZE.y * -0.5f,  0.0f));
    m_aGround[7].SetPosition(coreVector3(FIELD_SIZE.x *  (1.0f/3.0f), FIELD_SIZE.y * -0.5f,  0.0f));

    m_aGround[0].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[1].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[2].SetSize    (coreVector3(FIELD_SIZE.x * (2.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[3].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[4].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[5].SetSize    (coreVector3(FIELD_SIZE.x * (2.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[6].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
    m_aGround[7].SetSize    (coreVector3(FIELD_SIZE.x * (1.0f/3.0f), FIELD_THICK, FIELD_DEPTH));
}


// ****************************************************************
void cField::Render()
{
    for(coreUintW i = 0u; i < FIELD_GROUNDS; ++i)
        m_aGround[i].Render();

    this->coreObject2D::Render();
}


// ****************************************************************
void cField::Move()
{
    for(coreUintW i = 0u; i < FIELD_GROUNDS; ++i)
        m_aGround[i].Move();

    this->coreObject2D::Move();
}


// ****************************************************************
void cField::EnableGround(const coreUintW iIndex, const coreBool bEnabled)
{
    ASSERT(iIndex < FIELD_GROUNDS)

    m_aGround[iIndex].SetEnabled(bEnabled ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
    m_aGround[iIndex].ChangeType(bEnabled ? TYPE_GROUND            : 0);
}