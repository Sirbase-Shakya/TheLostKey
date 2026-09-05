#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <windows.h>
using namespace std;

bool hasPrimKey = false;
bool hasSecKey = false;
bool hasPhoto = false;
bool hasMainPhoto = false;
bool hasFlashlight = false;
bool enterBedroom = false;
bool enterLibrary = false;
bool enterBasement = false;
bool drawerOpened = false;
bool gameFinished = false;

void printArt(string filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Could not load ASCII art: " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
void badEnding()
{
    cout << "\n\n";
    cout << "========================================\n";
    cout << " TIME'S UP\n";
    cout << "========================================\n\n";
    printArt("ascii/bad_ending.txt");
    cout << "\nThe rain outside suddenly becomes louder...\n";
    cout << "You hear footsteps somewhere inside the house.\n";
    cout << "You realize that you have spent too much time searching.\n\n";
    cout << "The opportunity to escape is gone.\n";
    cout << "You failed to uncover the secret of the house in time.\n\n";
    cout << "========================================\n";
    cout << " BAD ENDING\n";
    cout << " INCOMPLETION\n";
    cout << "========================================\n\n";
    cout << "The story remains unfinished...\n";
    cout << "GAME OVER.\n";
}

DWORD WINAPI gameTimer(LPVOID lpParam)
{

    Sleep(60000);
    if (!gameFinished)
    {
        badEnding();
        ExitProcess(0);
    }

    return 0;
}

void bedroom()
{
    int choice;
    printArt("ascii/bedroom.txt");
    if (!enterBedroom)
    {
        cout << "You enter a dusty bedroom.\n";
        cout << "There is a bed, a broken mirror, and a locked drawer.\n\n";
        enterBedroom = true;
    }

    cout << "1. Search the bed\n";
    cout << "2. Examine the mirror\n";
    cout << "3. Try the drawer\n";
    cout << "4. Leave the bedroom\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        if (!hasPhoto)
        {
            cout << "\nYou search under the bed and find an old photograph.\n";
            cout << "The photograph shows the same house many years ago.\n";
            hasPhoto = true;
        }
        else
        {
            cout << "\nThere is nothing else under the bed.\n";
        }
    }
    else if (choice == 2)
    {
        cout << "\nYou examine the broken mirror.\n";
        if (hasPhoto)
        {
            cout << "You hold the old photograph up to the mirror.\n";
            cout << "A hidden message appears on the photograph:\n";
            cout << "\033[3mThe past is kept among the stories.\033[0m\n";
        }
        else
        {
            cout << "You see nothing unusual in the mirror.\n";
        }
        if (hasMainPhoto && !hasPrimKey)
        {
            printArt("ascii/bedroom_broken.txt");
            cout << "You show the photo of the owner to the mirror.\n";
            cout << "The cracked mirror shatters and reveals a shiny key.\n";
            hasPrimKey = true;
        }
        else if (hasPrimKey)
        {
            printArt("ascii/bedroom_broken.txt");
            cout << "The mirror is already shattered.\n";
        }
    }
    else if (choice == 3)
    {
        if (hasSecKey)
        {
            if (!drawerOpened)
            {
                cout << "The rusty key is inserted into the drawer...\n";
                cout << "...Click...\n";
                cout << "The drawer opens and a note is found:\n";
                cout << "\033[3mThe Owner holds the key\033[0m\n";

                drawerOpened = true;
            }
            else
            {
                cout << "The drawer is already open.\n";
            }
        }
        else
        {
            cout << "\nThe drawer is locked. You need a key.\n";
        }
    }
    else if (choice == 4)
    {
        return;
    }
    else
    {
        cout << "\nInvalid choice.\n";
    }

    bedroom();
}
void library()
{
    int choice;

    printArt("ascii/library.txt");
    if (!enterLibrary)
    {
        cout << "You enter a room filled with dusty books.\n";
        cout << "An enormous bookshelf covers one wall.\n\n";
        enterLibrary = true;
    }
    cout << "1. Search the books\n";
    cout << "2. Examine the bookshelf\n";
    cout << "3. Pull the strange book\n";
    cout << "4. Leave the library\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nYou search through the books.\n";
        cout << "You find a book about the history of this house.\n";
        cout << "It mentions a hidden secret in the Library\n";
    }
    else if (choice == 2)
    {
        cout << "\nYou carefully examine the bookshelf.\n";
        cout << "One book looks newer than the others.\n";
    }
    else if (choice == 3)
    {
        if (!hasSecKey)
        {
            printArt("ascii/library_secret.txt");
            cout << "\nYou pull the strange book.\n";
            cout << "CLICK!\n";
            cout << "A hidden compartment opens.\n";
            cout << "Inside, you find a small rusty key!\n";
            hasSecKey = true;
        }
        else
        {
            cout << "\nThe secret compartment is empty.\n";
        }
    }
    else if (choice == 4)
    {
        return;
    }
    else
    {
        cout << "\nInvalid choice.\n";
    }

    library();
}
void basement()
{
    int choice;

    printArt("ascii/basement.txt");
    if (!enterBasement)
    {
        cout << "You slowly walk down the stairs.\n";
        cout << "The basement is dark and cold.\n";
        cout << "You see an old wooden chest.\n\n";
        enterBasement = true;
    }

    cout << "1. Open the chest\n";
    cout << "2. Search the room\n";
    cout << "3. Leave the basement\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        if (!hasMainPhoto)
        {
            if (drawerOpened)
            {
                printArt("ascii/basement_open.txt");
                cout << "You open the chest.\n";
                cout << "Inside, you find a photograph of the previous owner.\n";
                hasMainPhoto = true;
            }
            else
            {
                printArt("ascii/basement.txt");
                cout << "The chest is locked somehow.\n";
                cout << "Maybe there is a clue somewhere else in the house.\n";
            }
        }
        else
        {
            printArt("ascii/basement.txt");
            cout << "The chest is empty.\n";
        }
    }
    else if (choice == 2)
    {
        if (!hasFlashlight)
        {
            printArt("ascii/basement.txt");
            cout << "\nYou search the room and find an old flashlight.\n";
            cout << "Unfortunately, it has no batteries.\n";
            hasFlashlight = true;
        }
        else
        {
            printArt("ascii/basement.txt");
            cout << "\nYou search the basement again but find nothing.\n";
        }
    }
    else if (choice == 3)
    {
        return;
    }
    else
    {
        cout << "\nInvalid choice.\n";
    }

    basement();
}

int main()
{
    HANDLE timerThread;

    timerThread = CreateThread(
        NULL,
        0,
        gameTimer,
        NULL,
        0,
        NULL);
    printArt("ascii/title.txt");
    cout << "You wake up in a dark room. Rain pounds against the windows, and the lights are out." << endl
         << "You try the front door, but it's locked." << endl
         << "On a nearby table, you find a note:" << endl;
    cout << "\033[3mThe key is closer than you think. Look where the past is kept.\033[0m" << endl;
    while (true)
    {

        printArt("ascii/house.txt");

        cout << "1. Go to Bedroom" << endl
             << "2. Go to Library" << endl
             << "3. Go to Basement" << endl
             << "4. Try the front door" << endl
             << "5. Quit Game" << endl
             << "Choice: ";

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            bedroom();
            break;
        }
        case 2:
        {
            library();
            break;
        }
        case 3:
        {
            basement();
            break;
        }
        case 4:
        {
            if (hasPrimKey)
            {
                cout << "\nYou take out the rusty key.\n";
                cout << "You insert it into the lock...\n";
                cout << "CLICK!\n\n";

                cout << "The door opens!\n";
                cout << "You run outside into the rain.\n\n";

                printArt("ascii/escape.txt");
                gameFinished = true;
                return 0;
            }
            else
            {
                printArt("ascii/locked_door.txt");
                cout << "\nThe door is still locked.\n";
                cout << "You need to find the key first.\n";
            }
            break;
        }
        case 5:
        {
            printArt("ascii/quit.txt");
            cout << "Thanks for Playing.\n";
            return 0;
        }
        default:
        {
            cout << "Invalid Choice. Try Again\n";
        }
        }
    }

    return 0;
}
