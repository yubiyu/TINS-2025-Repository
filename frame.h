#pragma once

#include "button.h"
#include "hax.h"

#include <vector>
#include <iostream>

class Frame
{
    float xPosition, yPosition;
    float width, height;


    bool isButtonFrame;
    std::vector<Button*>buttons;
    size_t buttonRows, buttonCols;
    int buttonWidth, buttonHeight;
    float buttonXSeparation, buttonYSeparation;


public:
    Frame();
    ~Frame();

    void Initialize(float x, float y, float w, float h, bool is_button_frame);

    void Drawing();

    bool CheckWithinFrame(float x_2, float y_2, float w_2, float h_2);
    void AddButton(int id);

    float GetXPosition() const { return xPosition;}
    float GetYPosition() const { return yPosition;}
    float GetWidth() const { return width;}
    float GetHeight() const { return height;}

    std::vector<Button*> &GetButtons() { return buttons;}

};
