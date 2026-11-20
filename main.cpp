/*********************************************************************************************
Program..........:MathTutorV4
Programmers......:Pedro Presidio
Date.............:2026.11.04
Course Section...:Section 1- 9:00am
Version..........:2
GitHub Report.:https://github.com/PedroPresidio/MathTutorV4
Description...:A simple math tutor for young children. The program displays the introduction
               and silly math facts, gets the user's name, welcomes the user, generates two
               random numbers and randomly selects a math operation (addition, subtraction,
               multiplication and division). It asks the user a math question, gives the user
               three attempts, checks the answer and asks whether the user wants to keep
               playing. After five correct answers the user levels up, after five wrong
               answers the user levels down. In version 4, every question is stored in a
               2D vector and a summary report is displayed when the user quits.

               - Display header
               - Prints silly math facts
               - Ask for user name and welcome user
               - Uses random lib to create the math operation and the question numbers
               - Checks for no negative numbers or fractions
               - Provides three attempts for the user
               - Check if user still wants to play
               - After five correct questions level up
               - After five wrong questions level down
               - Stores every question in a 2D vector (level, left, symbol, right, answer, attempts)
               - Displays a formatted summary report after the user decides to stop
**********************************************************************************************/


#include <iostream> // for input/output, PLUS left & right alignment
#include <string> // std::string and text handling
#include <cstdlib> // rand and srand handling
#include <ctime> // time(), used for random seed
#include <vector> // library to handle vector

#include "math_tutor.h" // Header file all the function prototypes

using namespace std;

int main() {
    //define and initialize the variables
    int MAX_ATMP = 3;             // Maximum number of guesses
    int LEV_RANG = 10;            // Max number used for the range

    // Defines the four possible math operations.
    enum mathType {add, subtract, multiply , divide};
    int plyLevel = 1;             // player level

    int leftNum = 0;              // First number in the equation
    int rightNum = 0;             // Second number in the equation
    int userAnswer = 0;           // Users answer to the equation
    int correctAnswer = 0;        // Correct answer to the equation

    int amtCorrect = 0;           // Amount the users answers correct
    int amtWrong = 0;             // Amount the users answers wrong

    int temp = 0;                 // Temporarily stores a number when swaping

    char mathSymbol = '?';       // Symbol displayed at the end of the questions

    vector<vector<int>> questions;

    string userInput = "";       // Stores player decision to continue
    string userName = "unknown"; // Stores player user name

    //

    //seed the random number generator
    srand(time(0));

    //Main title with a welcome
    cout << "**************************************************************************" << endl;
    cout << "    __  __       _   _       _____      _                  " << endl;
    cout << "   |  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __     " << endl;
    cout << "   | |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__| " << endl;
    cout << "   | |  | | (_| | |_| | | |   | || |_| | || (_) | |    " << endl;
    cout << "   |_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|    " << endl;
    cout << "**************************************************************************" << endl;
    cout << "#         Welcome to the Super Simple Math Tutor                         #" << endl;
    cout << "**************************************************************************" << endl;

    // States silly math jokes like facts
    cout << endl;
    cout << "   Fun Silly Math Facts:" << endl;
    cout << endl;
    cout << "       + A math Teachers favorite dessert is pie" << endl;
    cout << "       + A math teacher is like a pirate they are looking for x" << endl;
    cout << "       + A math book is always crying because it has so many problems" << endl;
    cout << "       + The first three digits of pi spell pie when looked at backwords " << endl;
    cout << endl;
    cout << "**************************************************************************" << endl;
    cout << endl;

    //Get the user's name
    cout << "What is your name? " << " ";
    getline(cin , userName);
    cout << endl;

    //Welcome the user
    cout << "Welcome " << userName << "!" << endl;
    cout << endl;

    //Start of the main loop
    do {

        //Generate random numbers
        leftNum = rand() % LEV_RANG + 1;
        rightNum = rand() % LEV_RANG + 1;
        mathType operation = static_cast<mathType>(rand() % 4);

        switch (operation) {
            //Addition
            case add:
                correctAnswer = leftNum + rightNum;
                mathSymbol = '+';
                break;

                //Subtraction avoids negative numbers
            case subtract:
                if (leftNum < rightNum) { // handling negative numbers
                    temp = leftNum;
                    leftNum = rightNum;
                    rightNum = temp;
                }

                correctAnswer = leftNum - rightNum;
                mathSymbol = '-';
                break;

                //Multiplication
            case multiply:
                correctAnswer = leftNum * rightNum;
                mathSymbol = '*';
                break;

                //Division avoids fractions
            case divide:
                correctAnswer = leftNum;
                leftNum *= rightNum;
                mathSymbol = '/';
                break;

                //Something went wrong
            default:
                cout << "Invalid question type: " << 'mathType' << endl;
                cout << "Program ended with an error -1" << endl;
                cout << "Please report this error to Terry Hofaker" << endl;
                return -1;
        } //switch case close

        // Single dimension vector (row) that stores this question
        vector<int> row = {plyLevel, leftNum, mathSymbol, rightNum, correctAnswer};

        // Ask the user a question and give them up to MAX_ATMP attempts
        for (int i = 1; i <= MAX_ATMP; i++) {

            if (i == 1) {
                cout << userName << ", what is " << leftNum << " " << mathSymbol << " "<< rightNum << " = ";
            }

            //loop until the user enters numeric data
            while (!(cin >> userAnswer)) {
                cin.clear(); //Clear the cin error flag
                //need to include the limits library to use numreic_limits
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore the max input, up to '\n'
                cout << "\tInvalid input!" << endl;
                cout << "\tPlease enter a number: ";
            }// end of get userAnswer while loop

        //Checks answer
        if (userAnswer == correctAnswer) {
            // Congrats the user for getting the question correct
            row.push_back(i);
            break;
        } else if (i == MAX_ATMP) {
            // Out of attempts: store the error value 0
            row.push_back(0);
        }else {
            // Tells the user how many attempts they have used out of MAX_ATMP
            cout << "Wrong answer! You have used " << i << " attempt(s) out of "
                 << MAX_ATMP << ". Try again: ";
            }
        } // end of for loop

        // Save this question in the 2D vector
        questions.push_back(row);

        //Checks answer
        if (userAnswer == correctAnswer) {
            // Congrats the user for getting the question correct
            amtCorrect++;
            cout << userName << ", that is correct!" << endl;
            cout << "Good job!" << endl;

            //Tells the user how many questions they have correct
            cout << "You have " << amtCorrect << " questions correct" << endl;

        } else {
            // adds to the amount wrong total
            amtWrong++;

            //tells user they were wrong and the correct answer
            cout << "Out of attempts! The correct answer was " << correctAnswer << endl;

            // tells the user the amount of questions they have incorrect
            cout << "You have this many questions incorrect : " << amtWrong << endl;
        }

        //levels up the user, increases number range by 5 per level
        if (amtCorrect == 5) {

            // Reset the counters for the next level
            amtCorrect = 0;
            amtWrong = 0;

            // Increase the player's level and number range
            plyLevel++;
            LEV_RANG += 5;

            cout << endl;
            cout << "Congratulations, " << userName
                 << "! You have leveled up!" << endl;

            cout << "Your new level is " << plyLevel << "." << endl;
            cout << "The number range is now 1 to "
                 << LEV_RANG << "." << endl;

        // levels user down if user level is above 1 and lessens the range by 5
        } else if (amtWrong == 5) {

            // tells the user the amount they got wrong
            cout << "You have got " << amtWrong << " incorrect!" << endl;

            // Reset the counters
            amtWrong = 0;
            amtCorrect = 0;

            if (plyLevel > 1) {
                //Decrease the player's level and number range
                plyLevel--;
                LEV_RANG -= 5;
                cout << "You have leveled down!! " << endl;
                cout << "Your level is now " << plyLevel << "." << endl;
            }
        }

        // asks the user if they want to continue playing
        cout << "Do you want to continue? (y=yes | n=no)" << endl;
        getline(cin, userInput);
        cin >> userInput;

        for (int i = 0; i < userInput.length(); i++) {
            userInput.at(i) = tolower(userInput.at(i));
        }

        while (userInput != "y" && userInput != "yes" && userInput != "n" && userInput != "no") {
            cout << "Please enter a valid input: ";
            getline(cin, userInput);

            for (int i = 0; i < userInput.length(); i++) {
                userInput.at(i) = tolower(userInput.at(i));
            }
        }

    } // end of the Do
    while (userInput == "y" || userInput == "yes" );

        // ------------------------------- Summary report -------------------------------
    int totalCorrect = 0;      // Number of questions answered correctly
    int totalIncorrect = 0;    // Number of questions never answered correctly
    int attempts = 0;          // Attempts pulled out of the 2D vector

    cout << "=====================================" << endl;
    cout << "           Summary Report" << endl;
    cout << "=====================================" << endl;

    // Column headings (setw is not persistent, left/right stay on until changed)
    cout << right << setw(5) << "Level" << " " << setw(18) << "Question" << " "
         << setw(9) << "Attempts" << endl;
    cout << "----- ------------------ ---------" << endl;

    for (size_t i = 0; i < questions.size(); i++) {
        // Level
        cout << right << setw(5) << questions.at(i).at(0) << " ";
        // Question: left number, symbol, right number, equals sign and answer
        cout << setw(4) << questions.at(i).at(1) << " ";
        cout << static_cast<char>(questions.at(i).at(2)) << " ";
        cout << left << setw(3) << questions.at(i).at(3) << right;
        cout << " = " << setw(5) << questions.at(i).at(4) << " ";

        // Attempts column (do not use endl until the column is finished)
        attempts = questions.at(i).at(5);
        if (attempts != 0) {
            cout << setw(5) << attempts << endl;
            totalCorrect++;
        } else {
            cout << "Incorrect" << endl;
            totalIncorrect++;
        }
    }

    // Summary totals (multiply by 100 first because we are using integers)
    int totalQuestions = static_cast<int>(questions.size());
    int averageCorrect = 0;
    if (totalQuestions > 0) {
        averageCorrect = (totalCorrect * 100) / totalQuestions;
    }

    cout << left;
    cout << endl;
    cout << setw(18) << "Total Questions:" << setw(4) << right << totalQuestions << endl;
    cout << left << setw(18) << "Total Correct:" << setw(4) << right << totalCorrect << endl;
    cout << left << setw(18) << "Total Incorrect:" << setw(4) << right << totalIncorrect << endl;
    cout << left << setw(18) << "Average Correct:" << setw(3) << right << averageCorrect << "%" << endl;
    cout << endl;
    cout << "Keep calm and do math!" << endl;
    cout << endl;

    // closes the program and tells the player their last level
    cout << "Your final level was " << plyLevel << "." << endl;
    cout << endl;
    cout << "Thanks for playing!" << endl;
    cout << "Check back for more updates." << endl;

    return 0;
} // end of main
