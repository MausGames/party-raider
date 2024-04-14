///////////////////////////////////////////////
//*-----------------------------------------*//
//| Auto-Generated by the Core Engine       |//
//| Direct modifications may be overwritten |//
//*-----------------------------------------*//
///////////////////////////////////////////////
#include "main.h"


// ****************************************************************
// project settings
const coreChar* const CoreApp::Settings::Name                          = "Party Raider";
const coreChar* const CoreApp::Settings::Version                       = "1.0.0";
const coreChar* const CoreApp::Settings::IconPath                      = "data/textures/game_icon.webp";
const coreChar* const CoreApp::Settings::CursorPath                    = "data/textures/default_cursor.webp";
const coreBool        CoreApp::Settings::UserManagement                = false;
const coreUint8       CoreApp::Settings::Graphics::DepthSize           = 16u;
const coreUint8       CoreApp::Settings::Graphics::StencilSize         = 0u;
const coreBool        CoreApp::Settings::Graphics::AlphaChannel        = false;
const coreBool        CoreApp::Settings::Graphics::DoubleBuffer        = true;
const coreBool        CoreApp::Settings::Graphics::StereoRender        = false;
const coreUint32      CoreApp::Settings::Platform::SteamAppID          = 0u;
const coreChar* const CoreApp::Settings::Platform::EpicProductID       = NULL;
const coreChar* const CoreApp::Settings::Platform::EpicSandboxID   [3] = {NULL, NULL, NULL};
const coreChar* const CoreApp::Settings::Platform::EpicDeploymentID[3] = {NULL, NULL, NULL};
const coreChar* const CoreApp::Settings::Platform::EpicClientID        = NULL;
const coreChar* const CoreApp::Settings::Platform::EpicClientSecret    = NULL;


// ****************************************************************
// setup the application
void CoreApp::Setup()
{
    Core::Manager::Resource->Load<coreModel>  ("default_cube.md3",            CORE_RESOURCE_UPDATE_AUTO,   "data/models/default_cube.md3");
    Core::Manager::Resource->Load<coreModel>  ("drink_blue.md5mesh",          CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_blue_straw.md5mesh",    CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue_straw.md5mesh", CORE_MODEL_LOAD_NO_CLUSTERS);
    Core::Manager::Resource->Load<coreModel>  ("drink_blue_glass.md5mesh",    CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_blue_glass.md5mesh", CORE_MODEL_LOAD_NO_CLUSTERS);
    Core::Manager::Resource->Load<coreModel>  ("drink_mojito.md5mesh",        CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_mojito.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_mojito_straw.md5mesh",  CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_mojito_straw.md5mesh", CORE_MODEL_LOAD_NO_CLUSTERS);
    Core::Manager::Resource->Load<coreModel>  ("drink_sunrise.md5mesh",       CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_sunrise.md5mesh");
    Core::Manager::Resource->Load<coreModel>  ("drink_sunrise_straw.md5mesh", CORE_RESOURCE_UPDATE_AUTO,   "data/models/drink_sunrise_straw.md5mesh", CORE_MODEL_LOAD_NO_CLUSTERS);

    Core::Manager::Resource->Load<coreTexture>("drink_mojito.webp",            CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_mojito.webp");
    Core::Manager::Resource->Load<coreTexture>("drink_sunrise.webp",           CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_sunrise.webp");
    Core::Manager::Resource->Load<coreTexture>("drink_citrus.webp",            CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_citrus.webp");
    Core::Manager::Resource->Load<coreTexture>("drink_blue.webp",              CORE_RESOURCE_UPDATE_AUTO,   "data/textures/drink_blue.webp");

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