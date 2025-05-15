#pragma once

#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct Util
{
    // Generate random float between 0 - range.
    static inline float RandFloat(float x)
    {
        return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / x));
    }

    // Generate random float within range.
    static inline float RandFloatRange(float low, float high)
    {
        return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
    }

    static inline bool AABBCollision(float a_x, float a_y, float a_width, float a_height,
                                     float b_x, float b_y, float b_width, float b_height)
    {
        if (a_x + a_width <= b_x || b_x + b_width <= a_x)
            return false;
        if (a_y + a_height <= b_y || b_y + b_height <= a_y)
            return false;

        return true;
    }

    static inline float LinearInterpolateX(float x1, float y1, float x2, float y2, float x)
    {
        float y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        return y;
    }

    static inline void al_round_rgb(ALLEGRO_COLOR *color)
    {
        int ri = static_cast<int>(color->r * 255.0f + 0.5f);
        int gi = static_cast<int>(color->g * 255.0f + 0.5f);
        int bi = static_cast<int>(color->b * 255.0f + 0.5f);

        *color = al_map_rgb(ri, gi, bi);
    }

    static inline void DrawPlaceholder32(float x, float y)
    {
        al_draw_filled_rectangle(x, y, x + 32, y + 32, al_map_rgb(100, 100, 100));
    }

    static inline int string_al_get_text_width(const ALLEGRO_FONT *f, std::string str)
    {
        const char *c = str.c_str();
        return al_get_text_width(f, c);
    }

    static inline void string_al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags, std::string text)
    {
        const char *c = text.c_str();
        al_draw_text(font, color, x, y, flags, c);
    }

    static inline void string_al_draw_multiline_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, float max_width, float line_height, int flags, std::string text)
    {
        const char *c = text.c_str();
        al_draw_multiline_text(font, color, x, y, max_width, line_height, flags, c);
    }

    /// Function borrowed from Mark Oates
    static inline bool do_multiline_text_line_num_callback(int line_num, const char *line, int size, void *extra)
    {
        *((int *)extra) = line_num;
        return true;
    }

    /// Function borrowed from Mark Oates
    static inline int count_multiline_rows(ALLEGRO_FONT *font, float max_width, std::string text)
    {
        if (text.empty())
            return 0;

        int multiline_rows = 0;
        al_do_multiline_text(font, max_width, text.c_str(), do_multiline_text_line_num_callback, &multiline_rows); // Actually calls the callback function once for each line. Could be many times.

        return multiline_rows + 1;
    }

    struct MultilineWidthCollectorContext
    {
        ALLEGRO_FONT* font;
        std::vector<int>* lineWidths;
    };

    static inline bool collect_multiline_widths_callback(int line_num, const char *line, int size, void *extra)
    {
        MultilineWidthCollectorContext*context = static_cast<MultilineWidthCollectorContext*>(extra);
        std::string lineString(line, size);
        context->lineWidths->push_back( al_get_text_width(context->font, lineString.c_str()));

        return true;
    }

    static inline std::vector<int> collect_multiline_widths(ALLEGRO_FONT *font, float max_width, const std::string &text)
    {
        std::vector<int> lineWidths;

        if (text.empty())
            return lineWidths;

        MultilineWidthCollectorContext context{font, &lineWidths};

        al_do_multiline_text(font, max_width, text.c_str(), collect_multiline_widths_callback, &context);

        /*
        std::cout << "Debug: Util: Multiline widths: ";
        for(size_t i = 0; i < lineWidths.size(); i++)
            std::cout << lineWidths[i] << " ";
        std::cout << std::endl;
        */

        return lineWidths;
    }
};
