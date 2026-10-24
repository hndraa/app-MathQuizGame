# Math Quiz Game
SOFTWARE | CONSOLE GAME | C++ · WINDOWS

An interactive console-based mathematics quiz game developed using C++. The game challenges players to solve arithmetic questions within a limited time, earn points, and compete for a place on the leaderboard.

## 01. Project Overview

### Description

Math Quiz Game is a Windows console application designed to make practicing basic arithmetic more engaging through timed challenges, interactive menus, and score tracking.

Players can choose different quiz modes, answer randomly generated mathematical questions, and view the top three scores recorded by the game.

### Objectives

- Provide an interactive way to practice basic arithmetic.
- Improve calculation speed and accuracy through timed questions.
- Implement fundamental C++ programming concepts in a practical project.
- Practice file handling, random number generation, keyboard input, and data sorting.

### Key Features

- **Interactive Main Menu** — Navigate through Start Game, Leaderboard, Help, and Quit using keyboard controls.
- **Multiple Game Modes** — Choose between fill-in-the-blank questions, multiple-choice questions, and a combination of both.
- **Five Quiz Levels** — Practice addition, subtraction, division, multiplication, and mixed arithmetic.
- **Timed Challenges** — Answer questions before the countdown reaches zero.
- **Score System** — Earn 10 points for each correct answer.
- **Dynamic Questions** — Generate arithmetic questions and randomized multiple-choice options.
- **Leaderboard** — Display and save the top three player scores.
- **Console UI** — Use colored text, menu highlighting, sound effects, and status messages to improve the gameplay experience.

## 02. Tech Stack

| Category | Technology |
|---|---|
| Programming Language | C++ |
| Standard Library | iostream, string, vector, algorithm, fstream, sstream, iomanip |
| Console Interaction | conio.h |
| Windows Console API | windows.h |
| File Storage | Plain-text file (top.txt) |
| Development Environment | Windows-compatible C++ compiler |

### C++ Concepts Applied

- Variables, data types, and structures (`struct`)
- Functions and parameter passing
- Conditional statements and loops
- Arrays and vectors
- Random number generation
- Keyboard input handling
- File input/output
- Sorting algorithms using `std::sort`
- Countdown timers and console cursor positioning

## 03. Screenshots / Results

Screenshots will be added to demonstrate the application's interface and gameplay.

1. **Main Menu** — Interactive navigation and menu highlighting.
   <img width="522" height="457" alt="image" src="https://github.com/user-attachments/assets/e36ec7a6-9a04-480d-89fb-1af6d7404853" />

2. **Game Mode Selection** — Fill-in-the-blank, multiple choice, and combined modes.
   <img width="558" height="303" alt="image" src="https://github.com/user-attachments/assets/09c7eb3b-7166-4ee8-8b61-a204cebb41c8" />

3. **Quiz Gameplay** — Arithmetic questions, countdown timer, and current score.
   <img width="478" height="127" alt="image" src="https://github.com/user-attachments/assets/8aaa62db-4cff-4c7f-a73b-5883849d408b" />

   <img width="350" height="219" alt="image" src="https://github.com/user-attachments/assets/06889c83-74bf-4d4f-922b-fbfe6433c045" />
   <img width="655" height="346" alt="image" src="https://github.com/user-attachments/assets/e36406f4-7ba1-4f4a-ab1b-6d37bd2d79be" />


  
5. **Answer Feedback** — Correct answers, incorrect answers, and time-up messages.
   <img width="655" height="311" alt="image" src="https://github.com/user-attachments/assets/49e915ab-a7ca-4de3-854e-e60623eaacc4" />
   <img width="656" height="338" alt="image" src="https://github.com/user-attachments/assets/53657813-b5b4-47eb-9c63-d58a19cc9b1f" />
   <img width="652" height="339" alt="image" src="https://github.com/user-attachments/assets/014c2576-a82b-43a7-a7cc-aa1f95073a20" />

6. **Leaderboard** — Top three players and their scores.

   <img width="527" height="258" alt="image" src="https://github.com/user-attachments/assets/02600d01-4f8e-4132-82d3-108806acf87e" />

8. **Game Over / Completion** — Final score and game results.
   <img width="531" height="267" alt="image" src="https://github.com/user-attachments/assets/7c476e0f-9060-4587-a93e-33db0a46db85" />

## 04. Installation & Usage

### Prerequisites

- Windows operating system.
- A C++ compiler that supports Windows console APIs, such as MinGW-w64 (GCC).
- A terminal or IDE, such as Visual Studio Code with a configured C++ compiler or Dev C++.

> This project uses `windows.h`, `conio.h`, `GetTickCount()`, `SetConsoleTextAttribute()`, and other Windows-specific functions. It is not directly portable to Linux or macOS.

### Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/app-MathQuizGame.git
cd app-MathQuizGame
```

Replace `YOUR_USERNAME` with your GitHub username.

### Compile the Program

Using MinGW-w64:

```bash
g++ -std=c++11 MTK GAME.cpp -o MTK GAME.exe
```

### Run the Game

```bash
MTK GAME.exe
```

If you are using an IDE, open the project source file, build the program, and run it in a Windows console terminal.

### How to Play

1. Launch the application.
2. Enter your player name when prompted.
3. Navigate the main menu using the arrow keys.
4. Select **START GAME** and choose a quiz mode.
5. Solve each question before the time limit expires.
6. Earn 10 points for each correct answer.
7. View your final score and the leaderboard after the game.

### Controls

| Key | Action |
|---|---|
| Up / Down Arrow | Navigate menus and multiple-choice answers |
| Left / Right Arrow | Select a game mode |
| Enter | Confirm a selection or submit an answer |
| Backspace | Delete the last digit in fill-in-the-blank mode |
| Esc | Return from game mode selection |
| Y / N | Confirm or cancel quitting |

## 05. Data Storage

The game uses `top.txt` to store leaderboard data locally.

Each record follows this format:

```text
250|PlayerOne
210|PlayerTwo
180|PlayerThree
```

The program sorts scores from highest to lowest and retains up to three leaderboard entries. For an existing player, it updates the stored score only when a higher score is achieved.

The leaderboard file is created in the program's working directory when scores are saved.

## 06. Project Structure

```text
├── MTK GAME.cpp
├── top.txt          # Generated during gameplay
├── README.md
```

`top.txt` is generated at runtime and does not need to be included in the repository. The screenshots directory can be added when application screenshots are available.

## 07. Future Improvements

- Refactor the game into separate source and header files.
- Improve score storage and player record management.
- Add difficulty settings and configurable time limits.
- Add persistent player profiles and gameplay statistics.
- Improve input validation and memory management.
- Introduce cross-platform console support.

## License

This project is available for educational and portfolio purposes. A formal open-source license can be added to define reuse and distribution permissions.

---

Developed as a C++ programming project to explore interactive console applications, basic game logic, and file-based score management.
