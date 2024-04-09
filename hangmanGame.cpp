
#include <iostream> 
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// Define the Game interface with two functions: StartGame and CheckLetter
class Game {
public:
    virtual void StartGame() = 0; // Function to start the game
    virtual bool CheckLetter(char guessLetter) = 0; // Function to check if the guessed letter is correct
};

// Implement the HangmanGame class derived from the Game class
class HangmanGame : public Game {
    // Declare the private variables that are going to be used
private:
    std::string secretWord; // Stores the secret word to be guessed by the player
    int attempts = 10; // Stores the number of attempts allowed for guessing
    std::vector<char> guesses; // Stores the guessed letters
    std::vector<char> wordToGuess; // Stores the characters of the secret word
    std::vector<char> revealedWord; // Stores the revealed characters of the secret word
    std::vector<char> incorrectGuesses; // Stores the incorrect guessed letters
    bool wordGuessed = false; // Indicates whether the word has been guessed

public:
    // Constructor to initialize the HangmanGame object with a vector of possible words
    HangmanGame(const std::vector<std::string>& words) {
        if (!words.empty()) { // Check if the provided vector of words is not empty
            srand(time(0)); // Initialize the random number generator using the current time
            int index = rand() % words.size(); // Generate a random index number within the range of the vector size
            secretWord = words[index]; // Assign the randomly selected word from the vector to the secretWord variable
        }
        else {
            std::cerr << "Error: Empty word list." << std::endl;
            return;
        }

        std::transform(secretWord.begin(), secretWord.end(), secretWord.begin(), ::toupper); // Convert the secret word to uppercase, so the program will not identify the same letter as different answers depending on whether it is lowercase or uppercase.

        // Initialize the revealedWord vector with underscores for letters and preserve non-letter characters
        for (char c : secretWord) {
            if (isalpha(c))
                revealedWord.push_back('_');
            else
                revealedWord.push_back(c);
            wordToGuess.push_back(c); // Store each character of the secret word
        }
    }

    // Function to start the game
    void StartGame() override {
        // Prints introducing lines of text for the user to the screen.
        std::cout << "Welcome to Hangman!" << std::endl;
        std::cout << "Try to guess the secret animal." << std::endl;
        std::cout << "You have " << attempts << " attempts." << std::endl;

        // Continue the game while the word has not been guessed and there are still attempts left
        while (!wordGuessed && attempts > 0) {
            std::cout << "" << std::endl;
            std::cout << "Enter a letter: ";
            DisplayWord(); // Display the current state of the word
            char guessLetter;
            std::cin >> guessLetter; // Get user input for the guessed letter

            if (!CheckLetter(guessLetter)) { // Check if the guessed letter is correct
                attempts--; // Decrement the number of attempts if the guess letter is incorrect
                std::cout << "Incorrect! You have " << attempts << " attempts left." << std::endl;

                incorrectGuesses.push_back(guessLetter); // Add incorrect guess to the vector
                std::cout << "Incorrect guesses: ";
                for (char c : incorrectGuesses) {
                    std::cout << c << " ";
                }
                std::cout << std::endl;
                

            }

            if (std::find(revealedWord.begin(), revealedWord.end(), '_') == revealedWord.end()) {
                wordGuessed = true; // The word is guessed correctly
                std::cout << "Congratulations! You've guessed the word: " << secretWord << std::endl;
            }
        }

        // Displays message if the user runs of attempts before guessing the word
        if (!wordGuessed)
            std::cout << "Sorry, you've run out of attempts. The word was: " << secretWord << std::endl;

        std::cout << "Thank you for playing Hangman!" << std::endl;
    }

    // Function to check if the guessed letter is correct
    bool CheckLetter(char guessLetter) override {
        guessLetter = toupper(guessLetter); // Convert the guessed letter to uppercase

        // Check if the letter has already been guessed
        if (std::find(guesses.begin(), guesses.end(), guessLetter) != guesses.end()) {
            std::cout << "You've already guessed that letter." << std::endl;
            return true; // Return true indicating the letter has been guessed
        }

        guesses.push_back(guessLetter); // Add the guessed letter to the vector of guesses

        bool letterFound = false;
        for (size_t i = 0; i < wordToGuess.size(); i++) { // Iterate through each character of the secret word
            if (toupper(wordToGuess[i]) == guessLetter) { // Check if the guessed letter matches the character of the secret word
                revealedWord[i] = secretWord[i]; // Reveal the letter in the revealed word
                letterFound = true;
            }
        }

        if (!letterFound) // Check if the guessed letter was not found in the secret word
            return false;

        return true; // Return true indicating the letter was found in the word
    }

    // Function to display the current state of the word
    void DisplayWord() {
        for (char c : revealedWord) {
            std::cout << c << " "; // Display each character of the revealed word
        }
        std::cout << std::endl;
    }
};


// Main function to create a HangmanGame object and start the game
int main() {
    std::vector<std::string> words = {"hippopotamus", "elephant", "rhinoceros", "peacock", "parrot", "cat", "porcupine", "crocodile", "hornet", "penguin"};
    HangmanGame game(words); // Create a HangmanGame object with a list of possible words
    game.StartGame(); // Start the game
    return 0;
}
