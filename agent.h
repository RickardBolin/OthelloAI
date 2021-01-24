//
// Created by Rickard Bolin on 2020-02-09.
//

#ifndef OTHELLO_AGENT_H
#define OTHELLO_AGENT_H
#include <vector>
#include <string>

// Depth limit
int DEPTH_LIMIT = 10;
// Time limit in milliseconds
double TIME_LIMIT = 1000;

struct Move {
    int score = 0;
    int x = -1;
    int y = -1;
};

bool operator==(const Move& m1, const Move& m2){
    return (m1.x == m2.x && m1.y == m2.y);
}

struct Board {
    signed int board[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1, -1, 0, 0, 0},
                              {0, 0, 0, -1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
};

void printBoard(Board b);

std::string convertMoveToString(Move m);

Move convertStringToMove(std::string move);

std::string getPlayerInput();

Move findMax(Board b, int alpha, int beta, int depth, signed int color,
        Move bestMove, int timeStart);

Move findMin(Board b, int alpha, int beta, int depth, signed int color,
        Move bestMove, int timeStart);

int getScore(Board b);

std::vector <Move> findPossibleMoves(Board b, signed int color);

bool isValid(Board b, Move m, signed int color);

Board makeMove(Board b, Move m, signed int color);

bool outOfBounds(int x, int y);

int countDigits(int n);

int agentVsAgent();

int playerVsAgent(int color);

int agentVsRandom();

int agentVsRandomBenchmark();

#endif //OTHELLO_AGENT_H
