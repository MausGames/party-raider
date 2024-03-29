////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////


// shader input
varying float v_v1Intensity;   // lighting intensity (Gouraud shading)


void FragmentMain()
{
    // remove top of the glass
    if(v_v1Intensity <= 0.0) gl_FragColor = vec4(0.0); // discard;
    else
    {
        // draw intensity-modified color
        gl_FragColor = vec4(coreTexture2D(0, v_av2TexCoord[0]).rgb * v_v1Intensity, 0.5);
    }
}