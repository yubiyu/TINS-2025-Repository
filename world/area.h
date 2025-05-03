#pragma once

#include "config/configuration.h"

#include "resource/image.h"

#include "world/cellindex.h"

#include <string>
#include <sstream>

#include <iostream>
#include <iomanip> // For setw

struct Area
{
    static constexpr const char* STARTING_AREA = "0";

    enum enumDomains
    {
        DOMAIN_SULWON = 0,
        DOMAIN_RUWON = 1,
        DOMAIN_YION = 2
    };

    static const int COLS = 10;
    static const int ROWS = 8;

    static int roomBlueprint[COLS*ROWS];
    static int room[COLS*ROWS];

    static int defaultSpawnCol, defaultSpawnRow;

    static void Initialize(const char* room);
    static void Uninitialize();
    static void LoadRoomBlueprint(const char* room);
    static void ParseToRoomBlueprint(int x, int y, int data);
    static void ConstructRoom();

    static void Drawing();
};
