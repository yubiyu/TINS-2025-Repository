#pragma once

#include "timer.h"

struct FeatureIndex
{
    enum enumFeatures
    {
        FEATURE_NONE = 0,

        FEATURE_CHEST_01 = 1,
        FEATURE_CHEST_02 = 2,
        FEATURE_CHEST_03 = 3,

        FEATURE_INSCRIPTION_01 = 4,
        FEATURE_INSCRIPTION_02 = 5,
        FEATURE_INSCRIPTION_03 = 6,
        FEATURE_INSCRIPTION_04 = 7,
        FEATURE_INSCRIPTION_05 = 8,
        FEATURE_INSCRIPTION_06 = 9,
        FEATURE_INSCRIPTION_07 = 10,
        FEATURE_INSCRIPTION_08 = 11,
        FEATURE_INSCRIPTION_09 = 12
    };
    static const int NUM_FEATURE_TYPES = FEATURE_INSCRIPTION_09 + 1;
    static const int MARKER_FEATURE_CHEST_BEGIN = FEATURE_CHEST_01;
    static const int MARKER_FEATURE_CHEST_END = FEATURE_CHEST_03;

    static const int MARKER_FEATURE_INSCRIPTION_BEGIN = FEATURE_INSCRIPTION_01;
    static const int MARKER_FEATURE_INSCRIPTION_END = FEATURE_INSCRIPTION_09;

    static const int SPRITE_CHEST_CLOSED_INDEX = 1;

    static const int SPRITE_CHEST_ACTIVATING_BEGIN = 1;
    static const int SPRITE_CHEST_ACTIVATING_END = 6;
    static const int NUM_SPRITE_CHEST_ACTIVATING_FRAMES = SPRITE_CHEST_ACTIVATING_END - SPRITE_CHEST_ACTIVATING_BEGIN;
    static const int CHEST_ACTIVATION_FRAME_DELAY_MAX = Timer::FPS * 0.12;
    static const int SPRITE_CHEST_OPEN_INDEX = 7;
    static const int SPRITE_INSCRIPTION_INDEX = 8;
    static const int NUM_SPRITES = SPRITE_INSCRIPTION_INDEX + 1;

    enum enumBlueprintFeatures
    {
        BLUEPRINT_FEATURE_NONE = 0x00,

        BLUEPRINT_FEATURE_CHEST_01 = 0x01,
        BLUEPRINT_FEATURE_CHEST_02 = 0x02,
        BLUEPRINT_FEATURE_CHEST_03 = 0x03,

        BLUEPRINT_FEATURE_INSCRIPTION_01 = 0x04,
        BLUEPRINT_FEATURE_INSCRIPTION_02 = 0x05,
        BLUEPRINT_FEATURE_INSCRIPTION_03 = 0x06,
        BLUEPRINT_FEATURE_INSCRIPTION_04 = 0x07,
        BLUEPRINT_FEATURE_INSCRIPTION_05 = 0x08,
        BLUEPRINT_FEATURE_INSCRIPTION_06 = 0x09,
        BLUEPRINT_FEATURE_INSCRIPTION_07 = 0x0A,
        BLUEPRINT_FEATURE_INSCRIPTION_08 = 0x0B,
        BLUEPRINT_FEATURE_INSCRIPTION_09 = 0x0C
    };
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_CLOSED_BEGIN = BLUEPRINT_FEATURE_CHEST_A_CLOSED;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_CLOSED_END = BLUEPRINT_FEATURE_CHEST_C_CLOSED;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_OPEN_BEGIN = BLUEPRINT_FEATURE_CHEST_A_OPEN;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_OPEN_END = BLUEPRINT_FEATURE_CHEST_C_OPEN;
    static const int NUM_BLUEPRINT_FEATURE_TYPES = NUM_FEATURE_TYPES; // For the time being, assuming 1:1 between blueprints and features.
};