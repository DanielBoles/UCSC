/*
    Name: Daniel Boles
    Class: CS109
    Professor: Ira Pohl
    Date 11/29/17
    Assignment: HW5

*/
#include<bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

# define INF 0x3f3f3f3f
const int BOARDSIZE = 25;
// intPair is the name I will use for this Integer Pair
typedef pair<int, int> intPair;

// For this graph class I will be using Adjacencly List representation.
class Graph {
    int V;
    list< pair<int, int> > *adj;
    char sBoard;

public:
    Graph(int V);  // Constructor
    void addEdge(int u, int v, int w);  // Simple function to add an edge to graph with a weight
    void printGraph(char sBoard[]);
};

// The Graph constructor will allocate memory for adjacency list
Graph::Graph(int V) {
    this->V = V;
    adj = new list<intPair> [V];
}

// This is the same edge function as used for dijkstra's in HW2
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// Prints the graph such that it is represented by Hex
void Graph::printGraph(char sBoard[]){
  cout           // Printout of the current game board.
        << "   ___ " << endl
        << "  / " << sBoard[1] << " \\___ "<< endl
        << "  \\___/ " << sBoard[2] << " \\___ B"<< endl
        << "  / " << sBoard[6] << " \\___/ " << sBoard[3] << " \\___ "<< endl
        << "  \\___/ " << sBoard[7] << " \\___/ " << sBoard[4] << " \\___ "<< endl
        << "R / " << sBoard[11] << " \\___/ " << sBoard[8] << " \\___/ " << sBoard[5] << " \\ "<< endl
        << "  \\___/ " << sBoard[12] << " \\___/ " << sBoard[9] << " \\___/ "<< endl
        << "  / " << sBoard[16] << " \\___/ " << sBoard[13] << " \\___/ " << sBoard[10] << " \\ "<< endl
        << "  \\___/ " << sBoard[17] << " \\___/ " << sBoard[14] << " \\___/ "<< endl
        << "  / " << sBoard[21] << " \\___/ " << sBoard[18] << " \\___/ " << sBoard[15] << " \\ "<< endl
        << "  \\___/ " << sBoard[22] << " \\___/ " << sBoard[19] << " \\___/ "<< endl
        << "      \\___/ " << sBoard[23] << " \\___/ " << sBoard[20] << " \\ "<< endl
        << "          \\___/ " << sBoard[24] << " \\___/ "<< endl
        << "              \\___/ " << sBoard[25] << " \\ "<< endl
        << "                  \\___/ "<< endl;
}
bool pathCheckR(int array[]){
    // This is my mostly-working algorithm. Albeit quite extensive, it works for most cases and I built it from the ground up
    int i = 1, j, k, l, m;
    int position = 1;
    while(i < 22){  // first position
      //cout << "inside r, iteration: " << i << endl;
      while(position == 1 && i < 22){     // The board checks the edge to see if it is filled in any space
        //cout << "in position 1" << endl;// if the board is filled along the edge, it begins to crawl forward
        if(array[i] != i){
          i += 5;
          continue;
        }
        if(i != 1 && array[i - 4] == i - 4){
          j = i - 4;
          position += 1;
          break;
        }
        else if(array[i + 1] == i + 1){
          j = i + 1;
          position += 1;
          break;
        }
        else if(i != 21 && array[i + 5] == i + 5){
          i += 5;
        }
        else i += 5;    // No path found but check the next filled space at position 1.
      }

      while(position == 2 && j < 23){ // second position
        //cout << "in position 2" << endl;
        if(j != 2 && array[j - 4] == j - 4){
          k = j - 4;
          position += 1;
          break;
        }
        else if(array[j + 1] == j + 1){
          k = j + 1;
          position += 1;
          break;
        }
        else if(j != 22 && array[j + 5] == j + 5){
          j += 5;
        }
        else{     // There is no path from the second space to the third
          i += 5;
          position = 1;
          break;
        }
      }
      while(position == 3 && k < 24){ // third position
        //cout << "in position 3" << endl;
        if(k != 3 && array[k - 4] == k - 4){
          l = k - 4;
          position += 1;
          break;
        }
        else if(array[k + 1] == k + 1){
          l = k + 1;
          position += 1;
          break;
        }
        else if(k != 23 && array[k + 5] == k + 5){
          k += 5;
        }
        else{
          i += 5;
          position = 1;
          break;
        }
      }
      while(position == 4 && l < 24){ // fourth position
        //cout << "in position 4" << endl;
        if(l != 4 && array[l - 4] == l - 4){
          m = l - 4;
          position += 1;
          break;
        }
        else if(array[l + 1] == l + 1){
          m = l + 1;
          position += 1;
          break;
        }
        else if(l != 24 && array[l + 5] == l + 5){
          l += 5;
        }
        else{
          i += 5;
          position = 1;
          break;
        }
      }
      if(position == 5){ // fifth position
        return 1;
      }
    }
    return 0;
}
bool pathCheckB(int array[]){
    // This is my mostly-working algorithm. Albeit quite extensive, it works for most cases and I built it from the ground up
    int i = 1, j, k, l, m;
    int position = 1;
    while(i < 6){  // first position
      //cout << "inside b, iteration: " << i << endl;
      while(position == 1 && i < 6){
        //cout << "in position 1" << endl;
        if(array[i] != i){
          i++;
          continue;
        }
        if(i != 1 && array[i + 4] == i + 4){
          j = i + 4;
          position += 1;
          break;
        }
        else if(array[i + 5] == i + 5){
          j = i + 5;
          position += 1;
          break;
        }
        else if(array[i + 1] == i + 1){
          i++;
        }
        else i++;
      }

      while(position == 2 && j < 11){ // second position
        //cout << "in position 2" << endl;
        if(j != 6 && array[j + 4] == j + 4){
          k = j + 4;
          position += 1;
          break;
        }
        else if(array[j + 5] == j + 5){
          k = j + 5;
          position += 1;
          break;
        }
        else if(j != 10 && array[j + 1] == j + 1){
          j++;
        }
        else{
          i++;
          position = 1;
          break;
        }
      }
      while(position == 3 && k < 16){ // third position
        //cout << "in position 3" << endl;
        if(k != 11 && array[k + 4] == k + 4){
          l = k + 4;
          position += 1;
          break;
        }
        else if(array[k + 5] == k + 5){
          l = k + 5;
          position += 1;
          break;
        }
        else if(k != 15 && array[k + 1] == k + 1){
          k++;
        }
        else{
          i++;
          position = 1;
          break;
        }
      }
      while(position == 4 && l < 21){ // fourth position
        //cout << "in position 4" << endl;
        if(l != 16 && array[l + 4] == l + 4){
          m = l + 4;
          position += 1;
          break;
        }
        else if(array[l + 5] == l + 5){
          m = l + 5;
          position += 1;
          break;
        }
        else if(l != 20 && array[l + 1] == l + 1){
          l++;
        }
        else{
          i++;
          position = 1;
          break;
        }
      }
      if(position == 5){ // fifth position
        return 1;
      }
    }
    return 0;
}

/* function minimax(node, depth, maximizingPlayer)
     if depth = 0 or node is a terminal node
         return the heuristic value of node

     if maximizingPlayer
         bestValue := −∞
         for each child of node
             v := minimax(child, depth − 1, FALSE)
             bestValue := max(bestValue, v)
         return bestValue

     else    (* minimizing player *)
         bestValue := +∞
         for each child of node
             v := minimax(child, depth − 1, TRUE)
             bestValue := min(bestValue, v)
         return bestValue                           */

int main()
{
    char board[BOARDSIZE];
    char sBoard[BOARDSIZE+2] = "0123452....3....4....5....";
    int redBoard[BOARDSIZE], blueBoard[BOARDSIZE];
    char player1 = 'R';
    char player2 = 'B';
    char activeTurn = '0';
    static short turnCount = 0;
    static short playerCount = 0;
    cout  << " ~ Game of Hex - First Draft ~ " << endl;
    // Construct the 25 Vertex Hex Graph
    int V = 25;                     // I end up using arrays but I would like to use a graph instead
    Graph g(V);
    g.printGraph(sBoard);
    short position = 0;             // Originally I was using coordinates
    cout << "How many players?:";
    cin >> playerCount;
    srand(time(NULL));
    if(rand() % 2 + 1 == 1){        // coin toss for who goes first
        activeTurn = 'R';
    }
    else{
        activeTurn = 'B';
    }

    for(int i = 0; i < 26; i++){    // Initialize the board to 0 in all locations
        board[i] = 0;
    }

    cout << "Player" << activeTurn << " goes first." << endl;       // Begin game.
    turnCount = 1;
    while(activeTurn != 0){
        if(playerCount == 0){         // This is the fully randomized game
          position = 0;               // note that the algorithm sometimes bugs out and crashes in this mode
          position = rand()% 25 + 1;
          if(board[position] == 0){   // Here if we have an unfilled space we continue to fill the game board
              if (activeTurn == 'R'){
                  board[position] = 'R';
                  sBoard[position] = 'R';
                  redBoard[position] = position;
                  activeTurn = 'B';
                  turnCount++;
                  if(turnCount > 9){
                      if(pathCheckR(redBoard)){
                        cout << " ~ Red Victory ~ " << endl;  // Printout of the finished game board.
                        g.printGraph(sBoard);
                        turnCount = 0;
                        activeTurn = 0;
                        break;
                      }
                  }
              }
              else{
                  board[position] = 'B';
                  sBoard[position] = 'B';                   // Keeping track of the Game Board
                  blueBoard[position] = position;           // Potentially could use edges but instead I am filling an array
                  activeTurn = 'R';                         // Change turns
                  turnCount++;
                  if(turnCount > 9){                        // If enough moves have passed, check for victory
                      if(pathCheckB(blueBoard)){
                        cout << " ~ Blue Victory ~ " << endl;// Printout of the finished game board.
                        g.printGraph(sBoard);
                        turnCount = 0;
                        activeTurn = 0;
                        break;
                      }
                  }
              }
          }
          if(turnCount == 26){
            g.printGraph(sBoard);          // Since this game is fully randomized, there will be cats games
            cout <<  "Cats Game!";
            break;
          }
          continue;
        }
        if(playerCount == 1){             // Single player game
          if(activeTurn == 'R'){
            position = 0;
            cout << "Choose your move position 1-25: ";
            cin >> position;
          }
          if(activeTurn == 'B'){
            position = 0;
            position = rand()% 25 + 1;
          }
          if(board[position] == 0){       // Here if we have an unfilled space we continue to fill the game board
              if (activeTurn == 'R'){
                  board[position] = 'R';
                  sBoard[position] = 'R';
                  redBoard[position] = position;
                  activeTurn = 'B';
                  turnCount++;
                  if(turnCount > 9){
                      if(pathCheckR(redBoard)){
                        cout << " ~ Red Victory ~ " << endl;// Printout of the finished game board.
                        g.printGraph(sBoard);
                        turnCount = 0;
                        activeTurn = 0;
                        break;
                      }
                  }
              }
              else{
                  board[position] = 'B';
                  sBoard[position] = 'B';                   // Keeping track of the Game Board
                  blueBoard[position] = position;           // Potentially could use edges but instead I am filling an array
                  activeTurn = 'R';                         // Change turns
                  turnCount++;
                  cout  << " ~ Game of Hex ~ " << endl;     // Printout of the current game board.
                  g.printGraph(sBoard);
                  cout << "Player" << activeTurn << "'s turn." << endl;
                  if(turnCount > 9){                        // If enough moves have passed, check for victory
                      if(pathCheckB(blueBoard)){
                        cout << " ~ Blue Victory ~ " << endl;// Printout of the finished game board.
                        g.printGraph(sBoard);
                        turnCount = 0;
                        activeTurn = 0;
                        break;
                      }
                  }
              }
          }
          else{
              cout << "Invalid: Postion already filled!" << endl;
          }
          if(turnCount == 26){
            g.printGraph(sBoard);
            cout <<  "Cats Game!";    // There will sometimes be cats games
            break;
          }
          continue;
        }
        position = 0;
        cout << "Choose your move position 1-25: ";
        cin >> position;
        while(position > 25 || position < 1){
            cout << "Sorry please reselect between the range of 1-25:";
            cin >> position;
        }

        if(board[position] == 0){     // Here if we have an unfilled space we continue to fill the game board
            if (activeTurn == 'R'){
                board[position] = 'R';
                sBoard[position] = 'R';
                redBoard[position] = position;
                activeTurn = 'B';
                turnCount++;
                if(turnCount > 9){
                    if(pathCheckR(redBoard)){
                      cout << " ~ Red Victory ~ " << endl;  // Printout of the finished game board.
                      g.printGraph(sBoard);
                      turnCount = 0;
                      activeTurn = 0;
                      break;
                    }
                }
            }
            else{
                board[position] = 'B';
                sBoard[position] = 'B';                 // Keeping track of the Game Board
                blueBoard[position] = position;         // Potentially could use edges but instead I am filling an array
                activeTurn = 'R';                       // Change turns
                turnCount++;
                if(turnCount > 9){                      // If enough moves have passed, check for victory
                    if(pathCheckB(blueBoard)){
                      cout << " ~ Blue Victory ~ " << endl; // Printout of the finished game board.
                      g.printGraph(sBoard);
                      turnCount = 0;
                      activeTurn = 0;
                      break;
                    }
                }
            }
        }
        else{
            cout << "Invalid: Postion already filled!" << endl;
        }
        cout  << " ~ Game of Hex ~ " << endl;          // Printout of the current game board.
        g.printGraph(sBoard);
        if(turnCount == 26){
          g.printGraph(sBoard);          // Sometimes there will be cats games
          cout <<  "Cats Game!";
          break;
        }
        cout << "Player" << activeTurn << "'s turn." << endl;

    }
    return 0;
}
