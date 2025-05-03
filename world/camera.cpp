#include "camera.h"

ALLEGRO_BITMAP* Camera::cameraBuffer;

ALLEGRO_TRANSFORM Camera::identityTransform; // identity transform
ALLEGRO_TRANSFORM Camera::zoomTransform;

float Camera::zoomScale;
float Camera::zoomTranslateX;
float Camera::zoomTranslateY;

bool Camera::worldviewCameraMousePanningDisabled;
float Camera::mouseTransformedX;
float Camera::mouseTransformedY;

bool Camera::atDestination;
bool Camera::approachingDestination;

int Camera::xCell;
int Camera::yCell;
float Camera::xPosition;
float Camera::yPosition;
float Camera::xDestination;
float Camera::yDestination;

void Camera::Initialize()
{
    al_identity_transform(&identityTransform);
    cameraBuffer = al_create_bitmap(Display::NATIVE_WIDTH, Display::NATIVE_HEIGHT);

    atDestination = true;
    approachingDestination = false;

    zoomScale = SCALE_MIN;
    zoomTranslateX = 0; // At 1.0 scale
    zoomTranslateY = 0;

    Camera::SetCell(0, 0);
    Camera::WarpToXYDestination();

}

void Camera::Uninitialize()
{
    al_destroy_bitmap(cameraBuffer);
}

void Camera::SetPosition(float x, float y)
{
    atDestination = true;
    xDestination = xPosition = x;
    yDestination = yPosition = y;
}
void Camera::SetCell(int x, int y)
{
    xCell = x;
    yCell = y;
    SetDestination(xCell*Tile::WIDTH, yCell*Tile::HEIGHT);
}
void Camera::SetDestination(float x, float y)
{
    atDestination = false;
    approachingDestination = true;
    xDestination = x;
    yDestination = y;
}
void Camera::SetDestinationCell(int x, int y)
{
    SetDestination(x*Tile::WIDTH, y*Tile::HEIGHT);
}

void Camera::Logic()
{
    if(atDestination)
    {
        if(xPosition < MIN_X_POSITION)
            xPosition = MIN_X_POSITION;
        else if(xPosition > MAX_X_POSITION)
            xPosition = MAX_X_POSITION;

        if(yPosition < MIN_Y_POSITION)
            yPosition = MIN_Y_POSITION;
        else if(yPosition > MAX_Y_POSITION)
            yPosition = MAX_Y_POSITION;
    }
}

void Camera::Input()
{
    if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_UP])
    {
        if(zoomScale < SCALE_MAX)
        {
            zoomScale += 0.1;

            zoomTranslateX -= Display::NATIVE_WIDTH*0.05; // Ten 0.05s = 0.5
            zoomTranslateY -= Display::NATIVE_HEIGHT*0.05;

            //std::cout << "zoom scale " << zoomScale << " (" << zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_DOWN])
    {
        if(zoomScale > SCALE_MIN)
        {
            zoomScale -= 0.1;

            zoomTranslateX += Display::NATIVE_WIDTH*0.05; // Ten 0.05s = 0.5
            zoomTranslateY += Display::NATIVE_HEIGHT*0.05;

            //std::cout << "zoom scale " << zoomScale << " (" << zoomScale*100 << "%)" << std::endl;
        }

        al_set_mouse_z(0);
    }
    else if(Mouse::mouseInput[Mouse::MOUSE_MIDDLE])
    {
        zoomScale = 1;
        zoomTranslateX = 0;
        zoomTranslateY = 0;
    }

    if(Mouse::mouseButtonHoldTicks[Mouse::MOUSE_LEFT] == 1)
    {

    }

}

void Camera::ApproachDestinationLinear(float change)
{
    if(!atDestination)
    {
        if(xPosition < xDestination)
            xPosition += change;
        else if(xPosition > xDestination)
            xPosition -= change;

        if(yPosition < yDestination)
            yPosition += change;
        else if(yPosition > yDestination)
            yPosition -= change;

        if(std::abs(xDestination - xPosition) <= 2.0 && std::abs(yDestination - yPosition) <= 2.0)
            WarpToXYDestination();
    }
}

void Camera::ApproachDestinationFractional(float change)
{
    if(!atDestination)
    {
        if(xPosition != xDestination)
            xPosition += (xDestination - xPosition)*change;

        if(yPosition != yDestination)
            yPosition += (yDestination - yPosition)*change;

        if(std::abs(xDestination - xPosition) <= 2.0 && std::abs(yDestination - yPosition) <= 2.0)
            WarpToXYDestination();
    }
}

void Camera::WarpToXYDestination()
{
    atDestination = true;
    approachingDestination = false;
    xPosition = xDestination;
    yPosition = yDestination;
}
