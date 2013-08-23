This commit consists of the first two versions of a calculator, written in C, that handles order of operations. So far, all that it can handle are the four operations of arithmetic without parenthesis. (I plan to support parentheses and exponents in future versions). It takes the problem as a command line argument, constructs a syntax tree, and recursively evaluate the tree to obtain the results. 
The first version does not do the parsing itself. Instead, the user is expected to pass each operator and operand as a seperate parameter like this:

   ./Calc 4 + 7 \* 10 / 2
The astrisk has to be escaped in order to avoid wildcard expasion.
The second version has its own parser, which goes through the first parameter character by character, ignoring spaces. The user passes it one argument like this:

   ./Calc "4+7*10/2"
See the comments within the source code for how the syntax tree is constructed.