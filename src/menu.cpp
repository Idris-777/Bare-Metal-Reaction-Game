#include <lcd.h>
#include <project.h>

void startMenu()
{

    sendLine("Reaction Game");

    gameState = GameStates::MENU;
}

void switchOption()
{

    lcdInstruction(0xc0);

    sendLine("                ");

    lcdInstruction(0xc0);

    sendData('*');

    int NumberOfSpaces = 0;

    for (int i = 0; i > -1; i++)
    {
        if (menuOptions[i] == ' ')
        {
            NumberOfSpaces += 1;
        }

        if (NumberOfSpaces == currMenu)
        {
            if (menuOptions[i] == ' ')
            {
                
            }

            else
            {
                sendData(menuOptions[i]);
            }
        }

        if (NumberOfSpaces > currMenu)
        {
            break;
        }

       
    }
}