#pragma once

struct FeatureIndex
{
    enum enumFeatures
    {
        FEATURE_NONE = 0,

        FEATURE_CHEST_A_CLOSED = 1,
        FEATURE_CHEST_B_CLOSED = 2,
        FEATURE_CHEST_C_CLOSED = 3,

        FEATURE_CHEST_A_OPEN = 4,
        FEATURE_CHEST_B_OPEN = 5,
        FEATURE_CHEST_C_OPEN = 6,
    };
    static const int MARKER_FEATURE_CHEST_CLOSED_BEGIN = FEATURE_CHEST_A_CLOSED;
    static const int MARKER_FEATURE_CHEST_CLOSED_END = FEATURE_CHEST_C_CLOSED;
    static const int MARKER_FEATURE_CHEST_OPEN_BEGIN = FEATURE_CHEST_A_OPEN;
    static const int MARKER_FEATURE_CHEST_OPEN_END = FEATURE_CHEST_C_OPEN;
    static const int NUM_FEATURE_TYPES = MARKER_FEATURE_CHEST_OPEN_END + 1;

};