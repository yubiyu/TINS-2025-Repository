#include "game.h"

bool Game::exit;
bool Game::redraw;

void Game::MainLoop()
{
    while (!exit)
    {
        al_wait_for_event(Event::eventQueue, &Event::event);

        if (Event::event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;

        if (Event::event.type == ALLEGRO_EVENT_KEY_DOWN)
            Keyboard::InputKeydown();

        if (Event::event.type == ALLEGRO_EVENT_KEY_UP)
            Keyboard::InputKeyup();

        /*
        if(Event::event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
        {

        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
        {

        }
        */

        if (Event::event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            Mouse::InputMouseXY();
            Mouse::InputMousewheel();
        }

        if (Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            Mouse::InputMouseDown();

        if (Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            Mouse::InputMouseUp();

        if (Event::event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            InputSwitchboard();
            LogicSwitchboard();

            Audio::Logic();
        }

        if (redraw && al_is_event_queue_empty(Event::eventQueue))
        {
            DrawingSwitchboard();
        }
    }
}

bool Game::Initialize(char **argv)
{
    exit = false;
    redraw = true;

    srand(time(NULL));

    al_install_system(ALLEGRO_VERSION_INT, NULL);
    uint32_t allegroVersion = al_get_allegro_version();
    int versionMajor = allegroVersion >> 24;
    int versionMinor = (allegroVersion >> 16) & 255;
    int versionRevision = (allegroVersion >> 8) & 255;
    int versionRelease = allegroVersion & 255;
    std::cout << "Game: Allegro version " << versionMajor << "." << versionMinor << "." << versionRevision << " " << versionRelease << std::endl;

    Display::Initialize();
    Keyboard::Initialize();
    Mouse::Initialize();
    Timer::Initialize();
    Event::Initialize();

    Filesystem::Initialize(argv);
    Configuration::LoadConfigurations();

    Filesystem::SetPhysfsFileInterface(); // Image, text, and audio resources are stored in data.zip. To be accessed by PHYSfs.
    Image::Initialize();
    Text::Initialize();
    Audio::Initialize();
    Filesystem::SetStandardFileInterface();

    Palette::InitializeGB();

    Scene::Initialize();
    Camera::Initialize();

    Title::Initialize();
    Worldview::Initialize();
    Settings::Initialize();
    Archive::Initialize();

    Settings::LoadFromConfig();

    Area::Initialize();

    PC::pc = new PC();

    FoodEater::Initialize();

    Dialog::Initialize();
    StatusFrame::Initialize();

    GameResult::Initialize();

    return true;
}

void Game::Uninitialize()
{
    GameResult::Uninitialize();

    StatusFrame::Uninitialize();
    Dialog::Uninitialize();

    delete PC::pc;

    Area::Uninitialize();

    Worldview::Uninitialize();

    Camera::Uninitialize();

    Audio::Uninitialize();
    Text::Uninitialize();
    Image::Uninitialize();

    Configuration::UnloadConfigurations();
    Filesystem::Uninitialize();

    Event::Uninitialize();
    Timer::Uninitialize();
    Mouse::Uninitialize();
    Keyboard::Uninitialize();
    Display::Uninitialize();

    al_uninstall_system();
}

void Game::ResetWorld()
{
    GameResult::Uninitialize();
    StatusFrame::Uninitialize();
    Dialog::Uninitialize();
    delete PC::pc;
    Area::Uninitialize();
    Worldview::Uninitialize();
    Camera::Uninitialize();

    Camera::Initialize();
    Worldview::Initialize();
    Area::Initialize();
    PC::pc = new PC();
    FoodEater::Initialize();
    Dialog::Initialize();
    StatusFrame::Initialize();
    GameResult::Initialize();

}

void Game::InputSwitchboard()
{
    Keyboard::InputKeyHold();
    Mouse::InputMouseButtonHold();

    switch (Scene::inputContext)
    {
    case Scene::INPUT_CONTEXT_TITLE:
        Title::Input();
        break;

    case Scene::INPUT_CONTEXT_WORLDVIEW:
        Worldview::Input();
        break;

    case Scene::INPUT_CONTEXT_GAME_RESULT:
        GameResult::Input();
        break;

    case Scene::INPUT_CONTEXT_LOADGAME:
        LoadGame::Input();
        break;

    case Scene::INPUT_CONTEXT_ARCHIVE:
        Archive::Input();
        break;

    case Scene::INPUT_CONTEXT_SETTINGS:
        Settings::Input();
        break;
    }

    Mouse::mouseAxesAltered = false;
}

void Game::LogicSwitchboard()
{
    if(Reset::needsReset)
    {
        ResetWorld();
        Reset::needsReset = false;
    }

    switch (Scene::scene)
    {
    case Scene::SCENE_TITLE:
        Title::Logic();
        if (Title::exitOptionSelected)
            exit = true;
        break;

    case Scene::SCENE_WORLDVIEW:
        Worldview::Logic();
        break;

    case Scene::SCENE_GAME_RESULT:
        GameResult::Logic();
        break;

    case Scene::SCENE_LOADGAME:
        LoadGame::Logic();
        break;

    case Scene::SCENE_SETTINGS:
        Settings::Logic();
        break;
    case Scene::SCENE_ARCHIVE:
        Archive::Logic();
        break;
    }
}

void Game::DrawingSwitchboard()
{
    Game::redraw = false;
    al_set_target_bitmap(Display::scaleBuffer);
    al_clear_to_color(COLKEY_BACKGROUND);

    switch (Scene::scene)
    {
    case Scene::SCENE_TITLE:
        Title::Drawing();
        break;

    case Scene::SCENE_WORLDVIEW:
        Worldview::Drawing();
        break;

    case Scene::SCENE_GAME_RESULT:
        GameResult::Drawing();
        break;

    case Scene::SCENE_LOADGAME:
        LoadGame::Drawing();
        break;

    case Scene::SCENE_SETTINGS:
        Settings::Drawing();
        break;
    case Scene::SCENE_ARCHIVE:
        Archive::Drawing();
        break;
    }

    al_set_target_backbuffer(Display::display);
    al_clear_to_color(COLKEY_BACKGROUND); // Might be unnecessary
    al_draw_scaled_bitmap(Display::scaleBuffer,
                          0, 0,
                          Display::NATIVE_WIDTH, Display::NATIVE_HEIGHT,
                          0, 0,
                          Display::width, Display::height,
                          0);

    al_flip_display();
}
