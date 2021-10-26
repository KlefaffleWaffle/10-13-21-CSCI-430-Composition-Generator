//Was having trouble with generating Random values earlier, some libraries are not necessary.

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <String>
#include <vector>

std::vector<int> key; 
std::vector<int> midiMelody; //Is used to get a common pattern, but later in the song may see variation.
std::vector<int> majorKeyProgression = { 0,2,2,1,2,2,2};
std::vector<int> minorKeyProgression = { 0,2,1,2,2,1,2 };
std::vector<std::string> notesHuman = { "C","C#","D","D#","E","F", "F#", "G","G#","A","A#","B" };




void setKeyNotes(std::string baseNote);

void BaselineGenerator(int ProgressionStyle);


int getNoteFullMIDINumber(int OctaveNum, int key);
// Generates Note, calls getKeyNote, which does the brunt of the work 

std::string Num2Value(int);
// Generates the Name of the Note and its midi octave in a human readable format based on the number input
// Gets called by getKeyNote


std::string Mod2Value(int);
//Same as Num2Value except does not include octave

std::string getNoteHumanWithOct(int key, int& midiNumber, int OctaveNum);
// Generates a random note based on the key. returns a string, but midiNumber is REDEFINED by the function. 
// Calls Num2Value
// Gets called by getNote

std::vector<int> values;

class Note {
public:
    std::string name;
    int octave;
    int midiNumber;
    int velocity;
    int length;
};


class Chord {
public:
    int midiNotes[3] = {};
    int noteModulus;
    int octaveNum;

    int getOctaveNum() {
        return octaveNum;
    }

    /*
    Make sure chord fits key.
    */
    Chord(int FMnote, bool majTrue) {
        noteModulus = FMnote % 12;
        octaveNum = ((FMnote - noteModulus) / 12) - 1;

        //Midi value of the notes in the chord
        midiNotes[0] = FMnote;

        int pos = -1;

        //Finds the position in key array 


        for (int i = 0; i < key.size(); i++) {
            if (key.at(i) == noteModulus) {
                pos = i;
                break;
            }
        }




        //Finds the 2nd value in key, if pos is greater than size it loops to beginning
        pos += 2;

        if (pos >= 7) {
            pos -= 7;
        }

        if (majTrue == true) {
            midiNotes[1] = ((octaveNum + 1) * 12) + key[pos];
        }
        else {
            //Verify Me;
            midiNotes[1] = ((octaveNum + 1) * 12) + (key[pos]-1);
        }

        pos += 2;

        if (pos >= 7) {
            pos -= 7;
        }

        midiNotes[2] = ((octaveNum + 1) * 12) + key[pos];


    }

    void displayChordNoteNumbers() {
        
    }

    void displayChordNoteLetters() {
        for (int i = 0; i < 3; i++) {
            std::cout << Num2Value(midiNotes[i]) << std::endl;
        }
    
    };


    

};
std::vector<Chord> chordListVec;

void arpeggiatorHelper(Chord, int numOfNotes);
void scale(int numOfNotes, int midiNote, bool up);



int main()
{
    srand(time(NULL));
    int iterations = 0;
    //Used to determine the number of notes 


    int startingNote = 0;
    setKeyNotes(Mod2Value(startingNote));

    std::cout << std:: endl;

   // Chord c(71, true);


    BaselineGenerator(0);

    for (int i = 0; i < 4; i++) {
        arpeggiatorHelper(chordListVec.at(i), 9);
    }

    std::cout << std::endl;

    scale(15, 0, true);

}


int getNoteFullMIDINumber(int OctaveNum, int key) {
  
    int NoteValue =-1;
    int change = (rand() % 3) - 1;
    //Gives SOME variance to the octave

    OctaveNum += change;
    int midiNoteValue = -1;

    
    getNoteHumanWithOct(key, midiNoteValue, OctaveNum);
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
 
std::string Mod2Value(int value) {
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


    return output;

}
//Midi Note Formula (octaveNumber + 1)*12 + NoteModulusValue
//NoteModulusValue is "Num" in the following code.

std::string getNoteHumanWithOct(int key, int& midiNumber, int OctaveNum) {
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
    
void setKeyNotes(std::string baseNote) {

    std::cout << "You have chosen the key of " << baseNote << std::endl;
    int noteValue = -1;
    for (int i = 0; i < 12; i++) {
        if (notesHuman[i] == baseNote) {
            noteValue = i;
         
            break;
        }
    }

        //change depend on major or minor
    
    key.push_back(noteValue);
       // std::cout << "Looping " << std::endl;
        for (int i = 1; i < 7; i++) {
            
            key.push_back(key.at(i-1) + majorKeyProgression.at(i));
           
            if (key.at(i) >= 12) {
                key.at(i) -= 12;
            }
        }
    
        std::cout << "Values are: ";
        for (int i = 0; i < key.size(); i++) {
            std::cout << key.at(i) << ", ";
        }
        std::cout << std::endl;
}

void BaselineGenerator(int ProgressionStyle) {
    //Assume 1451;   
    
    //Add octave to chord generation.;
    
    Chord first(key.at(0), true);
    Chord second(key.at(3), true);
    Chord third(key.at(4), true);
    Chord fourth = first;

    chordListVec.push_back(first);
    chordListVec.push_back(second);
    chordListVec.push_back(third);
    chordListVec.push_back(fourth);
}

void arpeggiatorHelper(Chord c, int numOfNotes) {
    //Notes per chord parameter

    int x = numOfNotes;
    int octaveNumber = c.getOctaveNum() +1;
    std::vector<int> arpeggNotes;
    
    int notesPlayed = 0;
    int pos = 0;

    bool up = true;

    while (notesPlayed < numOfNotes) {
        if (pos > 2) {
            pos = 1;
            up = false;
        }
        else if (pos < 0) {
            pos = 1;
            up = true;
        }

        arpeggNotes.push_back(c.midiNotes[pos]);
        std::cout << Num2Value(c.midiNotes[pos] + 12) << "   ";





        if (up == true) {
            pos++;
        }
        else {
            pos--;
        }
        notesPlayed++;
    }
    
    std::cout << std::endl;
    c.displayChordNoteLetters();
    std::cout << std::endl;
}

void scale(int numOfNotes, int midiNote, bool up) {
    int notesPlayed = 0;
    int pos = -1;
    int startingNoteMod = midiNote % 12;
    int octave = ((midiNote - startingNoteMod) / 12) + 1;
    int addedVal = octave * 12;


    for (int i = 0; i < 7; i++) {
        if (key[i] == startingNoteMod) {
            pos = i;
            break;
        }
    }

    while (notesPlayed < numOfNotes) {
        if (pos > 6) {
            pos = 5;
            up = false;
        }
        else if (pos < 0) {
            pos = 1;
            up = true;
        }

        std::cout << Num2Value(key[pos] + addedVal) << "   ";




        
        if (up == true) {
            pos++;
        }
        else {
            pos--;
        }
        notesPlayed++;
    }

    std::cout << std::endl;
}



