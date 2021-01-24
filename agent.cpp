//
// Created by Rickard Bolin on 2020-02-09.
//
#include <iostream>
#include <vector>
#include "agent.h"
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

Move findMax(Board b, int alpha, int beta, int depth, signed int color,
             Move bestMove, int timeStart) {
    std::vector<Move> possibleMoves = findPossibleMoves(b, color);
    int timeNow = 1000*clock()/CLOCKS_PER_SEC;
    bool outOfTime = 0.8*TIME_LIMIT < (timeNow - timeStart)/1e6;

    if (possibleMoves.empty() || depth > DEPTH_LIMIT || outOfTime) {
        bestMove.score = getScore(b);
        return bestMove;
    }
    int score = std::numeric_limits<int>::min();
    for (Move move : possibleMoves) {
        score = std::max(score, color * findMin(makeMove(b, move, color), alpha,
                                                beta, depth + 1, -color,
                                                bestMove, timeStart).score);
        if (score > bestMove.score) {
            bestMove.x = move.x;
            bestMove.y = move.y;
            bestMove.score = score;
        }
        if (bestMove.score >= beta) {
            return bestMove;
        }
        alpha = std::max(alpha, bestMove.score);
    }
    return bestMove;
}

Move findMin(Board b, int alpha, int beta, int depth, signed int color,
             Move bestMove, int timeStart) {
    std::vector<Move> possibleMoves = findPossibleMoves(b, color);
    int timeNow = 1000*clock()/CLOCKS_PER_SEC;
    bool outOfTime = 0.8*TIME_LIMIT < (timeNow - timeStart)/1e6;
    if (possibleMoves.empty() || depth > DEPTH_LIMIT || outOfTime) {
        bestMove.score = getScore(b);
        return bestMove;
    }
    int score = std::numeric_limits<int>::max();
    for (Move move : possibleMoves) {
        score = std::min(score, color * findMax(makeMove(b, move, color), alpha,
                                                beta, depth + 1, -color,
                                                bestMove, timeStart).score);

        if (score > bestMove.score) {
            bestMove.x = move.x;
            bestMove.y = move.y;
            bestMove.score = score;
        }
        // Pruning
        if (bestMove.score <= alpha) {
            return bestMove;
        }
        beta = std::min(beta, bestMove.score);
    }
    return bestMove;
}

Board copy(Board b) {
    Board newBoard;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            newBoard.board[i][j] = b.board[i][j];
        }
    }
    return newBoard;
}

bool outOfBounds(int x, int y){
    return (x < 0 || x > 7 || y < 0 || y > 7);
}

Board makeMove(Board b, Move m, signed int color) {
    if (m.x == -1) {
        return copy(b);
    }
    Board newBoard = copy(b);
    newBoard.board[m.x][m.y] = color;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int i = dx;
            int j = dy;

            while (newBoard.board[m.x + i][m.y + j] ==
                   newBoard.board[m.x][m.y] * -1 && !outOfBounds(m.x + i, m.y + j)) {
                i += dx;
                j += dy;
            }

            if (!outOfBounds(m.x + i, m.y + j) && newBoard.board[m.x + i][m.y + j]
                    == newBoard.board[m.x][m.y]) {
                i = dx;
                j = dy;

                while (newBoard.board[m.x + i][m.y + j] ==
                       newBoard.board[m.x][m.y] * -1 && !outOfBounds(m.x + i, m.y + j) ) {
                    newBoard.board[m.x + i][m.y + j] = newBoard.board[m.x][m.y];
                    i += dx;
                    j += dy;
                }
            }
        }
    }
    return newBoard;
}


int getScore(Board b) {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            score += b.board[i][j];
        }
    }
    return score;
}

std::vector<Move> findPossibleMoves(Board b, signed int color) {
    std::vector<Move> possibleMoves;
    Move m;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m.x = i;
            m.y = j;
            if (isValid(b, m, color)) {
                m.score = getScore(makeMove(b, m, color));
                possibleMoves.push_back(m);
            }
        }
    }
    return possibleMoves;
}

bool isValid(Board b, Move m, signed int color) {
    if (b.board[m.x][m.y] != 0 || outOfBounds(m.x, m.y)) {
        return false;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                bool leap = false;
                int i = dx;
                int j = dy;
                while (!outOfBounds(m.x + i, m.y + j) &&
                       b.board[m.x + i][m.y + j] == -color) {
                    i += dx;
                    j += dy;
                    leap = true;
                }
                if (!outOfBounds(m.x + i, m.y + j) && leap) {
                    if (b.board[m.x + i][m.y + j] == color) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::string convertMoveToString(Move m) {
    std::string move = "";
    if (m.x == -1){
        return "No valid moves!";
    }
    move += 'a' + m.y;
    move += to_string(m.x + 1);
    return move;
}

Move convertStringToMove(std::string move) {
    Move m;
    m.y = move[0] - 'a';
    m.x = atoi(&move[1]) - 1;
    return m;
}


std::string getPlayerInput() {
    std::string move;
    std::cout << "Enter move: ";
    std::cin >> move;
    return move;
}

void printBoard(Board b) {
    cout << endl << "   A  B  C  D  E  F  G  H" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++) {
            std::cout << setw(2) << b.board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int agentVsAgent(){
    Board b;
    printBoard(b);
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    Move playerMove;
    Move agentMove;
    Move bestMove;
    bestMove.score = std::numeric_limits<int>::min();

    Move bestMove2;
    bestMove2.score = std::numeric_limits<int>::min();

    int counter = 0;
    unsigned long long totalTime = 0;
    while (true) {
        counter++;
        int timeStart = 1000*clock()/CLOCKS_PER_SEC;
        agentMove = findMax(b, alpha, beta, 1, 1, bestMove, timeStart);
        int timeEnd = 1000*clock()/CLOCKS_PER_SEC;
        cout << (timeEnd - timeStart) << endl;
        totalTime += (timeEnd - timeStart);
        cout << "Agent 1 move: " << convertMoveToString(agentMove) << endl;
        b = makeMove(b, agentMove, 1);
        printBoard(b);

        timeStart = 1000*clock()/CLOCKS_PER_SEC;
        playerMove = findMax(b, alpha, beta, 1, -1, bestMove2, timeStart);
        cout << "Agent 2 move: " << convertMoveToString(playerMove) << endl;
        b = makeMove(b, playerMove, -1);
        printBoard(b);
        if (agentMove.x == -1 && playerMove.x == -1) {
            int score = getScore(b);
            cout << "Score: " << score << endl;
            if (score < 0) {
                cout << "Black player wins!" << endl;
            } else if (score > 0) {
                cout << "White player wins!" << endl;
            } else{
                cout << "It's a tie!" << endl;
            }
            cout << "Average time per move: " << totalTime / counter
                 << " milliseconds." << endl;
            return 1;
        }
    }
}

int playerVsAgent(int color){
    Board b;
    printBoard(b);
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    Move playerMove;
    Move agentMove;
    Move bestMove;
    bestMove.score = std::numeric_limits<int>::min();
    int counter = 0;
    unsigned long long totalTime = 0;

    // If player chose black
    if (color == -1) {
        while (true) {
            counter++;
            int timeStart = 1000*clock()/CLOCKS_PER_SEC;
            agentMove = findMax(b, alpha, beta, 1, -color, bestMove, timeStart);
            int timeEnd = 1000*clock()/CLOCKS_PER_SEC;
            totalTime += timeEnd - timeStart;
            cout << "Agent move: " << convertMoveToString(agentMove) << endl;
            b = makeMove(b, agentMove, -color);
            printBoard(b);

            std::vector <Move> possibleMoves = findPossibleMoves(b, color);
            if (!possibleMoves.empty()) {
                cout << "Suggested legal move: "
                     << convertMoveToString(possibleMoves.at(0)) << endl;
                bool validMove = false;
                std::string input;
                do {
                    input = getPlayerInput();
                    playerMove = convertStringToMove(input);
                    if (std::count(possibleMoves.begin(), possibleMoves.end(), playerMove) != 0){
                        validMove = true;
                    } else{
                        cout << "Invalid move, try again: ";
                    }
                } while (!validMove);
                cout << "Player move: " << input << endl;
                b = makeMove(b, playerMove, color);
                printBoard(b);
            } else{
                cout << "No possible moves for the player!" << endl;
                playerMove.x = -1;
            }
            if (agentMove.x == -1 && playerMove.x == -1) {
                int score = getScore(b);
                cout << "Score: " << score << endl;
                if (score < 0) {
                    cout << "Black player wins!" << endl;
                } else {
                    cout << "White player wins!" << endl;
                }
                cout << "Average time per move: " << totalTime / counter
                     << " milliseconds." << endl;
                return 1;
            }
        }
    } else {
        while (true) {
            std::vector <Move> possibleMoves = findPossibleMoves(b, color);
            if (!possibleMoves.empty()) {
                cout << "Suggested legal move: "
                     << convertMoveToString(possibleMoves.at(0)) << endl;
                bool validMove = false;
                std::string input;
                do {
                    input = getPlayerInput();
                    playerMove = convertStringToMove(input);
                    if (std::count(possibleMoves.begin(), possibleMoves.end(), playerMove) != 0){
                        validMove = true;
                    } else{
                        cout << "Invalid move, try again: ";
                    }
                } while (!validMove);
                b = makeMove(b, playerMove, color);
                printBoard(b);
            } else{
                cout << "No possible moves for the player!" << endl;
                playerMove.x = -1;
            }
            int timeStart = 1000*clock()/CLOCKS_PER_SEC;
            agentMove = findMax(b, alpha, beta, 1, -color, bestMove, timeStart);
            int timeEnd = 1000*clock()/CLOCKS_PER_SEC;
            totalTime += timeEnd - timeStart;
            std::cout << "Agent move: " << convertMoveToString(agentMove)
                      << std::endl;
            b = makeMove(b, agentMove, -color);
            printBoard(b);
            if (agentMove.x == -1 && playerMove.x == -1) {
                int score = getScore(b);
                cout << "Score: " << score << endl;
                if (score < 0) {
                    cout << "Black player wins!" << endl;
                } else {
                    cout << "White player wins!" << endl;
                }
                return 1;
            }
        }
    }
}

int countDigits(int n) {
    int digits = 0;
    if (n == 0) {
        return 1;
    }
    while (n != 0) {
        n /= 10;
        digits++;
    }
    return digits;
}


int main() {
    std::cout << "Enter time limit (ms): ";
    cin >> TIME_LIMIT;
    int digits = countDigits(int(TIME_LIMIT));
    DEPTH_LIMIT = min(9.0, TIME_LIMIT / (10 * digits) + 1.0);
    cout << "Agent depth limit: " << DEPTH_LIMIT << endl;

    std::cout << "Choose mode: " << endl
              << "1. Agent vs Agent" << endl
              << "2. Player vs Agent" << endl
              << "3. Agent vs Random" << endl
              << "4. Benchmark" << endl
              << "Your choice: ";
    int choice;
    std::cin >> choice;
    if (choice == 1){
        agentVsAgent();
    } else if (choice == 2){
        std::cout << "Choose color: " << endl
                  << "1. White" << endl
                  << "2. Black" << endl
                  << "Your choice: ";
        cin >> choice;
        if (choice == 1) {
            playerVsAgent(1);
        } else{
            playerVsAgent(-1);
        }
    } else if (choice == 3) {
        agentVsRandom();
    } else{
        agentVsRandomBenchmark();
    }
}

int agentVsRandom(){
    Board b;
    printBoard(b);
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    Move playerMove;
    Move agentMove;
    Move bestMove;
    bestMove.score = std::numeric_limits<int>::min();

    Move bestMove2;
    bestMove2.score = std::numeric_limits<int>::min();

    int counter = 0;
    unsigned long long totalTime = 0;
    while (true) {
        counter++;
        int timeStart = 1000*clock()/CLOCKS_PER_SEC;
        agentMove = findMax(b, alpha, beta, 1, 1, bestMove, timeStart);
        int timeEnd = 1000*clock()/CLOCKS_PER_SEC;
        cout << (timeEnd - timeStart) << endl;
        totalTime += (timeEnd - timeStart);
        cout << "Agent 1 move: " << convertMoveToString(agentMove) << endl;
        b = makeMove(b, agentMove, 1);
        printBoard(b);

        std::vector <Move> possibleMoves = findPossibleMoves(b, -1);
        if (possibleMoves.empty() == 0){
            Move m;
            possibleMoves.push_back(m);
        }
        playerMove = *select_randomly(possibleMoves.begin(), possibleMoves.end());
        cout << "Random move: " << convertMoveToString(playerMove) << endl;
        b = makeMove(b, playerMove, -1);
        printBoard(b);

        if (agentMove.x == -1 && playerMove.x == -1) {
            int score = getScore(b);
            cout << "Score: " << score << endl;
            if (score < 0) {
                cout << "Random player wins!" << endl;
            } else if (score > 0) {
                cout << "Agent wins!" << endl;
            } else{
                cout << "It's a tie!" << endl;
            }
            cout << "Average time per move: " << totalTime / counter
                 << " milliseconds." << endl;
            return 1;
        }
    }
}

int agentVsRandomBenchmark(){
    int agentWins = 0;
    int randomWins = 0;
    int ties = 0;
    for (int game = 0; game < 100; game++) {
        cout << "Game number: " << game+1 << endl;
        Board b;
        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();
        Move playerMove;
        Move agentMove;
        Move bestMove;
        bestMove.score = std::numeric_limits<int>::min();

        Move bestMove2;
        bestMove2.score = std::numeric_limits<int>::min();
        int counter = 0;
        bool newGame = false;
        while (!newGame) {
            counter++;
            int timeStart = 1000 * clock() / CLOCKS_PER_SEC;
            agentMove = findMax(b, alpha, beta, 1, 1, bestMove, timeStart);
            b = makeMove(b, agentMove, 1);

            std::vector<Move> possibleMoves = findPossibleMoves(b, -1);
            if (possibleMoves.empty()) {
                Move m;
                possibleMoves.push_back(m);
            }
            playerMove = *select_randomly(possibleMoves.begin(),
                                          possibleMoves.end());
            b = makeMove(b, playerMove, -1);

            if (agentMove.x == -1 && playerMove.x == -1) {
                int score = getScore(b);
                if (score < 0) {
                    randomWins++;
                } else if (score > 0) {
                    agentWins++;
                } else {
                    ties++;
                }
                newGame = true;
            }
        }
    }
    cout << "Agent wins: " << agentWins << endl
         << "Random wins: " << randomWins << endl
         << "Ties:   " << ties << endl;
    return 1;
}