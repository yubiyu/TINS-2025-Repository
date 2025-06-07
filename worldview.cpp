#include "worldview.h"

void Worldview::Initialize()
{
}

void Worldview::Uninitialize()
{
}

void Worldview::Logic()
{
    Area::Logic();
    PC::pc->Logic();
    StatusFrame::Logic();

    Camera::Logic();

    Dialog::Logic();
}

void Worldview::Input()
{
    if (Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1)
        Scene::ChangeScene(Scene::SCENE_TITLE);

    if (!Area::inRoomTransition)
    {
        if (Dialog::isActive)
        {
            Dialog::Input();
        }
        else
        {
            PC::pc->Input();

            if (Keyboard::keyHoldTicks[Keyboard::KEY_Z] == 1)
            {
                switch (PC::pc->GetFacing())
                {
                case Direction::NORTH:
                    Area::ActivateFeature(PC::pc->GetRoomXCell(), PC::pc->GetRoomYCell() - 1);
                    break;

                case Direction::SOUTH:
                    Area::ActivateFeature(PC::pc->GetRoomXCell(), PC::pc->GetRoomYCell() + 1);
                    break;

                case Direction::WEST:
                    Area::ActivateFeature(PC::pc->GetRoomXCell() - 1, PC::pc->GetRoomYCell());
                    break;

                case Direction::EAST:
                    Area::ActivateFeature(PC::pc->GetRoomXCell() + 1, PC::pc->GetRoomYCell());
                    break;
                }
                // Dialog::Activate("Test","Test");
            }
        }
    }

    Camera::Input();
}

void Worldview::Drawing()
{
    al_set_target_bitmap(Camera::cameraBuffer);
    al_clear_to_color(COLKEY_BACKGROUND);

    al_identity_transform(&Camera::zoomTransform);
    al_scale_transform(&Camera::zoomTransform, Camera::zoomScale, Camera::zoomScale);
    al_translate_transform(&Camera::zoomTransform, Camera::zoomTranslateX, Camera::zoomTranslateY);
    al_use_transform(&Camera::zoomTransform);

    // DrawGridUnderlay();

    al_use_transform(&Camera::identityTransform);

    Area::Drawing();
    PC::pc->Drawing();

    al_set_target_bitmap(Display::scaleBuffer);
    al_clear_to_color(COLKEY_BACKGROUND);
    al_draw_bitmap(Camera::cameraBuffer, 0, 0, 0);

    Util::string_al_draw_text(Text::publicPixel8, COLKEY_DEBUG_TEXT_HIGHLIGHTED, 0, 0, ALLEGRO_ALIGN_LEFT, "(" + std::to_string((int)Camera::xPosition) + "," + std::to_string((int)Camera::yPosition) + " @ " + Area::worldRoomID);

    StatusFrame::Drawing();
    Dialog::Drawing();
}

void Worldview::DrawGridUnderlay()
{

    for (int x = 0; x <= Display::NATIVE_WIDTH / Tile::WIDTH; x++) // Columns
    {
        int cxp = Camera::xPosition;
        int tw = Tile::WIDTH;

        al_draw_line(x * Tile::WIDTH - cxp % tw,
                     0,
                     x * Tile::WIDTH - cxp % tw,
                     Display::NATIVE_HEIGHT,
                     COLKEY_DEBUG_GRID_UNDERLAY, 1);
    }

    for (int y = 0; y <= Display::NATIVE_HEIGHT / Tile::WIDTH; y++) // Rows
    {
        int cyp = Camera::yPosition;
        int th = Tile::HEIGHT;

        al_draw_line(0,
                     y * Tile::HEIGHT - cyp % th,
                     Display::NATIVE_WIDTH,
                     y * Tile::HEIGHT - cyp % th,
                     COLKEY_DEBUG_GRID_UNDERLAY, 1);
    }
}

void Worldview::DrawGridText(float mouseTransformedX, float mouseTransformedY)
{
    int mouseCrosshairXPosition = Camera::xPosition + mouseTransformedX;
    int mouseCrosshairYPosition = Camera::yPosition + mouseTransformedY;

    int mouseCrosshairXPositionCell = mouseCrosshairXPosition / Tile::WIDTH;
    int mouseCrosshairYPositionCell = mouseCrosshairYPosition / Tile::HEIGHT;

    //int zoomPercentage = Camera::zoomScale * 100;

    std::string mouseCrosshairPositionString = "(" + std::to_string(mouseCrosshairXPosition) + ", " + std::to_string(mouseCrosshairYPosition) + ") : (" + std::to_string(mouseCrosshairXPositionCell) + ", " + std::to_string(mouseCrosshairYPositionCell) + ") " /* + std::to_string(zoomPercentage) + "%"*/;

    Util::string_al_draw_text(Text::builtin8, COLKEY_DEBUG_TEXT_HIGHLIGHTED, 0, 0, ALLEGRO_ALIGN_LEFT, mouseCrosshairPositionString);
}
