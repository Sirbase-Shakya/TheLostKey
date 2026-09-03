#include "raylib.h"
#include <string>

using namespace std;

// ===============================
// GAME STATE
// ===============================

bool hasPrimKey = false;
bool hasSecKey = false;
bool hasPhoto = false;
bool hasMainPhoto = false;
bool hasFlashlight = false;

bool drawerOpened = false;
bool mirrorBroken = false;

enum Room
{
    HOUSE,
    BEDROOM,
    LIBRARY,
    BASEMENT,
    FRONT_DOOR,
    ESCAPED
};

Room currentRoom = HOUSE;

// Message shown at the bottom
string message = "You wake up in an abandoned house...";

// ===============================
// COLORS
// ===============================

Color bgColor = {15, 15, 18, 255};
Color textColor = {220, 220, 220, 255};
Color dimColor = {130, 130, 130, 255};
Color borderColor = {100, 100, 100, 255};
Color highlightColor = {230, 200, 120, 255};

// ===============================
// DRAW TEXT HELPER
// ===============================

void DrawASCII(string text, int x, int y, int fontSize = 20)
{
    DrawText(text.c_str(), x, y, fontSize, textColor);
}

void DrawCentered(string text, int y, int fontSize = 20)
{
    int width = MeasureText(text.c_str(), fontSize);

    DrawText(
        text.c_str(),
        (GetScreenWidth() - width) / 2,
        y,
        fontSize,
        textColor);
}

// ===============================
// HOUSE
// ===============================

void house()
{
    ClearBackground(bgColor);

    DrawCentered("THE LOST KEY", 40, 32);

    DrawASCII(
        "============================================================",
        70, 100);

    DrawASCII(
        "                 ABANDONED HOUSE",
        70, 130);

    DrawASCII(
        "============================================================",
        70, 160);

    DrawASCII(
        "             _______________________",
        70, 210);

    DrawASCII(
        "            |                       |",
        70, 235);

    DrawASCII(
        "            |       LIVING ROOM     |",
        70, 260);

    DrawASCII(
        "            |                       |",
        70, 285);

    DrawASCII(
        "            |_______________________|",
        70, 310);

    DrawASCII(
        "                 |       |",
        70, 350);

    DrawASCII(
        "          [1] BEDROOM   [2] LIBRARY",
        70, 380);

    DrawASCII(
        "          [3] BASEMENT  [4] FRONT DOOR",
        70, 410);

    DrawASCII(
        "------------------------------------------------------------",
        70, 470);

    DrawASCII("> " + message, 70, 500);

    DrawASCII("[1] Bedroom", 70, 550);
    DrawASCII("[2] Library", 250, 550);
    DrawASCII("[3] Basement", 410, 550);
    DrawASCII("[4] Front Door", 620, 550);
}

// ===============================
// BEDROOM
// ===============================

void bedroom()
{
    ClearBackground(bgColor);

    DrawCentered("BEDROOM", 30, 30);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 80);

    DrawASCII(
        "|                                                          |",
        50, 105);

    // Mirror
    DrawASCII(
        "|              +------------------+                        |",
        50, 130);

    DrawASCII(
        "|              |                  |                        |",
        50, 155);

    if (!mirrorBroken)
    {
        DrawASCII(
            "|              |      MIRROR      |                        |",
            50, 180);

        DrawASCII(
            "|              |                  |                        |",
            50, 205);
    }
    else
    {
        DrawASCII(
            "|              |    /  /  /  /   |                        |",
            50, 180);

        DrawASCII(
            "|              |  /  BROKEN  /   |                        |",
            50, 205);
    }

    DrawASCII(
        "|              +------------------+                        |",
        50, 230);

    // Bed
    DrawASCII(
        "|                                                          |",
        50, 255);

    DrawASCII(
        "|      +----------------------------------+                |",
        50, 280);

    DrawASCII(
        "|      |              BED                 |                |",
        50, 305);

    DrawASCII(
        "|      +----------------------------------+                |",
        50, 330);

    // Drawer
    DrawASCII(
        "|                                                          |",
        50, 355);

    DrawASCII(
        "|       +-----------+                     +-----------+     |",
        50, 380);

    DrawASCII(
        "|       |  DRAWER   |                     |   DOOR    |     |",
        50, 405);

    DrawASCII(
        "|       +-----------+                     +-----------+     |",
        50, 430);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 455);

    DrawASCII("> " + message, 50, 490);

    DrawASCII("[1] Search Bed", 50, 530);
    DrawASCII("[2] Examine Mirror", 250, 530);
    DrawASCII("[3] Open Drawer", 500, 530);

    DrawASCII("[4] Leave Room", 50, 565);
}

// ===============================
// LIBRARY
// ===============================

void library()
{
    ClearBackground(bgColor);

    DrawCentered("LIBRARY", 30, 30);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 80);

    DrawASCII(
        "|  +------+ +------+ +------+ +------+ +------+ +------+  |",
        50, 120);

    DrawASCII(
        "|  | BOOK | | BOOK | | BOOK | | BOOK | | BOOK | | BOOK |  |",
        50, 145);

    DrawASCII(
        "|  |      | |      | |      | |      | |      | |      |  |",
        50, 170);

    DrawASCII(
        "|  +------+ +------+ +------+ +------+ +------+ +------+  |",
        50, 195);

    DrawASCII(
        "|                                                          |",
        50, 225);

    DrawASCII(
        "|              +----------------------+                    |",
        50, 255);

    DrawASCII(
        "|              |        DESK          |                    |",
        50, 280);

    DrawASCII(
        "|              +----------------------+                    |",
        50, 305);

    DrawASCII(
        "|                                                          |",
        50, 335);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 365);

    DrawASCII("> " + message, 50, 405);

    DrawASCII("[1] Search Bookshelf", 50, 450);
    DrawASCII("[2] Pull Strange Book", 320, 450);
    DrawASCII("[3] Leave Library", 50, 490);
}

// ===============================
// BASEMENT
// ===============================

void basement()
{
    ClearBackground(bgColor);

    DrawCentered("BASEMENT", 30, 30);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 80);

    DrawASCII(
        "|  ||      ||      ||      ||      ||      ||             |",
        50, 120);

    DrawASCII(
        "|  ||                OLD STORAGE ROOM      ||             |",
        50, 145);

    DrawASCII(
        "|  ||                                      ||             |",
        50, 170);

    DrawASCII(
        "|  ||          +----------------+          ||             |",
        50, 210);

    DrawASCII(
        "|  ||          |                |          ||             |",
        50, 235);

    DrawASCII(
        "|  ||          |      CHEST     |          ||             |",
        50, 260);

    DrawASCII(
        "|  ||          |                |          ||             |",
        50, 285);

    DrawASCII(
        "|  ||          +----------------+          ||             |",
        50, 310);

    DrawASCII(
        "|  ||                                      ||             |",
        50, 340);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 380);

    DrawASCII("> " + message, 50, 420);

    DrawASCII("[1] Open Chest", 50, 470);
    DrawASCII("[2] Search Basement", 300, 470);
    DrawASCII("[3] Leave Basement", 50, 510);
}

// ===============================
// FRONT DOOR
// ===============================

void frontDoor()
{
    ClearBackground(bgColor);

    DrawCentered("FRONT DOOR", 30, 30);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 80);

    DrawASCII(
        "|                                                          |",
        50, 120);

    DrawASCII(
        "|                    +----------------+                    |",
        50, 150);

    DrawASCII(
        "|                    |                |                    |",
        50, 175);

    DrawASCII(
        "|                    |                |                    |",
        50, 200);

    DrawASCII(
        "|                    |     DOOR       |                    |",
        50, 225);

    DrawASCII(
        "|                    |                |                    |",
        50, 250);

    DrawASCII(
        "|                    |        O       |                    |",
        50, 275);

    DrawASCII(
        "|                    |                |                    |",
        50, 300);

    DrawASCII(
        "|                    +----------------+                    |",
        50, 325);

    DrawASCII(
        "|                                                          |",
        50, 360);

    DrawASCII(
        "+----------------------------------------------------------+",
        50, 390);

    DrawASCII("> " + message, 50, 430);

    DrawASCII("[1] Try to Open Door", 50, 480);
    DrawASCII("[2] Return to House", 50, 520);
}

// ===============================
// ESCAPE SCREEN
// ===============================

void escapeScreen()
{
    ClearBackground(bgColor);

    DrawCentered("THE LOST KEY", 100, 36);

    DrawCentered("YOU ESCAPED", 180, 42);

    DrawCentered(
        "The door slowly opens...",
        250,
        22);

    DrawCentered(
        "Cold rain hits your face.",
        290,
        22);

    DrawCentered(
        "You are finally free.",
        330,
        22);

    DrawCentered(
        "[ESC] Exit Game",
        430,
        20);
}

// ===============================
// BEDROOM LOGIC
// ===============================

void bedroomLogic()
{
    if (IsKeyPressed(KEY_ONE))
    {
        if (!hasPhoto)
        {
            hasPhoto = true;
            message = "You search beneath the bed and find an old photograph.";
        }
        else
        {
            message = "There is nothing else beneath the bed.";
        }
    }

    if (IsKeyPressed(KEY_TWO))
    {
        if (!mirrorBroken)
        {
            if (hasMainPhoto)
            {
                mirrorBroken = true;
                hasPrimKey = true;

                message =
                    "You hold the owner's photograph toward the mirror. "
                    "CRACK! A key falls from behind it.";
            }
            else
            {
                message =
                    "Your reflection stares back at you. "
                    "Something feels wrong...";
            }
        }
        else
        {
            message = "The broken mirror has revealed an empty space.";
        }
    }

    if (IsKeyPressed(KEY_THREE))
    {
        if (!hasSecKey)
        {
            message = "The drawer is locked. You need another key.";
        }
        else if (!drawerOpened)
        {
            drawerOpened = true;

            message =
                "The rusty key opens the drawer. "
                "Inside is a note: 'The Owner holds the key.'";
        }
        else
        {
            message = "The drawer is already open.";
        }
    }

    if (IsKeyPressed(KEY_FOUR))
    {
        currentRoom = HOUSE;
        message = "You return to the hallway.";
    }
}

// ===============================
// LIBRARY LOGIC
// ===============================

void libraryLogic()
{
    if (IsKeyPressed(KEY_ONE))
    {
        message =
            "Dusty books fill the shelves. "
            "One book seems strangely out of place.";
    }

    if (IsKeyPressed(KEY_TWO))
    {
        if (!hasSecKey)
        {
            hasSecKey = true;

            message =
                "You pull the strange book. "
                "A rusty key falls from behind the shelf.";
        }
        else
        {
            message = "There is nothing else hidden here.";
        }
    }

    if (IsKeyPressed(KEY_THREE))
    {
        currentRoom = HOUSE;
        message = "You leave the library.";
    }
}

// ===============================
// BASEMENT LOGIC
// ===============================

void basementLogic()
{
    if (IsKeyPressed(KEY_ONE))
    {
        if (!drawerOpened)
        {
            message =
                "The chest is locked. "
                "You feel like you are missing something.";
        }
        else if (!hasMainPhoto)
        {
            hasMainPhoto = true;

            message =
                "Inside the chest is a photograph of the previous owner.";
        }
        else
        {
            message = "The chest is empty.";
        }
    }

    if (IsKeyPressed(KEY_TWO))
    {
        message =
            "You search the dark corners of the basement. "
            "Nothing else catches your eye.";
    }

    if (IsKeyPressed(KEY_THREE))
    {
        currentRoom = HOUSE;
        message = "You climb back upstairs.";
    }
}

// ===============================
// FRONT DOOR LOGIC
// ===============================

void frontDoorLogic()
{
    if (IsKeyPressed(KEY_ONE))
    {
        if (hasPrimKey)
        {
            currentRoom = ESCAPED;
        }
        else
        {
            message =
                "The door is locked. "
                "You need the primary key.";
        }
    }

    if (IsKeyPressed(KEY_TWO))
    {
        currentRoom = HOUSE;
        message = "You step away from the front door.";
    }
}

// ===============================
// HOUSE LOGIC
// ===============================

void houseLogic()
{
    if (IsKeyPressed(KEY_ONE))
    {
        currentRoom = BEDROOM;
        message = "You enter the bedroom.";
    }

    if (IsKeyPressed(KEY_TWO))
    {
        currentRoom = LIBRARY;
        message = "You enter the library.";
    }

    if (IsKeyPressed(KEY_THREE))
    {
        currentRoom = BASEMENT;
        message = "You descend into the basement.";
    }

    if (IsKeyPressed(KEY_FOUR))
    {
        currentRoom = FRONT_DOOR;
        message = "You approach the locked front door.";
    }
}

// ===============================
// MAIN
// ===============================

int main()
{
    InitWindow(1000, 650, "The Lost Key");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // =========================
        // LOGIC
        // =========================

        switch (currentRoom)
        {
        case HOUSE:
            houseLogic();
            break;

        case BEDROOM:
            bedroomLogic();
            break;

        case LIBRARY:
            libraryLogic();
            break;

        case BASEMENT:
            basementLogic();
            break;

        case FRONT_DOOR:
            frontDoorLogic();
            break;

        case ESCAPED:
            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
                return 0;
            }
            break;
        }

        // =========================
        // DRAW
        // =========================

        BeginDrawing();

        switch (currentRoom)
        {
        case HOUSE:
            house();
            break;

        case BEDROOM:
            bedroom();
            break;

        case LIBRARY:
            library();
            break;

        case BASEMENT:
            basement();
            break;

        case FRONT_DOOR:
            frontDoor();
            break;

        case ESCAPED:
            escapeScreen();
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}