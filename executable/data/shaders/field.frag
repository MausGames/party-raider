////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////


void FragmentMain()
{
    vec2  v2ScreenCoord = gl_FragCoord.xy * u_v4Resolution.zw;
    float v1Intensity   = 0.25 - length(v2ScreenCoord - vec2(0.5)) * 0.5;
    vec4  v4Color       = vec4(u_v4Color.rgb * v1Intensity, u_v4Color.a);

    gl_FragColor = v4Color;
}