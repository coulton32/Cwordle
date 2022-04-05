#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <regex>
// by github/coulton32 
std::string getNewWord() {
    srand(time(NULL));
    std::vector<std::string> words;
    std::ifstream file("wordlist.txt"); // wordlist.txt is from Wordle
    std::string line;
    while (getline(file, line)) words.push_back(line);
    return words[rand() % words.size()];
}
std::string guessWord() {
    std::cout << "Guess the word:";
    std::string a;
    std::cin >> a;
    if (a.length() != 5) {
        std::cout << "5 letter words only please !\n";
        a = guessWord();
    }
    else {
        std::ifstream ifs("wordlist.txt");
        std::regex e{ "\\b" + a + "\\b" };
        std::string line;
        while (getline(ifs, line))
        {
            if (regex_search(line, e)) {
                return a;
            }
        }
        std::cout << "Not in the word list. Try again.\n";
        a = guessWord();
        return a;
    }

}
std::string checkDupe(std::string s) {
    std::string p;
    bool alphabets[26];
    memset(alphabets, false, 26);
    for (int i = 0; i < s.size(); i++)
    {
        if (alphabets[s.at(i) - 'a'] == false)
        {
            alphabets[s.at(i) - 'a'] = true;
            p.push_back(s.at(i));
        }
    }
    return p;
}
int main() {
    std::cout << "Hello Cwordle!\n";
    std::string chosenWord = getNewWord();
    // begin guess routine
    std::string correct; // correct letters
    std::string wrongSpot; // correct letters but wrong space
    std::string notInWord; // letters that are not in the word at all
    for (int b = 0; b < 6; b++) {
        std::string guessedWord = guessWord();

        if (guessedWord == chosenWord) {
            std::cout << "\nCorrect! The word was: " << chosenWord;
            return 0;
        }
        // Check letters in the correct spaces
        for (int i = 0; i < 5; i++) {
            if (chosenWord[i] == guessedWord[i]) {
                correct.push_back(chosenWord[i]);
            }
            else if (chosenWord[i] != guessedWord[i]) {
                correct.push_back(0x23);
            }
        }
        // Check for existing letters in the wrong space but in the word
        // Set up this way in order to not give away the word
        for (int y = 0; y < 5; y++) {
            if (chosenWord[4] == guessedWord[y]) {
                wrongSpot.push_back(guessedWord[y]);
            }
            else if (chosenWord[2] == guessedWord[y]) {
                wrongSpot.push_back(guessedWord[y]);
            }
            else if (chosenWord[3] == guessedWord[y]) {
                wrongSpot.push_back(guessedWord[y]);
            }
            else if (chosenWord[0] == guessedWord[y]) {
                wrongSpot.push_back(guessedWord[y]);
            }
            else if (chosenWord[1] == guessedWord[y]) {
                wrongSpot.push_back(guessedWord[y]);
            }
            else {
                notInWord.push_back(guessedWord[y]);
                notInWord = checkDupe(notInWord);
            }
        }
        wrongSpot = checkDupe(wrongSpot);
        //return correct letters
        std::cout << "Letters in the correct spots: " << correct << "\n";
        correct.clear();
        std::cout << "Letters in the word: " << wrongSpot << "\n";
        std::cout << "Letters not in the word at all: " << notInWord << "\n\n";
    }
    std::cout << "Out of guesses! The correct word was: " << chosenWord;
}