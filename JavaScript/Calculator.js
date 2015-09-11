//JavaScript source code
//alert("Started Script");
//document.onload = function () {
    console.log("Started onLoad");
    var form = document.body.getElementsByTagName("form")[0];
    var digits = new Array();
    for (var counter = 0; counter < 10; counter++) {
       var element = document.createElement("input");
       element.setAttribute('type', 'button');
       element.setAttribute('class', 'digits');
       element.setAttribute('id', counter);
       element.setAttribute('value', counter);
       element.addEventListener("click", digit_Onclick.bind(counter));
       form.appendChild(element);
       digits[counter] = element;
       console.log("Added #%d to page.\n", counter);
   }
//}();
function digit_Onclick(digit) {

}
