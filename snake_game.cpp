// Include necessary headers
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Use the standard namespace
using namespace std;

// Define the possible directions for the snake
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

// Define the SnakeGame class
class SnakeGame {
public:
    // Constructor to initialize the game
    SnakeGame() : dir(STOP), specialFoodExists(false), diff(1), w(20), h(10) {
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    }

    // Function to run the game
    void run() {
        showStartingAnimation(); // Show the starting animation
        setMapSize(); // Set the map size
        setDifficulty(); // Set the difficulty level
        chooseSnakeType(); // Choose the snake type
        chooseFoodType(); // Choose the food type
        showMapAnimation(); // Show the map animation
        initialize(); // Initialize the game
        setTerminalRawMode(true); // Set the terminal to raw mode

        int sleepDur = getSleepDuration(); // Get the sleep duration based on difficulty

        while (true) {
            draw(); // Draw the game
            input(); // Handle user input
            update(); // Update the game state
            usleep(sleepDur); // Sleep for the specified duration
        }

        setTerminalRawMode(false); // Reset the terminal mode
    }

private:
    // Define a structure for positions
    struct Pos {
        int x, y;
    };

    Direction dir; // Current direction of the snake
    list<Pos> snake; // List of positions representing the snake
    Pos food; // Position of the food
    Pos specialFood; // Position of the special food
    bool specialFoodExists; // Flag to check if special food exists
    string specialFoodChar = "\033[48;5;82mS\033[0m"; // Character for special food
    vector<Pos> obstacles; // Vector of positions representing obstacles
    int diff; // Difficulty level
    int w; // Width of the map
    int h; // Height of the map
    string snakeChar; // Character for the snake
    string foodChar; // Character for the food

    // Function to set the map size
    void setMapSize() {
        cout << "Enter the width of the map: ";
        cin >> w;
        cout << "Enter the height(width/2 for square shape) of the map: ";
        cin >> h;
    }

    // Function to set the difficulty level
    void setDifficulty() {
        cout << "Select Difficulty Level:" << endl;
        cout << "1. Noob" << endl;
        cout << "2. Rookie" << endl;
        cout << "3. Elite" << endl;
        cout << "4. Pro" << endl;
        cout << "5. Sigma" << endl;
        cout << "6. Pro Sigma" << endl;
        cout << "Enter your choice: ";
        cin >> diff;
    }

    // Function to choose the snake type
    void chooseSnakeType() {
        cout << "Select Snake Type:" << endl;
        cout << "1. Blue Block" << endl;
        cout << "2. Green Block" << endl;
        cout << "3. Yellow Block" << endl;
        cout << "4. Red Block" << endl;
        cout << "5. Purple Block" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: snakeChar = "\033[44mB\033[0m"; break;
            case 2: snakeChar = "\033[42mG\033[0m"; break;
            case 3: snakeChar = "\033[43mY\033[0m"; break;
            case 4: snakeChar = "\033[41mR\033[0m"; break;
            case 5: snakeChar = "\033[45mP\033[0m"; break;
            default: snakeChar = "\033[44m \033[0m"; break;
        }
    }

    // Function to choose the food type
    void chooseFoodType() {
        cout << "Select Food Type:" << endl;
        cout << "1. Red Block" << endl;
        cout << "2. White Block" << endl;
        cout << "3. Cyan Block" << endl;
        cout << "4. Magenta Block" << endl;
        cout << "5. Yellow Block" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: foodChar = "\033[48;5;196mR\033[0m"; break;
            case 2: foodChar = "\033[47mW\033[0m"; break;
            case 3: foodChar = "\033[46mC\033[0m"; break;
            case 4: foodChar = "\033[48;5;201mM\033[0m"; break;
            case 5: foodChar = "\033[48;5;226mY\033[0m"; break;
            default: foodChar = "\033[41mR\033[0m"; break;
        }
    }

    // Function to generate food at a random position
    void generateFood() {
        bool validPos = false;
        while (!validPos) {
            food = {rand() % h, rand() % w};
            validPos = true;

            for (auto part : snake) {
                if (food.x == part.x && food.y == part.y) {
                    validPos = false;
                    break;
                }
            }

            for (auto obs : obstacles) {
                if (food.x == obs.x && food.y == obs.y) {
                    validPos = false;
                    break;
                }
            }
        }
    }

    // Function to generate special food at a random position
    void generateSpecialFood() {
        bool validPos = false;
        while (!validPos) {
            specialFood = {rand() % h, rand() % w};
            validPos = true;

            for (auto part : snake) {
                if (specialFood.x == part.x && specialFood.y == part.y) {
                    validPos = false;
                    break;
                }
            }

            for (auto obs : obstacles) {
                if (specialFood.x == obs.x && specialFood.y == obs.y) {
                    validPos = false;
                    break;
                }
            }

            if (specialFood.x == food.x && specialFood.y == food.y) {
                validPos = false;
            }
        }
        specialFoodExists = true;
    }

    // Function to initialize the game
    void initialize() {
        dir = STOP;
        snake.clear();
        snake.push_back({h / 2, w / 2});
        obstacles.clear();
        specialFoodExists = false;

        if (diff >= 3) {
            int numObs = (diff == 3) ? h / 5 : (diff == 4) ? h / 2 : 0;
            for (int i = 0; i < numObs; ++i) {
                obstacles.push_back({rand() % h, rand() % w});
            }
        }
        generateFood();
    }

    // Function to draw the game
    void draw() {
        system("clear");
        for (int i = 0; i < h + 2; ++i) {
            for (int j = 0; j < w + 2; ++j) {
                if (i == 0 || i == h + 1) {
                    cout << "#";
                } else if (j == 0 || j == w + 1) {
                    cout << "#";
                } else if (diff == 1) {
                    cout << "Error Found : NOOB!!" << endl;
                    bool isFood = false;
                    if (isFood);
                    else {
                        bool isSnake = false;
                        for (auto part : snake) {
                            if (part.x == i && part.y == j) {
                                isSnake = true;
                                break;
                            }
                        }
                        if (isSnake) {
                            cout << snakeChar;
                        } else {
                            bool isObs = false;
                            for (auto obs : obstacles) {
                                if (obs.x == i && obs.y == j) {
                                    isObs = true;
                                    break;
                                }
                            }
                            if (isObs) {
                                cout << "\033[45m \033[0m";
                            } else {
                                cout << " ";
                            }
                        }
                    }
                } else if (i == food.x && j == food.y) {
                    cout << foodChar;
                } else if (specialFoodExists && i == specialFood.x && j == specialFood.y) {
                    cout << specialFoodChar;
                } else {
                    bool isSnake = false;
                    for (auto part : snake) {
                        if (part.x == i && part.y == j) {
                            isSnake = true;
                            break;
                        }
                    }
                    if (isSnake) {
                        cout << snakeChar;
                    } else {
                        bool isObs = false;
                        for (auto obs : obstacles) {
                            if (obs.x == i && obs.y == j) {
                                isObs = true;
                                break;
                            }
                        }
                        if (isObs) {
                            cout << "\033[45m \033[0m";
                        } else {
                            cout << " ";
                        }
                    }
                }
            }
            cout << endl;
        }
        cout << "Score: " << snake.size() - 1 << endl;
        cout << "Use W/A/S/D to move. Press X to quit. Press R to restart. Press I to show Instructions" << endl;
    }

    // Function to set the terminal to raw mode
    void setTerminalRawMode(bool enable) {
        static struct termios oldt, newt;
        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }

    // Function to check if a key has been pressed
    bool kbhit() {
        struct timeval tv = { 0L, 0L };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    }

    // Function to get a character from the terminal
    char getch() {
        char buf = 0;
        if (read(STDIN_FILENO, &buf, 1) < 0) {
            perror("read()");
        }
        return buf;
    }

    // Function to handle user input
    void input() {
        if (kbhit()) {
            char key = getch();
            if (diff == 6) {
                switch (key) {
                case 'x': exit(0);
                case 'r': initialize(); break;
                case 'i': showInstructions(); break;
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    int randomDir = rand() % 4;
                    switch (randomDir) {
                    case 0: dir = UP; break;
                    case 1: dir = LEFT; break;
                    case 2: dir = DOWN; break;
                    case 3: dir = RIGHT; break;
                    }
                    break;
                }
            } else {
                switch (key) {
                case 'w': dir = UP; break;
                case 'a': dir = LEFT; break;
                case 's': dir = DOWN; break;
                case 'd': dir = RIGHT; break;
                case 'x': exit(0);
                case 'r': initialize(); break;
                case 'i': showInstructions(); break;
                }
            }
        }
    }

    // Function to update the game state
    void update() {
        Pos head = snake.front();
        switch (dir) {
        case UP: head.x--; break;
        case DOWN: head.x++; break;
        case LEFT: head.y--; break;
        case RIGHT: head.y++; break;
        default: return;
        }

        if (diff == 2 || diff == 3 || diff == 6) { 
            if (head.x <= 0) head.x = h;
            else if (head.x >= h + 1) head.x = 1;
            if (head.y <= 0) head.y = w;
            else if (head.y >= w + 1) head.y = 1;
        } else {
            if (head.x <= 0 || head.x >= h + 1 || head.y <= 0 || head.y >= w + 1) {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        for (auto part : snake) {
            if (head.x == part.x && head.y == part.y) {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        for (auto obs : obstacles) {
            if (head.x == obs.x && head.y == obs.y) {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        snake.push_front(head);
        if (head.x == food.x && head.y == food.y) {
            generateFood();
        } else if (specialFoodExists && head.x == specialFood.x && head.y == specialFood.y) {
            specialFoodExists = false;
            for (int i = 0; i < 2; ++i) {
                snake.push_back(snake.back());
            }
        } else {
            snake.pop_back();
        }

        if (diff == 4) { 
            for (auto& obs : obstacles) {
                int moveDir = rand() % 4;
                switch (moveDir) {
                case 0: if (obs.x > 1) obs.x--; break;
                case 1: if (obs.x < h) obs.x++; break; 
                case 2: if (obs.y > 1) obs.y--; break; 
                case 3: if (obs.y < w) obs.y++; break; 
                }
            }
        }
        if (diff == 5) {
            switch (dir) {
                case STOP: break;
            case UP: food.x = head.x - 2; food.y = head.y; break;
            case DOWN: food.x = head.x + 2; food.y = head.y; break;
            case LEFT: food.x = head.x; food.y = head.y - 2; break;
            case RIGHT: food.x = head.x; food.y = head.y + 2; break;
            }
        }
        if (diff == 6) { 
            if (abs(head.x - food.x) <= 5 && abs(head.y - food.y) <= 5) {
                generateFood();
            }
        }

        if (diff >= 1 && diff <= 4 && !specialFoodExists && rand() % 100 < 1) { 
            generateSpecialFood();
        }
        if (diff == 3 && snake.size() == 5) {
            cout << "\033[44mAccessing DAIICT servers...Exit the terminal otherwise it will not good for you\033[0m" << endl;
            usleep(200000); 
            system("clear");
        }
    }

    // Function to show the starting animation
    void showStartingAnimation() {
        system("clear");
        string text = "SNAKE GAME";
        string displayText = "               ";
        for (int i = 0; i < 10; ++i) {
            displayText[i] = text[i];
            system("clear");
            for (int j = 0; j < 10; ++j) {
                if (j == 2) {
                    cout << displayText;
                } else {
                    cout << "     ";
                }
                cout << endl;
            }
            usleep(200000);
        }
    }

    // Function to show the map animation
    void showMapAnimation() {
        system("clear");
        for (int i = h; i >= 0; --i) {
            system("clear");
            for (int j = 0; j < h + 2; ++j) {
                for (int k = 0; k < w + 2; ++k) {
                    if (j == 0 || j == h + 1) {
                        cout << "#";
                    } else if (k == 0 || k == w + 1) {
                        cout << "#";
                    } else if (j == i) {
                        cout << snakeChar;
                    } else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            usleep(100000);
        }
    }

    // Function to get the sleep duration based on difficulty
    int getSleepDuration() {
        switch (diff) {
            case 2: return 100000;
            case 3: return 50000;
            case 4: return 50000;
            case 5: return 30000;
            case 6: return 120000;
            default: return 100000;
        }
    }

    // Function to show the game instructions
    void showInstructions() {
        system("clear");
        cout << "Game Instructions:" << endl;
        cout << "Difficulty Level: ";
        switch (diff) {
            case 1:
                cout << "Noob" << endl;
                cout << "This is not your cup of tea Kid" << endl;
                break;
            case 2:
                cout << "Rookie" << endl;
                cout << "Press Buttons and Play, Dont Panic Rookie, Take Your Time" << endl;
                break;
            case 3:
                cout << "Elite" << endl;
                cout << "HAHA, Boy you are on the journey, but be careful, don't eat too much" << endl;
                break;
            case 4:
                cout << "Pro" << endl;
                cout << "Hey Man,I think you have some balls, Keep it up broski you surely make it" << endl;
                break;
            case 5:
                cout << "Sigma" << endl;
                cout << "Hey Man, You think you are sigma?, Hah! Tate's Brainrots" << endl;
                break;
            case 6:
                cout << "Pro Sigma" << endl;
                cout << "Hey Hey, This shit is for some real OGs!! ya sure? you are on the right place Man, Show me some Skills bruh!!" << endl;
                break;
        }
        cout << "Snake Color: " << snakeChar << endl;
        cout << "Food Color: " << foodChar << endl;
        cout << "Map Size: " << w << "x" << h << endl;
        cout << "Use W/A/S/D to move. Press X to quit. Press R to restart." << endl;
        cout << "Press any key to return to the game." << endl;
        getch();
    }
};

// Main function to start the game
int main() {
    SnakeGame game; // Create a SnakeGame object
    game.run(); // Run the game
    return 0; // Return 0 to indicate successful execution
}
