/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
/******************************************************************************/
//Name: Jonathan Wong
//Email: jzwong@usc.edu
/*Description: This program allows the user to play
 * blackjack. It allows the user to hit or stand
 * and then compares the score with the dealer to determine
 * a winner.
// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for(int i= NUM_CARDS-1; i>=1; i--){
		int temp;
		int j = rand()%(i+1);
		temp = cards[i];
		cards[i]=cards[j];
		cards[j]= temp; 
	}
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  if(id%13==0){
    cout << "2-";
  }else if(id%13==1){
    cout << "3-";
  }else if(id%13==2){
    cout << "4-";
  }else if(id%13==3){
    cout << "5-";
  }else if(id%13==4){
    cout << "6-";
  }else if(id%13==5){
    cout << "7-";
  }else if(id%13==6){
    cout << "8-";
  }else if(id%13==7){
    cout << "9-";
  }else if(id%13==8){
    cout << "10-";
  }else if(id%13==9){
    cout << "J-";
  }else if(id%13==10){
    cout << "Q-";
  }else if(id%13==11){
    cout << "K-";
  }else if(id%13==12){
    cout << "A-";
  }
	if(id/13==0){
    cout << "H";
  }else if(id/13==1){
    cout << "S";
  }else if(id/13==2){
    cout << "D";
  }else if(id/13==3){
    cout << "C";
  }
	cout << " ";
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int val = id%13;
	return value[val];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i=0;i<numCards;i++){
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum=0;
  int numAces;
  for(int i=0;i<numCards;i++){
    sum+=cardValue(hand[i]);
    if(cardValue(hand[i])==11){
      numAces++;
    }
    if(sum>21 && numAces>=1){
      sum-=10;
      numAces--;
    }
  }
  return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  bool play=true;
  while(play){
    for(int i=0;i<NUM_CARDS;i++){ //Initialize deck
      cards[i]=i;
    }
    shuffle(cards); //Shuffle the cards
    int dsize=0; //Set size of hands and deck
    int psize=0;
    int decksize=0;
    for(int i=0;i<2;i++){ //Deal
      phand[psize]=cards[decksize];
      psize++;
      decksize++;
      dhand[dsize]=cards[decksize];
      dsize++;
      decksize++;
    }
    cout << "Dealer: ? "; //Print beginning hands
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand,psize);
    char move;
    while(getBestScore(phand,psize)<21){ 
      cout << "Type 'h' to hit and 's' to stay: " << endl;
      cin >> move;
      if(move == 'h'){ //If player hits
        phand[psize]=cards[decksize]; //Deal them a card
        psize++;
        decksize++;
        cout << "Player: ";
        printHand(phand,psize); //Print new hand
      }
      if(move=='s'){
        break;
      }
    }
    while(getBestScore(dhand,dsize)<17 && getBestScore(phand,psize)<=21){ //Dealer
      dhand[dsize]=cards[decksize]; //Deal them a card
      dsize++;
      decksize++;
    }
    int pscore=getBestScore(phand,psize);
    int dscore=getBestScore(dhand,dsize);
    if(pscore<=21){
      cout << "Dealer: "; //Print dealers hand
      printHand(dhand,dsize);
    }
    if(pscore>21){
      cout << "Player busts" << endl;
      cout << "Lose " << pscore << " " << dscore << endl;
    }
    if(dscore>21){
      cout << "Dealer busts" << endl;
      cout << "Win " << pscore << " " << dscore << endl;
    }
    if(pscore<=21 && dscore<=21){
      if(pscore>dscore){
        cout << "Win " << pscore << " " << dscore << endl;
      }else if(pscore<dscore){
        cout << "Lose " << pscore << " " << dscore << endl;
      }else if(pscore == dscore){
        cout << "Tie " << pscore << " " << dscore << endl;
      }
    }
    cout << endl;
    cout << "Play again? [y/n]" << endl;
    char choice;
    cin >> choice;
    if(choice!='y'){
      play=false;
    }
  }
  return 0;
}