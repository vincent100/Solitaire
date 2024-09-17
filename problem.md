## Problem:

Given a configuration of Marble Solitaire, find if it is solvable

# Time Complexity:

O(2^N * R * C), where R = #Rows and C = #Columns

# Explanation:

Bitmask DP, where bitmask represents which nodes are filled and which aren't
