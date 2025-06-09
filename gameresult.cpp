#include "gameresult.h"
bool GameResult::isActive{};
bool GameResult::isScrolling{};

std::string GameResult::text{};
ALLEGRO_BITMAP *GameResult::textBuffer{};
int GameResult::textBufferXPosition{}, GameResult::textBufferYPosition{};

int GameResult::textFieldTopRow{};
int GameResult::textBufferNumRows{};
std::vector<int> GameResult::textBufferRowWidths{};

int GameResult::textFieldRevealedRow{};
int GameResult::textFieldRevealedCol{};

int GameResult::frameScrollingTick{};

bool GameResult::spaceAtCaret{};
int GameResult::caretFrame{};

void GameResult::Initialize()
{
    Deactivate();
}

void GameResult::Uninitialize()
{
    if (textBuffer != nullptr)
    {
        al_destroy_bitmap(textBuffer);
    }
}

void GameResult::Logic()
{
    if (isActive)
    {
        if (isScrolling)
        {
            frameScrollingTick++;
            if (frameScrollingTick >= FRAME_SCROLLING_TICKS_NEEDED)
            {
                frameScrollingTick = 0;
                textFieldRevealedCol++;

                // Scrolling advances one line if revealed to the end of line.
                if (textFieldTopRow + textFieldRevealedRow < textBufferNumRows // Guards against memory access outside textBufferRowWidths
                    && textFieldRevealedCol >= textBufferRowWidths[textFieldTopRow + textFieldRevealedRow] / TEXT_CHAR_WIDTH)
                {
                    /*if(textFieldRevealedCol >= TEXT_FIELD_COLS) is not necessary
                    because textBufferRowWidths = Util::collect_multiline_widths() already takes into account the width of the textfield.*/
                    textFieldRevealedCol = 0;
                    textFieldRevealedRow++;
                }

                if (textFieldRevealedRow >= TEXT_FIELD_ROWS // To clarify, textFieldRevealedRow would have to be at least one line beyond the end of the text field.
                    || textFieldRevealedRow > textBufferNumRows - textFieldTopRow - 1)
                    isScrolling = false;

                caretFrame++;
                if (caretFrame > 1)
                    caretFrame = 0;
            }
        }
    }
}

void GameResult::Drawing()
{
    if (isActive)
    {
        al_clear_to_color(COLKEY_GAME_RESULT_BACKGROUND);

        al_draw_bitmap_region(textBuffer,
                              textBufferXPosition, textBufferYPosition,
                              TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT,
                              TEXT_FIELD_X, TEXT_FIELD_Y, 0);

        if (isScrolling)
        {
            if (textFieldRevealedRow < TEXT_FIELD_ROWS)
            {
                // Draws two overlapping rectangles the same colour as the textfield. Obscures cols and rows beyond textFieldRevealedCol and textFieldRevealedRow.
                // In the future, update to use masking alpha colour on a transparent bitmap.
                al_draw_filled_rectangle(TEXT_FIELD_X, TEXT_FIELD_Y + (textFieldRevealedRow + 1) * TEXT_FIELD_ROW_HEIGHT,
                                         TEXT_FIELD_X + TEXT_FIELD_WIDTH, TEXT_FIELD_Y + TEXT_FIELD_HEIGHT,
                                         COLKEY_DIALOG_TEXTFIELD);

                if (textFieldRevealedCol < TEXT_FIELD_COLS)
                    al_draw_filled_rectangle(TEXT_FIELD_X + textFieldRevealedCol * Tile::HALF_WIDTH, TEXT_FIELD_Y + textFieldRevealedRow * TEXT_FIELD_ROW_HEIGHT,
                                             TEXT_FIELD_X + TEXT_FIELD_WIDTH, TEXT_FIELD_Y + TEXT_FIELD_HEIGHT,
                                             COLKEY_DIALOG_TEXTFIELD);
            }

            al_draw_bitmap(Image::dialogCaretSub[caretFrame],
                           TEXT_FIELD_X + textFieldRevealedCol * Tile::HALF_WIDTH,
                           TEXT_FIELD_Y + textFieldRevealedRow * TEXT_FIELD_ROW_HEIGHT, 0);
        }
    }
}

void GameResult::Input()
{
    if (isActive)
    {
        //if (Keyboard::keyHoldTicks[Keyboard::KEY_Z] == 1)
          //  Advance();
        
            if (Keyboard::keyHoldTicks[Keyboard::KEY_X] == 1)
        {
            Deactivate();
            Scene::ChangeScene(Scene::SCENE_TITLE);
            Reset::needsReset = true;
        }
    }
}

void GameResult::Activate(std::string text_content)
{
    if (isActive || textBuffer != nullptr)
        Deactivate();

    isActive = true;
    isScrolling = true;

    textBufferXPosition = 0;
    textBufferYPosition = 0;
    text = text_content;
    textBufferNumRows = Util::count_multiline_rows(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);
    textBufferRowWidths = Util::collect_multiline_widths(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);

    textBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textBufferNumRows * TEXT_FIELD_ROW_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_ROW_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);

    textFieldTopRow = 0;
    textFieldRevealedRow = 0;
    textFieldRevealedCol = 0;

    frameScrollingTick = 0;
}

/*
void GameResult::Activate(const char *section, const char *key, std::string appendText)
{
    std::string text = Configuration::GetString(Configuration::dialogsCfg, section, key) + appendText;
    Activate(text);
}

void GameResult::Activate(const char *section, const char *key)
{
    Activate(Configuration::GetString(Configuration::dialogsCfg, section, key));
}
*/


void GameResult::ActivateEnding()
{
    std::string endingText;
    if(Area::winConditionAchieved)
        endingText = "Well done! You escaped the maze.";
    else
        endingText = "Lost and hungry, you seek sustenance in your dreams...";

    std::string stepsWalkedText = "Walked " + std::to_string(PC::pc->GetStepsWalkedCount()) + " cells.";
    std::string layersAscendedText = "Ascended " + std::to_string(Area::layersAscendedTally) + "F.";
    std::string layersDescendedText = "Descended " + std::to_string(Area::layersDescendedTally) + "F.";
    std::string chestsLootedText = "Looted " + std::to_string(Area::chestsLootedCount) + " chests.";

    const std::string theEndText = "(Press X to exit).";
    

    std::string combinedText = endingText + "\n\n" + stepsWalkedText + "\n" + layersAscendedText + "\n" + layersDescendedText + "\n" + chestsLootedText + "\n\n" + theEndText;
    Activate(combinedText);

}

void GameResult::Deactivate()
{
    isActive = false;
    isScrolling = false;

    if (textBuffer != nullptr)
        al_destroy_bitmap(textBuffer);

    textBuffer = nullptr;
}

void GameResult::Advance()
{
    // Note that textfieldTopRow counts from zeroth line, while textBufferNumRows is equal to the number of lines in textBuffer.
    int availableRows = std::min(TEXT_FIELD_ROWS, textBufferNumRows - textFieldTopRow); // "available" to textfield, available to textBuffer. The smaller of the two.
    if (textFieldRevealedRow < availableRows)                                           // Current textfield is not fully revealed
    {
        // Advance to the end of the current textfield region. Stop scrolling.
        textFieldRevealedRow = TEXT_FIELD_ROWS;
        textFieldRevealedCol = TEXT_FIELD_COLS;
        isScrolling = false;
    }
    else
    {
        if (textFieldTopRow + TEXT_FIELD_ROWS >= textBufferNumRows)
        {
            Deactivate();
            return;
        }
        // Advance to the *next* textbuffer region (default: three rows ahead).
        textFieldTopRow += TEXT_BUFFER_ADVANCE_ROWS;
        textBufferYPosition += TEXT_FIELD_ROW_HEIGHT * TEXT_BUFFER_ADVANCE_ROWS;

        textFieldRevealedRow = 0;
        textFieldRevealedCol = 0;

        isScrolling = true;
    }
}