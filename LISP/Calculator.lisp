(defclass node () ()(:documentation "An abstract class that represents a leaf or branch node.
It has two generics: precedence and proccess-node"))
(defclass branch-node (node)
  ((operator :initarg :operator
	     :documentation "This slot should contain a character, such as #\\+")
   (left-node :initarg :left-node)
   (right-node :initarg :right-node :initform nil)))
(defclass leaf-node (node)
  ((operand :initarg :operand) ()))
(defgeneric proccess-node (node)
  (:documentation "Proccesses a node that it is passed."))
(defgeneric precedence (node)
  (:documentation "Returns a number representing the precedence of the node in terms of order of
 operations, such as 1 for addition and 2 for multiplication."))
(defmethod proccess-node ((node leaf-node))
  "Returns the operand that the node represents"
  (slot-value node 'operand))
(defmethod proccess-node ((node branch-node))
  "Returns the result of the operator that the node represents, performed on its two children"

  ;;Call the operator that the node represents on what tbis generic returns for the left-node
  (funcall (parse-operator (slot-value node 'operator)) 
  ;;If its child is a leaf node then proccess-node will return the operand, and that is the base
  ;; case. If it is a branch-node, then this function will recursively call itself.
	   (proccess-node (slot-value node 'left-node))  
	   (proccess-node (slot-value node 'right-node))))
(defmethod precedence ((node leaf-node))
"A leaf node always has highest precedence"
  4)
(defmethod precedence ((node branch-node))
"Takes a node and returns an integer representing its precedence in order of operations.
For example, precedence(+) returns 1"
(if (null (slot-value node 'operator))
    0
  (case (slot-value node 'operator)
	((#\+ #\-) 1)
	((#\* #\/) 2)
	(#\^ 3)
	(otherwise (error "Invalid Operator, thrown by precedence.")))))
(defun parse-operator (operator)
"Takes a character with an operator and returns a pointer to the appropriate function"
  (case operator
	(#\+ #'+)
	(#\- #'-)
	(#\* #'*)
	(#\/ #'/)
	(#\^ #'expt)
	(otherwise (error "Invalid Operator"))))
(defun make-branch (operator left-operand &optional (right-operand nil))
  (make-instance 'branch-node :operator operator
		 :left-node left-operand :right-node right-operand))
(defun make-leaf (operand)
  (make-instance 'leaf-node :operand operand))
(defun parse-expression (expression)
"This is a recursive function that takes an expression (such as 3*4+2) and turns it into
a tree.  "
;;;It parses one expression, resulting in a node called toInsert, and calls itself on the rest of
;;;the expression, which returns a tree that is bound to next-node.  Then, it uses the 
;;;find-position function to find the position among the children of next-node in which to insert 
;;;to-insert.

;;;This is how it determines where to insert the node:
;;;find-position is used to find the parent node for to-insert.  Since it is possible that 
;;;to-insert should be made the root node (for example, if it is addition and next-node is 
;;;multiplication), it passes find-position temp-root, whose left node is the current root, which
;;;is next-root.  insert-under will go down the left side of the tree and return the first node
;;;whose left child is of greater precedence than the node to insert (in other words, the uppermost
;;;node that should be lower on the tree than the node to insert).  Then, to-insert is inserted as
;;;the left node of insert-under and what used to be the left node of insert-under becomes the 
;;;right-node of to-insert.  temp-root is created so that the same code would work to replace
;;;the root-node (next-node) with to-insert.

;;This is the base case. It is invoked when it reaches the end of the list
  (if (= (length expression) 1)
      (make-leaf (first expression))
    ;;The operand is the first element of the list and the operator is the second element.
    (let* ((operand (first expression)) (operator (second expression))
	   ;;Bind next-node to the return value of a recursive call of this function
	   (next-node (parse-expression (subseq expression 2)))
	   (to-insert (make-branch operator (make-leaf operand)))
	   (temp-root (make-branch nil next-node))
	   ;;insert-under is the node that should be the parent of to-insert
	   (insert-under (find-position to-insert temp-root)))
      ;;The first statement within the let is to assign to-insert's right node to be what is now
      ;;the left node of insert-under.
      (setf (slot-value to-insert 'right-Node) (slot-value insert-under 'left-Node))
      (setf (slot-value insert-under 'left-Node) to-insert)
      ;;This line ensures that the function always returns what is now the root-node, whether it
      ;;is next-node or if it is to-insert (if to-insert has lower precedence and replaced 
      ;;next-node as the root node).
      (slot-value temp-root 'left-node))))

					   
  (defun find-Position(to-insert root-node)
"Takes the root node of a tree and finds the node under which a node with the specified operator
should be inserted"
;;;This function recursively transverses the tree, going down the left side until it reaches
;;;the first node whose left child is of higher precedence than the node to be inserted (in other
;;;words, that should be lower on the tree than to-insert).
    (if (> (precedence to-insert) (precedence (slot-value root-node 'left-node)))
	(find-position to-insert (slot-value root-node 'left-node))
      root-node))
;;Here is the actual interface
(format t "Enter an expression to evaluate.  Make sure to surround it with parentheses and to 
preface operators with #\\~%")
(let ((expression (read)))
  (format t "The result of the calculation is ~5$~%" 
	  (proccess-node (parse-expression expression))))
