////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#include "engine/data_transform_3d.glsl"


// constant values
const vec3 c_v3CamDir = vec3(0.0, 0.0, -1.0);   // normalized camera vector

// shader output
varying float v_v1Intensity;   // lighting intensity (Gouraud shading)


void VertexMain()
{
    // transform position and texture coordinates
    gl_Position      = coreObject3DPositionRaw();
    v_av2TexCoord[0] = a_v2RawTexCoord;

    // calculate intensity value
    vec3 v3NewNormal = coreQuatApply(u_v4Rotation, a_v3RawNormal);
    v_v1Intensity    = 1.4 * abs(dot(v3NewNormal, c_v3CamDir)) + 0.28 * abs(v3NewNormal.z);
}