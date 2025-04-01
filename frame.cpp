#include "frame.h"

Frame::Frame()
{

}

Frame::~Frame()
{
    for(std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end();)
    {
        delete *it;
        it = buttons.erase(it);
    }
}


void Frame::Initialize(float x, float y, float w, float h, bool is_button_frame)
{
    xPosition = x;
    yPosition = y;
    isButtonFrame = is_button_frame;

    if(isButtonFrame)
    {
        buttonRows = FrameIndex::BUTTON_ROWS_STANDARD;
        buttonCols = FrameIndex::BUTTON_COLS_STANDARD;
        buttonWidth = ButtonIndex::BUTTON_WIDTH_STANDARD;
        buttonHeight = ButtonIndex::BUTTON_HEIGHT_STANDARD;
        buttonXSeparation = FrameIndex::BUTTON_X_SEPARATION_STANDARD;
        buttonYSeparation = FrameIndex::BUTTON_Y_SEPARATION_STANDARD;

        width = buttonWidth*buttonCols + buttonXSeparation*(buttonCols-1);
        height = buttonHeight*buttonRows + buttonYSeparation*(buttonRows-1);
    }
    else
    {
        width = w;
        height = h;
    }
}

void Frame::Drawing()
{
    if(!isButtonFrame)
        al_draw_rounded_rectangle(xPosition, yPosition, xPosition+width, yPosition+height, 8.0, 8.0, al_map_rgb(0,0,0), 4);

    for(std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
    {
        (*it)->Drawing(xPosition, yPosition);
    }
}

bool Frame::CheckWithinFrame(float x_2, float y_2, float w_2, float h_2)
{
    return Hax::AABBCollision(xPosition, yPosition, width, height,
                              x_2, y_2, w_2, h_2);

}

void Frame::AddButton(int id)
{
    Button*button = new Button();
    size_t index = buttons.size(); // The point is that it increases by one every time a button is push_back()ed, starting from 0.
    size_t col = index%buttonCols;
    size_t row = index/buttonCols;

    float x = col*buttonWidth + col*buttonXSeparation;
    float y = row*buttonHeight + row*buttonYSeparation;
    float w = buttonWidth;
    float h = buttonHeight;

    button->Initialize(xPosition, yPosition, x,y,w,h,id);
    buttons.push_back(button);
}
