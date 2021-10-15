//Was having trouble with generating Random values earlier, some libraries are not necessary.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <String>
#include <vector>

int getNote(int OctaveNum, int key);
// Generates Midi Note Number, calls getKeyNote, which does the brunt of the work 

std::string Num2Value(int);
// Generates the Name of the Note and its midi octave in a human readable format based on the number input
// Gets called by getKeyNote

std::string getKeyNote(int key, int& midiNumber, int OctaveNum);
// Generates a random note based on the key. returns a string, but midiNumber is REDEFINED by the function. 
// Calls Num2Value
// Gets called by getNote

std::vector<int> values;



int main()
{
    srand(time(NULL));
    int iterations = 0;
    //Used to determine the number of notes 

    while (iterations < 15) {
        //int key = rand() % 12;
        int key = 11; 
        /*
        0 is C
        1 is C#
        2 is D
        3 is D# 
        ...
        11 is B

        10/13/21 all keys are assumed to be major 
        */


        int reUse = getNote(3, key);
        // getNote uses a random function, calling it twice will produce different results.
        // Saving the value in reUse allows us to reuse the value which will be necessary for display purposes.

        std::cout << reUse << "    ";
        values.push_back(reUse);
        iterations++;
    }
    std::cout << std::endl;


    std::string x;
    for (int i = 0; i < values.size(); i++) {
        x = Num2Value(values.at(i));
        std::cout << x  << "    ";
    }
}


int getNote(int OctaveNum, int key) {
  
    int NoteValue =-1;
    int change = (rand() % 3) - 1;
    //Gives SOME variance to the octave

    OctaveNum += change;
    int midiNoteValue = -1;

    
    getKeyNote(key, midiNoteValue, OctaveNum);
    //Returns string name; i.e. C3, C#1, D4 etc.
    //midiNoteValue is pass by reference. 

    return midiNoteValue;
}


std::string Num2Value(int value) {
    int x = value % 12;
    std::string output;
    output = "";


    switch (x) {
    case 0: 
        output += "C";
        break;
    case 1:
        output += "C#";
        break;
    case 2:
        output += "D";
        break;
    case 3:
        output += "D#";
        break;
    case 4:
        output += "E";
        break;
    case 5:
        output += "F";
        break;
    case 6:
        output += "F#";
        break;
    case 7:
        output += "G";
        break;
    case 8:
        output += "G#";
        break;
    case 9:
        output += "A";
        break;
    case 10:
        output += "A#";
        break;
    case 11:
        output += "B";
        break;
    case 12:
        output += "C";
        break;
    }

    int ON = -1; //octave Number

    ON = (value - x) / 12 - 1;
    output += std::to_string(ON);

    return output;

}
 

//Midi Note Formula (octaveNumber + 1)*12 + NoteModulusValue
//NoteModulusValue is "Num" in the following code.

std::string getKeyNote(int key, int& midiNumber, int OctaveNum) {
    while (true) {
        int num = rand() % 12;
        /*
        num is the numerical value of a note. 
        0 is C
        1 is C#
        2 is D
        etc.
        */

        switch (key) {
        case 0:// Key in C

            if (num == 1|| num == 3 || num == 6 || num == 8 || num == 10) {
                /*
                if the key is in C, 
                    if the note produced is C#, D#, F#, etc. Repeat the loop. Pick a new note.
                    Else break out of the loop

                */
                continue;
            }
            break;
        case 1://C#
            if (num == 2 || num == 4 || num == 7 || num == 9 || num == 11) {
                continue;
            }
            break;
        
        case 2://D
            if (num == 3 || num == 5 || num == 8 || num == 10 || num == 0) {
                continue;
            }
            break;

        case 3://D#
            if (num == 4 || num == 6 || num == 9 || num == 11 || num == 1) {
                continue;
            }
            break;

        case 4://E
            if (num == 5 || num == 7 || num == 10 || num == 0 || num == 2) {
                continue;
            }
            break;

        case 5://F
            if (num == 6 || num == 8 || num == 11 || num == 1 || num == 3) {
                continue;
            }
            break;

        case 6://F#
            if (num == 7 || num == 9 || num == 0 || num == 2 || num == 4) {
                continue;
            }
            break;

        case 7://G
            if (num == 8 || num == 10 || num == 1 || num == 3 || num == 5) {
                continue;
            }
            break;

        case 8://G#
            if (num == 9 || num == 11 || num == 2 || num == 4 || num == 6) {
                continue;
            }
            break;

        case 9://A
            if (num == 10 || num == 0 || num == 3 || num == 5 || num == 7) {
                continue;
            }
            break;

        case 10://A#
            if (num == 11 || num == 1 || num == 4 || num == 6 || num == 8) {
                continue;
            }
            break;

        case 11://B
            if (num == 0 || num == 2 || num == 5 || num == 7 || num == 9) {
                continue;
            }
            break;
        }

        midiNumber = (OctaveNum * 12) + num;
        //midiNumber is Passed by Reference.

        return Num2Value(num);
        //returns the note name;
    }



}
    



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
