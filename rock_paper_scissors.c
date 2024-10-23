#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*

    Rule: DO NOT USE AI except to generate ideas for this list.

    [X] - Fix Input Validation
    [X] - Handle Invalid Inputs
    [] - Different Modes of Play: Best of 5 or Endless Mode
    [] - Tie Breaker logic in win mode

    [] - Better UI
    [] - Add Score History Display
    [] - Display Game Instructions at the start
    [] - ASCI Art or EMOJIS
    [] - Colors in terminal

    [] - Colors in terminal
    [] - Retry Option
    [] - Multiplayer Mode
    [] - Leaderboards Feature
    [] - Timed Inputs
    [] - AI Bot

    [] - Lizard - Spock variations
    [] - Bot Difficulty Levels
    [] - Tournament Mode

    [] - Save and Resume Game
    [] - Cooldown between rounds
    [] - Countdown timer
    [] - Profile streaks

    [] - Make the Bot Speak and Interact with the player
    [] - Sound Effects
    [] - Play background music

    [] - Online Multiplayer
    [] - GUI Version
    [] - Add Achievements
    [] - Add Random events (Double Points)

    [] - Package it

    // bugs
    [] - When exiting game, it prints everything on its path.
 */

void game_logic(char c, int *score)
{
    char choices[3] = {'r', 'p', 's'};
    char bot = choices[rand() % 3];
    char lc = tolower(c);

    if (lc == bot)
    {
        printf("\nYou played %c\n", c);
        printf("bot played %c\n", bot);
        printf("\nDraw !!!");
    }

    if ((lc == 'r' && bot == 'p') || (lc == 'p' && bot == 's') || (lc == 's' && bot == 'r'))
    {
        printf("\nYou played %c\n", c);
        printf("bot played %c\n", bot);
        printf("\nYou Lost");
        *score -= 1;
    }

    if ((bot == 'r' && lc == 'p') || (bot == 'p' && lc == 's') || (bot == 's' && lc == 'r'))
    {
        printf("\nYou played %c\n", c);
        printf("bot played %c\n", bot);
        printf("\nYou Win !!");
        *score += 1;
    }
}

int rock_paper_scissors(char choice, int *score, int *exit)
{
    printf("\n\nCurrent score: %d", *score);
    printf("\nEnter Choice: ");
    scanf(" %c", &choice);

    if (tolower(choice) == 'r' || tolower(choice) == 's' || tolower(choice) == 'p' || tolower(choice) == 'e')
    {
        if (choice == 'E' || choice == 'e')
        {
            printf("Exiting Program...");
            *exit = 0;
        }
        else
        {
            game_logic(choice, score);
        }
    }
    else
    {
        printf("Input Must Follow the Instructions of the Game... Try again !");
    }
}

void game_mode_choices(void)
{
    printf("\n");
    printf("PICK YOUR GAME MODE: \n");
    printf("1: Best of 7\n");
    printf("2: Endless Mode\n");
    printf("3: Coming Soon...\n");
    printf("0: Exit \n");
    printf("\n");
}

void input_instructions(void)
{
    printf("\n");
    printf("Type the character corresponding to the move: \n");
    printf("R: Rock\n");
    printf("P: Paper\n");
    printf("S: Scissors\n");
    printf("E: Exit \n");
    printf("\n");
}

int main(void)
{
    char choice;
    int exit = 1;
    int score = 0;
    int rounds;
    int mode;
    /*
    Mode Of Play:
        0 -> Exit
        1 -> Best of 5 Mode
        2 -> Endless Mode
    */

    printf("\n>============= Rock Paper Scissors =============<\n\n\n");
    game_mode_choices();

    while (exit)
    {
        printf("\nPick Mode: ");
        scanf(" %d", &mode);

        switch (mode)
        {
        case 0:
            printf("Exiting Game...");
            exit = 0;
        case 1: // Best of 7;
            rounds = 7;
            printf("\n\nWelcome to Best of 7, Score 4 or higher to Win...");
            printf("\n+1 Point if you Win");
            printf("\n-1 Point if you Lose");
            printf("\nNo Points if you Draw");

            while (rounds > 0 && exit)
            {
                input_instructions();
                rock_paper_scissors(choice, &score, &exit);
                rounds--;
            }

            if (score >= 4)
            {
                printf("\nYou Win with a Score of %d!\n", score);
            }
            else
            {
                printf("\nYou Lose! You only scored %d\n", score);
            }
            score = 0;
            break;

        case 2: // endless mode
            printf("\n\n Welcome to Endless Mode... Play Until You Are Tired;");
            input_instructions();
            rock_paper_scissors(choice, &score, &exit);
            break;

        case 3:
            printf("Coming Soon...");
            break;

        default:
            printf("\nWrong input Dumbass... Pick from these...");
            game_mode_choices();
            break;
        }
    }
}