#include "statusframe.h"

void StatusFrame::Initialize()
{

}

void StatusFrame::Uninitialize()
{

}

void StatusFrame::Logic()
{
    if(PC::pc != nullptr)
    {

    }
}

void StatusFrame::Drawing()
{
    al_draw_bitmap(Image::statusFramePng, FRAME_X_POSITION, FRAME_Y_POSITION, 0);
    
}

void StatusFrame::Input()
{


}