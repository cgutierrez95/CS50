#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int LETTER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
}

//Function for calculating the score
int compute_score(string word)
{
    int LETTER_len = sizeof(LETTER);

    int word_len = strlen(word);

    int score = 0;

    for (int i = 0; i <= word_len; i++)
    {
        for (int j = 0; j <= LETTER_len; j++)
        {
            if (tolower(word[i]) == LETTER[j])
            {
                score += POINTS[j];
            }
        }
    }
    return score;
}