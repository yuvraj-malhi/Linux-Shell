# Linux-Shell

## Description
This is a linux shell, written in C with a sweet interface and with added functionality of a few custom commands.

### Features
1. **General Terminal commands** - The shell supports general commands like ls, cat, grep, who, date etc.   

2. **Commands with arguements**  - Commands with arguments are also supported.  

3. **Piping** - A pipe command redirects the output of _command 1_ as the input of _command 2_.    
``` (command 1) | (command 2) ```   

4. **Option of verbose output**, which if chosen then the shell displays the output of each command, and also the input and output pipe fd's and the process id's of the respective processes.

5. **Double pipe** operator -  New operator custom defined for redirecting the output of _command 1_ to both _command 2_ and _command 3_.   
``` (command 1) | (command 2) (command 3) ```  
6. **Triple pipe** operator -  New operator custom defined for redirecting the output of _command 1_ to all of _command 2_,_command 3_ and _command 4_.   
``` (command 1) | (command 2) (command 3) (command 4) ```  

7. **Input and Output redirection** is supported -   
-> Input redirection: '>' taking input from _file 1_ instead of _stdin_ and giving it to _command 1_.   
``` (file 1) > (command 1) ```   
-> Output redirection: Giving output of _command 1_ to _file 2_ instead of _stdout_.
``` (command 1) > (file 2)```
	
	
8. **Getting history of previous commands** - Using SIGINT and SIGQUIT behaviour
	when _SIGINT (Ctrl + C)_ is pressed on the keyboard, the shell displays the last 10 executed commands on the console, alongwith their status and exits.
	when _SIGQUIT (Ctrl + \)_ is pressed, the shell asks the user to quit or not.

