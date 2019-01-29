# Connect Three Game Tree
*Connect Three* is a version of popular Connect Four game. It is played on a 5x5 board and the winner is the first person to connect 3 disks horizontally, vertically or diagonally. 

This project builds a Game Tree from given board state of the game. Game Tree starts from given state and evaluates all possible moves for both players in their own turn until either board is full or one of players has won. Each game state is given state that's calculated using MiniMax method.

Game state was implemented with space efficiency in mind using bit fields and bit packing. 
