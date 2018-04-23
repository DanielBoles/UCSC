Name: Daniel Boles
Email: dawboles@ucsc.edu
Assignment: CS109 HW4
Collaboration: None
Time Spent: 10hrs

Within this assignment I created a small game of Hex (5x5). I was very overwhelmed with the assignment at first. But I broke it down into segments that I worked on all weekend. The idea I had was to create a forest of existing graphs that would be checked for a path from one end to another end (victory) but I was unable to get a graph
or algorithm working to check for such. Instead I used a few arrays. I broke the game down sort of like how I
worked through the game in my CE100 class. I made the game have a few different states. I have a state for each players turn as well as the state for the game to begin. 

There are 2 bugs in my code. One is the code does not work well with finding appropriate paths throug the Hex 
board. This meaning it only can check for linear victory (all 5 numbers sequentially: 1, 2, 3, 4, 5 or 1, 6, 11, 16, 21, etc.). The other bug I have is the printed version of the board is using a string array and I cannot seem to figure out how to insert or edit a member of the string array without adding a nul termination point. This only affects the board that is printed, and it covers the next space up with a blank spot after a move is take. 
Once I had a working 2 player mode, I randomized some of the responses for one of the players and created a 
single player mode as well as a 0 player mode. The 0 player mode does not function well as it is fully 
randomized, which leads to a lot of draws. But otherwise I will be working more on this soon.