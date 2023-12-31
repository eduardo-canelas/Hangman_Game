
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ctype.h>

#define SIZE 20
#define STRIKES 6

void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no


int main()
{

  rules();

  //File pointer
  FILE * inp;

  int player_opt = 0;

  //Initializing pointer
  int * ptr_p_o = &player_opt;

  char input_word[SIZE];
  char star_w[SIZE];

  //Opening file to read from
  inp = fopen("words.txt", "r");

  //status of the file read
  int r_status = fscanf(inp, "%s", input_word); //do I need an addres for this string reed?

//While the the status of the file reads a word from file
  while (r_status == 1)
  {
    //get lenght of reed word
    int word_lenght = strlen(input_word);

    //function call for hidding word
    maskWord(star_w, word_lenght);

    int result = playRound(star_w, input_word);
    if (result == 0)
    {
      printf("Congratulations! You won! The word was %s.\n", input_word);
    }
    else
    {
      printf("Sorry you did NOT win the round. The word was %s.\n", input_word);
    }

    playAgain(ptr_p_o);
    if (player_opt == 2)
    {
      printf("************************************************************************\n");
      printf("Thank you for playing today!\n");
      break;
    }

    //keep on reading form file
    r_status = fscanf(inp, "%s", input_word);
  }

  //close the file
  fclose(inp);

  return 0;
}

void rules(void)
{
  printf("Welcome to the Hangman Game!\n");
  printf("************************************************************************\n");
  printf("Here are the rules.\n");
  printf("I will provide you a set of Each You must figure out each letter of the missing word.\n");
  printf("For every correct letter guessed, I will reveal its place in the word.\n");
  printf("Each mistake will result in a strike.\n");
  printf("6 strikes will result in a loss that round.\n");
  printf("Are you ready? Here we go!\n");
}

void maskWord (char starword[], int size)
{
  //for loop that will replace every iteration of starword with a *
  for (int i = 0; i < size; ++i)
  {
    starword[i] = '*';
  }
  starword[size]= '\0';
  //assigning the null character to the last element of the string
  //because if not, the null character will also be replaced with an *
}

int playRound(char starword[], char answer[])
{
  char guess;
  //string array to store the user guesses
  char guesses[100];
  int occr;
  int guess_count = 0;

  //get the lenght of the word to work with the for loop
  int word_lenght = strlen(answer);

  printf("************************************************************************\n");
  printf("Welcome to the Round!\n");
  printf("The size of the word has %d letters.\n\n", word_lenght);
  int updating_Strikes;

  updating_Strikes = 0;

  while(updating_Strikes < 6)
  {
    printf("You currently have %d strikes.\n", updating_Strikes);
    printf("Letters you have guessed: ");
    for(int i = 0; i < guess_count; i++)
    {
      printf("%c", guesses[i]);
    }
    printf("\n\n%s\n\n", starword);
    printf("Enter your guess: ");
    scanf(" %c", &guess);

    //isalpha built in function to ! so that if the user inputs a number
    //or other characters it will ask the user for input again.
    if (!isalpha(guess))
    {
      printf("\nPlease enter a valid character!\n\n");
      printf("Enter your guess: ");
      scanf(" %c", &guess);
    }

    guesses[guess_count++] = guess;

    //lowercase user input
    guess = tolower(guess);

    occr = occurancesInWord(guess, answer);

    //ifelse to update strikes or to update the starword based on the return counter
    if(occr == 0)
    {
      printf("\n\nThe letter %c is NOT in the word.\n\n", guess);
      ++updating_Strikes;
    }
    else
    {
      printf("\n\nThe letter %c is in the word\n\n", guess);
      updateStarWord(starword, answer, guess);
    }
    int counter = 0;

    //for loop to iterate through both the starword and the answer strings
    //and if they are equal to each other, increase the counter
    for (int i = 0; i < word_lenght; ++i)
    {
      if(starword[i] == answer[i])
      {
        ++counter;
      }
    }
    if (updating_Strikes == 6)
    {
      return 1;
    }

    //if the counter has reached the lenght of the word
    //then you have already guessed the word therefore return a 0
    if (counter == word_lenght)
    {
      return 0;
    }
  }
  return 0;
}

int occurancesInWord(char userguess, char answer[])
{
  int word_lenght = strlen(answer);
  int count = 0;
  for(int i = 0; i < word_lenght; ++i)
  {
    //if userguess is in the iteration of the answer string
    //update count depending on how manu times the user guess is in the answer string indexes
    if (answer[i] == userguess)
    {
      count ++;
    }
  }

  //return count to see if trikes are updated or if starword is updated
  return count;
}

void updateStarWord(char starword[], char answer[], char userguess)
{
  int word_len = strlen(answer);
  for (int i = 0; i < word_len; ++i)
  {
    //if userguess is found in the iteration fo the string answer
    //assign the userguess to the star index position
    if (answer[i]==userguess)
    {
      starword[i]=userguess;
    }
  }
}

void playAgain(int *play)
{
  printf("************************************************************************\n");
  printf("Would you like to play another round?\n");
  printf("Press (1) if yes\n");
  printf("Press (2) if no\n");
  printf("Enter option: ");
  scanf("%d", play);
}
