This repository consists of four versions of a calculator, written in C, that handles order of operations. It takes the problem as a command line argument, constructs a syntax tree, and recursively evaluate the tree to obtain the results. 
The first version can only handle the four operations of arithmetic without parenthesis. It does not do the parsing itself. Instead, the user is expected to pass each operator and operand as a seperate parameter like this:

      ./Calc 4 + 7 \* 10 / 2

The astrisk has to be escaped in order to avoid wildcard expasion.
The second version has its own parser, which goes through the first parameter character by character, ignoring spaces. The user passes it one argument like this:

   ./Calc "4+7*10/2"

The parser is in a seperate module called Parser.c.
The third version adds support for expontentiation. In order to support order of operations with three levels, it changes the algorithm with which the syntax tree is constructed. In the proccess, it solves a bug that my roomate noticed in the first two versions. They solve multiplication and division right-to-left, instead of left-to-right. The third version handles them correctly.
The fourth version adds support for parentheses. It also further modularizes the code. Calculator.c consists entirely of the main function, which simply calls functions from other modules to construct the tree from the parameter and proccess it, and then it displays the result. CreateTree.c contains the code to syntax tree using the parser. It is the longest module by far. ProccessTree.c contains the proccessNode function, which recursively evaulates each node to produce the result. Parser.c is almost completely unmodified. Since three modules use the tree (Calculator.c, CreateTree.c and ProccessTree.c), the node struct has to be kept in its own header file, called Node.h.
