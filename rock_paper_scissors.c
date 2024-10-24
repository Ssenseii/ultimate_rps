#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

/*

    Rule: DO NOT USE AI except to generate ideas for this list.

    [X] - Fix Input Validation
    [X] - Handle Invalid Inputs
    [X] - Different Modes of Play: Best of 5 or Endless Mode

    [X] - Better UI
    [X] - Add Score History Display
    [X] - Display Game Instructions at the start
    [X] - ASCII Art or EMOJIS (didn't like them);
    [X] - Colors in terminal

    [X] - Retry Option
    [] - Multiplayer Mode                                           /// I still haven't learned network programming in c
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

    [] - Organize code using comments.
    [] - Package it

    // bugs
    [] - When exiting game, it prints everything on its path.
 */

void setColor(int color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}
/*
0 = Black
1 = Blue
2 = Green
4 = Red
7 = Default (White/Gray)
9 = Light Blue
10 = Light Green
12 = Light Red
14 = Yellow
15 = Bright White
 */

/*
    Players Zone
*/

/// Logging Players In

// save player info in a file.
// prompt("Player: ");
// get input
// see if it exists in the file
// if yes: use his score
// if not: create new player
// update score everytime

typedef struct
{
    char *name;
    int score;
} Player;

void print_leaderboard(char *filename)
{

    FILE *fp;
    char player[1024];
    int linecount = 0;

    fp = fopen(filename, "r");

    while (fgets(player, sizeof player, fp) != NULL)
    {
        printf("%d: %s", ++linecount, player);
    }

    fclose(fp);
}

void save_player_info(char *filename, Player player)
{
    FILE *fp;

    fp = fopen(filename, "w");
    
    fprintf(fp, "%s - %d", player.name, player.score);

    fclose(fp);
}

/*
    End of Players Zone
*/

/*
    Game Logic Zone
*/

char *symbol(char c)
{
    if (c == 'r')
        return "Rock";
    if (c == 's')
        return "Scissors";
    if (c == 'p')
        return "Papers";
}

void game_logic(char c, int *score)
{
    char choices[3] = {'r', 'p', 's'};
    char bot = choices[rand() % 3];
    char lc = tolower(c);

    if (lc == bot)
    {
        printf("\nYou played %s\n", symbol(lc));
        printf("bot played %s\n", symbol(bot));
        setColor(1);
        printf("\nDraw !!!");
        setColor(7);
    }

    if ((lc == 'r' && bot == 'p') || (lc == 'p' && bot == 's') || (lc == 's' && bot == 'r'))
    {
        printf("\nYou played %s\n", symbol(lc));
        printf("bot played %s\n", symbol(bot));
        setColor(4);
        printf("\nYou Lost");
        setColor(7);
        *score -= 1;
    }

    if ((bot == 'r' && lc == 'p') || (bot == 'p' && lc == 's') || (bot == 's' && lc == 'r'))
    {
        printf("\nYou played %s\n", symbol(lc));
        printf("bot played %s\n", symbol(bot));
        setColor(2);
        printf("\nYou Win !!");
        setColor(7);
        *score += 1;
    }
}

int rock_paper_scissors(char choice, int *score, int *exit)
{
    printf("\nCurrent score: %d", *score);
    setColor(9);
    printf("\nEnter Choice: ");
    scanf(" %c", &choice);
    setColor(7);

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

/*
    End of Game Logic Zone
*/

/*
    Instruction Zone
*/

void game_mode_choices(void)
{
    printf("\n");
    printf("PICK YOUR GAME MODE: \n");
    printf("1: Best of 7\n");
    printf("2: Endless Mode\n");
    printf("3: Multiplayer Mode\n");
    printf("4: Coming Soon...\n");
    printf("0: Exit \n");
    printf("\n");
    printf("11: Access User Score");
    printf("11: Leaderboards");
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

/*
    End of Instruction Zone
*/

int main(void)
{

    Player rps_player = {
        .name = "JUH",
        .score = 12,
    };
    save_player_info("players.txt", rps_player);
    print_leaderboard("players.txt");

    char choice;
    int exit = 1;
    int ultimate_score = 0;
    int score = 0;
    int rounds;
    int mode;

    printf("\n>============= Rock Paper Scissors =============<\n");
    game_mode_choices();

    while (exit)
    {
        setColor(9);
        printf("\nPick Mode: ");
        scanf(" %d", &mode);
        setColor(7);

        switch (mode)
        {
        case 0:
            printf("Exiting Game...");
            exit = 0;

        case 1: // Best of 7;
            rounds = 7;
            printf("\n\nWelcome to Best of 7, Score 4 or higher to Win...\n");
            printf("\n+1 Point if you Win");
            printf("\n-1 Point if you Lose");
            printf("\nNo Points if you Draw\n");

            while (rounds > 0 && exit)
            {
                input_instructions();
                rock_paper_scissors(choice, &score, &exit);
                rounds--;
            }

            if (score >= 4)
            {
                setColor(2);
                printf("\n -- Best of 7 --");
                printf("\nYou Win with a Score of %d!\n", score);
                setColor(7);
                ultimate_score += 1;
            }
            else
            {
                setColor(4);
                printf("\n -- Best of 7 --");
                printf("\nYou Lose! You only scored %d\n", score);
                setColor(7);
            }
            score = 0;
            game_mode_choices();
            break;

        case 2: // endless mode
            printf("\n\n Welcome to Endless Mode... Play Until You Are Tired;");
            input_instructions();
            while (exit)
            {
                rock_paper_scissors(choice, &score, &exit);
            }
            game_mode_choices();
            break;

        case 3:
            printf("\n\n Welcome to Multiplayer Mode... Play against your friend");
            setColor(10);
            printf("\nPlayer Number 1: (◣_◢)");
            setColor(12);
            printf("\nPlayer Number 2: (◕_◕)");
            setColor(7);
            printf("\n\nComing Soon After I learn C's Networking Programming");
            break;

        case 4:
            printf("\nComing Soon...");
            game_mode_choices();
            break;

        case 11:
            printf("\nThe User has a total score of %d", ultimate_score);
            break;

        default:
            printf("\nWrong input Dumbass, Pick from these...");
            game_mode_choices();
            break;
        }
    }
}