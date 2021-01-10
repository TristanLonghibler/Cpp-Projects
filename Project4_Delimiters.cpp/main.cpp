#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// class DeliiterStack is used to keep track of left and right delimiters from input
class DelimiterStack {
private:
//
    struct DelimiterNode{
        char character;
        int lineNumber;
        int charCount;
        // Pointer making a placeholder for the next character in the stack
        struct DelimiterNode *nextNode;
    };
    DelimiterNode *topOfStack;

    // Define stack top

public:
    //Constructor DelimiterStack
    DelimiterStack(){
        topOfStack = NULL;
    }
    //Destructor
    ~DelimiterStack();

    //Stack Operations
    void push(char, int, int);

    void popDelimiter(char&, int &, int &); // reference variables because the main function is using the pass variables to the output

    bool isEmpty();
};

//class function definitions


// Destructor for the class and de-allocates pointers
DelimiterStack::~DelimiterStack(){

    DelimiterNode *delimNodePtr = NULL;
    DelimiterNode *delimNextNodePtr = NULL;

    delimNodePtr = topOfStack;

    //while statement to delete any hanging pointers
    while(delimNodePtr !=0){

        delimNextNodePtr = delimNodePtr;
        delete delimNodePtr;
        delimNextNodePtr = delimNextNodePtr;

    }


}

//Push is a function(one at a time) to the class DelimiterStack that pushes passed characters onto the stack with the character count and line number
void DelimiterStack::push(char character, int input1, int input2){
//pointer tempDelimNode is an empty placeholder
    DelimiterNode *tempDelimNode = 0;
    tempDelimNode = new DelimiterNode;

    tempDelimNode->character = character;
    tempDelimNode->charCount = input1;
    tempDelimNode->lineNumber = input2;
//for the first character put on, the next node is NULL
    if (isEmpty()){
        topOfStack = tempDelimNode;
        tempDelimNode->nextNode = 0;
    }// for additional characters there is an existing node before it
    else{
        tempDelimNode->nextNode = topOfStack;
        topOfStack = tempDelimNode;
    }

}

//function that will pop the stack
//takes one character off the stack, unless it is an empty stack
void DelimiterStack::popDelimiter(char &character, int &input1, int &input2){
    //pointer temp used to pop from stack
    DelimiterNode *temp = 0;

    if (isEmpty()){
        character = ';';
        input1 = -1;
        input2 = -1;
    }else{
        character = topOfStack->character;
        input1 = topOfStack->charCount;
        input2 = topOfStack->lineNumber;
        temp = topOfStack->nextNode;
        delete topOfStack;
        topOfStack = temp;
    }

}
// returns true if the whole stack is empty else false if characters are in the stack
bool DelimiterStack::isEmpty(){
    bool emptySpotFound;
    if (topOfStack == 0)
        emptySpotFound = true;

    else{
        emptySpotFound = false;
    }
    return emptySpotFound;

}

int main() {

// variable declarations and initializations
        int count = 0;
        DelimiterStack mydelistack;
        //declare the Push Variables
        char charPush = '~';
        int pushCharNum = -1;
        int pushLineNum = -1;

        //Pop Variables declaration
        char popCharacter;
        int popCharNum;
        int popLineNum;
        bool popCheck = false;

        string currentLine = "";

        do {
            charPush = '~'; // placeholder character that is not a delimiter (you can use any non-delimiter character)
            pushCharNum = -1; // initialize to -1 but wont allow you to find this position in the string
            pushLineNum = -1; // initialize to -1 but wont allow you to find this position in the string
            count++;

            //read the line from user
            cout << "Please enter your text with or without delimiters";
            getline(cin, currentLine);
            // parse the input line ignore non delimiters
            //goes through each character in a line, reads them, and checks individually for delimeter/nondelimiter
            //then pushes or pops the stack as needed
            for (int i = 0; i < currentLine.length(); i++) {
                // string function has a .at function that returns the character at the position requested in the string
                // (I want to know the string position at (some requested position))
                if (currentLine.at(i) == '{' || currentLine.at(i) == '[' || currentLine.at(i) == '(') {
                    charPush = currentLine.at(i);
                    pushCharNum = i;
                    pushLineNum = count;
                    mydelistack.push(charPush, pushCharNum, pushLineNum);
                }


                if (currentLine.at(i) == '}' || currentLine.at(i) == ']' || currentLine.at(i) == ')') {

                    mydelistack.popDelimiter(popCharacter, popCharNum, popLineNum);
//if it is a real number go through each case to make sure there is a matching pair of delimiters for it
//otherwise write an exception for the mis-matched delimiter
                    if (popCharNum != -1) {
                        if (currentLine.at(i) == ']' && popCharacter == '['){
                            break;
                        } else if (currentLine.at(i) == '}' && popCharacter == '{') {
                            break;
                        } else if (currentLine.at(i) == ')' && popCharacter == '(') {
                            break;
                        } else {
                            cout << "Mismatched delimiter " << currentLine.at(i) << " found at line " << count
                                 << ", char ";
                            cout << i + 1 << popCharacter << " found at line " << popLineNum << ", char " << popCharNum << endl;
                        }
                    } else if (!popCheck && charPush == '~' && pushCharNum == -1 && pushLineNum == -1) {
                        cout << "Right delimiter " << currentLine.at(i) << " at line " << count << ", char " << i + 1 << " has no found left delimiter.\n";
                    }
                }
            }

//Keep reading/processing lines until user types in DONE
        } while (currentLine != "DONE");
//If there are two matching delimiters, output this
        bool emptyCheck = mydelistack.isEmpty();
        if (emptyCheck) {
            cout << "The block is delimeter matched" << endl;
        }
 //else if they are not matching delimiters, output this
        while (!emptyCheck) {
            mydelistack.popDelimiter(popCharacter, popCharNum, popLineNum);
            cout << "Left delimiter " << popCharacter << " at line " << popLineNum << ", char " << popCharNum
                 << " has no right delimiter.\n";
            emptyCheck = mydelistack.isEmpty();
        }

        //pause the console so you can read what happens(some compilers will close out without cin.get()
        cin.get();
        return 0;
};