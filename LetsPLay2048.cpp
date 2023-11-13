#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int SIZE = 4;

int board[SIZE][SIZE];
int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition()
{
    int occupied = 1;
    pair<int, int> pos;
    while (occupied)
    {
        pos.first = rand() % SIZE;
        pos.second = rand() % SIZE;
        if (board[pos.first][pos.second] == 0)
            occupied = 0;
    }
    return pos;
}

void addPiece()
{
    pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

void newGame()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            board[i][j] = 0;
        }
    }
    addPiece();
}

void printUI()
{
    system("cls");
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        }
        cout << "\n";
    }
    cout << "n: new game, w: up, s: down, a: left, d: right, q: quit\n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn)
{
    if (nextLine < 0 || nextColumn < 0 || nextLine >= SIZE || nextColumn >= SIZE || board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0)
        return false;
    return true;
}

void applyMove(int direction)
{
    int startline = 0, startcolumn = 0, lineStep = 1, columnStep = 1;
    if (direction == 0)
    {
        startline = SIZE - 1;
        lineStep = -1;
    }
    if (direction == 1)
    {
        startcolumn = SIZE - 1;
        columnStep = -1;
    }

    int movepossible, canAddPiece = 0;
    do
    {
        movepossible = 0;
        for (int i = startline; i >= 0 && i < SIZE; i += lineStep)
            for (int j = startcolumn; j >= 0 && j < SIZE; j += columnStep)
            {
                int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                if (board[i][j] && canDoMove(i, j, nextI, nextJ))
                {
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    movepossible = canAddPiece = 1;
                }
            }
        printUI();
        if (movepossible)
        {
            char additionalInput;
            cin >> additionalInput;
            if (additionalInput == 'q')
                exit(0); // exit the game if 'q' is pressed
        }
    } while (movepossible);

    if (canAddPiece)
        addPiece();
}


int main()
{
    srand(time(0));
    char commandToDir[120];
    commandToDir['a'] = 2; // Left
    commandToDir['d'] = 3; // Right
    commandToDir['w'] = 0; // Up
    commandToDir['s'] = 1; // Down

    newGame();

    while (true)
    {
        printUI();
        char command;
        cin >> command;

        if (command == 'n')
            newGame();
        else if (command == 'q')
            break;
        else
        {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection);
        }
    }

    return 0;
}
