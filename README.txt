The most difficult part of the implementation of this assignment was the ai part.
I followed a very straight-forward algorithm for this:
I made a two level deep algorithm using a recursive function(minimax).
After the player made a move,I simply forced the ai to check for each of its own possible move,
checking all the seven possibilities using minimax().That's the first level.
Then,I made the ai test all the possible moves of the player if the ai had made 
that particular move in the second level.From those two level depth I calculated a score.
And,the ai finally made the move that should have given it the highest score.
Here,the the scoring sets who wins the game,the evaluate_board() function does that.
score = -INF denotes the player has won the game,score = INF denotes the ai has won the game.
