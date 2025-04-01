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
    Camera::WarpToDestination();

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
            WarpToDestination();
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
            WarpToDestination();
    }
}

void Camera::WarpToDestination()
{
    atDestination = true;
    approachingDestination = false;
    xPosition = xDestination;
    yPosition = yDestination;
}
