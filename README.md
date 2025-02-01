Here’s what the functions and header files do in your Snake Game code:

---

Header Files and Their Purpose

1. #include <iostream>
Used for input (cin) and output (cout).

2. #include <termios.h>
Used to control terminal settings, such as enabling/disabling raw mode for real-time input.

3. #include <unistd.h>
Provides system-related calls, such as usleep() (to introduce delays).

4. #include <list>
Used to store the snake’s body segments dynamically as a list of positions.

5. #include <vector>
Used to store obstacles dynamically.

6. #include <string>
Used for string manipulation (e.g., storing snake and food colors).

7. #include <cstdlib>
Used for generating random numbers (rand()).

8. #include <ctime>
Used to seed the random number generator (srand(time(0))).

---

Functions and Their Purpose

1. run()

Starts the game.
Calls setup functions (showStartingAnimation(), setMapSize(), setDifficulty(), chooseSnakeType(), chooseFoodType()).
Initializes game settings and enters the main game loop (draw(), input(), update()).

2. setMapSize()
Allows the user to define the game’s width and height.

3. setDifficulty()
Allows the user to select difficulty, affecting gameplay mechanics.

4. chooseSnakeType()
Lets the user pick a snake appearance (colored blocks).

5. chooseFoodType()
Lets the user pick food appearance (colored blocks).

6. generateFood()
Randomly places food on the map while ensuring it doesn’t overlap with obstacles or the snake.

7. generateSpecialFood()
Randomly places special food with similar constraints as generateFood().

8. initialize()

Resets game variables.
Places the snake in the center of the map.
Generates obstacles (if difficulty is high).
Calls generateFood().

9. draw()

Renders the game map with:

Snake (snakeChar)
Food (foodChar)
Obstacles (vector<Position> obstacles)
Uses ANSI escape sequences for color formatting.

10. setTerminalRawMode(bool enable)
Enables/disables raw mode for real-time keyboard input.

11. kbhit()
Checks if a key was pressed without blocking execution.

12. getch()
Reads a single character from input without requiring Enter key.

13. input()
Detects user input (WASD for movement, X for exit, R for reset).

14. update()
Moves the snake.
Handles collisions (walls, self, obstacles).
Checks food consumption.
Implements special effects based on difficulty.

5. showStartingAnimation()
Displays an animated title screen.

16. showMapAnimation()
Animates the map before starting the game.

17. getSleepDuration()
Returns sleep duration (affects game speed) based on difficulty.

18. showInstructions()
Displays difficulty-specific instructions and controls.

19. main()
Creates an instance of SnakeGame and starts the game.

---

Additional Notes

Game Speed: Controlled by usleep(getSleepDuration()).

Collision Handling: Checks for self-collision, wall collision, and obstacle collision.

Difficulty Modifiers:

Noob (1): Displays error.

Rookie (2): Snake wraps around edges.

Elite (3): More obstacles.

Pro (4): Moving obstacles.

Sigma (5): Food moves based on snake direction.

Pro Sigma (6): Special difficulty settings.
