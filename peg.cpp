#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "movement.h"
using namespace std;

struct boards{
    char board[7][7];
};

vector <vector<boards> > chronos;

bool areBoardEquals(char (&board)[7][7], char (&newBoard)[7][7]){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if ( newBoard[i][j]!=board[i][j] ) {
                return false;
            }

        }
    }
    return true;
}

bool isBoardHere(char (&board)[7][7], vector <boards> vet){
    for(int i=0; i<vet.size(); i++){
        if (areBoardEquals(board,vet[i].board))
            return true;
    }
    return false;
}


bool condition(movement a, movement b){
    string possibleMoves[] = {"up", "down", "left", "right"};
    for(int i=0; i<4; i++){
        if(a.direction==possibleMoves[i])
            return 1;
        if(b.direction==possibleMoves[i])
            return 0;
    }
}

vector <movement> possibleMoves(char (&board)[7][7]){
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

    return moves;
}

void copyBoard(char (&board)[7][7], char (&newBoard)[7][7]){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            newBoard[i][j]=board[i][j];
        }
    }
}

bool makeMove(char (&board)[7][7], char (&newBoard)[7][7], string pos, int x, int y){
    copyBoard(board,newBoard);

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
        newBoard[x][y] = '0';
        newBoard[xKill][yKill] = '0';
        newBoard[xNewPos][yNewPos] = '1';
        return 1;
    }
    return 0;
}

boards tempBoard;
bool finalAnswerAchieved = false;
void BFSolution(char (&board)[7][7]){
    char newBoard[7][7];

    vector <movement> moves = possibleMoves(board);

    if(moves.size()==0){
        if(score(board)==1){
            cout << "Possible score: " << score(board) << endl;
            printBoard(board);
            finalAnswerAchieved = true;
        }
    } else {
        for(int i=0; i<moves.size() && !finalAnswerAchieved; i++){
            if(makeMove(board, newBoard, moves[i].direction ,moves[i].x, moves[i].y)){
                if(!isBoardHere(newBoard,chronos[score(board)-1])){
                    copyBoard(newBoard,tempBoard.board);
                    chronos[score(board)-1].push_back(tempBoard);
                    BFSolution(newBoard);
                }
            }
        }
    }

}

void naiveSolution(char (&board)[7][7]){
    string possibleMoves[] = {"up", "down", "left", "right"};
    while (checkPossibleMoves(board, 0) ) {
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                for(int k=0; k<4; k++){
                    move(board, possibleMoves[k], i, j);
                }
            }
        }
    }
}

int main(){
    clear();
    chronos.resize(35);
    char board[7][7];
    cout << "Start with: " << endl;
    initializeBoard(board);
    printBoard(board);

    vector <pair<int, int> > movementsMade;
    BFSolution(board);

    return 0;
}
