/*****************************************
* Smithjack
* Authors: Daniel Hatfield, Matthew Barnett
* Group: Cryptic Card Counters
* Date: 3/4/17
* Purpose: Blackjack game with a deck of a
        perpetual count of 54
*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/****************************************/
int i;
int choice = 1;

double points = 0;

char c;
/****************************************/
int getValue(int, int);
char getSuit(int);
/****************************************/

int main()
{
    printf("Welcome to SmithJack!\n");
    srand(time(0)); //Set seed to timestamp
    
    /* Loop through rounds */
    for(i=0;choice==1;i++)
    {
        printf("Round %d)\n", i+1); //State round
        
        /* Dealer's initial hand */
        int card1 = rand()%52;
        int card2 = rand()%52;
        /* User's initial hand */
        int card3 = rand()%52;
        int card4 = rand()%52;
        
        /* Test if dealer's initial hand is equal to 21 */
        if(getValue(card1, 0) + getValue(card2, 0) == 21)
            /* Test if user's hand is also 21 */
            if(getValue(card3, 0) + getValue(card4, 0) == 21)
            {
                printf("It's a knock\n");
                continue;
            } else
            {
                points -= 1.0; //<Daniel> Matthew, is it supposed to be interval decay? should it not be interval growth?
                continue;
            }
        /* Test for if user user's initial hand is 21 */    
        if(getValue(card3, 0) + getValue(card4, 0) == 21)
        {
            points += 1.5;
            printf("You got SmithJack!\n");
            continue;
        }
        
        /*****************************************************************************************************/
        /* Print card status visible to user */
        printf("\n");
        printf("The dealer's cards: ");
        printf("Unknown, %d of %c\n", getValue(card2, 0), getSuit(card2));
        printf("Your cards: ");
        printf("%d of %c, %d of %c\n", getValue(card3, 0), getSuit(card3), getValue(card4, 0), getSuit(card4));
        printf("\n");
        /*****************************************************************************************************/
        
        /* Define user's total card count within the round */
        int total = getValue(card3, 0) + getValue(card4, 0);
        
        /* Prompt user for action */
        do
        {
            printf("Stay (s) or hit (h)? ");
            scanf(" %c", &c);
            
            if(c == 'h')
            {
                int newCard = rand()%52;
                total += getValue(newCard, total);
                printf("New card: %d of %c\n", getValue(newCard, total), getSuit(newCard));
            }
            
        } while(c != 's' && total <= 21);
        if(total > 21)
            printf("BUST!\n");
    }
}
/********************************/
int getValue(int val, int total)
{
    if(val <= 10 * 4)
        if(val < 4 && total <= 10)
            return 11;
        return val/4 + 1;
    return 10;
}
/********************************/
char getSuit(int val)
{
    switch(val%4)
    {
        case 0:
            return 'S';
        case 1:
            return 'C';
        case 2:
            return 'H';
        case 3:
            return 'D';
    }
}
/********************************/
