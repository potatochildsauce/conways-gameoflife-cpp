#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>

const int MAX = 60;

// 🎨 Animated ASCII Title
void ShowAnimatedTitle() {
    const std::string banner[] = {
        "  ____                        _        _     _       ",
        " / ___| __ _ _ __ ___   ___ | | ___  | |__ (_)_ __  ",
        "| |  _ / _` | '_ ` _ \\ / _ \\| |/ _ \\ | '_ \\| | '_ \\ ",
        "| |_| | (_| | | | | | | (_) | |  __/ | | | | | | | |",
        " \\____|\\__,_|_| |_| |_|\\___/|_|\\___| |_| |_|_|_| |_|",
        "",
        "      Conway's Game of Life - C++ Edition",
        "-------------------------------------------------------"
    };

    for (const auto& line : banner) {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

// 🧠 Grid Class
class Grid {
private:
    int grid[MAX][MAX];
    int generation;
    int liveCount;
    std::string currentFile;

public:
    Grid() {
        Clear();
        generation = 0;
        liveCount = 0;
        currentFile = "none";
        srand(time(0));
    }

    void SetAlive(int i, int j) {
        if (i >= 0 && i < MAX && j >= 0 && j < MAX && grid[i][j] == 0) {
            grid[i][j] = 1;
            liveCount++;
        }
    }

    void Kill(int i, int j) {
        if (i >= 0 && i < MAX && j >= 0 && j < MAX && grid[i][j] == 1) {
            grid[i][j] = 0;
            liveCount--;
        }
    }

    bool IsAlive(int i, int j) {
        return (i >= 0 && i < MAX && j >= 0 && j < MAX) ? grid[i][j] == 1 : false;
    }

    int CountNeighbors(int i, int j) {
        int count = 0;
        for (int x = i - 1; x <= i + 1; x++) {
            for (int y = j - 1; y <= j + 1; y++) {
                if ((x != i || y != j) && IsAlive(x, y)) {
                    count++;
                }
            }
        }
        return count;
    }

    void PopulateRandom(int r) {
        int placed = 0;
        while (placed < r) {
            int x = rand() % MAX;
            int y = rand() % MAX;
            if (!IsAlive(x, y)) {
                SetAlive(x, y);
                placed++;
            }
        }
    }

    void Clear() {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                grid[i][j] = 0;
        liveCount = 0;
        generation = 0;
    }

    void Save(const char fileName[]) {
        std::ofstream out(fileName);
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                out << grid[i][j] << " ";
            }
            out << "\n";
        }
        out.close();
        currentFile = fileName;
    }

    void Load(const char fileName[]) {
        std::ifstream in(fileName);
        Clear();
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                in >> grid[i][j];
                if (grid[i][j] == 1) liveCount++;
            }
        }
        in.close();
        currentFile = fileName;
    }

    void Step() {
        int temp[MAX][MAX] = {0};
        int newLiveCount = 0;

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                int neighbors = CountNeighbors(i, j);
                if (IsAlive(i, j)) {
                    temp[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    temp[i][j] = (neighbors == 3) ? 1 : 0;
                }
                if (temp[i][j] == 1) newLiveCount++;
            }
        }

        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                grid[i][j] = temp[i][j];

        liveCount = newLiveCount;
        generation++;
    }

    void Show() {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                std::cout << (grid[i][j] ? "O" : ".") << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\nLive Cells: " << liveCount
                  << " | Generation: " << generation
                  << " | File: " << currentFile << "\n";
    }
};

// 🕹️ Main Menu
int main() {
    ShowAnimatedTitle();  // 🎬 Show animated banner

    Grid game;
    game.Show();          // 🧱 Show initial grid

    char choice;
    char fileName[100];

    do {
        std::cout << "\n--- Game of Life Menu ---\n";
        std::cout << "C - Clear\nR - Random (50 cells)\nS - Step\nG - Go\nV - Save\nL - Load\nQ - Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (toupper(choice)) {
            case 'C':
                game.Clear();
                break;
            case 'R':
                game.PopulateRandom(50);
                break;
            case 'S':
                game.Step();
                break;
            case 'G':
                for (int i = 1; i < 10; i++) {
                    game.Step();
                    game.Show();
                }
                break;
            case 'V':
                std::cout << "Enter filename to save: ";
                std::cin >> fileName;
                game.Save(fileName);
                break;
            case 'L':
                std::cout << "Enter filename to load: ";
                std::cin >> fileName;
                game.Load(fileName);
                break;
            case 'Q':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

        game.Show();  // 🔁 Show grid after each action

    } while (toupper(choice) != 'Q');

    return 0;
}
