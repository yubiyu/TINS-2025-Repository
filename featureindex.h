#pragma once

struct FeatureIndex
{
    enum enumFeatures
    {
        FEATURE_NONE = 0,

        FEATURE_CHEST_01 = 1,
        FEATURE_CHEST_02 = 2,
        FEATURE_CHEST_03 = 3
    };
    static const int NUM_FEATURE_TYPES = FEATURE_CHEST_03 + 1;
    static const int MARKER_FEATURE_CHEST_BEGIN = FEATURE_CHEST_01;
    static const int MARKER_FEATURE_CHEST_END = FEATURE_CHEST_03;

    static const int SPRITE_CHEST_CLOSED_INDEX = 1;

    static const int SPRITE_CHEST_ACTIVATING_BEGIN = 2;
    static const int SPRITE_CHEST_ACTIVATING_END = 6;

    static const int SPRITE_CHEST_OPEN_INDEX = 7;

    static const int NUM_SPRITES = SPRITE_CHEST_OPEN_INDEX + 1;

    enum enumBlueprintFeatures
    {
        BLUEPRINT_FEATURE_NONE = 0x00,

        BLUEPRINT_FEATURE_CHEST_01 = 0x01,
        BLUEPRINT_FEATURE_CHEST_02 = 0x02,
        BLUEPRINT_FEATURE_CHEST_03 = 0x03
    };
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_CLOSED_BEGIN = BLUEPRINT_FEATURE_CHEST_A_CLOSED;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_CLOSED_END = BLUEPRINT_FEATURE_CHEST_C_CLOSED;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_OPEN_BEGIN = BLUEPRINT_FEATURE_CHEST_A_OPEN;
    // static const int MARKER_BLUEPRINT_FEATURE_CHEST_OPEN_END = BLUEPRINT_FEATURE_CHEST_C_OPEN;
    static const int NUM_BLUEPRINT_FEATURE_TYPES = NUM_FEATURE_TYPES; // For the time being, assuming 1:1 between blueprints and features.
};