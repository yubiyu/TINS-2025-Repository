#include "statusframe.h"

void StatusFrame::Initialize()
{
}

void StatusFrame::Uninitialize()
{
}

void StatusFrame::Logic()
{
    if (PC::pc != nullptr)
    {
    }
}

void StatusFrame::Drawing()
{
    al_draw_bitmap(Image::statusFramePng, FRAME_X_POSITION, FRAME_Y_POSITION, 0);

    std::ostringstream chestsLootedOSS;
    chestsLootedOSS << std::setw(2) << std::setfill('0') << Area::chestsLootedCount;

    Util::string_al_draw_text(FONTDEF_STATUS_FRAME, COLKEY_STATUS_FRAME_TEXT,
                              FRAME_X_POSITION + TEXT_AREA_CHESTS_LOOTED_X_POSITION,
                              FRAME_Y_POSITION + TEXT_Y_POSITION,
                              ALLEGRO_ALIGN_LEFT, chestsLootedOSS.str());

}

void StatusFrame::Input()
{
}