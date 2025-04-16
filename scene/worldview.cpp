#include "worldview.h"


void Worldview::Initialize()
{
    //Palette::currentClearColour = ;
}

void Worldview::Uninitialize()
{


}

void Worldview::Logic()
{
    ProgressWorld();
    UpdateUI();
    Camera::Logic();
}

void Worldview::Input()
{
    if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_UP])
    {
        if(Camera::zoomScale < Camera::SCALE_MAX)
        {
            Camera::zoomScale += 0.1;

            Camera::zoomTranslateX -= Display::NATIVE_WIDTH*0.05; // Ten 0.05s = 0.5
            Camera::zoomTranslateY -= Display::NATIVE_HEIGHT*0.05;

            //std::cout << "zoom scale " << Camera::zoomScale << " (" << Camera::zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_DOWN])
    {
        if(Camera::zoomScale > Camera::SCALE_MIN)
        {
            Camera::zoomScale -= 0.1;

            Camera::zoomTranslateX += Display::NATIVE_WIDTH*0.05; // Ten 0.05s = 0.5
            Camera::zoomTranslateY += Display::NATIVE_HEIGHT*0.05;

            //std::cout << "zoom scale " << Camera::zoomScale << " (" << Camera::zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Mouse::mouseInput[Mouse::MOUSE_MIDDLE])
    {
        Camera::zoomScale = 1;
        Camera::zoomTranslateX = 0;
        Camera::zoomTranslateY = 0;
    }

    if(Mouse::mouseButtonHoldTicks[Mouse::MOUSE_LEFT] == 1)
    {

    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1)
    {
        Scene::ChangeScene(Scene::SCENE_TITLE);
    }

    /// Camera panning


    if(Keyboard::keyHoldTicks[Keyboard::KEY_SPACE] == 1)
    {

    }
}

void Worldview::Drawing()
{
    al_set_target_bitmap(Camera::cameraBuffer);
    al_clear_to_color(COLKEY_BACKGROUND);

    al_identity_transform(&Camera::zoomTransform);
    al_scale_transform(&Camera::zoomTransform,Camera::zoomScale,Camera::zoomScale);
    al_translate_transform(&Camera::zoomTransform,Camera::zoomTranslateX,Camera::zoomTranslateY);
    al_use_transform(&Camera::zoomTransform);

    //DrawGridUnderlay();

    al_use_transform(&Camera::identityTransform);

    Area::Drawing();

    al_set_target_bitmap(Display::scaleBuffer);
    al_clear_to_color(COLKEY_BACKGROUND);
    al_draw_bitmap(Camera::cameraBuffer, 0, 0, 0);
}

void Worldview::ProgressWorld()
{

}

void Worldview::UpdateUI()
{

}

void Worldview::DrawGridUnderlay()
{

    for(int x = 0; x <= Display::NATIVE_WIDTH/Tile::WIDTH; x++) //Columns
    {
        int cxp = Camera::xPosition;
        int tw = Tile::WIDTH;

        al_draw_line(x*Tile::WIDTH - cxp%tw,
                     0,
                     x*Tile::WIDTH - cxp%tw,
                     Display::NATIVE_HEIGHT,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }

    for(int y = 0; y <= Display::NATIVE_HEIGHT/Tile::WIDTH; y++) //Rows
    {
        int cyp = Camera::yPosition;
        int th = Tile::HEIGHT;

        al_draw_line(0,
                     y*Tile::HEIGHT - cyp%th,
                     Display::NATIVE_WIDTH,
                     y*Tile::HEIGHT - cyp%th,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }
}


void Worldview::DrawGridText(float mouseTransformedX, float mouseTransformedY)
{
    int mouseCrosshairXPosition = Camera::xPosition+mouseTransformedX;
    int mouseCrosshairYPosition = Camera::yPosition+mouseTransformedY;

    int mouseCrosshairXPositionCell = mouseCrosshairXPosition/Tile::WIDTH;
    int mouseCrosshairYPositionCell = mouseCrosshairYPosition/Tile::HEIGHT;

    int zoomPercentage = Camera::zoomScale*100;

    std::string mouseCrosshairPositionString = "(" + std::to_string(mouseCrosshairXPosition) + ", " + std::to_string(mouseCrosshairYPosition) + ") : ("
            + std::to_string(mouseCrosshairXPositionCell) + ", " + std::to_string(mouseCrosshairYPositionCell) + ") "
            + std::to_string(zoomPercentage) + "%";

    Util::string_al_draw_text(Text::builtin8,COLKEY_TEXT_VALUE_HIGHLIGHTED,0,0,ALLEGRO_ALIGN_LEFT,mouseCrosshairPositionString);

}
