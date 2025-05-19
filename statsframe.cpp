#include "statsframe.h"

void StatsFrame::Initialize()
{

}

void StatsFrame::Uninitialize()
{

}

void StatsFrame::Logic()
{
    if(PC::pc != nullptr)
    {

    }
}

void StatsFrame::Drawing()
{
    al_draw_bitmap(Image::pcStatsFramePng, X_POSITION, Y_POSITION, 0);
}

void StatsFrame::Input()
{


}