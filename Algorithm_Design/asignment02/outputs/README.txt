ANALYSIS OF COMPUTER ALGORITHMS 
ASSIGNMENT 04

--------------------------------------------------------------------------------------------------------------------------------------
euid : gg0640 

I use a MacOS so this requires some softwares like 
1. filezilla 
2. terminal with xcode installed tools 
3. cisco any connect app . 

--------------------------------------------------------------------------------------------------------------------------------------
"I had implemented the code and then made changes to the given code by inserting the required code in the implementation part of the code only . " 

--------------------------------------------------------------------------------------------------------------------------------------
STEPS FOLLOWED TO CONNECT TO THE SERVER AKA CELL MACHINE ON THE SERVER . 

a. First thing to do is install the cisco connect which will let me work from my home . 
b. then i had setup a connection to the unt servers using vpn by cisco by using vpn.unt.edu
c. Then i had access to the cell machine server which is basically from a ubuntu software by using a command :% ssh gg0640@CELL06-CSE.ENG.UNT.EDU
d. This sets us up with a connection after some questions . 
e. Then , the next goal is to make a setup with the filezilla so that i can forward the code file to the server .
f. Filezilla can be made connected to the server by using the hostname as CELL06-CSE.ENG.UNT.EDU and username as 'gg060' with my password and the port number as 22 , by pressing on quick connect this sets a file transfer sharing between filezilla and server . 
g. Then i dropped the respective file into the server . filezilla allows you to 'drag and drop'.
h. then i had choosen one algorithm after one and then compiled it . 
i . This code is already written before so all the compilation errors are being resolved.

Compilation of codes: 
a. In order to compile the codes , we use the command 

       g++ *.cpp or the g** algorithm_file_name.cpp

b. If it doesnt reply anything then the compilation is executed successfully or else it returns with the errors. 
c. Then we test with the inputs files inputs by 
       
        ./a.out .. /inputs/input.10.1

d. To get the real runtime to calculate the average run time we use .
     
  $ time for f in ../inputs/input.10.1; do echo $f; ./a.out $f; done

Then all the run times are being noted with each algorithm being tested with multiple input values.

--------------------------------------------------------------------------------------------------------------------------------------

Screenshots and brief analysis of four sorting algorithms are explained in the pdf 
run time analysis are being stored in runtimes.pdf. 

