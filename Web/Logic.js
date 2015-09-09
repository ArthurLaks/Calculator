/**
   This module contains the logic that is used to construct and proccess the tree.  It interacts
   with the other module (Interface.js) in three ways: through the enterOperator, calculateResult,
   and reset functions.
   The enterOperator function is to be called after the user enters a number and clicks on an
   operator (in other words, it is called from the operators' click event handler).  It takes the
   operand and operator and inserts them at the correct place in the syntax tree.
   The calculateResult function is to be called when the user finishes entering
   a problem (in other words, from the click event handler of the '=' button).  It takes the last
   operand that the user entered, inserts it into the last open spot in syntax tree, recursively
   proccesses the tree, and returns the result of the calculation.  
   The reset function is also to be called when the user presses equals.  It resets the tree.
   All of the functions and objects associated with the tree are kept local to the module because
   they are defined in an IIFE.  The enterOperator and calculateResult functions are exported by
   being attached to the logic object, which is defined outside of the IIFE.
*/
var logic=new Object();
~function (){
    //This variable maps every operator to its place in order of operations. The empty string is
    //used by the enterOperator function for tempRoot (see the comments there).
    var precedence={'+':1,'-':1,'*':2,'/':2,'^':3,'':0};
    /**
       Initializes a branch node.
       @param operator A single character that represents an operator ('+','-','*', or '^').
       */
    function BranchNode(leftNode,operator,rightNode){
	this.leftNode=leftNode;
	this.operator=operator;
	this.rightNode=rightNode;
    };
    /**
       Returns a number representing the place of the operator that the node represents in terms
       of order of operations (eg. 1 for + and -).
    */
    BranchNode.prototype.precedence=function(){
	return precedence[this.operator];
    };
    /**
       Recursively evaluates the node and its subnodes.
       @return Returns the result of the operator that the node represents perfomed its children.
    */
    BranchNode.prototype.proccess=function(){
	switch(this.operator){
	case '+':
	    return this.leftNode.proccess()+this.rightNode.proccess();
	case '-':
	    return this.leftNode.proccess()-this.rightNode.proccess();
	case '*':
	    return this.leftNode.proccess()*this.rightNode.proccess();
	case '/':
	    return this.leftNode.proccess()/this.rightNode.proccess();
	}
    };
    /**
       Creates a leaf node containing an operand.
    */
    function LeafNode(operand){
	this.operand=operand;
    }
    /**
       @return the operand that the node contains.
    */
    LeafNode.prototype.proccess=function(){
	return this.operand;
    }
    /**
       The precedence of an operand is highest because it is always grouped with an adjacent
       operator. 
    */
    LeafNode.prototype.precedence=function(){
	return 4;
    }
    var rootNode=null;
    //The previously inserted node.  It is neccessary to keep track of it in order to determine
    //whether the next operand should be grouped with it or the next operator, depending on which
    //one has higher precedence.
    var previousNode=null;
    /**
       Takes an operand and operator and inserts them in the correct place in the tree.
       @param operand the operand as a number
       @param operator the operator as a single character (eg '+').
    */
    logic.enterOperator=function(operand,operator){
	var operandNode=new LeafNode(operand);
	var toInsert=new BranchNode(operandNode,operator);
	//If this function is being called the first time, initialize the root node and skip
	//the code that determines where to insert the operator
	if(rootNode==null)
	    rootNode=toInsert;
	else{
	    //This is how the program determines where to insert a node (for more detail, see the 
	    //c version of this program):

	    //The program transverses the syntax tree, going through the right child of each node
	    //until it reaches a node whose child is of higher or equal precedence than the one
	    //to be inserted (in other words, that should be lower on the tree).  The node to be
	    //inserted is assigned to be the right child of that node.  If it is of greater 
	    //precedence than the previously inserted operator than the operand is grouped with
	    //it.  Otherwise, the operand is grouped with the previous node as its right child.

	    //tempRoot is where the for loop starts transversing the tree.  It is created so that
	    //a case where toInsert is of lower or equal precedence than the current root and
	    //is supposed to be above the current root and replace it as the root node is handled 
	    //correctly.  Therefore, insertUnder.rightNode will always be the node that belongs
	    //below the one that is being inserted.
	    var tempRoot=new BranchNode(undefined,'',rootNode);  //'' has a precedence of 0.
	    //This loop transverses the right side of the syntax tree until it reaches the
	    //first node whose right node is of higher or equal precedence to the one being 
	    //inserted.
	    for(var insertUnder=tempRoot;
		insertUnder.rightNode!=undefined&&
		precedence[insertUnder.rightNode.operator]<precedence[operator];
		insertUnder=insertUnder.rightNode)
		;
	    //If operator is of greater precedence than the previously inserted operator then the
	    //operand should be grouped with it.  In such a case, insertUnder is the same as 
	    //previousNode, and, since toInsert is assigned to its insertUnder.rightNode in the
	    //line after the if statement, it will not be left uninitialized.
	    if(precedence[operator]>precedence[previousNode.operator]){
		toInsert.leftNode=operandNode;
	    }else{
		//If toInsert should be above previousNode and not at the bottom of the tree,
		//group the operand with the previous operator, whose right node would otherwise
		//be left hanging, and assign the part of the tree below insertUnder (which is of
		//higher precedence so it should be lower on the tree than toInsert) to toInsert's
		//leftNode.  Either way, toInsert's right node is left hanging until the next 
		//operator is inserted and the function is called again.
		previousNode.rightNode=operandNode;
		toInsert.leftNode=insertUnder.rightNode;
	    }
	    insertUnder.rightNode=toInsert;
	  
	    //If toInsert was supposed to replace the root node (see ealier comment blocks), this
	    //line does it.  If not, it does nothing because tempRoots right node started out as
	    //rootNode.
	    rootNode=tempRoot.rightNode;
	}
	previousNode=toInsert;
    };
    /**
       Completes the syntax tree, evaluates it, and returns the result.
       @param operand the final operand.
       @return the result of evaluating the tree.
    */
    logic.calculateResult=function(operand){
	previousNode.rightNode=new LeafNode(operand);
	return rootNode.proccess();
    }
    /**
       Resets the calculator for a new calculation.
    */
    logic.reset=function(){
	rootNode=null;
	previousNode=null;
    };

}();
