//Uses an IIFE for encapsulation.
-function(){
    //Add ten buttons to the form, one for each digit.
    var form = document.body.getElementsByTagName("form")[0];
    var digits = [];
    for (var counter = 0; counter < 10; counter++) {
	//The button to add to the form
	var element = document.createElement("input");
	element.setAttribute('type', 'button');
	element.setAttribute('class', 'digits');
	element.setAttribute('id', counter);
	element.setAttribute('value', counter);
	//Curries the digit to the even handler.  Therefore, the first 
	//argument to digit_Onclick is the digit the button represents.
	element.addEventListener("click", digit_Onclick.bind(null,counter));
	form.appendChild(element);
	digits.push(element);   //Add the button to the array of digits.
    }
    //For each operator, add its event listener.
    ['+','-','*','/'].forEach(function(operator){
	var element=document.getElementById(operator);
	//As with the digits, curry a character reperesenting the operator to
	//the event handler.
	element.addEventListener("click",operator_Onclick.bind(null,operator));
    });
    document.getElementById('=').addEventListener("click",equal_OnClick);
    document.getElementById('clear').addEventListener("click",clear_OnClick);
    //This variable stores the number that the user is currently entering.
    var cOperand=0;
    var eoOperation=true;
    var display=document.getElementById('display');
    /**
       Updates cOperand by appending a digit to it.
    */
    function digit_Onclick(digit) {
	//Append the digit to cOperand by multiplying it by ten and adding 
	//digit to it.
	cOperand*=10;
	cOperand+=digit;
	if(eoOperation){
	    display.textContent=digit;
	    eoOperation=false;
	}else
	    display.textContent+=digit;
    }
    function operator_Onclick(operator){
	logic.enterOperator(cOperand,operator);
	display.textContent+=operator;
	cOperand=0;
    }
    function equal_OnClick(){
	display.textContent=logic.calculateResult(cOperand);
	cOperand=0;
	logic.reset();
	eoOperation=true;
    }
    function clear_OnClick(){
	cOperand=0;
	eoOperation=true;
	display.textContent='0';
	logic.reset();
    }
}();
