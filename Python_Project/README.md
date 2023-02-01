![image](https://user-images.githubusercontent.com/79211949/208044981-1c9d5d66-4e40-4c05-b0d7-5ec9f20953f1.png)

MINMAX Algorithm 

To begin, let's start by defining what it means to play a perfect game of tic tac toe:

If I play perfectly, every time I play I will either win the game, or I will draw the game. Furthermore if I play against another perfect player, I will always draw the game.

How might we describe these situations quantitatively? Let's assign a score to the "end game conditions:"

What is Minimax?
Minimax is a artificial intelligence applied in two player games, such as tic-tac-toe, checkers, chess and go. This games are known as zero-sum games, because in a mathematical representation: one player wins (+1) and other player loses (-1) or both of anyone not to win (0).

How does it works?
The algorithm search, recursively, the best move that leads the Max player to win or not lose (draw). It consider the current state of the game and the available moves at that state, then for each valid move it plays (alternating min and max) until it finds a terminal state (win, draw or lose).
![image](https://user-images.githubusercontent.com/79211949/208045415-68014635-83a9-4b94-9ac8-8644b3e4687a.png)

![image](https://user-images.githubusercontent.com/79211949/208045257-a8220483-2b3b-4b60-acf6-c32edb6e0074.png)




Bibliografy:

- https://www.pygame.org/docs/
- https://www.researchgate.net/figure/Game-tree-for-Tic-Tac-Toe-game-using-MiniMax-algorithm_fig1_262672371
- https://www.neverstopbuilding.com/blog/minimax

CODE:

- https://github.com/AlejoG10/python-tictactoe-ai-yt
- https://github.com/CaptainRavel/TicTacToe-Pygame-PvP-PvC
- https://github.com/Cledersonbc/tic-tac-toe-minimax

