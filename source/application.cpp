///////////////////////////////////////////////
//*-----------------------------------------*//
//| Auto-Generated by the Core Engine       |//
//| Direct modifications may be overwritten |//
//*-----------------------------------------*//
///////////////////////////////////////////////
#include "main.h"


// ****************************************************************
// project settings
const coreChar* const CoreApp::Settings::Name                       = "Party Raider";
const coreChar* const CoreApp::Settings::IconPath                   = "data/textures/game_icon.png";
const coreChar* const CoreApp::Settings::CursorPath                 = "data/textures/default_cursor.png";
const coreUint8       CoreApp::Settings::RenderBuffer::DepthSize    = 16u;
const coreUint8       CoreApp::Settings::RenderBuffer::StencilSize  = 0u;
const coreBool        CoreApp::Settings::RenderBuffer::AlphaChannel = false;
const coreBool        CoreApp::Settings::RenderBuffer::DoubleBuffer = true;
const coreBool        CoreApp::Settings::RenderBuffer::StereoRender = false;
const coreUint32      CoreApp::Settings::Platform::SteamAppID       = 0u;


// ****************************************************************
// setup the application
void CoreApp::Setup()
{
    Core::Manager::Resource->Load<coreModel>  ("default_cube.md3",            CORE_RESOURCE_UPDATE_AUTO,   "data/models/default_cube.md3");
    Core::Manager::Resource->Load<coreModel>  ("drink_blue.md5mesh",          CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_blue_straw.md5mesh",    CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue_straw.md5mesh", false);
    Core::Manager::Resource->Load<coreModel>  ("drink_blue_glass.md5mesh",    CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue_glass.md5mesh", false);
    Core::Manager::Resource->Load<coreModel>  ("drink_mojito.md5mesh",        CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_mojito.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_mojito_straw.md5mesh",  CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_mojito_straw.md5mesh", false);
    Core::Manager::Resource->Load<coreModel>  ("drink_sunrise.md5mesh",       CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_sunrise.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_sunrise_straw.md5mesh", CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_sunrise_straw.md5mesh", false);

    Core::Manager::Resource->Load<coreTexture>("drink_mojito.png",            CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_mojito.png");
    Core::Manager::Resource->Load<coreTexture>("drink_sunrise.png",           CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_sunrise.png");
    Core::Manager::Resource->Load<coreTexture>("drink_citrus.png",            CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_citrus.png");
    Core::Manager::Resource->Load<coreTexture>("drink_blue.png",              CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_blue.png");

    Core::Manager::Resource->Load<coreShader> ("drink.vert",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/drink.vert");
    Core::Manager::Resource->Load<coreShader> ("drink.frag",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/drink.frag");
    Core::Manager::Resource->Load<coreShader> ("field.vert",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/field.vert");
    Core::Manager::Resource->Load<coreShader> ("field.frag",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/field.frag");
    Core::Manager::Resource->Load<coreShader> ("glass.vert",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/glass.vert");
    Core::Manager::Resource->Load<coreShader> ("glass.frag",                  CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/glass.frag");
    Core::Manager::Resource->Load<coreShader> ("object.vert",                 CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/object.vert");
    Core::Manager::Resource->Load<coreShader> ("object.frag",                 CORE_RESOURCE_UPDATE_MANUAL, "data/shaders/object.frag");

    d_cast<coreProgram*>(Core::Manager::Resource->Load<coreProgram>("drink_program", CORE_RESOURCE_UPDATE_AUTO, NULL)->GetRawResource())
        ->AttachShader("drink.vert")
        ->AttachShader("drink.frag")
        ->Finish();

    d_cast<coreProgram*>(Core::Manager::Resource->Load<coreProgram>("field_program", CORE_RESOURCE_UPDATE_AUTO, NULL)->GetRawResource())
        ->AttachShader("field.vert")
        ->AttachShader("field.frag")
        ->Finish();

    d_cast<coreProgram*>(Core::Manager::Resource->Load<coreProgram>("glass_program", CORE_RESOURCE_UPDATE_AUTO, NULL)->GetRawResource())
        ->AttachShader("glass.vert")
        ->AttachShader("glass.frag")
        ->Finish();

    d_cast<coreProgram*>(Core::Manager::Resource->Load<coreProgram>("object_program", CORE_RESOURCE_UPDATE_AUTO, NULL)->GetRawResource())
        ->AttachShader("object.vert")
        ->AttachShader("object.frag")
        ->Finish();
}