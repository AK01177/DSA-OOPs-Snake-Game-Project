# 🐍 Snake Game 🎮

A terminal-based Snake Game with customizable settings and multiple difficulty levels. The game features various snake and food types, as well as special foods and obstacles, making the gameplay dynamic and challenging. 🚀

## ⭐ Features

- **🎨 Customizable Map Size**: Set the width and height of the game area.
- **🔥 Multiple Difficulty Levels**: Choose from six difficulty levels: Noob, Rookie, Elite, Pro, Sigma, and Pro Sigma.
- **🐍 Custom Snake and Food Types**: Select different colors and styles for your snake and food.
- **🍏 Special Food**: Occasionally appears and grants additional benefits.
- **🚧 Obstacles**: Adds complexity and challenge to the game.
- **🎬 Animated Start and Map Loading**: A visually appealing introduction to the game.
- **🕹️ Classic Snake Mechanics**: Move around, eat food, and grow your snake.
- **🌍 Wall-Wrapping Mode**: Enabled on certain difficulty levels.

## 🎮 Controls

- `W` - ⬆️ Move Up
- `A` - ⬅️ Move Left
- `S` - ⬇️ Move Down
- `D` - ➡️ Move Right
- `X` - ❌ Exit the Game
- `R` - 🔄 Restart the Game
- `I` - ℹ️ Show Instructions

## 🛠️ Installation and Execution (Linux Only 🐧)

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/snake-game.git
   cd snake-game
   ```
2. **Install Dependencies (if needed):**
   ```sh
   sudo apt update && sudo apt install g++
   ```
3. **Compile the Code:**
   ```sh
   g++ snake_game.cpp -o snake_game
   ```
4. **Run the Game:**
   ```sh
   ./snake_game
   ```

## 📋 Requirements

- A C++ compiler (g++ recommended)
- A Linux terminal that supports ANSI escape codes for colored output 🎨

## 🎯 How to Play

1. Start the game and configure the map size. 📏
2. Select the difficulty level and snake/food type. 🎨
3. Navigate the snake to eat food while avoiding obstacles and itself. 🐍
4. Special food grants extra benefits when eaten. 🍏✨
5. Survive as long as possible and achieve the highest score! 🏆

## ⚡ Difficulty Levels

| Level         | Features                                      |
| ------------- | --------------------------------------------- |
| 🟢 Noob      | Error-prone, not recommended. 🚧              |
| 🟡 Rookie    | Standard gameplay with normal speed. 🏃       |
| 🔵 Elite     | Includes obstacles, increased speed. 🚀       |
| 🔴 Pro       | Moving obstacles, requires quick reflexes. 🎯 |
| 🟣 Sigma     | Dynamic food movement, challenging. 💨        |
| ⚫ Pro Sigma | Random direction shifts, extremely hard. 💀   |

## 📚 Data Structure Analysis

- 🗂️ **Arrays:** Used for storing the snake's body coordinates.
- 📦 **Structs:** Defines food and obstacle properties.
- 🔗 **Linked Lists:** Can be used to dynamically manage snake growth.
- 📊 **2D Arrays:** Represents the game board efficiently.

## 👨‍💻 Object-Oriented Programming (OOPs)

- 🔒 **Encapsulation:** Game elements like snake, food, and obstacles are encapsulated in classes.
- 📂 **Abstraction:** Hides complex game logic behind simple interfaces.

## 🤝 Contributions

Feel free to contribute by:

- 🐛 Fixing bugs
- 🆕 Adding new features
- 🎮 Improving game mechanics

Fork the repository, create a branch, and submit a pull request! 🚀

## 📜 License

This project is open-source and available under the MIT License.

---

Enjoy the game! Have fun avoiding obstacles and chasing food! 🎉🐍
