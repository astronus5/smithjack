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
char flag = 'y';
int caseMet = 0;

double points = 0;

char c;
/****************************************/
int getValue(int, int);
void printName(int);
char getSuit(int);
/****************************************/

int main()
{
    printf("Welcome to SmithJack!\n");
    srand(time(0)); //Set seed to timestamp
    
    /* Loop through rounds */
    for(i=0;flag=='y';i++)
    {
        caseMet = 0;
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
                caseMet = 1;
            } else
            {
                printf("Dealer got SmithJack\n");
                points -= 1.0; 
                caseMet = 1;
            }
        /* Test for if user user's initial hand is 21 */    
        if(getValue(card3, 0) + getValue(card4, 0) == 21 && caseMet == 0)
        {
            points += 1.5;
            printf("You got SmithJack!\n");
        }
        if(caseMet == 0)
    {
        /*****************************************************************************************************/
        /* Print card status visible to user */
        printf("\n");
        printf("The dealer's cards: ");
        printf("Unknown, "); printName(card2); printf(" of %c\n", getSuit(card2));
        printf("Your cards: ");
        printName(card3); printf(" of %c, ", getSuit(card3)); printName(card4); printf(" of %c\n", getSuit(card4));
        printf("\n");
        /*****************************************************************************************************/
        
        /* Define user's total card count within the round */
        int total = getValue(card3, 0) + getValue(card4, 0);
        int dealerTotal = getValue(card1, 0) + getValue(card2, 0);
        
        /* Prompt user for action */
        do
        {
            printf("Stay (s) or hit (h)? ");
            scanf(" %c", &c);
            
            if(c == 'h')
            {
                int newCard = rand()%52;
                total += getValue(newCard, total);
                printf("*New card: "); printName(newCard); printf(" of %c\n", getSuit(newCard));
            }
            
        } while(c != 's' && total <= 21);
        if(total > 21)
            printf("You BUST!\n");
        printf("\n");
        
        printf("*Dealer's unknown card: "); printName(card1); printf(" of %c\n", getSuit(card1));
        while (dealerTotal < 17 && total <= 21)
        {
            int dealerNewCard = rand()%52;
            dealerTotal += getValue(dealerNewCard, dealerTotal);
            printf("*Dealer dealt himself: "); printName(dealerNewCard); printf(" of %c\n", getSuit(dealerNewCard));
        }
        if(dealerTotal > 21)
            printf("Dealer BUSTED!\n");
        
        
        
        if((dealerTotal < total && total <= 21) || (dealerTotal > 21 && total <= 21))
        {
            points += 1;
            printf("You won!\n");
        }else if(dealerTotal == total)
        {
            printf("Tie!\n");
        } else
        {
            points -= 1;
            printf("Player loses\n");
        }
    }
        printf("-[Total score = %0.1lf]-\n", points);
        
        printf("Wish to play again'y/n': ");
        scanf("&c", &flag);
        printf("\n");
    }
    
    return 0;
    
}
/********************************/
int getValue(int val, int total)
{
    if(val <= 10 * 4)
    {
        if(val < 4 && total <= 10)
            return 11;
        return val/4 + 1;
    }
    return 10;
}

void printName(int val)
{
    switch(val/4)
    {
        case 0:
            printf("Ace");
            break;
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9:
            printf("%d", val/4);
            break;
        case 10:
            printf("Jack");
            break;
        case 11:
            printf("Queen");
            break;
        case 12:
            printf("King");
            break;
        default:
            printf("Error");
    }
    return;
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
    /*If the card is not returned from the switch statement, return 'E' for error*/
    return 'E';
}
/********************************/
