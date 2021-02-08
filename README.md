# Linux Shell
_Creators:_   
_Yuvraj Singh Malhi (BITS Pilani Electronics)_   
_Shivam Goyal       (BITS Pilani Computers)_   


## Description
This is a linux shell, written in C with a sweet interface and with added functionality of a few custom commands.

### Intallation
Simple download shell.c, compile, and run the code.
To do this:   
``` git clone https://github.com/yuvrajmalhi/Linux-Shell.git```   
``` cd Linux-Shell/ ```   
``` gcc shell.c ```   
``` sudo ./a.out ```   

Give yes/y if you want to print all the details (PIDs, FDs, status) of each command. i recommend entering 'n' or 'No'.

![1-setup](https://user-images.githubusercontent.com/76866159/107150019-b9924280-6981-11eb-8889-60688b4136e9.gif)


### Features
1. **General Terminal commands** - The shell supports general commands like ls, cat, grep, who, date, cp etc.   

2. **Commands with arguements**  - Commands with arguments are also supported.  

3. **Piping** - A pipe command redirects the output of _command 1_ as the input of _command 2_.    
``` (command 1) | (command 2) ```   

![2-pipe,arg,general](https://user-images.githubusercontent.com/76866159/107150022-bc8d3300-6981-11eb-9d50-2db6b70b6247.gif)



4. **Option of verbose output**, which if chosen then the shell displays the output of each command, and also the input and output pipe fd's and the process id's of the respective processes.

5. **Double pipe** operator -  New operator custom defined for redirecting the output of _command 1_ to both _command 2_ and _command 3_.   
``` (command 1) || (command 2) (command 3) ```  
6. **Triple pipe** operator -  New operator custom defined for redirecting the output of _command 1_ to all of _command 2_,_command 3_ and _command 4_.   
``` (command 1) ||| (command 2) (command 3) (command 4) ```  

![3-double,triple pipe](https://user-images.githubusercontent.com/76866159/107150025-beef8d00-6981-11eb-9439-ed6a62872aaf.gif)



7. **Input and Output redirection** is supported -   
-> Input redirection: '>' taking input from _file 1_ instead of _stdin_ and giving it to _command 1_.   
``` (file 1) > (command 1) ```   
-> Output redirection: Giving output of _command 1_ to _file 2_ instead of _stdout_.   
``` (command 1) > (file 2)```
	
	
8. **Getting history of previous commands** - Using SIGINT and SIGQUIT behaviour
	when _SIGINT (Ctrl + C)_ is pressed on the keyboard, the shell displays the last 10 executed commands on the console, alongwith their status and exits.
	when _SIGQUIT (Ctrl + \)_ is pressed, the shell asks the user to quit or not.
	
![4-i o redirection](https://user-images.githubusercontent.com/76866159/107150028-c3b44100-6981-11eb-9393-ccbf8e635668.gif)


9. **Opening external applications** - Can easily open other applications like firefox, peek, leafpad, etc directly from the shell.

![5-software](https://user-images.githubusercontent.com/76866159/107150030-c9118b80-6981-11eb-83e7-6428d1bfd9d7.gif)


Do share if you liked our work. Thanks!

:smile:

