#include <iostream> // Include input-output stream library
#include <termios.h> // Include terminal I/O library
#include <unistd.h> // Include POSIX operating system API
#include <list> // Include list container
#include <vector> // Include vector container
#include <string> // Include string library
#include <cstdlib> // Include C standard library
#include <ctime> // Include time library

using namespace std; // Use the standard namespace

// Define directions for snake movement
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
public:
    // Constructor to initialize game variables
    SnakeGame() : dir(STOP), specialFoodExists(false), difficulty(2), width(20), height(10)
    {
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    }

    // Function to run the game
    void run() 
    {
        showStartingAnimation(); // Show starting animation
        setMapSize(); // Set the map size
        setDifficulty(); // Set the difficulty level
        chooseSnakeType(); // Choose the snake type
        chooseFoodType(); // Choose the food type
        showMapAnimation(); // Show map animation
        initialize(); // Initialize the game
        setTerminalRawMode(true); // Set terminal to raw mode

        int sleepDuration = getSleepDuration(); // Get sleep duration based on difficulty

        while (true) 
        {
            draw(); // Draw the game
            input(); // Handle user input
            update(); // Update the game state
            usleep(sleepDuration); // Sleep for a duration
        }

        setTerminalRawMode(false); // Reset terminal mode
    }

private:
    struct Position 
    {
        int x, y; // Position coordinates
    };
    Direction dir; // Current direction of the snake
    list<Position> snake; // List to store snake positions
    Position food; // Position of the food
    Position specialFood; // Position of the special food
    bool specialFoodExists; // Flag to check if special food exists
    string specialFoodChar = "\033[48;5;82mS\033[0m"; // Special food character
    vector<Position> obstacles; // Vector to store obstacle positions
    int difficulty; // Difficulty level
    int width; // Width of the map
    int height; // Height of the map
    string snakeChar; // Snake character
    string foodChar; // Food character

    // Function to set the map size
    void setMapSize() 
    {
        cout << "Enter the width of the map: ";
        cin >> width;
        cout << "Enter the height(width/2 for square shape) of the map: ";
        cin >> height;
    }

    // Function to set the difficulty level
    void setDifficulty() 
    {
        cout << "Select Difficulty Level:" << endl;
        cout << "1. Noob" << endl;
        cout << "2. Rookie" << endl;
        cout << "3. Elite" << endl;
        cout << "4. Pro" << endl;
        cout << "5. Sigma" << endl;
        cout << "6. Pro Sigma" << endl;
        cout << "Enter your choice: ";
        cin >> difficulty;
    }

    // Function to choose the snake type
    void chooseSnakeType() 
    {
        cout << "Select Snake Type:" << endl;
        cout << "1. Blue Block" << endl;
        cout << "2. Green Block" << endl;
        cout << "3. Yellow Block" << endl;
        cout << "4. Red Block" << endl;
        cout << "5. Purple Block" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) 
        {
            case 1: snakeChar = "\033[44mB\033[0m"; break;
            case 2: snakeChar = "\033[42mG\033[0m"; break;
            case 3: snakeChar = "\033[43mY\033[0m"; break;
            case 4: snakeChar = "\033[41mR\033[0m"; break;
            case 5: snakeChar = "\033[45mP\033[0m"; break;
            default: snakeChar = "\033[44m \033[0m"; break;
        }
    }

    // Function to choose the food type
    void chooseFoodType() 
    {
        cout << "Select Food Type:" << endl;
        cout << "1. Red Block" << endl;
        cout << "2. White Block" << endl;
        cout << "3. Cyan Block" << endl;
        cout << "4. Magenta Block" << endl;
        cout << "5. Yellow Block" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1: foodChar = "\033[48;5;196mR\033[0m"; break;
            case 2: foodChar = "\033[47mW\033[0m"; break;
            case 3: foodChar = "\033[46mC\033[0m"; break;
            case 4: foodChar = "\033[48;5;201mM\033[0m"; break;
            case 5: foodChar = "\033[48;5;226mY\033[0m"; break;
            default: foodChar = "\033[41mR\033[0m"; break;
        }
    }

    // Function to generate food at a random position
    void generateFood() 
    {
        bool validPosition = false;
        while (!validPosition) 
        {
            food = {rand() % height, rand() % width};
            validPosition = true;

            for (auto part : snake) 
            {
                if (food.x == part.x && food.y == part.y) 
                {
                    validPosition = false;
                    break;
                }
            }

            for (auto obstacle : obstacles) 
            {
                if (food.x == obstacle.x && food.y == obstacle.y) 
                {
                    validPosition = false;
                    break;
                }
            }
        }
    }

    // Function to generate special food at a random position
    void generateSpecialFood() 
    {
        bool validPosition = false;
        while (!validPosition) 
        {
            specialFood = {rand() % height, rand() % width};
            validPosition = true;

            for (auto part : snake) 
            {
                if (specialFood.x == part.x && specialFood.y == part.y) 
                {
                    validPosition = false;
                    break;
                }
            }

            for (auto obstacle : obstacles) 
            {
                if (specialFood.x == obstacle.x && specialFood.y == obstacle.y) 
                {
                    validPosition = false;
                    break;
                }
            }

            if (specialFood.x == food.x && specialFood.y == food.y) 
            {
                validPosition = false;
            }
        }
        specialFoodExists = true;
    }

    // Function to initialize the game
    void initialize() 
    {
        dir = STOP;
        snake.clear();
        snake.push_back({height / 2, width / 2});
        obstacles.clear();
        specialFoodExists = false;

        if (difficulty >= 3) 
        {
            int numObstacles = (difficulty == 3) ? height / 5 : (difficulty == 4) ? height / 2 : 0;
            for (int i = 0; i < numObstacles; ++i) 
            {
                obstacles.push_back({rand() % height, rand() % width});
            }
        }
        generateFood();
    }

    // Function to draw the game
    // Function to draw the game
    void draw() {
        system("clear"); // Clear the terminal screen
        for (int i = 0; i < height + 2; ++i) 
        {
            for (int j = 0; j < width + 2; ++j) 
            { 
                if (i == 0 || i == height + 1) 
                {
                    cout << "#"; // Draw the top and bottom borders
                } 
                else if (j == 0 || j == width + 1) 
                {
                    cout << "#"; // Draw the left and right borders
                } 
                else if (difficulty == 1) 
                {
                    cout << "Error Found : NOOB!!" << endl; // Display error message for difficulty level 1
                    bool isFood = false;
                    if (isFood);
                    else 
                    {
                        bool isSnake = false;
                        for (auto part : snake) 
                        {
                            if (part.x == i && part.y == j) 
                            {
                                isSnake = true;
                                break;
                            }
                        }
                        if (isSnake) 
                        {
                            cout << snakeChar; // Draw the snake
                        } 
                        else 
                        {
                            bool isObstacle = false;
                            for (auto obstacle : obstacles) 
                            {
                                if (obstacle.x == i && obstacle.y == j) 
                                {
                                    isObstacle = true;
                                    break;
                                }
                            }
                            if (isObstacle) 
                            {
                                cout << "\033[45m \033[0m"; // Draw the obstacles
                            } 
                            else 
                            {
                                cout << " "; // Draw empty space
                            }
                        }
                    }
                } 
                else if (i == food.x && j == food.y) 
                {
                    cout << foodChar; // Draw the food
                } 
                else if (specialFoodExists && i == specialFood.x && j == specialFood.y) 
                {
                    cout << specialFoodChar; // Draw the special food
                } 
                else 
                {
                    bool isSnake = false;
                    for (auto part : snake) 
                    {
                        if (part.x == i && part.y == j) 
                        {
                            isSnake = true;
                            break;
                        }
                    }
                    if (isSnake)
                    {
                        cout << snakeChar; // Draw the snake
                    } 
                    else 
                    {
                        bool isObstacle = false;
                        for (auto obstacle : obstacles) 
                        {
                            if (obstacle.x == i && obstacle.y == j) 
                            {
                                isObstacle = true;
                                break;
                            }
                        }
                        if (isObstacle) 
                        {
                            cout << "\033[45m \033[0m"; // Draw the obstacles
                        } 
                        else 
                        {
                            cout << " "; // Draw empty space
                        }
                    }
                }
            }
            cout << endl; // Move to the next line
        }
        cout << "Score: " << snake.size() - 1 << endl; // Display the score
        cout << "Use W/A/S/D to move. Press X to quit. Press R to restart. Press I to show Instructions" << endl; // Display instructions
    }

    // Function to set terminal to raw mode
    void setTerminalRawMode(bool enable) 
    {
        static struct termios oldt, newt;
        if (enable) 
        {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } 
        else 
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }

    // Function to check if a key is pressed
    bool kbhit() 
    {
        struct timeval tv = { 0L, 0L };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    }

    // Function to get a character from the terminal
    char getch() 
    {
        char buf = 0;
        if (read(STDIN_FILENO, &buf, 1) < 0) 
        {
            perror("read()");
        }
        return buf;
    }

    // Function to handle user input
    void input() 
    {
        if (kbhit()) 
        {
            char key = getch();
            if (difficulty == 6) 
            {
                switch (key) 
                {
                case 'x': exit(0);
                case 'r': initialize(); break;
                case 'i': showInstructions(); break;
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    int randomDir = rand() % 4;
                    switch (randomDir) 
                    {
                    case 0: dir = UP; break;
                    case 1: dir = LEFT; break;
                    case 2: dir = DOWN; break;
                    case 3: dir = RIGHT; break;
                    }
                    break;
                }
            } 
            else 
            {
                switch (key) 
                {
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
    void update() 
    {
        Position head = snake.front();
        switch (dir) 
        {
        case UP: head.x--; break;
        case DOWN: head.x++; break;
        case LEFT: head.y--; break;
        case RIGHT: head.y++; break;
        default: return;
        }

        if (difficulty == 2 || difficulty == 3 || difficulty == 6) 
        { 
            if (head.x <= 0) head.x = height;
            else if (head.x >= height + 1) head.x = 1;
            if (head.y <= 0) head.y = width;
            else if (head.y >= width + 1) head.y = 1;
        } 
        else 
        {
            if (head.x <= 0 || head.x >= height + 1 || head.y <= 0 || head.y >= width + 1) 
            {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        for (auto part : snake) 
        {
            if (head.x == part.x && head.y == part.y) 
            {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        for (auto obstacle : obstacles) 
        {
            if (head.x == obstacle.x && head.y == obstacle.y) 
            {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        snake.push_front(head);
        if (head.x == food.x && head.y == food.y) 
        {
            generateFood();
        } 
        else if (specialFoodExists && head.x == specialFood.x && head.y == specialFood.y) 
        {
            specialFoodExists = false;
            for (int i = 0; i < 2; ++i) 
            {
                snake.push_back(snake.back());
            }
        } 
        else 
        {
            snake.pop_back();
        }

        if (difficulty == 4) 
        { 
            for (auto& obstacle : obstacles) 
            {
                int moveDirection = rand() % 4;
                switch (moveDirection) {
                case 0: if (obstacle.x > 1) obstacle.x--; break;
                case 1: if (obstacle.x < height) obstacle.x++; break; 
                case 2: if (obstacle.y > 1) obstacle.y--; break; 
                case 3: if (obstacle.y < width) obstacle.y++; break; 
                }
            }
        }
        if (difficulty == 5) 
        {
            switch (dir) 
            {
            case STOP: break;
            case UP: food.x = head.x - 2; food.y = head.y; break;
            case DOWN: food.x = head.x + 2; food.y = head.y; break;
            case LEFT: food.x = head.x; food.y = head.y - 2; break;
            case RIGHT: food.x = head.x; food.y = head.y + 2; break;
            }
        }
        if (difficulty == 6) 
        { 
            if (abs(head.x - food.x) <= 5 && abs(head.y - food.y) <= 5) 
            {
                generateFood();
            }
        }

        if (difficulty >= 1 && difficulty <= 4 && !specialFoodExists && rand() % 100 < 1) 
        { 
            generateSpecialFood();
        }
        if (difficulty == 3 && snake.size() == 5) 
        {
            cout << "\033[44mAccessing DAIICT servers...Exit the terminal otherwise it will not good for you\033[0m" << endl;
            usleep(200000); 
            system("clear");
        }
    }

    // Function to show starting animation
    void showStartingAnimation() 
    {
        system("clear");
        string text = "SNAKE GAME";
        string displayText = "          ";
        for (int i = 0; i < 10; ++i) 
        {
            displayText[i] = text[i];
            system("clear");
            for (int j = 0; j < 10; ++j) 
            {
                if (j == 2) 
                {
                    cout << displayText;
                } 
                else 
                {
                    cout << "     ";
                }
                cout << endl;
            }
            usleep(200000);
        }
    }

    // Function to show map animation
    void showMapAnimation() 
    {
        system("clear");
        for (int i = height; i >= 0; --i) 
        {
            system("clear");
            for (int j = 0; j < height + 2; ++j) 
            {
                for (int k = 0; k < width + 2; ++k) 
                {
                    if (j == 0 || j == height + 1) 
                    {
                        cout << "#";
                    } 
                    else if (k == 0 || k == width + 1) 
                    {
                        cout << "#";
                    } 
                    else if (j == i) 
                    {
                        cout << snakeChar;
                    } 
                    else 
                    {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            usleep(100000);
        }
    }

    // Function to get sleep duration based on difficulty
    int getSleepDuration() 
    {
        switch (difficulty) 
        {
            case 1: return 100000; // Noob
            case 2: return 80000;  // Rookie
            case 3: return 60000;  // Elite
            case 4: return 40000;  // Pro
            case 5: return 20000;  // Sigma
            case 6: return 10000;  // Pro Sigma
            default: return 100000; // Default case
        }
    }

    // Function to show game instructions
    void showInstructions() 
    {
        system("clear");
        cout << "Game Instructions:" << endl;
        cout << "Difficulty Level: ";
        switch (difficulty) 
        {
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
        cout << "Map Size: " << width << "x" << height << endl;
        cout << "Use W/A/S/D to move. Press X to quit. Press R to restart." << endl;
        cout << "Press any key to return to the game." << endl;
        getch();
    }
};

int main() 
{
    SnakeGame game; // Create a SnakeGame object
    game.run(); // Run the game
    return 0;
}
