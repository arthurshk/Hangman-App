
#include <iostream>
#include <fstream>
#include<windows.h>
#include <string>
#include <conio.h>
using namespace std;
class Hangman
{
private:
    string array[50]; // array of words
    int tries = 7; // number of tries left
    string response; //word storage
    string shown = ""; // depth of search guesses
    string temporary;
public:
    void drawHangman(); //to draw the figure
    void resetWord(); // to make the word reusable
    string chooseWord(); //fstream function to open the file
    void storeWord(string hangWord); // private setting storage to not touch
    void displayLogo(); // hangman logo as first display
    void guess();
    void tryMinus();
    void guess2();
};
void Hangman::tryMinus()
{
    tries--;
}
string Hangman::chooseWord() //file opener
{
    srand(time(NULL)); // randomize the words to choose from
    int random = rand() % 50; // randomizes to 1 in 50
    int storage = random; // the storage of the word when the randomizer chooses it
    int bit = 0; // leveler to check number of words that have opened, se to 0 by default
    ifstream fin("WordSpread.txt"); // name of file that will open to match
    if (!fin) //if the name is not found or does not match the record it will not open and display message
    {
        cout << "File has failed to initiate " << endl;
    }
    /*string temporary;*/ // the temporary word that will be used to guess
    while (!fin.eof()) //eof is the string opener, while checks until it does not open, if it does open then initiates the opening of it
    {
        getline(fin, temporary); //temporary is the reference to the word selected, fin to the word read
        if (bit == storage)// the condition that satisfies that checks if a word is found 
        {
            fin.close(); // close the file if the condition that the word has been selected is met
            return temporary; // returns the temporary word for our use
        }
        bit++; // else, the word incrementer will keep rising if the word has not been allocated to guess 
    }
}
void Hangman::storeWord(string x) // private storage of word
{
    response = x; // word storage in variable x
}
void Hangman::resetWord() // resets word for extra use after the fact
{
    response = ""; // resseting the word storage
    shown = ""; //how far the guesser has guessed back to reset the depth
    tries = 7; //resseting number of tries back to 7
}
void Hangman::displayLogo() // logo as first display
{
    cout << endl;
    cout << "        .---------------------------------------------------------------------------.\n"
        "        |   o     o      o     o      o    o o o    o       o      o     o      o   |\n"
        "        |   o     o    o   o   o o    o   o         o o   o o    o   o   o o    o   |\n"
        "        |   o     o   o     o  o  o   o   o         o   o   o   o     o  o  o   o   |\n"
        "        |   ooooooo   ooooooo  o   o  o   o   ooo   o       o   ooooooo  o   o  o   |\n"
        "        |   o     o   o     o  o    o o   o     o   o       o   o     o  o    o o   |\n"
        "        |   o     o   o     o  o     oo    o   o    o       o   o     o  o     oo   |\n"
        "        |   o     o   o     o  o      o     ooo     o       o   o     o  o      o   |\n"
        "        .---------------------------------------------------------------------------.\n";
}
void Hangman::drawHangman() // outputs the hangman drawing 
{
    if (tries == 6 || tries == 7) // if 6 tries left of if all tries left
    {
        cout << " ___________" << endl;
        cout << " |        }" << endl;
        cout << " |         " << endl;
        cout << "_|______________" << endl;
    }
    else if (tries == 5)
    {
        cout << " ___________" << endl;
        cout << " |        }" << endl;
        cout << " |       \\  " << endl;
        cout << "_|______________" << endl;
    }
    else if (tries == 4)
    {
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 " << endl;
        cout << "_|______________" << endl;
    }
    else if (tries == 3)
    {
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << "_|______________" << endl;
    }
    else if (tries == 2)
    {
        cout << " ___________" << endl;
        cout << " |        }" << endl;
        cout << " |      \\ 0 /" << endl;
        cout << " |        |" << endl;
        cout << "_|______________" << endl;
    }
    else if (tries == 1)
    {
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << " |         | " << endl;
        cout << " |        /  " << endl;
        cout << "_|______________" << endl;
    }
    else // final when all hope is lost
    {
        cout << " ___________" << endl;
        cout << " |         }" << endl;
        cout << " |       \\ 0 /" << endl;
        cout << " |         | " << endl;
        cout << " |        / \\ " << endl;
        cout << "_|______________" << endl;
    }
}
void Hangman::guess()
{
    char letter; //char for one symbol to guess
    int loop = 1; // for the while loop sequence later to iterate the condition once when guessing letters
    int discoveryCount = 0; //how many letters have been discovered through the guesses for number of letters and numbers
    for (int i = 0; i < (int)response.length(); i++) // cycle to iterate number of characters
    {
        if (isalnum(response[i])) //if letter A-Z or a number 1234567890 converts it into an under
        {
            shown = shown + '-'; // conversion of adding an underscore
            discoveryCount++; //have many underscores are needed depending on number of chars in a word
        }
        else
        {
            shown = shown + response[i]; //if does not correspond to a letter or number just leave it as it is
        }

    }
    cout << shown << '\n'; //show the puzzle with underscores to guess
    while (loop) // the loop equaling 1 to assess the user letter input
    {
        int track = 0; //try track of left user tries to guess
        int showntrack = 0; // how many underscores are left to win 
        cout << "Guess the letter, type ';' to exit " << '\n';
        cin >> letter;
        if (letter == ';')
        {
            break; // leaves the while loop if the user types this character
        }
        for (int x = 0; x < (int)response.size(); x++) // guess for loop checker
        {
            if (response[x] == letter || toupper(letter) == response[x] || tolower(letter) == response[x]) // if the user input matches
            {
                shown[x] = letter; // the guess matches the letter 
                track = 1; // user must still have a try left if the guess is correct
            }
            else if (response[x] != letter || toupper(letter) != response[x] || tolower(letter) != response[x]) // iteration to have a track of letter that are incorrect
            {
                track = track + 0; //if wrong tracker does not add to tries of user
            }

        }
        for (int y = 0; y < discoveryCount; y++) //how many letter or numbers have been discovered loop
        {
            if (shown[y] == '-' || shown[y] == ' ') // if there is an underscore than you have not won
            {
                showntrack = 1;
            }
            else if (shown[y] != '-') //you win when it is at a zero when there are no underscores and all letters filled into the word
            {
                showntrack = showntrack + 0;
            }

        }
        if (track == 0) // when the user guesses incorrectly then the track goes to 0 and draws a part of the hangman picture
        {
            tryMinus();
            drawHangman();
        }
        if (showntrack == 0 || shown == response) //no underscores and the shown word matches the response 
        {
            loop = 0; //the while loop to input the letter is broken 
            cout << "YOU WIIIIIIIIIINNNNNNNN" << '\n';
            cout << "The word was  " << response << '\n';

            cout << "Please attempt again" << '\n';
            resetWord(); // place back the word for use within all other words 
        }
        cout << shown << '\n'; // shows the final word
        if (tries > 0 && showntrack != 0 && response != shown) // when tries have not ended, and underscores are still present
        {
            cout << "You've got  " << tries << " left " << '\n';
        }
        if (tries == 0) // when user has gotten no attempts left and the hangman appears on screen
        {
            loop = 0; //breaks off the guess loop
            cout << "You have not guessed the word " << '\n';
            cout << "The word you had to guess was " << response << '\n';
            cout << "Try again next time " << '\n';
            resetWord(); //recycles word and puts it back just like in above statement
            cout << '\n';
            cout << '\n';
            cout << '\n';
            cout << '\n';
        }
    }
}
void Hangman::guess2()
{
    char letter; //char for one symbol to guess
    int loop = 1; // for the while loop sequence later to iterate the condition once when guessing letters
    int discoveryCount = 0; //how many letters have been discovered through the guesses for number of letters and numbers
    for (int i = 0; i < (int)temporary.length(); i++) // cycle to iterate number of characters
    {
        if (isalnum(temporary[i])) //if letter A-Z or a number 1234567890 converts it into an under
        {
            shown = shown + '-'; // conversion of adding an underscore
            discoveryCount++; //have many underscores are needed depending on number of chars in a word
        }
        else
        {
            shown = shown + temporary[i]; //if does not correspond to a letter or number just leave it as it is
        }

    }
    cout << shown << '\n'; //show the puzzle with underscores to guess
    while (loop) // the loop equaling 1 to assess the user letter input
    {
        int track = 0; //try track of left user tries to guess
        int showntrack = 0; // how many underscores are left to win 
        cout << "Guess the letter, type ';' to exit " << '\n';
        cin >> letter;
        if (letter == ';')
        {
            break; // leaves the while loop if the user types this character
        }
        for (int x = 0; x < (int)temporary.size(); x++) // guess for loop checker
        {
            if (temporary[x] == letter || toupper(letter) == temporary[x] || tolower(letter) == temporary[x]) // if the user input matches
            {
                shown[x] = letter; // the guess matches the letter 
                track = 1; // user must still have a try left if the guess is correct
            }
            else if (temporary[x] != letter || toupper(letter) != temporary[x] || tolower(letter) != temporary[x]) // iteration to have a track of letter that are incorrect
            {
                track = track + 0; //if wrong tracker does not add to tries of user
            }

        }
        for (int y = 0; y < discoveryCount; y++) //how many letter or numbers have been discovered loop
        {
            if (shown[y] == '-' || shown[y] == ' ') // if there is an underscore than you have not won
            {
                showntrack = 1;
            }
            else if (shown[y] != '-') //you win when it is at a zero when there are no underscores and all letters filled into the word
            {
                showntrack = showntrack + 0;
            }

        }
        if (track == 0) // when the user guesses incorrectly then the track goes to 0 and draws a part of the hangman picture
        {
            tryMinus();
            drawHangman();
        }
        if (showntrack == 0 || shown == temporary) //no underscores and the shown word matches the temporary 
        {
            loop = 0; //the while loop to input the letter is broken 
            cout << "YOU WIIIIIIIIIINNNNNNNN" << '\n';

            cout << "The word was  " << temporary << '\n';

            cout << "Please attempt again" << '\n';
            resetWord(); // place back the word for use within all other words 
        }
        cout << shown << '\n'; // shows the final word
        if (tries > 0 && showntrack != 0 && temporary != shown) // when tries have not ended, and underscores are still present
        {
            cout << "You've got  " << tries << " left " << '\n';
        }
        if (tries == 0) // when user has gotten no attempts left and the hangman appears on screen
        {
            loop = 0; //breaks off the guess loop
            cout << "You have not guessed the word " << '\n';
            cout << "The word you had to guess was " << temporary << '\n';
            cout << "Try again next time " << '\n';
            resetWord(); //recycles word and puts it back just like in above statement
            cout << '\n';
            cout << '\n';
            cout << '\n';
            cout << '\n';
        }
    }
}
int main()
{
    Hangman o;
    int loop = 1; //the loop to dsiplay the menu options
    int pick; //storage of the option the user chooses
    char input = 'j'; //as long as not j it will bypass to enter the menu
    string inputWord; // the word the user types on option number 1
    string userName;
    while (input == 'j')
    {
        o.displayLogo();
        cout << '\n';
        cout << "Please enter any key other than 'j' to enter the menu ";
        cin >> input;
        system("cls");
    }
    cout << "Enter your name   " << '\n';
    cin >> userName;
    while (loop)
    {
        cout << "Name of Player " << userName << '\n';
        cout << "------------------------------------------------------------------" << '\n';
        cout << "1. Input your own word to guess option (you won't see the word when typing to prevent cheating, after you type the word press enter and select option 3 to guess the word)" << '\n';
        cout << "2. Random shuffle of words to guess option " << '\n';
        cout << "3. If you picked number 1 and entered your word press this option " << '\n';
        cout << "4. Reset the game " << '\n';
        cout << "5. Exit the  game " << '\n';
        cout << "------------------------------------------------------------------" << '\n';
        cout << userName << ", Input your pick in this field ->   ";
        cin >> pick;
        if (pick == 1)
        {
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); //use of Windows.h library a describer of standard entering of data
            DWORD mode = 0; //dobule word data type unsigned 32 bit 
            GetConsoleMode(hStdin, &mode); //takes the input of console buffer
            SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT)); //character are printed when they are typed by the user, does not show on screen but records it
            cout << "Put in the secret phrase" << endl;
            cin.ignore();//clears the console inputs before getting the line
            getline(cin, inputWord); //takes the input line in
            SetConsoleMode(hStdin, mode);//setting the input again
            o.storeWord(inputWord);//stores the input word that the user typed
            cout << "YOUR SECRET WORD WAS SUCCESSFULLY INPUT!!" << endl;
            cout << '\n';
            cout << '\n';
        }
        if (pick == 2)
        {
            o.chooseWord();
            o.guess2();
        }
        if (pick == 3)
        {
            o.guess();
        }
        if (pick == 4)
        {
            o.resetWord();
            cout << "Reset has completed!!!! " << '\n' << '\n';
        }
        if (pick == 5)
        {
            cout << "Thanks for playing !" << '\n';
            loop = 0;
        }
    }

}
