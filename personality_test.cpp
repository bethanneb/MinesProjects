//Author: Elizabeth Bauch
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "personality_test.h"

using namespace std;

/* Load method
 * 1) Provided an istream object, read in each line and process them accordingly
 * 2) Ensure to see if the input is "correct" (do at least one simple check, like first character is a number)
 * Input: istream object
 * Output: Boolean
 */

bool personality_test::load(istream &in) {
    string firstLine;
    string line;
    char category_id;
    char ans1;
    char ans2;
    getline(in, firstLine);
    //cout << firstLine << endl;
    while (!in.eof()) {
        in >> category_id >> ans1 >> ans2; //take in the (1,2,3, or 4) and the (I,E,N,S,F,T,P, or J) for both the yes_answer and no_answer
        if (category_id == '@') { //if the category_id is equal to @, then it's the last line of the file, so break the loop
            break;
        }
        //test 1
        //if the category id isn't between '1' and '4' inclusive then the file is not valid
        else if ((category_id < '1') || (category_id > '4')) {
            cerr << "Input file \"filename\" appears to not be a proper file!" << endl;
            return false; //return false
        }
        //test 2
        //if both are NOT true then return false, but if either one is true then the data is valid
        else if (!checkAnswer(ans1, ans2) && !checkAnswer(ans2, ans1)) {
            cerr << "Input file \"filename\" appears to not be a proper file!" << endl;
            return false;
        }
        //data.set_id(category_id);
        getline (in, line); //take in the rest of the line which is the question
        //cout << category_id << ans1 << ans2 << line << endl; //Part 3: printout test
        question *q = new question(); //q is a memory address that points to memory reserved for an instance of the question class
        q->category_id = category_id; //assign the category_id in question class to the category_id in this function
        q->yes_answer = ans1; //assign the yes_answer in question class to the answer 1 in this function
        q->no_answer = ans2; //assign the no_answer in question class to the answer 2 in this function
        q->text = line; //assign the text in question class to the line (which is the question part) in this function
        this->questions.push_back(q); //pushing back memory address q, and "this" refers to test because test is a personality_test obj
        //it is like each index of questions is a box with four different files and the files have category id, the first answer, the second answer, and the question
    }
    //cout << questions.size() << " is the size" << endl;
    //cout << "called load" << endl;
    return true;
}

//this function tests if the file is valid by testing if the yes and no answer are correct and match up to the four categories (Introvert and Extrovert, etc.)
bool personality_test::checkAnswer(char a, char b) {
    switch(a) {
        case 'I':
            return (b == 'E');
        case 'N':
            return (b == 'S');
        case 'F':
            return (b == 'T');
        case 'P':
            return (b == 'J');
    }
    return false;
}
        
/* personality_test::printout method
 * 1) Printout the questions to ensure that the load method was written correctly
 * This part will not be graded, just for your own check
 */

/* Analyze Personality Method
 * 1) Ask user one question at a time
 * 2) Read in user's response and construct a vector containing the responses
 * 3) Analyze the responses to construct a personality type (eg. ENFJ)
 * @param None
 * @return string
 */
string personality_test::analyze_personality() {
    string output = "";
    string answer = "";
    int a = 0;
    int size = questions.size(); //this is so this test can be done with any file size, not just 12 questions
    char input;
    int i;
    for (i = 0; i < size; i++) {
        question *q = questions.at(i); //creates pointer q for index of questions
        cout << q->text << endl;
        input = 'x';
        while (input == 'x') {
            //answer = answers[a]; //REMOVE THIS
            cin >> answer; //UNCOMMENT THIS OUT
            input = checkInput(answer);
            if (input == 'x') {
                cout << "Sorry, I didn't recognize your input, please type again" << endl;
            }
            else if (input == 'y') {
                //add ans1 to the i index of questions for results
                q->result = q->yes_answer;
            }
            else if (input == 'n') {
                q->result = q->no_answer;
            }
            a++;
        }
    }
    //increments categories
    int I = 0, E = 0, N = 0, S = 0, F = 0, T = 0, P = 0, J = 0;
    for (i = 0; i < size; i++) {
        question *q = questions.at(i);
        switch (q->result) {
            case 'I':
                I++;
                break;
            case 'E':
                E++;
                break;
            case 'N':
                N++;
                break;
            case 'S':
                S++;
                break;
            case 'F':
                F++;
                break;
            case 'T':
                T++;
                break;
            case 'P':
                P++;
                break;
            case 'J':
                J++;
                break;
        }
    }
    //shorthand if statement
    output+= E > I ? "E" : "I"; //for example, if E is greater than i is true return E, if false then return I
    output+= N > S ? "N" : "S";
    output+= F > T ? "F" : "T";
    output+= P > J ? "P" : "J";
    return output;
}

//checks the user's input to see if it is valid
char personality_test::checkInput(string ans) {
    if ((ans == "Y") || (ans == "y") || (ans == "yes") || (ans == "Yes") || (ans == "YES")) {
        return 'y'; //if the yes is valid return char 'y'
    }
    else if ((ans == "N") || (ans == "n") || (ans == "no") || (ans == "No") || (ans == "NO")) {
        return 'n'; //if the no is valid return 'n'
    }
    return 'x'; //else return 'x'
}

void personality_test::load2(istream &in) {
    string firstLine;
    string type;
    string job;
    string person;
    string description;
    getline(in, firstLine);
    //cout << firstLine << endl;
    while (!in.eof()) {
        in >> type >> job >> person;
        //cout << type << " " << job << " " << person;
        getline(in, description);
        //cout << " " << description << endl;
        question *a = new question();
        a->personality = type;
        a->category = job;
        a->youAre = person;
        a->describe = description;
        this->analysis.push_back(a);
    }
}
/* Categorize Output Method
 * 1) Read in the analysis.txt file
 * 2) Provided a user's personality type, print out to console the user's personality description
 * @param Personality type string (eg. "ENFJ")
 * @return None, Text to console
 */
//the ostream passed in this makes it so if cout is passed in it will print out the "=====" and "Your personality types is...", etc.
//but if a file is passed in to ostream then is saves all of the text into the file by outputting it in different ways
void personality_test::categorize_output(string my_personality, ostream &ost) {
    int size = analysis.size();
    int i;
    //passes in personality
    for (i = 0; i < size; i++) {
        question *a = analysis.at(i);
        if (my_personality == (a->personality)) {
            ost << "===============" << endl;
            ost << "Your personality type is: " << a->personality << endl;
            ost << "The category is: " << a->category << endl;
            ost << "You are: " << a->youAre << endl;
            ost << "Description:" << a->describe << endl;
            ost << "===============" << endl;
            break; //so there's no possibility of it printing out the description twice
        }
    }
    //if personality equals type then print out stuff
}


