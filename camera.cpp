#include "camera.h"

ALLEGRO_BITMAP *Camera::cameraBuffer {};

ALLEGRO_TRANSFORM Camera::identityTransform {}; // identity transform
ALLEGRO_TRANSFORM Camera::zoomTransform {};

float Camera::zoomScale {};
float Camera::zoomTranslateX {};
float Camera::zoomTranslateY {};

// bool Camera::worldviewCameraMousePanningDisabled;
// float Camera::mouseTransformedX;
// float Camera::mouseTransformedY;

bool Camera::atDestination {};
bool Camera::approachingDestination {};

int Camera::worldXCell {};
int Camera::worldYCell {};
float Camera::xPosition {};
float Camera::yPosition {};
float Camera::xDestination {};
float Camera::yDestination {};

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
    worldXCell = x;
    worldYCell = y;
    SetDestination(worldXCell * Tile::WIDTH, worldYCell * Tile::HEIGHT);
}
void Camera::SetDestination(float x, float y)
{
    atDestination = false;
    approachingDestination = true;
    xDestination = x;
    yDestination = y;

    //std::cout << "destination reset" << std::endl;
}
void Camera::SetDestinationCell(int x, int y)
{
    SetDestination(x * Tile::WIDTH, y * Tile::HEIGHT);
}

void Camera::Logic()
{

}

void Camera::Input()
{
    /*
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
        */
}

void Camera::ApproachDestinationLinear(float x_change, float y_change)
{
    if (!atDestination)
    {
        if (xPosition < xDestination)
            xPosition += x_change;
        else if (xPosition > xDestination)
            xPosition -= x_change;

        if (yPosition < yDestination)
            yPosition += y_change;
        else if (yPosition > yDestination)
            yPosition -= y_change;

        if (std::abs(xDestination - xPosition) <= APPROACH_DESTINATION_X_PRECISION && std::abs(yDestination - yPosition) <= APPROACH_DESTINATION_Y_PRECISION)
            WarpToXYDestination();
    }
}

void Camera::ApproachDestinationFractional(float x_change, float y_change)
{
    if (!atDestination)
    {
        if (xPosition != xDestination)
            xPosition += (xDestination - xPosition) * x_change;

        if (yPosition != yDestination)
            yPosition += (yDestination - yPosition) * y_change;

        if (std::abs(xDestination - xPosition) <= APPROACH_DESTINATION_X_PRECISION && std::abs(yDestination - yPosition) <= APPROACH_DESTINATION_Y_PRECISION)
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
