//============================================================================
// Name        : CS2250_Project2.cpp
// Author      : Tristan Longhibler
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Word
{
    string english;
    string piglatin;
};

Word* splitSentence(const string words, int& size); // function that returns a pointer to a structure
void convertToPigLatin(Word wordArr[], int size);
void displayPigLatin(const Word wordArr[], int size);

int main()
{
    int size = 1;
    string input;
    Word* wordPtr; // causes the structure to be inserted to wordPtr

    cout<<"Please enter a string to convert to PigLatin:"<<endl;
    getline(cin, input);

    wordPtr = splitSentence(input, size);

    convertToPigLatin(wordPtr, size);

    displayPigLatin(wordPtr, size);

    return 0;
}


Word* splitSentence(const string words, int& size)
{
    int index = 0, countedWords;
    bool eraseChar, check; // two safety checks
    string changedVariable;
    Word* wordPtr = NULL;

    //This loop removes all invalid characters and copies all spaces into a new string
    int stringSize = words.length();
    for(int i = 0; i < stringSize; i++) // .length returns the length of the string
    {
        if(isalpha(words[i]) ||  isspace(words[i]) ) //alphabetical letters in string
        {
            changedVariable += words[i];
        }
    }

    //This loop removes all whitespace from the beginning of the string only
    do
    {
        eraseChar = false;
        if(isspace(changedVariable[0]))
        {
            changedVariable.erase(index, 1); // .erase will remove a certain amount of characters from the string, in this case just one
            eraseChar = true;
        }
    }
    while(eraseChar == true);

    changedVariable += '*';

    eraseChar = true;

    //Removes invalid whitespace and corrects sentence structure.
    while(eraseChar == true)
    {
        eraseChar = false;
        countedWords = changedVariable.length();

        for(int i = 0; i < countedWords; i++)
        {
            changedVariable[i] = tolower(changedVariable[i]);
            if(changedVariable[i] == '*')
            {
                if(isspace(changedVariable[i - 1]))
                {
                    changedVariable.erase(i - 1, 1);
                    eraseChar = true;
                    break;
                }

                changedVariable.erase(i, 1);
                eraseChar = true;
                break;
            }
            if(isspace(changedVariable[i]))
            {
                if(isspace(changedVariable[i + 1]))
                {
                    changedVariable.erase(i, 1);
                    eraseChar = true;
                    break;
                }
            }
        }
    }

    changedVariable += " "; // adds spacing to the end of each word

    countedWords = changedVariable.length(); // .length returns the length of the variable

    //This loop counts the number of spaces to determine how many words there are
    for(int i = 0; i < countedWords; i++)
    {
        if(isspace(changedVariable[i]))
        {
            size++;
        }
    }

    size--;

    wordPtr = new Word[size];

    //This loop separates all the words in a single sentence
    for(int j = 0; j < size; j++)
    {
        check = false;
        for(int k = index; k < countedWords; k++)
        {
            if(isspace(changedVariable[k]))
            {
                for(int l = index; l < k; l++)
                {
                    wordPtr[j].english += changedVariable[l];
                    check = true;
                }
            }

            if(check)
            {
                index = k + 1;
                break;
            }
        }
    }
    return wordPtr;
}


void convertToPigLatin(Word wordArr[], int size)
{
    const int vowelSize = 5;
    int loopsMade = 0;
    bool vowelFound;
    string vowel ="aeiou";

    do
    {
        vowelFound = false;
        for(int i = 0; i < vowelSize; i++)
        {
            if((wordArr[loopsMade]).english[0] == vowel[i])
            {
                vowelFound = true;  // a, e, i, o, u is found in the first loop array
                break;
            }
        }

        if(vowelFound == true)
        {
            wordArr[loopsMade].piglatin = wordArr[loopsMade].english; //both structures will be the same
            wordArr[loopsMade].piglatin += "way"; //but will add way to the end of the vowels a, e, i, o, u.
        }
        else
        {
            wordArr[loopsMade].piglatin = wordArr[loopsMade].english;
            wordArr[loopsMade].piglatin.erase(0, 1);
            wordArr[loopsMade].piglatin += (wordArr[loopsMade].english)[0]; //example: west becomes estw
            wordArr[loopsMade].piglatin += "ay"; // adds ay to the end of any consonant
        }
        loopsMade++;
    }
    while(loopsMade < size); // goes through do loop once and continues if the loopsMade is less than size
}


void displayPigLatin(const Word wordArr[], int size)
{
    cout<<"Output:"<<endl;
    for(int i = 0; i < size; i++)
    {
        cout<<wordArr[i].piglatin<<" ";
    }
    cout<<endl;
}
