#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Buffer { /// 用來讀檔的class
public:
    vector<char> characters_;
    int size_x;
    int size_y;

    Buffer(const string& filename) : filename_(filename), size_x(0), size_y(0) {}

    bool ReadFile();

private:
    string filename_;
};

class Mouse {
private:
    int position_x;
    int position_y;

public:
    Mouse(int x, int y) : position_x(x), position_y(y) {}

    int getx() const {
        return position_x;
    }

    int gety() const {
        return position_y;
    }

    void move(int x, int y) {
        position_x = x;
        position_y = y;
    }
};

class Maze {
private:
    int direction = 0;
    vector<vector<char>> dynamicArray;

public:
    Buffer buffer;
    enum Direction { RIGHT, LEFT, UP, DOWN };
    Maze(const string& filename) : buffer(filename) {
        if (buffer.ReadFile()) {
            dynamicArray = vector<vector<char>>(buffer.size_y, vector<char>(buffer.size_x));
            char character;
            int index = 0;
            for (int i = 0; i < buffer.size_y; ++i) {
                for (int j = 0; j < buffer.size_x; ++j) {
                    character = buffer.characters_[index++];
                    dynamicArray[i][j] = character;
                }
            }
            dynamicArray[0][0] = 'V';
        }
    }

    void printMaze();
    void printRoute();
    bool go_right(Mouse& mouse);
    bool go_down(Mouse& mouse);
    bool go_left(Mouse& mouse);
    bool go_up(Mouse& mouse);

    bool is_valid_move(int x, int y) const {
        return x >= 0 && x < buffer.size_x && y >= 0 && y < buffer.size_y &&
               dynamicArray[y][x] != 'O' && dynamicArray[y][x] != 'V' && dynamicArray[y][x] != 'G';
    }

    void process(Mouse& mouse);
};

bool Buffer::ReadFile() {
    ifstream ifs(filename_);
    if (!ifs.is_open()) {
        cerr << "Can't open file " << filename_ << endl;
        return false;
    }

    char character;
    ifs >> size_x;
    ifs >> size_y;

    characters_.clear();
    while (ifs.get(character)) {
        if (character != ' ' && character != '\n') {
            characters_.push_back(character);
        }
    }

    ifs.close();
    return true;
}

void Maze::printMaze() {
    for (const vector<char>& row : dynamicArray) {
        for (char element : row) {
            cout << element;
        }
        cout << endl;
    }
}

// C:\Users\imagi\CLionProjects\hw\input101.txt
bool Maze::go_down(Mouse& mouse) {
    int x = mouse.getx();
    int y = mouse.gety();
    if (x < buffer.size_x - 1 && dynamicArray[x + 1][y] != 'O' && dynamicArray[x + 1][y] != 'V' && dynamicArray[x + 1][y] != 'G' ) {
        // It's possible to move right one step
        x++;
        dynamicArray[x][y] = 'V';  // Set as visited
        mouse.move(x, y);
        return true;
    }
    if (  dynamicArray[x+1][y ] == 'G' ) {
        x++;
        mouse.move(x, y);
    }

    return false; // Couldn't move right one step
}

bool Maze::go_up(Mouse& mouse) {
    int x = mouse.getx();
    int y = mouse.gety();
    if (x > 0 && dynamicArray[x-1][y ] != 'O' && dynamicArray[x-1][y] != 'V' && dynamicArray[x-1][y ] != 'G' ) {
        x--;
        dynamicArray[x][y] = 'V';
        mouse.move(x, y);
        return true;
    }
    if (  dynamicArray[x-1][y ] == 'G' ) {
        x--;
        mouse.move(x, y);
    }

    return false;
}

bool Maze::go_left(Mouse& mouse) {
    int x = mouse.getx();
    int y = mouse.gety();

    if (y > 0 && dynamicArray[x ][y-1] != 'O' && dynamicArray[x ][y - 1] != 'V' && dynamicArray[x ][y - 1] != 'G') {
        y--;
        dynamicArray[x][y] = 'V';
        mouse.move(x, y);
        return true;
    }
    if ( dynamicArray[x ][y - 1] == 'G' ) {
        y--;
        mouse.move(x, y);
    }
    return false;
}

bool Maze::go_right(Mouse& mouse) {
    int x = mouse.getx();
    int y = mouse.gety();
    while (y < buffer.size_x - 1 && dynamicArray[x][y + 1] != 'O' && dynamicArray[x][y + 1] != 'V' && dynamicArray[x][y + 1] != 'G') {
        y++;
        dynamicArray[x][y] = 'V';
        mouse.move(x, y);
        return true;
    }
    if ( dynamicArray[x][y + 1] == 'G' ) {
        y++;
        mouse.move(x, y);
    }
    return false;
}

void Maze::process(Mouse& mouse) {
    int direction = 0;  // Initialize the direction to 0 (RIGHT)

    while (true) {
        bool moved = false;  // Flag to track if the mouse has successfully moved
        switch (direction % 4) {
            case 0:
                if (go_right(mouse)) {
                    moved = true;
                }
                else
                    direction++;
                break;
            case 1:
                if (go_down(mouse)) {
                    moved = true;
                }
                else
                    direction++;
                break;
            case 2:
                if (go_left(mouse)) {
                    moved = true;
                } else
                    direction++;
                break;
            case 3:
                if (go_up(mouse)) {
                    moved = true;
                }
                else
                    direction++;
                break;
        }

        // Check if the mouse has successfully moved in any direction


        // If the mouse has reached 'G', exit the loop
        if (dynamicArray[mouse.getx()][mouse.gety()] == 'G') {
            break;
        }
    }
}

void Maze::printRoute() {
    for (const vector<char>& row : dynamicArray) {
        for (char element : row) {
            if ( element == 'V' )
                cout << 'R';
            else
                cout << element;
        }
        cout << endl;
    }
}

int main() {
    string file_name;
    cin >> file_name;
    Maze maze(file_name);
    if (!maze.buffer.ReadFile()) {
        cerr << "Input error" << endl;
        return 1;
    }
    Mouse mouse(0, 0); // 初始化老鼠的位置
    maze.process(mouse); // 開始處理老鼠的移動
    maze.printMaze(); // 顯示地圖
    cout << endl;
    maze.printRoute();
    return 0;
}
