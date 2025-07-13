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
graphGen.cpp generate a directed graph with each node as a city
and each edge as a flight service from one node to the
other. The output is in the format of:
-------------------------------------------------------------
From:   Moscow, Russia
To  :   Beijing, People's Republic of China
        Montevideo, Uruguay

From:   Hong Kong, SAR
To  :   Miami, United States
        Dhaka, Bangladesh
...
-------------------------------------------------------------  

WA.cpp will be basically reading from city.name and flight.txt and intializes a
adjacency matrix which is based on graph representation of the flight actual
information.  The program assigns each city a unique integer ID and then displays flight information from each city to other cities using these IDs.

Compiling the graphGen Program:

Open a terminal window.
Change the current working directory to the location of the graphGen.cpp file using the cd command. Replace your_directory_path with the path to the directory containing your file:

cd your_directory_path


now , Enter the following command to compile graphGen.cpp into an executable:
g++ graphGen.cpp -o graphGen


This command will be  invoking the g++ compiler, compiles graphGen.cpp, and outputs an executable named graphGen.

Running the graphGen Program:

To run the graphGen executable, use the following command, replacing <number_cities> with the desired number of cities (between 1 and 140):

./graphGen <number_cities>

This command executes the graphGen program, which generates data for the specified number of cities.


Compiling the WA Program:

Ensure that you are in the directory containing WA.cpp.
Compile WA.cpp by entering the following command:


g++ WA.cpp -o WA


Running the WA Program:

To execute the WA program, simply type

./WA



