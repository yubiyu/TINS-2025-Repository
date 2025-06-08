#include "settings.h"

int Settings::optionTextY[NUM_OPTIONS];
std::unordered_map<int, std::string> Settings::optionValues{};
int Settings::targetedOption{};

bool Settings::fullscreenOption{};
int Settings::windowScaleOption{};
std::string Settings::windowWidthText{};
std::string Settings::windowHeightText{};
int Settings::vsyncOption{};
int Settings::fpsOption{};
int Settings::paletteOption{};

int Settings::bgmBars{};
int Settings::sfxBars{};

float Settings::bgmBarsTotalWidth{};
float Settings::sfxBarsTotalWidth{};

bool Settings::cheatsEnabled{};

void Settings::Initialize()
{
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        if (i >= FIRST_DISPLAY_OPTION && i <= LAST_DISPLAY_OPTION)
            optionTextY[i] = OPTION_TEXT_Y_BASE + i * OPTION_TEXT_Y_SPACING + 0 * OPTION_TEXT_Y_SPACING;
        else if (i >= FIRST_AUDIO_OPTION && i <= LAST_AUDIO_OPTION)
            optionTextY[i] = OPTION_TEXT_Y_BASE + i * OPTION_TEXT_Y_SPACING + 1 * OPTION_TEXT_Y_SPACING;
        else if (i == OPTION_RETURN_TO_TITLE)
            optionTextY[i] = OPTION_TEXT_Y_BASE + i * OPTION_TEXT_Y_SPACING + 2 * OPTION_TEXT_Y_SPACING;

        optionValues[i] = "";
    }

    SetTargetedOption(OPTION_FULLSCREEN);
}

void Settings::Logic()
{
}

void Settings::Input()
{
    if (Keyboard::keyHoldTicks[Keyboard::KEY_UP] == 1)
    {
        AdjustTargetedOptionUp();
    }
    else if (Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] == 1)
    {
        AdjustTargetedOptionDown();
    }

    if (Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] == 1)
    {
        switch (targetedOption)
        {
        case OPTION_FULLSCREEN:
            SetFullscreenOption(false);
            break;
        case OPTION_RESOLUTION:
            SetWindowScaleOption(windowScaleOption - 1);
            break;
        case OPTION_VSYNC:
            SetVsyncOption(vsyncOption - 1);
            break;
        case OPTION_FPS:
            SetFPSOption(fpsOption - 5);
            break;
        case OPTION_PALETTE:
            SetPaletteOption(paletteOption - 1);
            break;

        case OPTION_BGM_LEVEL:
            SetBgmBarsOption(bgmBars - 1);
            break;
        case OPTION_SFX_LEVEL:
            SetSfxBarsOption(sfxBars - 1);
            break;
        }
    }
    else if (Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] == 1)
    {
        switch (targetedOption)
        {
        case OPTION_FULLSCREEN:
            SetFullscreenOption(true);
            break;
        case OPTION_RESOLUTION:
            SetWindowScaleOption(windowScaleOption + 1);
            break;
        case OPTION_VSYNC:
            SetVsyncOption(vsyncOption + 1);
            break;
        case OPTION_FPS:
            SetFPSOption(fpsOption + 5);
            break;
        case OPTION_PALETTE:
            SetPaletteOption(paletteOption + 1);
            break;

        case OPTION_BGM_LEVEL:
            SetBgmBarsOption(bgmBars + 1);
            break;
        case OPTION_SFX_LEVEL:
            SetSfxBarsOption(sfxBars + 1);
            break;
        }
    }

    if (Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1)
    {
        SetTargetedOption(OPTION_RETURN_TO_TITLE);
    }
    else if (Keyboard::keyHoldTicks[Keyboard::KEY_ENTER] == 1)
    {
        if (targetedOption == OPTION_RETURN_TO_TITLE)
        {
            SaveToConfig();
            Scene::ChangeScene(Scene::SCENE_TITLE);
        }
    }
}

void Settings::Drawing()
{
    al_draw_bitmap(Image::menuOptionMarkerPng,
                   OPTION_LABELS_X - Menu::OPTION_MARKER_SPRITE_X_SPACING,
                   optionTextY[targetedOption],
                   0);

    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        if (targetedOption == i)
        {
            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_MENU_TEXT_HIGHLIGHTED,
                                      OPTION_LABELS_X, optionTextY[i],
                                      ALLEGRO_ALIGN_LEFT | ALLEGRO_ALIGN_INTEGER, optionLabels.at(i));

            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_MENU_TEXT_HIGHLIGHTED,
                                      OPTION_VALUES_X, optionTextY[i],
                                      ALLEGRO_ALIGN_LEFT | ALLEGRO_ALIGN_INTEGER, optionValues.at(i));
        }
        else
        {
            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_MENU_TEXT,
                                      OPTION_LABELS_X, optionTextY[i],
                                      ALLEGRO_ALIGN_LEFT | ALLEGRO_ALIGN_INTEGER, optionLabels.at(i));

            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_MENU_TEXT,
                                      OPTION_VALUES_X, optionTextY[i],
                                      ALLEGRO_ALIGN_LEFT | ALLEGRO_ALIGN_INTEGER, optionValues.at(i));
        }
    }

    al_draw_bitmap(Image::settingsVolumeBarEmptyPng,
                   VOLUME_BARS_X, optionTextY[OPTION_BGM_LEVEL],
                   0);

    al_draw_bitmap_region(Image::settingsVolumeBarFullPng,
                          0, 0,
                          bgmBarsTotalWidth, VOLUME_BAR_HEIGHT,
                          VOLUME_BARS_X, optionTextY[OPTION_BGM_LEVEL],
                          0);

    al_draw_bitmap(Image::settingsVolumeBarEmptyPng,
                   VOLUME_BARS_X, optionTextY[OPTION_SFX_LEVEL],
                   0);

    al_draw_bitmap_region(Image::settingsVolumeBarFullPng,
                          0, 0,
                          sfxBarsTotalWidth, VOLUME_BAR_HEIGHT,
                          VOLUME_BARS_X, optionTextY[OPTION_SFX_LEVEL],
                          0);
}

void Settings::AdjustTargetedOptionUp()
{
    if (targetedOption > FIRST_OPTION)
        targetedOption--;
}

void Settings::AdjustTargetedOptionDown()
{
    if (targetedOption < LAST_OPTION)
        targetedOption++;
}

void Settings::SetTargetedOption(int whichOption)
{
    targetedOption = whichOption;
}

void Settings::UpdateWindowScaleText()
{
    windowWidthText = std::to_string(Display::width);
    windowHeightText = std::to_string(Display::height);

    optionValues[OPTION_RESOLUTION] = windowWidthText + "x" + windowHeightText;
}

void Settings::SetFullscreenOption(bool is_fullscreen)
{
    fullscreenOption = is_fullscreen;
    Display::SetFullscreen(fullscreenOption);

    if (fullscreenOption)
        optionValues[OPTION_FULLSCREEN] = "Full";
    else
        optionValues[OPTION_FULLSCREEN] = "Windowed";

    UpdateWindowScaleText();
}

void Settings::SetWindowScaleOption(int scale)
{
    if (!fullscreenOption)
    {
        windowScaleOption = scale;
        if (windowScaleOption < WINDOW_SCALE_MIN)
            windowScaleOption = WINDOW_SCALE_MIN;
        else if (windowScaleOption > WINDOW_SCALE_MAX)
            windowScaleOption = WINDOW_SCALE_MAX;

        Display::SetWindowScale(windowScaleOption);

        UpdateWindowScaleText();
    }
}

void Settings::SetVsyncOption(int vsync_mode)
{
    if (vsync_mode >= Display::VSYNC_MODE_FIRST && vsync_mode <= Display::VSYNC_MODE_LAST)
    {
        vsyncOption = vsync_mode;
        Display::SetVsync(vsyncOption);

        if (vsyncOption == Display::VSYNC_DRIVER)
            optionValues[OPTION_VSYNC] = "Driver";
        else if (vsyncOption == Display::VSYNC_ON)
            optionValues[OPTION_VSYNC] = "On";
        else if (vsyncOption == Display::VSYNC_OFF)
            optionValues[OPTION_VSYNC] = "Off";
    }
}

void Settings::SetFPSOption(int set_fps)
{
    fpsOption = set_fps;
    if (fpsOption < Display::FPS_MIN)
        fpsOption = Display::FPS_MIN;
    else if (fpsOption > Display::FPS_MAX)
        fpsOption = Display::FPS_MAX;

    Display::SetFPS(fpsOption);

    optionValues[OPTION_FPS] = std::to_string(fpsOption);
}

void Settings::SetPaletteOption(int set_pal)
{
    paletteOption = set_pal;
    if (paletteOption < Palette::COL_GB_FIRST)
        paletteOption = Palette::COL_GB_FIRST;
    else if (paletteOption > Palette::COL_GB_LAST)
        paletteOption = Palette::COL_GB_LAST;

    Palette::SwapPalette(paletteOption);

    optionValues[OPTION_PALETTE] = Palette::palettePresetNames.at(paletteOption);
}

void Settings::SetBgmBarsOption(int bars)
{
    bgmBars = bars;
    if (bgmBars < 0)
        bgmBars = 0;
    else if (bgmBars > MAX_VOLUME_BARS)
        bgmBars = MAX_VOLUME_BARS;

    bgmBarsTotalWidth = VOLUME_BAR_WIDTH * bgmBars;

    Audio::SetBgmGain(bars * 0.1);
}

void Settings::SetSfxBarsOption(int bars)
{
    sfxBars = bars;
    if (sfxBars < 0)
        sfxBars = 0;
    else if (sfxBars > MAX_VOLUME_BARS)
        sfxBars = MAX_VOLUME_BARS;

    sfxBarsTotalWidth = VOLUME_BAR_WIDTH * sfxBars;

    Audio::SetSfxGain(bars * 0.1);
}

void Settings::SetCheatsEnabledOption(int enabled)
{
    cheatsEnabled = enabled;
}

void Settings::SaveToConfig()
{
    Configuration::SetKey(Configuration::settingsCfg, "display", "fullscreen window", fullscreenOption);
    Configuration::SetKey(Configuration::settingsCfg, "display", "window scale", windowScaleOption);
    Configuration::SetKey(Configuration::settingsCfg, "display", "vsync", vsyncOption);
    Configuration::SetKey(Configuration::settingsCfg, "display", "fps", fpsOption);
    Configuration::SetKey(Configuration::settingsCfg, "display", "palette", paletteOption);

    Configuration::SetKey(Configuration::settingsCfg, "audio", "bgm bars", bgmBars);
    Configuration::SetKey(Configuration::settingsCfg, "audio", "sfx bars", sfxBars);

    if (!al_save_config_file("config/settings.cfg", Configuration::settingsCfg))
        std::cout << "Error - Settings: Failed to save to config/settings." << std::endl;
    else
        std::cout << "Settings: config/settings.cfg successfully updated." << std::endl;
}

void Settings::LoadFromConfig()
{
    SetFullscreenOption(Configuration::GetInt(Configuration::settingsCfg, "display", "fullscreen window"));
    SetWindowScaleOption(Configuration::GetInt(Configuration::settingsCfg, "display", "window scale"));
    SetVsyncOption(Configuration::GetInt(Configuration::settingsCfg, "display", "vsync"));
    SetFPSOption(Configuration::GetInt(Configuration::settingsCfg, "display", "fps"));
    SetPaletteOption(Configuration::GetInt(Configuration::settingsCfg, "display", "palette"));

    SetBgmBarsOption(Configuration::GetInt(Configuration::settingsCfg, "audio", "bgm bars"));
    SetSfxBarsOption(Configuration::GetInt(Configuration::settingsCfg, "audio", "sfx bars"));

    SetCheatsEnabledOption(Configuration::GetInt(Configuration::settingsCfg, "cheats", "cheats enabled"));
}
