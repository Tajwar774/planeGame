// Very basic plane game (console, turn-based)
// Controls: a = left, d = right, s = stay, then press Enter
// Dodge the falling rocks (#). Survive as long as you can!

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 15;
const int HEIGHT = 10;

int main() {
    srand(time(0));

    int planeX = WIDTH / 2;
    int score = 0;
    bool rocks[HEIGHT][WIDTH] = {false};

    while (true) {
        // ----- Draw -----
        cout << "\n\n";
        cout << "Score: " << score << "\n";
        cout << "+" << string(WIDTH, '-') << "+\n";
        for (int y = 0; y < HEIGHT; y++) {
            cout << "|";
            for (int x = 0; x < WIDTH; x++) {
                if (y == HEIGHT - 1 && x == planeX) cout << "^";   // the plane
                else if (rocks[y][x]) cout << "#";                  // a rock
                else cout << " ";
            }
            cout << "|\n";
        }
        cout << "+" << string(WIDTH, '-') << "+\n";

        // ----- Input -----
        cout << "Move (a=left, d=right, s=stay, q=quit): ";
        char c;
        cin >> c;
        if (c == 'q') break;
        if (c == 'a' && planeX > 0) planeX--;
        if (c == 'd' && planeX < WIDTH - 1) planeX++;

        // ----- Move rocks down -----
        for (int y = HEIGHT - 1; y > 0; y--)
            for (int x = 0; x < WIDTH; x++)
                rocks[y][x] = rocks[y - 1][x];

        // New row of rocks at the top (about 2 rocks per row)
        for (int x = 0; x < WIDTH; x++)
            rocks[0][x] = (rand() % 7 == 0);

        // ----- Collision check -----
        if (rocks[HEIGHT - 1][planeX]) {
            cout << "\n*** BOOM! You crashed! ***\n";
            cout << "Final score: " << score << "\n";
            break;
        }

        score++;
    }

    return 0;
}
