#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <string>
#include<string.h>
#include<Windows.h>

void move(int dir);
void gameBoard();
void clear();

bool lose = false;
bool win = false;
int noEmptyCell;
int totalScore;
int loseSum;
int turn;
int board [4][4];
int score;
int dirLine[] = { 1,0,-1,0 };
int dirColumn[] = { 0,1,0,-1 };

std::pair<int, int> generateNum() {
    int engaged = 1;
    int line, column;
    while (engaged != 0) {
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0) {
            engaged = 0;
        }
    }
    return std::make_pair(line, column);
}

void fromTxt() {
    std::ifstream f("Score.txt");
    f >> totalScore;
    f.close();
}

void toTxt() {
    std::ofstream f("Score.txt", std::ios::out | std::ios::trunc);
    f.close();
    std::ofstream fs("Score.txt");
    fs << totalScore;
    fs.close();
}

void gameOverText() {
    clear();
    std::cout << "Игра окончена";
    Sleep(4000);
}

void gameOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0;j < 4; j++)
        {
            if (board[i][j] != 0) {
                noEmptyCell++;
        }
            if (i == 3&& j!=3) {
                if (board[i][j] != board[i][j + 1]) {
                    loseSum++;
                }
            }
            if (j == 3 && i != 3) {
                if (board[i][j] != board[i + 1][j]) {
                    loseSum++;
                }
            }
            else {
                if (board[i][j] != board[i][j + 1] && board[i][j] != board[i + 1][j]&&i!=3&&j!=3) {
                    loseSum++;
                }
            }
        }
    }
    if (loseSum == 15&&noEmptyCell==16&&lose==false) {
        Sleep(4000);
        gameOverText();
        lose = true;
    }
    else {
        noEmptyCell = 0;
        loseSum = 0;
    }
}

void logo() {
    system("color 0E");
    std::cout <<" " << "________________________________" << std::endl;
    std::cout << "|" <<" " << "@@@@"<< " " << " " << "   "<<"@@@@"<<" " << " " << "    "<<"@@"<<" " << " " << "  "<<"@@@@"<<" " << " | " << std::endl;
    std::cout << "|" <<" " << "@@"<<"  "<<"@@" << " " << " "<<"@@"<<"  " << "@@" << " " << "   "<<"@@@"<<" " << " " << " "<<"@@" << "  " << "@@" << " | " << std::endl;
    std::cout << "|" << "     "<<"@@" << " " << " "<<"@@"<<"  " << "@@" << " " << "   "<<"@@@"<<" " << " " << " "<<"@@"<<"  " << "@@" << " | " << std::endl;
    std::cout << "|" << "     "<<"@@" << " " << " "<<"@@"<<"  "<<"@@" << " " << "  "<<"@@@@"<<" " << " " << " "<<"@@"<<"  "<<"@@" <<" | "<< std::endl;
    std::cout << "|" << "    "<<"@@"<<" " << " " << " "<<"@@"<<"  "<<"@@" << " " << "  "<<"@" << " " << "@@" << " " << " " << "  "<<"@@@@"<<" " << " | " << std::endl;
    std::cout << "|" << "   "<<"@@" << " " << "   "<<"@@"<<"  "<<"@@" << " " << " "<<"@@"<<" " << "@@"<<" " << " " << " "<<"@@" << "  " << "@@" <<" | "<< std::endl;
    std::cout << "|" << "  "<<"@@"<<"   " << " " << " "<<"@@" << "  " << "@@" << " " << " "<<"@@@@@@" << " " << " "<<"@@"<<"  " << "@@" << " | " << std::endl;
    std::cout << "|" << " "<<"@@" << "    " << " " << " "<<"@@" << "  " << "@@" << " " << "    "<<"@@"<<" " << " " << " "<<"@@"<<"  "<<"@@" << " | " << std::endl;
    std::cout << "|" << " "<<"@@@@@@" << " " << "  "<<"@@@@"<<" " << " " << "    "<<"@@"<<" " << " " << "  "<<"@@@@"<<" " <<" | "<< std::endl;
    std::cout << "|" << "________________________________" <<"|"<< std::endl;
    std::cout << std::endl;
}

int menu() {
    clear();
    logo();
    setlocale(0, "rus");
    bool fm = true;
    int a;
    std::cout << "1.Игра" << std::endl;
    std::cout << "2.Управление" << std::endl;
    std::cout << "0.Выход" << std::endl;
    while (fm ==true) {
        char choice;
        choice = _getch();
        if (choice == '1' || choice == '2' || choice == '3' || choice == '0') {
            fm = false;
            a = choice - '0';
        }
    }
     return a;
}

void addPiece() {
    std::pair<int, int> position = generateNum();
    board[position.first][position.second] = 2;
}

void resetGame() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = 0;
        }
    }
    score = 0;
    addPiece();
}

void clear() {
    std::system("cls");
}

char enterCommand() {
    char a;
    bool m = true;
    while (m == true) {
        a = _getch();
        if (a == 'w' || a == 's' || a == 'a' || a == 'd' || a == 'q' || a == 'n') {
            m = false;
        }
    }
    return a;
}

void game() {
    char commandToDir[128];
    commandToDir['s'] = 0;
    commandToDir['d'] = 1;
    commandToDir['w'] = 2;
    commandToDir['a'] = 3;
    resetGame();    
    while (true) {
        gameBoard();
        char command;
        command = enterCommand();
        if (command == 'n') {
            resetGame();
            turn = 0;
        } else if (command == 'q') {
            break;
        }
        else {
             int curDir = commandToDir[command];           
            move(curDir);
        }        
    }
}

void color(int a) {
    if (a == 0) {
        system("color 7");
    }
    if (a == 2) {

    }
}

std::string noZeroOnBoard(int a) {
    if (a == 0) {
        std::string zer;
        zer = ' ';
        return zer;
    }
    else {
        std::string sum =std::to_string(a);
        return sum;
    }
}

void gameBoard() {
        clear();
        setlocale(0, "rus");
        std::cout << " ________________________________ " << std::endl;
        std::cout << "|       |       |       |        |" << std::endl;
        std::cout << "| " << std::setw(4) << noZeroOnBoard(board[0][0]) << std::setw(4) << " | " << std::setw(4) << 
        noZeroOnBoard(board[0][1]) << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[0][2]) << std::setw(4) 
        << " | " << std::setw(4) <<noZeroOnBoard(board[0][3]) << std::setw(4) << "|" << std::endl;
        std::cout << "|_______|_______|_______|________|" << std::endl;
        std::cout << "|       |       |       |        |" << std::endl;
        std::cout << "| " << std::setw(4) << noZeroOnBoard(board[1][0]) << std::setw(4) << " | " << 
        std::setw(4) << noZeroOnBoard(board[1][1]) << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[1][2]) 
        << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[1][3]) << std::setw(4) << "|" << std::endl;
        std::cout << "|_______|_______|_______|________|" << std::endl;
        std::cout << "|       |       |       |        |" << std::endl;
        std::cout << "| " << std::setw(4) << noZeroOnBoard(board[2][0]) << std::setw(4)
        << " | " << std::setw(4) << noZeroOnBoard(board[2][1]) << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[2][2])
        << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[2][3]) << std::setw(4) << "|" << std::endl;
        std::cout << "|_______|_______|_______|________|" << std::endl;
        std::cout << "|       |       |       |        |" << std::endl;
        std::cout << "| " << std::setw(4) << noZeroOnBoard(board[3][0]) << std::setw(4) << " | " << std::setw(4) 
        << noZeroOnBoard(board[3][1]) << std::setw(4) << " | " << std::setw(4) << noZeroOnBoard(board[3][2]) << std::setw(4) << " | " 
        << std::setw(4) << noZeroOnBoard(board[3][3]) << std::setw(4) << "|" << std::endl;
        std::cout << "|_______|_______|_______|________|" << std::endl;
        std::cout << "Рекорд: " << totalScore<<std::endl;
        std::cout << "Счёт: " << score << std::endl;
        std::cout << "Ход: " << turn << std::endl;
        gameOver();
}

void settings() {
    char back = 12;
                while (back != '0') {
                    clear();
                    std::cout << " ________________ " << std::endl;
                    std::cout << "|" << "Вверх" << "          " << "w" << "|" << std::endl;
                    std::cout << "|" << "Вниз" << "           "<< "s" << "|" << std::endl;
                    std::cout << "|" << "Влево" << "          " << "a" << "|" << std::endl;
                    std::cout << "|" << "Вправо" << "         " << "d" << "|" << std::endl;
                    std::cout << "|" << "Новая игра" << "     " << "n" << "|" << std::endl;
                    std::cout << "|" << "Выход" << "          " << "q" << "|" << std::endl;
                    std::cout << "|" << "0.Назад" << "         |" << std::endl;
                    std::cout << "|________________|" << std::endl;
                    back = _getch();
                }                
}

bool possibilityMove(int line, int column, int nextLine, int nextColumn) {
    if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 || board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0) {
        return false;
    }
    else {
        return true;
    }
}

void move(int dir) {
    bool movePossible, canAddPiece = 0;
    do {
        movePossible = 0;
        for (int i = 0; i >= 0 && i < 4; i++) {
            for (int j = 0; j >= 0 && j < 4; j++) {
                int nextI = i + dirLine[dir];
                int nextJ = j + dirColumn[dir];
                if (board[i][j] != 0 && possibilityMove(i, j, nextI, nextJ)) {
                    board[nextI][nextJ] += board[i][j];
                    if (board[nextI][nextJ] > 2) {
                        score += board[nextI][nextJ];
                    }
                    if (win == false && board[nextI][nextJ] == 2048) {
                        std::cout << "Поздравляю с победой!" << std::endl;
                        win = true;
                    }
                    board[i][j] = 0;
                    movePossible = canAddPiece = true;
                }

            }
        }
    } while (movePossible == true);
    if (canAddPiece == true) {
        addPiece();
        turn++;
    }
        if (score > totalScore) {
            totalScore = score;
        }
}

int main() {
    fromTxt();
    bool flag = true;
    while (flag == true) {
        int act;
        act = menu();
        switch (act) {
        case 1:
            game();
            break;
        case 2:settings();
            break;
        case 0:
            toTxt();
            flag = false;
        }
        
     }
    return 0;
}