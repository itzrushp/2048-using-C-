#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;


int board[4][4];
int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition()
{
    int occupied = 1;
    pair<int, int> pos;
    while (occupied)
    {
        pos.first = rand() % 4;
        pos.second = rand() % 4;
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
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            board[i][j] = 0;
        }
    }
    addPiece();
}
void printUI()
{
    system("cls");
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        }
        cout << "\n";
    }
    cout << "n: new game , w: up , s: down , a: left , d: right  , q: quit  \n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn)
{
    if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 || board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0)
        return false;
    return true;
}

void applyMove(int direction)
{
    int startline = 0, startcolumn = 0, lineStep = 1, columnStep = 1;
    if (direction == 0)
    {
        startline = 3;
        lineStep = -1;
    }
    if (direction == 1)
    {
        startcolumn = 3;
        columnStep = -1;
    }

    int movepossible, canAddPiece = 0;
    do
    {
        movepossible = 0;
        for (int i = startline; i >= 0 && i < 4; i += lineStep)
        {
            for (int j = startcolumn; j >= 0 && j < 4; j += columnStep)
            {
                int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                if (board[i][j] && canDoMove(i, j, nextI, nextJ))
                {
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    movepossible = canAddPiece = 1;
                }
            }
        }
        printUI();
    } while (movepossible);
    if (canAddPiece)
        addPiece();
}
int main()
{
    srand(time(0));
    char commandToDir[120];
    commandToDir['s'] = 0;
    commandToDir['d'] = 1;
    commandToDir['w'] = 2;
    commandToDir['a'] = 3;
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