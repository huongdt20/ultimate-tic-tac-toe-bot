#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;


string rule(80, '_');

class Grid
{
private:
    char subgrid[3][3];
    char left, right;

public:
    Grid(){} // ham xay dung mac nhien tu dong duoc goi khi tao doi tuong
    void set (int x, int y, char cell);
    char get (int x, int y);
};
// ham gan ki tu bang o cua mang
void Grid::set (int x, int y, char cell) {
    subgrid[x][y] = cell;
}
// ham lay ki tu cua o trong mang
char Grid::get(int x, int y) {
    return subgrid[x][y];
}

int X (int pos) {
    return pos / 3;
}

int Y (int pos) {
    return pos % 3 - 1;
}

class Game
{
private:
    Grid grid[3][3];
    char player;
    size_t cur;

public:
    Game();
    void display(); 
    void play();
    void input (int& g);
    bool checkWin (Grid grid);
    void computer_player();
    void comp_input(int& k);
};

Game::Game() {
    for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 3; ++j)
    for (size_t k = 0; k < 3; ++k)
    for (size_t l = 0; l < 3; ++l)
    {
        grid[i][j].set(k, l, '_');
    }
    player = 'x';
    cur = 0; // current grid luu tru chi so cua grid hien tai
}

void Game::play()
{
    int g, s;
    display();
    while (1) {
        display();
        cout << "\n  Player " << player << " - Enter Grid: ";// nguoi choi dau tien chon grid bat ki de danh
        cin >> g;
        if (g > 0 && g < 10) {
            break;
        }
        display();
        cout << "\n  Try again.";
        cin.get();
    }
    s = g;
    while (1) {
        display();
        if (checkWin(grid[X(cur)][Y(cur)])) {
            display();
            cout << "\n  Player " << player << " won!";
            cin.get();
            cin.ignore();
            break;
        }
        player = player == 'x' ? 'o' : 'x';
        cur = g;
        input(g);
    }

}

void Game::display()
{
    system("cls");
    cout << "\n  ULTIMATE TIC TAC TOE\n" << rule;

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t k = 0; k < 3; ++k)
        {
            cout << "\n";
            char left, right;
            left = right = ' ';

            for (size_t j = 0; j < 3; ++j)
            {
                if (k == 1)
                {
                    if (3*i + j + 1  == cur) {
                        left = '>';
                        right = '<';
                    }
                    else {
                        left = right = ' ';
                    }
                }
                cout << "  " << left << " ";
                for (size_t l = 0; l < 3; ++l) {
                    cout << grid[i][j].get(k, l) << " ";
                }
                cout << right;
            }
        }
        cout << "\n\n";
    }
    cout << "\n";
}

void Game::input(int& g) // nhap dau vao tai subgrid thu g
{

    int s;
    while (1) {
        display();
        cout << "\n  Player " << player << " - Enter subgrid: ";
        cin >> s;
        if (s > 0 && s < 10)
        {
            if (grid[X(g)][Y(g)].get(X(s), Y(s)) == '_') { 
                break;
            }
        }
        display();
        cout << "\n  Try again.";
        cin.ignore(); cin.get();
    }
    grid[X(g)][Y(g)].set(X(s), Y(s), player);
    g = s; // gan grid cu bang subgrid vua nhap
}
// ham kiem tra khi nao thang
bool Game::checkWin(Grid grid)
{
    char p = player;
    int row = 1, col = 1, main_diag = 1, anti_diag = 1;
    for (size_t i = 0; i < 3; ++i)
    {
        row = col = 1;
        if (grid.get(i, 3-1-i) != p) {
            anti_diag = 0;
        }
        if (grid.get(i, i) != p) {
            row = col = main_diag = 0;
        }

        else {
            for (size_t j = 0; j < 3; ++j)
            {
                if (grid.get(i, j) != p) {
                    row = 0;
                }
                if (grid.get(j, i) != p) {
                    col = 0;
                }
            }
        }

        if (row || col) {
            return 1;
        }
    }

    if (main_diag || anti_diag) {
        return 1;
    }
    return 0;
}
// ham tao nuoc di ngau nhien cho may
void Game::comp_input(int& g) // may tu nhap dau vao tai grid thu g
{
    int s;
    char comp = 'o';
    while (1) {
        display();
        srand(time(NULL));
    	s = (rand() % 9 ) + 1 ;
    	cout<<"\n Computer playing at subgrid "<<s<<endl;
        if (s > 0 && s < 10)
        {
            if (grid[X(g)][Y(g)].get(X(s), Y(s)) == '_') { 
                break;
            }
        }
        display();
        cout << "\n  Try again.";
        cin.ignore(); cin.get();
    }
    grid[X(g)][Y(g)].set(X(s), Y(s), comp);
    g = s;
}
void Game::computer_player(){
	int g, s;
    display();
//  	vong lap cai dat cho may chon grid
    while (1) {
        display();
        srand(time(NULL));
        g = (rand() % 9 ) + 1 ; // chon grid tu dong
//     cout<<"\n Computer playing at grid "<<g;
        if (g > 0 && g < 10) {
            break;
        }
        display();
        cout << "\n  Try again.";
        cin.get();
    }
    s = g;
    // vong lap kiem tra thang va nhap dau vao trong subgrid
    while (1) {
        display();
        // kiem tra van co da co nguoi thang chua
        if (checkWin(grid[X(cur)][Y(cur)])) {
            display();
            cout << "\n  Player " << player << " won!";
            cin.get();
            cin.ignore();
            break;
        }
//        player = player == 'x' ? 'o' : 'x';
        cur = g;
        comp_input(g);
        input(g);
    }
}

int main()
{
    Game game;
    game.display();
    cout << "\n  Welcome to Ultimate Tic Tac Toe." <<endl;
    cout<<"\n The rules:Each small 3-by-3 tic-tac-toe board is referred to as a local board, and the larger 3-by-3 board is referred to as the global board. "<<endl;
    cout<<"\n The game starts with X playing wherever they want in any of the 81 empty spots. This move 'sends' their opponent to its relative location."<<endl;
    cout<<"\n For example, if X played in the top right square of their local board, then O needs to play next in the local board at the top right of the global"<<endl;
    cout<<"\n board. O can then play in any one of the nine available spots in that local board, each move sending X to a different local board."<<endl;
    cout<<"\n If a move is played so that it is to win a local board by the rules of normal tic-tac-toe, then the entire local board is marked as a victory for"<<endl;
    cout<<"\n the player in the global board. Once a local board is won by a player or it is filled completely, no more moves may be played in that board. If a "<<endl;
    cout<<"\n player is sent to such a board, then that player may play in any other board."<<endl;
    cout<<"\n Game play ends when either a player wins the global board or there are no legal moves remaining, in which case the game is a draw."<<endl;
	cout<< "\n Press Enter to start."<<endl;;
    cin.get();

    int input, error = 0;
    do {
        game.display();
        if (error) {
            cout << "  Invalid option. Try again.\n";
            error = 0;
        }
        else {
            cout << "  Select an option: \n";
        }
        cout << "    1) Play with friend\n    2) Play with computer    3) Quit\n" << "\n> ";
        cin >> input;
        switch (input) {
            case 1:
                game.play(); break;
            case 2:
                game.computer_player();
                break;
            case 3:
                std::exit(0);
            default:
                error = 1;
        }
        system("cls");
    } while (error);

    system("pause");
    return 0;
}
