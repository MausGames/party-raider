////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#include "engine/data_transform_2d.glsl"


void VertexMain()
{
    gl_Position = coreObject2DPosition();
}