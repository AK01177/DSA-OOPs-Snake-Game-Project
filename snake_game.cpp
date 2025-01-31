#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
public:
    SnakeGame() : dir(STOP), specialFoodExists(false), difficulty(1), width(20), height(10) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void run() {
        showStartingAnimation();
        setMapSize();
        setDifficulty();
        chooseSnakeType();
        chooseFoodType();
        showMapAnimation();
        initialize();
        setTerminalRawMode(true);

        int sleepDuration = getSleepDuration();

        while (true) {
            draw();
            input();
            update();
            usleep(sleepDuration);
        }

        setTerminalRawMode(false);
    }

private:
    struct Position {
        int x, y;
    };
    Direction dir;
    list<Position> snake;
    Position food;
    Position specialFood;
    bool specialFoodExists;
    string specialFoodChar = "\033[48;5;82mS\033[0m"; 
    vector<Position> obstacles;
    int difficulty;
    int width;
    int height;
    string snakeChar;
    string foodChar;
    

    void setMapSize() {
        cout << "Enter the width of the map: ";
        cin >> width;
        cout << "Enter the height(width/2 for square shape) of the map: ";
        cin >> height;
    }

    void setDifficulty() {
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

    void generateSpecialFood() {
        bool validPosition = false;
        while (!validPosition) {
            specialFood = {rand() % height, rand() % width};
            validPosition = true;

            for (auto part : snake) {
                if (specialFood.x == part.x && specialFood.y == part.y) {
                    validPosition = false;
                    break;
                }
            }

            for (auto obstacle : obstacles) {
                if (specialFood.x == obstacle.x && specialFood.y == obstacle.y) {
                    validPosition = false;
                    break;
                }
            }

            if (specialFood.x == food.x && specialFood.y == food.y) {
                validPosition = false;
            }
        }
        specialFoodExists = true;
    }

    void initialize() {
        dir = STOP;
        snake.clear();
        snake.push_back({height / 2, width / 2});
        obstacles.clear();
        specialFoodExists = false;

        if (difficulty >= 3) {
            int numObstacles = (difficulty == 3) ? 10 : (difficulty == 4) ? 20 : 0;
            for (int i = 0; i < numObstacles; ++i) {
                obstacles.push_back({rand() % height, rand() % width});
            }
        }
        generateFood();
    }

    void draw() {
        system("clear");
        for (int i = 0; i < height + 2; ++i) {
            for (int j = 0; j < width + 2; ++j) {
                if (i == 0 || i == height + 1) {
                    cout << "#";
                } else if (j == 0 || j == width + 1) {
                    cout << "#";
                } else if (difficulty == 1) {
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
                            bool isObstacle = false;
                            for (auto obstacle : obstacles) {
                                if (obstacle.x == i && obstacle.y == j) {
                                    isObstacle = true;
                                    break;
                                }
                            }
                            if (isObstacle) {
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
                        bool isObstacle = false;
                        for (auto obstacle : obstacles) {
                            if (obstacle.x == i && obstacle.y == j) {
                                isObstacle = true;
                                break;
                            }
                        }
                        if (isObstacle) {
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

    bool kbhit() {
        struct timeval tv = { 0L, 0L };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    }

    char getch() {
        char buf = 0;
        if (read(STDIN_FILENO, &buf, 1) < 0) {
            perror("read()");
        }
        return buf;
    }

    void input() {
        if (kbhit()) {
            char key = getch();
            if (difficulty == 6) {
                switch (key) {
                case 'w': dir = LEFT; break;
                case 'a': dir = DOWN; break;
                case 's': dir = RIGHT; break;
                case 'd': dir = UP; break;
                case 'x': exit(0);
                case 'r': initialize(); break;
                case 'i': showInstructions(); break;
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

    void update() {
        Position head = snake.front();
        Position prevFood = food;
        switch (dir) {
        case UP: head.x--; break;
        case DOWN: head.x++; break;
        case LEFT: head.y--; break;
        case RIGHT: head.y++; break;
        default: return;
        }

        if (difficulty == 2 || difficulty == 3) { 
            if (head.x <= 0) head.x = height;
            else if (head.x >= height + 1) head.x = 1;
            if (head.y <= 0) head.y = width;
            else if (head.y >= width + 1) head.y = 1;
        } else {
            if (head.x <= 0 || head.x >= height + 1 || head.y <= 0 || head.y >= width + 1) {
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

        for (auto obstacle : obstacles) {
            if (head.x == obstacle.x && head.y == obstacle.y) {
                cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
                exit(0);
            }
        }

        snake.push_front(head);
        if (head.x == food.x && head.y == food.y) 
        {
            generateFood();
        } 
        else if (specialFoodExists && head.x == specialFood.x && head.y == specialFood.y) {
            specialFoodExists = false;
            for (int i = 0; i < 2; ++i) {
                snake.push_back(snake.back());
            }
        } 
        else {
            snake.pop_back();
        }

        if (difficulty == 4) { 
            for (auto& obstacle : obstacles) {
                int moveDirection = rand() % 4;
                switch (moveDirection) {
                case 0: if (obstacle.x > 1) obstacle.x--; break;
                case 1: if (obstacle.x < height) obstacle.x++; break; 
                case 2: if (obstacle.y > 1) obstacle.y--; break; 
                case 3: if (obstacle.y < width) obstacle.y++; break; 
                }
            }
        }
        if (difficulty == 5) {
            switch (dir) {
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

    void showStartingAnimation() {
        system("clear");
        string text = "SNAKE GAME";
        string displayText = "          ";
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

    void showMapAnimation() {
        system("clear");
        for (int i = height; i >= 0; --i) {
            system("clear");
            for (int j = 0; j < height + 2; ++j) {
                for (int k = 0; k < width + 2; ++k) {
                    if (j == 0 || j == height + 1) {
                        cout << "#";
                    } else if (k == 0 || k == width + 1) {
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

    int getSleepDuration() {
        switch (difficulty) {
            case 2: return 100000;
            case 3: return 50000;
            case 4: return 50000;
            case 5: return 30000;
            case 6: return 50000;
            default: return 100000;
        }
    }

    void showInstructions() {
        system("clear");
        cout << "Game Instructions:" << endl;
        cout << "Difficulty Level: ";
        switch (difficulty) {
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
    SnakeGame game;
    game.run();
    return 0;
}