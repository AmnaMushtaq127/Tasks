#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include<vector>
using namespace std;

// ANSI Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

// PLAYER BASE CLASS
class Player
{
protected:
    string name;
    int score;

public:
    Player(string n)
    {
        name = n;
        score = 0;
    }

    virtual char makeChoice() = 0;

    virtual void setLastMove(char) {}   // for polymorphism (used by Hard only)

    void increaseScore() { score++; }

    void resetScore() { score = 0; }

    int getScore() { return score; }

    string getName() { return name; }
};

//  HUMAN PLAYER 
class HumanPlayer : public Player
{
public:
    HumanPlayer(string n) : Player(n) {}

    char makeChoice()
    {
        char choice;

        while (true)
        {
            cout << YELLOW << "Enter move (R/P/S): " << RESET;
            cin >> choice;

            if (choice == 'r' || choice == 'R')
                return 'R';

            else if (choice == 'p' || choice == 'P')
                return 'P';

            else if (choice == 's' || choice == 'S')
                return 'S';

            cout << RED << "Invalid input!\n" << RESET;
        }
    }
};

// COMPUTER BASE CLASS
class ComputerPlayer : public Player
{
public:
    ComputerPlayer(string n) : Player(n) {}

    virtual char makeChoice() = 0;
};

//  EASY COMPUTER 
class EasyComputer : public ComputerPlayer
{
public:
    EasyComputer() : ComputerPlayer("Easy Computer") {}

    char makeChoice()
    {
        return 'R';
    }
};

// MEDIUM COMPUTER 
class MediumComputer : public ComputerPlayer
{
public:
    MediumComputer() : ComputerPlayer("Medium Computer") {}

    char makeChoice()
    {
        int r = rand() % 3;

        if (r == 0) return 'R';
        if (r == 1) return 'P';
        return 'S';
    }
};

//  HARD COMPUTER 
class HardComputer : public ComputerPlayer
{
private:
    char lastMove;

public:
    HardComputer() : ComputerPlayer("Hard Computer")
    {
        lastMove = ' ';
    }

    void setLastMove(char move)
    {
        lastMove = move;
    }

    char makeChoice()
    {
        if (lastMove == ' ')
        {
            int r = rand() % 3;
            if (r == 0) return 'R';
            if (r == 1) return 'P';
            return 'S';
        }

        if (lastMove == 'R') return 'P';
        if (lastMove == 'P') return 'S';
        return 'R';
    }
};
class RoundRecord
{
    char playerMove;
    char computerMove;
    string winner;
public:
    RoundRecord(char p, char c, string w)
    {
        playerMove = p;
        computerMove = c;
        winner = w;
    }
};

//  GAME CLASS 
class Game
{
private:
    HumanPlayer human;
    ComputerPlayer* computer;
    vector<RoundRecord> history;

public:
    Game(string name) : human(name)
    {
        computer = NULL;
    }

    string moveToWord(char m)
    {
        if (m == 'R') return "Rock";
        if (m == 'P') return "Paper";
        return "Scissors";
    }
    void addHistory(char p, char c, string w)
    {
        history.push_back(RoundRecord(p, c, w));
    }
    void displayHistory()
    {
        cout << "CYAN" << "\n=== ROUND HISTORY===\n" << RESET;
        for (int i = 0;i<=3;i++)
        {
            cout << "MAGNETA" << "\n Round" << i + 1 << endl;
            cout << "You :" << history[i].playerMove << "  Computer: " << history[i].computerMove<<" Winner: "<<history[i].winner << endl;
        }
    }

    int checkWinner(char h, char c)
    {
        if (h == c) return 0;

        if ((h == 'R' && c == 'S') ||
            (h == 'P' && c == 'R') ||
            (h == 'S' && c == 'P'))
            return 1;

        return -1;
    }

    void selectLevel(int level)
    {
        if (computer != NULL)
            delete computer;

        if (level == 1)
            computer = new EasyComputer();
        else if (level == 2)
            computer = new MediumComputer();
        else
            computer = new HardComputer();
    }

    void play()
        
    {
        history.clear();
        int level;

        cout << CYAN << "\n==== ROCK PAPER SCISSORS ====\n" << RESET;

        cout << "1. Easy\n2. Medium\n3. Hard\n";

        while (true)
        {
            cout << "Select level: ";
            cin >> level;

            if (level >= 1 && level <= 3)
                break;

            cout << RED << "Invalid level!\n" << RESET;
        }

        selectLevel(level);

        human.resetScore();
        computer->resetScore();

        char lastHuman = ' ';

        for (int i = 1; i <= 3; i++)
        {
            cout << MAGENTA << "\nRound " << i << RESET << endl;

            char hMove = human.makeChoice();

            computer->setLastMove(lastHuman);

            char cMove = computer->makeChoice();

            cout << BLUE << "Computer: " << moveToWord(cMove) << RESET << endl;

            int result = checkWinner(hMove, cMove);

            if (result == 1)
            {
                cout << GREEN << "You win!\n" << RESET;
                human.increaseScore();
                addtoHistory(hMove, cMove, " You win ");
            }
            else if (result == -1)
            {
                cout << RED << "Computer wins!\n" << RESET;
                computer->increaseScore();
                addtoHistory(hMove, cMove, " Computer wins ")
            }
            else
            {
                cout << YELLOW << "Tie!\n" << RESET;
                addtoHistory(hMove, cMove, " Tie Win ")
            }

            cout << "Score: " << human.getScore()
                << " - " << computer->getScore() << endl;

            lastHuman = hMove;
        }

        cout << CYAN << "\nFINAL RESULT: ";

        if (human.getScore() > computer->getScore())
            cout << "YOU WIN!\n";
        else if (human.getScore() < computer->getScore())
            cout << "COMPUTER WINS!\n";
        else
            cout << "DRAW!\n";

        cout << RESET;
        displayHistory();
    }

    ~Game()
    {
        delete computer;
    }
};

// MAIN 
int main()
{
    srand(time(0));

    string name;
    char again;

    cout << GREEN << "Enter your name: " << RESET;
    getline(cin, name);

    Game g(name);

    do
    {
        g.play();

        cout << "\nPlay again? (Y/N): ";
        cin >> again;

        if (again == 'y')
            again = 'Y';

    } while (again == 'Y');

    cout << CYAN << "Thanks for playing!\n" << RESET;

    return 0;
}