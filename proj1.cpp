//Author: Elizabeth Bauch
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "personality_test.h"

using namespace std;

void load_file(personality_test&);
/* main
 * Calls necessary functions in this file as well as functions in personality_test
 * @param None
 * @return None, Text to Console
 */
int main () {
    cout << "====================================" << endl;
    cout << "Welcome to CSCI262 Personality Test!" << endl;
    cout << "====================================" << endl << endl;

    personality_test test; //personality_test object which is used to call functions from that class below

    // Uncomment the below methods as you complete them
    load_file(test); //calls function below and passes test into it

}

/* Load File Method
 * 1) Prompt the user for a file name. 
 * 2) Confirm that the file can be loaded
 * 3) Run personality_test::load to load in the data
 * 4) If personality_test::load fails, report this and retry
 * @param personality_test object (by reference)
 * @return None, Text to Console
 */
void load_file(personality_test& test) {
    bool playing = true; //used to keep looping personality test if user wants to play again or not
    string fileName; //first file - questions.txt
    ifstream questions; //ifsteam to open first file
    ifstream analysis; //ifstream to open second file
    string ans; //string for user's input
    string fileName2; //string for name of second file - analysis.txt
    ofstream saveFile; //ofstream to save user's personality data / write out to it
    string fileA; //string for analysis filen name
    string ans2; //string for user's input
    //fileName = "questions.txt"; //REMOVE THIS
    while (playing) { //while playing is true keep playing the game (test)
        while (true) { //while true ask for the name of the questions file
            cout << "Please enter the input file name, e.g., \"questions.txt\": ";
            cin >> fileName; //take in user's input for the name of the file
            questions.open(fileName); //open the file the user entered
            if (questions.fail()) { //if the file fails to open
                cerr << "Error opening file " << fileName << endl; //tell the user
                questions.close(); //close the file
            } else if (test.load(questions)) { //call load function to load the data
                questions.close(); //close the file
                break; //break the while loop
            }
        }

        string output = test.analyze_personality(); //assign output to the string returned from analyzing the personality type
        //cout << output << endl;
        while (true) { //while true ask for the name of the analysis file
            cout << "Please enter the analysis file name, e.g., \"analysis.txt\": ";
            cin >> fileA; //take in user's input for the name of the file
            analysis.open(fileA); //open the file the user entered
            if (analysis.fail()) { //if the file fails to open
                cerr << "Error opening file " << fileA << endl; //tell the user
                analysis.close(); //close the file
            } else {
                test.load2(analysis); //call the second load function to load the data from the analysis file
                analysis.close(); //close the file
                break; //break the while loop
            }
        }
        test.categorize_output(output, cout); //call categorize output function and pass in string output (personality type) and cout is an ostream which is passed in to print out the data
        char input = 'x'; //initializes x to input
        while (input == 'x') { //while input equals x keep asking the user if they want to save
            cout << "Would you like to save?" << endl;
            cin >> ans; //enter user's answer if they want to save description to the file
            input = test.checkInput(ans); //assign input to the checkInput function which returns 'y','n',or 'x' to know if the user's input was valid
            if (input == 'y') { //if the user says yes
                cout << "Please enter a file name" << endl;
                cin >> fileName2; //enter name of the file that will be written to
                saveFile.open(fileName2); //open the file
                saveFile.clear(); //clear the file if they have saved a previous description
                if (saveFile.fail()) { //if it fails
                    cerr << "Error opening save file" << endl; //tell user
                } else {
                    test.categorize_output(output, saveFile); //if the file doesn't fail then pass in output and the file that the information will be written out to
                    break; //break the loop
                }
            } else if (input == 'n') { //if they don't want to save
                break; //break the loop
            }
        }
        input = 'x'; //input is assigned to x
        while (input == 'x') {
            cout << "Would you like to play again?" << endl;
            cin >> ans2; //take in user's answer
            input = test.checkInput(ans2); //check the user's input
            if (input == 'y') { //if they want to play again, break this while loop and go to the beginning of the overall while loop to put in the question file again
                break; //break the loop
            }
            if (input == 'n') { //if they don't want to play again
                playing = false; //then playing equals false and the overall loop will be false / not continue, and the game won't continue
                break; //break this while loop
            }
        }
    }
}

