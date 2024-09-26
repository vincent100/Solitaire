## Problem:

Given a configuration of Marble Solitaire, find if it is solvable

# Time Complexity:

O(2^N * R * C), where R = #Rows and C = #Columns

# Explanation:

Bitmask DP, where bitmask represents which nodes are filled and which aren't
It would also be possible to find a solution, but this would require ~4x more 
memory (as it would store ints instead of bools). It would be possible to 
optimize memory usage by 8x, but the performance would (probably?) not be worth it.

For further solitaire, read github pages
