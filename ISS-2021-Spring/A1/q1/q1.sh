#!/bash/bin/ 
clear 
echo  ***KNOW YOUR GRAD YEAR*** 
read --p "What is your current Course year:" cyear 
case grad_year on 
{ 
"1") grad_year="2022";; 
"2") grad_year="2021";; 
"3") grad_year="2020";; 
 "4" | "5") grad_year="2020";; 
 *)clear echo "Don’t ask me now!";exit;
 esae 
 clear 
 echo "You will be Graduated in '$grad_year'" 
 echo 
 } 
fi 