The LISP version does not support parentheses and does not have a 
proper tokenizer.  (I have not gotten around to adding those features).

The syntax tree is represented via a class hierarchy (using CLOS).
There is a base node class, inherited by branch and leaf.

The LISP version uses a modified version of the parsing algorithm that is 
designed to use recursion instead of iteration when processing 
operand-operator pairs.  The parse function peels off the first two
tokens (operand and operator), calls itself on the rest, and incorperates
the first two tokens into that tree.

Due to the lack of a tokenizer, the expression has to be put in 
parantheses, tokens must be delimited by space, and operators must be
preceded by #\, as the program explains when it is invoked.