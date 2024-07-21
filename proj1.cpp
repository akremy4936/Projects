/*****************************************                                      
** File:    Proj1.cpp                                                           
** Project: CMSC 202 Project 1, Spring 2024                                     
** Author:  Akrem Yusuf                                                         
** Date:    02/27/24                                                            
** Section: 24                                                                  
** E-mail:  ayusuf2@gl.umbc.edu                                                 
** Description:                                                                 
** In this project, I created 6 functions to take puzzles from a file randomly \
and play the game wheel of fortune.                                             
** I made the function loadFile to load the categories and puzzles from the tex\
t file provided. It used arrays for the puzzles and categories as it iterated   
through. I made a getRandomIndex function to randomly select a puzzle from the \
file that will be played. The getAnswer function gives the category and gets    
** the puzzle. The inPuzzle function checks if the guess is in the puzzle. The \
getinput function takes the input from the user for the guess. If it isnt       
** a letter or uppercase then it will make the user enter again. The function i\
sCompleted checks to see if the puzzle is completed. The printPuzzle function   
** prints the puzzle with every correct guess. The main function starts the gam\
e and keeps it going as logn as it is not complete.It uses all the other        
** functions to do this.It lets you know if the letter is in or not in the puzz\
le.Once the game is complete it lets you know that you won.                     
**                                                                              
**                                                                              
***********************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int NumCategories = 24; // 24 categories in the file                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
const int MaxPuzzleLength = 50; // Maximum length of  puzzle                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

const string Filename = "proj1_data.txt";
const int ASCII_TABLE_SIZE = 256; // Size of the ASCII table                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

// Function prototypes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
void loadFile(string categories[], string puzzles[]);
int getRandomIndex();
string getAnswer(const string categories[], const string puzzles[]);
bool inPuzzle(const string puzzle, char guess);
char getInput();
bool isCompleted(const string puzzle, const bool guessed[]);
void printPuzzle(const string puzzle, const bool guessed[]);

int main() {
    string categories[NumCategories];
    string puzzles[NumCategories];
    bool guessed[ASCII_TABLE_SIZE] = {false}; //Starts with all being not guessed                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    bool guessedLetters[ASCII_TABLE_SIZE] = {false}; // Remembers the guessed letters                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    srand(time(NULL));

    loadFile(categories, puzzles);

    string puzzle = getAnswer(categories, puzzles);

    cout << "Welcome to UMBC Fortune Wheel!" << endl;

    while (!isCompleted(puzzle, guessed)) {//if the puzzle isnt finished then it keeps asking for guesses until complete                                                                                                                                                                                                                                                                                                                                                                                                                          
      printPuzzle(puzzle, guessed);
      unsigned char guess;
      do {
        guess = getInput();
        if (guessedLetters[guess]) {//if the letter has been guessed already it will ask to input another letter                                                                                                                                                                                                                                                                                                                                                                                                                                  
          cout << "The letter '" << guess << "' has already been guessed. Please try another letter: ";
            }
        }
      while (guessedLetters[guess]);

        guessedLetters[guess] = true; // Knows the guessed letters                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

        if (inPuzzle(puzzle, guess)) {
          cout << guess << " is in the puzzle!" << endl;//tells if the guessed letter is in the puzzle                                                                                                                                                                                                                                                                                                                                                                                                                                            
        }
        else {
          cout << guess << " is not in the puzzle." << endl;//tells if the guessed letter is not in the puzzle                                                                                                                                                                                                                                                                                                                                                                                                                                    
        }

        guessed[guess] = true;
    }

    printPuzzle(puzzle, guessed);//prints the puzzle with the guessed letters                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    cout << "You won!" << endl;//prints you won when all the letters have been guessed in the puzzle                                                                                                                                                                                                                                                                                                                                                                                                                                              

    return 0;
}


void loadFile(string categories[], string puzzles[]) {
  ifstream file(Filename); //loading file                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

    for (int i = 0; i < NumCategories; ++i) {
      getline(file, categories[i]);//this is for categories                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
      getline(file, puzzles[i]);//this is for puzzles                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    }

    file.close();
}

int getRandomIndex() {
  return rand() % NumCategories; //used to randomize the puzzle selected                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}

string getAnswer(const string categories[], const string puzzles[]) {
  int index = getRandomIndex();//randomizing                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    cout << "Category is: " << categories[index] << endl;
    return puzzles[index];
}

bool isLetter(unsigned char let) {//makes sure its a letter                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    return (let >= 'A' && let <= 'Z');
}

bool inPuzzle(const string puzzle, char guess) {//checks if the guess is in the puzzle                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  for (unsigned int i = 0; i < puzzle.length(); ++i) {
        if (puzzle[i]  == guess) {
            return true;
        }
    }
    return false;
}


char getInput() {//takes the user input for the guess letter                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    char guess;
    cout << "What letter would you like to try?" << endl;
    cin >> guess;
    cin.ignore();

    while (!isLetter(guess)) {//if the guess isnt a letter or upper case, it will make the user retry                                                                                                                                                                                                                                                                                                                                                                                                                                             
        cout << "Invalid input! Please enter a letter: ";
        cin >> guess;
        cin.ignore();
    }

    return guess;
}

bool isCompleted(const string puzzle, const bool guessed[]) {
  for (unsigned int i = 0; i < puzzle.length(); i++) {//checks over the length of the puzzle if it is completed                                                                                                                                                                                                                                                                                                                                                                                                                                   
       unsigned char let = puzzle[i];
        if (isLetter(let) && !guessed[let]) {
            return false;
        }
    }
    return true;
}

void printPuzzle(const string puzzle, const bool guessed[]) {
  for (unsigned int i = 0; i < puzzle.length(); i++) {//prints the puzzle with every correct guess                                                                                                                                                                                                                                                                                                                                                                                                                                                
        unsigned char let = puzzle[i];
        if (isLetter(let)) {
            if (guessed[let]) {
                cout << let << " ";
            }
            else {
                cout << "_ ";
            }
        }
        else {
            cout << let << " ";
        }
    }
    cout << endl;
}
