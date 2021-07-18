# C-calculator
A lightweight CLI calculator written in C. 

Supports complex order of operations, with basic input validation (incomplete parenthesis, unrecognized characters). 

Under the hood, the calculator parses the user's input, converts it into Polish (postfix) notation using and implementation of Djikstra's Shunting Yard algorithm. 

There are still a few edge cases related to negative numbers -- for example, 4 - - 3. 
