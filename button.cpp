#include "button.h"

void Button::Initialize(float frame_x, float frame_y, float x, float y, float w, float h, int id)
{
    frameXPosition = frame_x;
    frameYPosition = frame_y;
    xPosition = x;
    yPosition = y;
    width = w;
    height = h;

    identity = id;

    //name = ButtonIndex::buttonNames.at(id);
}

void Button::Drawing(float frame_x, float frame_y)
{
    float drawXPosition = frame_x + xPosition;
    float drawYPosition = frame_y + yPosition;

    al_draw_filled_rounded_rectangle(drawXPosition, drawYPosition,
                                     drawXPosition + width, drawYPosition + height,
                                     8.0, 8.0,
                                     al_map_rgb(0,0,0));
    al_draw_rounded_rectangle(drawXPosition, drawYPosition,
                              drawXPosition + width, drawYPosition + height,
                              8.0, 8.0,
                              al_map_rgb(255,255,255), 2);

    Hax::string_al_draw_text(Font::monogram32, al_map_rgb(255,255,255),
                             drawXPosition + width/2, drawYPosition, ALLEGRO_ALIGN_CENTER,
                             name);
}

bool Button::CheckWithinButton(float x_2, float y_2, float w_2, float h_2)
{
    return Hax::AABBCollision(frameXPosition+xPosition, frameYPosition+yPosition, width, height,
                              x_2, y_2, w_2, h_2);

}
