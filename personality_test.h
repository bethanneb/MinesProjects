//Author: Elizabeth Bauch
#ifndef _PERSONALITY_TEST_H
#define _PERSONALITY_TEST_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

//function descriptions are in personality_test.cpp above each function
class question {
public:
    string text;
    char category_id;
    char yes_answer;
    char no_answer;
    char result;
    string personality;
    string category;
    string youAre;
    string describe;
};

// personality test class
class personality_test {
    public:
        //these were used to test different answer inputs:
        //string answers[13] = {"y","y","y","n","n","y", "asf","n","no","NO", "yes","YES", "N"};
        //string answers[14] = {"y","yes","y","YES","Y","y", "y","y","yes","y", "yasg","yup", "y", "yes"};
        char checkInput (string ans);
        bool checkAnswer(char a, char b);
        bool load(istream&);
        void load2(istream&);
        string analyze_personality();
        void categorize_output(string, ostream &ost);
        vector <question*> questions;
        vector <question*> analysis;

};

#endif
