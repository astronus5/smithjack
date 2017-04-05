/*****************************************
* Smithjack
* Authors: Daniel Hatfield, Matthew Barnett
* Group: Cryptic Card Counters
* Date: 3/4/17
* Purpose: Blackjack game with a deck of a
        perpetual count of 52
*****************************************/
#include <stdio.h> //For basic input and output
#include <stdlib.h> //For rand()
#include <time.h> //For time()
/****************************************/
int i; //For counting the rounds
char flag = 'y'; //Checking whether the user wants another round
int caseMet; //Whether a SmithJack or a knock occured

double points = 0; //The point count to be displayed after every round

/****************************************/
int getValue(int, int); //Prototype for a function which returns the card value
void printName(int); //Prototype for a function which prints the name of a card
/****************************************/

int main()
{
    /*Welcome the user in the program*/
    printf("Welcome to SmithJack!\n");
    srand(time(0)); //Set seed to timestamp
    
    /* Loop through rounds */
    for(i=0;flag=='y';i++)
    {
        /*This is case where the cards dealt had neither a SmithJack or a knock*/
        caseMet = 0;
        
        /*Print the round number*/
        printf("Round %d)\n", i+1); //State round
        
        /* Dealer's initial hand */
        int card1 = rand()%52;
        int card2 = rand()%52;
        /* User's initial hand */
        int card3 = rand()%52;
        int card4 = rand()%52;
        
        /* Test if dealer's initial hand is equal to 21 */
        if(getValue(card1, 0) + getValue(card2, 0) == 21)
        {
            /* Test if user's hand is also 21 */
            if(getValue(card3, 0) + getValue(card4, 0) == 21)
            {
                printf("\nIt's a knock\n");
                caseMet = 1;
            } else
            {
                printf("\nDealer got SmithJack\n");
                points -= 1.0; 
                caseMet = 1;
            }
        }
        
        /* Print newline for formatting */
        printf("\n");
        
        /* Test for if user user's initial hand is 21 */    
        if(getValue(card3, 0) + getValue(card4, 0) == 21 && caseMet == 0)
        {
            points += 1.5;
            printf("\nYou got SmithJack!\n");
            caseMet = 1;
        }
        
        /*This will only only play the game as long as there was no SmithJack and no knocking*/
        if(caseMet == 0)
    {
        /*****************************************************************************************************/
        /* Print card status visible to user */
        printf("The dealer's cards: ");
        printf("Hidden, "); printName(card2); printf("\n");
        printf("Your cards: ");
        printName(card3); printf(", "); printName(card4); printf("\n");
        printf("\n");
        /*****************************************************************************************************/
        
        /* Define user's total card count within the round */
        int total = getValue(card3, 0) + getValue(card4, 0);
        int dealerTotal = getValue(card1, 0) + getValue(card2, 0);
        
        /* Prompt user for action */
        char c; //For a stay or hit
        do
        {
            printf("Stay (s) or hit (h)? ");
            scanf(" %c", &c);
            
            /*If the user entered an h for hit*/
            if(c == 'h')
            {
                int newCard = rand()%52;
                total += getValue(newCard, total);
                printf("*New card: "); printName(newCard); printf("\n");
            }
            
        } while(c != 's' && total <= 21);
        /*If the player has more than 21, they busted*/
        if(total > 21)
            printf("You BUST!\n");
        printf("\n");
        
        /*Print the dealer's cards and what they deal themselves*/
        printf("*Dealer's unknown card: "); printName(card1); printf("\n");
        while (dealerTotal < 17 && total <= 21)
        {
            int dealerNewCard = rand()%52;
            dealerTotal += getValue(dealerNewCard, dealerTotal);
            printf("*Dealer dealt himself: "); printName(dealerNewCard); printf("\n");
        }
        /*If the dealer has more than 21, they busted*/
        if(dealerTotal > 21)
            printf("Dealer BUSTED!\n");
        
        /*Print the win state of the game*/
        if((dealerTotal < total && total <= 21) || (dealerTotal > 21 && total <= 21))
        {
            points += 1;
            printf("You won!\n");
        }else if(dealerTotal == total)
        {
            printf("It's a knock!\n");
        } else
        {
            points -= 1;
            printf("Player loses\n");
        }
    }
        /*Print the total score at the moment*/
        printf("-[Total score = %0.1lf]-\n", points);
        
        /*Ask if the player wants to play again*/
        printf("Wish to play again? 'y/n': ");
        scanf(" %c", &flag);
    
        /*Add a newline for readability*/
        printf("\n");
    }
    
    /*Send the user a message as they leave*/
    if(points > 0)
        printf("Good game!\n");
    else if(points < 0)
        printf("Better luck next time!\n");
    else
        printf("Fun playing!\n");
    
    /*Default case of 0 (successful exit)*/
    return 0;
}

/********************************/
/*Returns the value of a card given its value identification and the total value in a hand*/
int getValue(int val, int total)
{
    /*If the card is less than forty it is not a face card*/
    if(val <= 10 * 4)
    {
        /*If it is an ace, check the total to determine its value*/
        if(val < 4 && total <= 10)
            return 11;
        return val/4 + 1;
    }
    /*Return 10 if it is a face card (above a value of 40)*/
    return 10;
}

/********************************/

/*Prints the name of a card given its value identification*/
void printName(int val)
{
    /*Divide the value by four to find the name of the card*/
    switch(val/4)
    {
        case 0:
            printf("Ace");
            break;
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9:
            printf("%d", val/4 + 1);
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
            /*In the default case, print that there was an error*/
            printf("Error");
            break;
    }
    printf(" of ");
    
    /*The suit of the card is determined by checking the value modulo 4*/
    switch(val%4)
    {
        case 0:
            printf("Spades");
            break;
        case 1:
            printf("Clubs");
            break;
        case 2:
            printf("Hearts");
            break;
        case 3:
            printf("Diamonds");
            break;
        default:
            /*In the default case, print that there was an error*/
            printf("Error");
            break;
    }
    return;
}
/********************************/
