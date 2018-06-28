#ifndef _movement_h
#define _movement_h

#include <iostream>
using namespace std;

#define clear() printf("\033[H\033[J")

void printBoard(char (&board)[7][7]){
    cout << "  ";
    for(int i=0; i<7; i++){
        cout << i << " ";
    }
    cout << endl;

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(j==0){
                cout << i << " ";
            }
            cout << board[i][j] << " ";
        }
        cout << i << endl;
    }
    cout << "  ";
    for(int i=0; i<7; i++){
        cout << i << " ";
    }
    cout << endl << endl;
}

int score(char (&board)[7][7]){
    int sum = 0;
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(board[i][j] == '1'){
                sum++;
            }
        }
    }
    return sum;
}

bool inRange( char (&board)[7][7], int x, int y){
    if (x>=7 || x<0 || y>=7 || y<0 || board[x][y]=='#')
        return false;
    return true;
}

void initializeBoard( char (&board)[7][7] ){
    string line;
    ifstream myfile("board.txt");

    int i=0;
    if(myfile.is_open()){
        while( getline(myfile, line) ){
            if(i<7){
                for(int j=0; j<7; j++){
                    board[i][j] = line[j*2];
                }
                i++;
            }
        }
        myfile.close();
    } else {
        cout << "Unable to open file" << endl;
    }

}

bool moveIsValid(char (&board)[7][7], string pos, int x, int y){
    int xKill, xNewPos, yKill, yNewPos;
    xKill = xNewPos = yKill = yNewPos = 0;

    if(pos=="up"){
        xKill = x-1;
        yKill = y;
        xNewPos = x-2;
        yNewPos = y;
    } else if(pos=="down"){
        xKill = x+1;
        yKill = y;
        xNewPos = x+2;
        yNewPos = y;
    } else if(pos=="left"){
        xKill = x;
        yKill = y-1;
        xNewPos = x;
        yNewPos = y-2;
    } else if(pos=="right"){
        xKill = x;
        yKill = y+1;
        xNewPos = x;
        yNewPos = y+2;
    }

    if(board[x][y] == '1' && board[xKill][yKill] == '1' && board[xNewPos][yNewPos] == '0'
    && inRange(board, x,y) && inRange(board, xKill,yKill) && inRange(board, xNewPos,yNewPos))
        return true;
    return false;

}

bool moveIsValid(char (&board)[7][7], int x, int xKill, int xNewPos, int y, int yKill, int yNewPos){

    if(board[x][y] == '1' && board[xKill][yKill] == '1' && board[xNewPos][yNewPos] == '0'
    && inRange(board, x,y) && inRange(board, xKill,yKill) && inRange(board, xNewPos,yNewPos))
        return true;
    return false;

}

struct movement {
    int x;
    int y;
    string direction;
};

int checkPossibleMoves(char (&board)[7][7], bool print){
    string possibleMoves[] = {"up", "down", "left", "right"};
    vector <movement> moves;
    movement tempMove;
    int moveCount[] = {0, 0, 0, 0};

    int sum = 0;

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){

            for(int k=0; k<4; k++){
                if( moveIsValid(board, possibleMoves[k], i, j) ){
                    tempMove.x = i;
                    tempMove.y = j;
                    tempMove.direction = possibleMoves[k];
                    moves.push_back(tempMove);
                    moveCount[k]++;
                    sum++;
                }
            }

        }
    }

    if(sum>0 && print){
        cout << "Total de possíveis movimentos: " << sum << endl;
        for(int k=0; k<4; k++){
            if(moveCount[k]>0){
                cout << possibleMoves[k] << ": " << moveCount[k] << endl;
            }
        }
    }
    return sum;

}


bool move(char (&board)[7][7], string pos, int x, int y){
    int xKill, xNewPos, yKill, yNewPos;
    xKill = xNewPos = yKill = yNewPos = 0;

    if(pos=="up"){
        xKill = x-1;
        yKill = y;
        xNewPos = x-2;
        yNewPos = y;
    } else if(pos=="down"){
        xKill = x+1;
        yKill = y;
        xNewPos = x+2;
        yNewPos = y;
    } else if(pos=="left"){
        xKill = x;
        yKill = y-1;
        xNewPos = x;
        yNewPos = y-2;
    } else if(pos=="right"){
        xKill = x;
        yKill = y+1;
        xNewPos = x;
        yNewPos = y+2;
    }

    if(moveIsValid(board, x,xKill,xNewPos,y,yKill,yNewPos)){
        cout << "Made "<< pos <<" (" << x << "," << y << ") to (" << xNewPos << "," << yNewPos << ");" << endl;
        board[x][y] = '0';
        board[xKill][yKill] = '0';
        board[xNewPos][yNewPos] = '1';
        return 1;
    }
    return 0;

}

#endif
