#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <stdlib.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <sys/wait.h>



char *last10[10];

int p_stat[10];

int head;

int verbose;



struct comm								

{

	char* ipdir;

	char* opdir;

	char name[10];							

	int arguements;							

	char arg[10][10];						

};



static void sig (int sign)

{

	if(sign==SIGINT)

	{	printf("\nPrinting last 10 commands (from oldest to newest) :\n");

		int hh=head;

		for(int i=0; i<10; i++)

		{ 	if(last10[hh]==NULL) break;

			printf("(%d) - %s\n",i+1,last10[hh]);

			

			if(verbose==1)	

				printf("STATUS - ");

			

			int status = p_stat[hh];

			

			if(verbose==1){

            if(WIFEXITED(status))

			    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));

    		else if(WIFSIGNALED(status))

	    		printf("abnormal termination, signal number = %d\n", WTERMSIG(status));

	    	else if(WIFSTOPPED(status))

	    		printf("child stopped, signal number = %d\n", WSTOPSIG(status));

	    	else if(WIFCONTINUED(status))

	    		printf("child continued\n");

	    	printf("\n");

			}



			if(hh==9) hh=0;

			else hh++;

		}

	}



	printf("\nDo you really want to exit? (Y/N)\n>>> ");

	char choice[20];

    	scanf("%[^\n]s",choice); getchar();

	if((choice[0]=='y')||(choice[0]=='Y')) 

	{

    		printf("\n\n******************** HAVE A GOOD DAY! ********************\n\n");

		exit(0);

	}

	else printf("\n>>> ");

	

}



void parser(char *command, struct comm *commstruct)

{



	int op=0, ip=0;

	for(int i=0; (command[i]!='|')&&(command[i]!='\n')&&(command[i]!='\0')&&(command[i]!=','); i++)

	{       if(command[i]=='>') op=i+1;

		if(command[i]=='<') ip=i+1;			

	}

	

	commstruct->ipdir=commstruct->opdir=NULL;

	if(op!=0)

	{

		int t1=0;

		commstruct->opdir = (char *)malloc(15*sizeof(char));

		while((command[op]==' ')||(command[op]=='\t')) op++;

		while((command[op]!='\0')&&(command[op]!=',')&&(command[op]!='\t')&&(command[op]!=' ')&&(command[op]!='\n')&&(command[op]!='|'))

			commstruct->opdir[t1++]=command[op++];

		commstruct->opdir[t1]='\0';	

	

	}

	if(ip!=0)

	{

		int t2=0;

		commstruct->ipdir = (char *)malloc(15*sizeof(char));

		while((command[ip]==' ')||(command[ip]=='\t')) ip++;			

		while((command[ip]!='\0')&&(command[ip]!=',')&&(command[ip]!='\t')&&(command[ip]!=' ')&&(command[ip]!='\n')&&(command[ip]!='|'))

			commstruct->ipdir[t2++]=command[ip++];

		commstruct->ipdir[t2]='\0';	

	}





	int i=0;						

	while((command[i]==' ')||(command[i]=='\t')) i++;			



	int f;

	for( f=0; ((command[i]!='\0')&&(command[i]!=',')&&(command[i]!='\t')&&(command[i]!=' ')&&(command[i]!='\n')&&(command[i]!='|')); f++, i++)

		commstruct->name[f]=command[i];

	commstruct->name[f]='\0';



	strcpy(commstruct->arg[0],commstruct->name);



	commstruct->arguements=1;

	while((command[i]==' ')||(command[i]=='\t')) i++;

	

	int pre=1;

	if((command[i]=='|')||(command[i]=='\n')||(command[i]=='\0')||(command[i]==','))

	{  commstruct->arg[1][0]='\0'; pre=0; }



	int t;

	for(int j=1;(pre);j++)

	{

		

		for(t=0; ((command[i]!='\t')&&(command[i]!=' ')&&(command[i]!='\n')&&(command[i]!='|')&&(command[i]!='\0')&&(command[i]!=',')); i++)

			commstruct->arg[j][t++]=command[i];

		commstruct->arg[j][t]='\0';



		while((command[i]==' ')||(command[i]=='\t')) i++;

		

		if((command[i]=='|')||(command[i]=='\n')||(command[i]=='\0')||(command[i]==','))

		{

			commstruct->arguements=j+1;

			commstruct->arg[j+1][0]='\0';

			break;

		}

	}





	if((ip==0)&&(op==0))  return;



	char *str; int check=0;

	

	

	if((op!=0)&&(op>ip))

	for(int i=0; (i<commstruct->arguements); i++)

	{

		str=commstruct->arg[i];

		if(str[0]=='>')

		{       if(strlen(str)!=1) strcpy(str,commstruct->arg[i+1]);

			else

			{       strcpy(str,commstruct->arg[i+2]);

				strcpy(commstruct->arg[i+1],commstruct->arg[i+2]);    

			}

			break;

		}



		for(int j=0; j<strlen(str); j++)

			if(str[j]=='>') 

			{ 	str[j]='\0'; 

			  	check=1;

			  	if(j==(strlen(str)-1)) strcpy(commstruct->arg[i+1],commstruct->arg[i+2]);

			  	break;   

			}

		if(check==1) break;

	}



	check=0;

	if(ip!=0)

	for(int i=0; (i<commstruct->arguements); i++)

	{

		str=commstruct->arg[i];

		if(str[0]=='<')

		{

			if(strlen(str)!=1) strcpy(str,commstruct->arg[i+1]);

			else

			{ 	strcpy(str,commstruct->arg[i+2]);

			  	strcpy(commstruct->arg[i+1],commstruct->arg[i+2]); 

			}

			break;

		}



		for(int j=0; j<strlen(str); j++)

			if(str[j]=='<') 

			{ 	str[j]='\0'; 

			  	check=1;

			  	if(j==(strlen(str)-1)) strcpy(commstruct->arg[i+1],commstruct->arg[i+2]);

			  	break;                                                                       

			}

		if(check==1) break;

	}

	

	if((op!=0)&&(op<ip))

	for(int i=0; (i<commstruct->arguements); i++)

	{

		str=commstruct->arg[i];

		if(str[0]=='>')

		{       if(strlen(str)!=1) strcpy(str,commstruct->arg[i+1]);

			else

			{       strcpy(str,commstruct->arg[i+2]);

				strcpy(commstruct->arg[i+1],commstruct->arg[i+2]);    

			}

			break;

		}



		for(int j=0; j<strlen(str); j++)

			if(str[j]=='>') 

			{ 	str[j]='\0'; 

			  	check=1;

			  	if(j==(strlen(str)-1)) strcpy(commstruct->arg[i+1],commstruct->arg[i+2]);

			  	break;   

			}

		if(check==1) break;

	}



}



void run_which(char* buf, int size, char* comm){

	

	int filedes[2];

	if(pipe(filedes) == -1){

		printf("error creating a pipe in run_which\n");

		exit(-1);

	}



	pid_t child = fork();



	if(child == -1){

		printf("error while forking in run_which\n");

		exit(-1);

	}

	else if(child == 0){

	// child process

		close(filedes[0]);

		close(1);

		dup(filedes[1]);

	

		char *p[] = {"which", comm, NULL};

		execv("/usr/bin/which", p);

	}

	else{

	// parent process

		

		close(filedes[1]);

		int ind = read(filedes[0], buf, size);



		if(ind >= 1 && buf[ind-1] == '\n')

			buf[ind-1] = '\0';

		else

			buf[ind] = '\0';

	}

}





void main()	

{



    printf("\n******************** WELCOME TO SHELL ********************\n\n");

    

    char choice[100];

    printf("Do you want to print the status of each transfer continuously? (Y/N)\n>>> ");

    scanf("%[^\n]s",choice); getchar();



    	if((choice[0]=='Y')||(choice[0]=='y')) verbose = 1;

	else verbose = 0;



    signal(SIGINT,sig);

    signal(SIGQUIT,sig);

	head = 0;

  

  for(int num_command = 0; ; ++num_command){

    printf("\n\n>>> ");



    char* command = malloc(100 * sizeof(char));

	

    command[0] = '\0';

    

	scanf("%[^\n]s",command);

	getchar();

	last10[num_command%10] = command;

	

	int commands=1;							

	for(int i=0; i<strlen(command); i++)					

		if((command[i]==',')||((command[i]=='|')&&(command[i-1]!='|')))

			commands++;

	

	

        struct comm * commstruct;	

	commstruct = (struct comm*)malloc(sizeof(struct comm)*commands);	



	for(int i=0, t=0; i<strlen(command); i++)				

		if((i==0)||((command[i-1]==',')||((command[i-1]=='|')&&(command[i]!='|'))))

			parser(command+i,&commstruct[t++]);





	//Structures for each command have been filled now



	int pipeval = 0;

	for(int i=0; i<strlen(command); i++)

	{

		if(command[i]=='|')

			if(command[i+1]=='|')

			{

				if(command[i+2]=='|')

				{ pipeval = 3; break; }

				

				else

				{ pipeval = 2; break; }

	

			}

			else

			{ pipeval = 1; break; }



	}







	char ** q[commands];



	for(int j= 0; j<commands; ++j){

		q[j] = (char**)malloc((commstruct[j].arguements+1) * sizeof(char *));



		for(int i = 0; i<=commstruct[j].arguements; ++i){

			if(commstruct[j].arg[i][0] == '\0' || i==commstruct[j].arguements)

				q[j][i] = NULL;

			else

				q[j][i] = commstruct[j].arg[i];

		}

	}





	



	pid_t childpid = fork();

	

	if(childpid == -1)

		printf("Unsuccessful fork\n");



	else if(childpid == 0){



		int size = 1000;

		char buf[size];

		

		if(pipeval == 0){

            		if(commstruct[0].opdir != NULL){

					close(1);

					int opfil = open(commstruct[0].opdir, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

					if(opfil == -1){

						printf("Error opening file for output redirection\n");

						exit(1);

						}

					dup(opfil);

					}

	

					if(commstruct[0].ipdir != NULL){

						close(0);

						int ipfil = open(commstruct[0].ipdir, O_RDONLY);

						if(ipfil == -1){

							printf("Error opening file for input redirection\n");

							exit(1);

						}

						dup(ipfil);

					}



			run_which(buf, size, q[0][0]);

			execv(buf, q[0]);

		}

		

		else if(pipeval == 1){

			int filedes[(commands-1)][2];

			

			for(int i = 0; i< commands -1 ; ++i){

				if(pipe(filedes[i]) == -1){

					printf("Error creating pipe\n");

					exit(1);

				}

			}



			for(int i = 0; i< commands; ++i){

				pid_t child = fork();

				if(child == -1){

					printf("Error creating child process\n");

					exit(1);

				}

				else if(child == 0){

					if(commstruct[i].opdir != NULL){

						close(1);

						int opfil = open(commstruct[i].opdir, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

						if(opfil == -1){

							printf("Error opening file for ooutput redirection\n");

							exit(1);

						}

						dup(opfil);

					}

					else if(i < commands - 1){

						close(filedes[i][0]);

						close(1);

						dup(filedes[i][1]);

					}

	

					if(commstruct[i].ipdir != NULL){

						close(0);

						int ipfil = open(commstruct[i].ipdir, O_RDONLY);

						if(ipfil == -1){

							printf("Error opening file for input redirection\n");

							exit(1);

						}

						dup(ipfil);

					}

					else if(i >= 1){

						close(filedes[i-1][1]);

						close(0);

						dup(filedes[i-1][0]);

					}

					char buffer[1000];

					run_which(buffer, 1000, q[i][0]);

					execv(buffer, q[i]);

					exit(0);

				}

				else{

                    waitpid(child, NULL, WUNTRACED | WCONTINUED);

                    if(verbose==1){

		    printf("~> %dth child (%s) in single pipe executed with pid = %d!!\n", i, q[i][0], child);

                    if(i >= 1)

                        printf("Input pipe fd = %d\t", filedes[i-1][0]);

                    if(i<commands-1)

                        printf("Output pipe fd = %d\n", filedes[i][1]);

                    else

                        printf("\n");

                    if(commstruct[i].ipdir != NULL)

                        printf("Input redirection - %s\n", commstruct[i].ipdir);

                    if(commstruct[i].opdir != NULL)

                        printf("Output redirection - %s\n", commstruct[i].opdir);

		    }

                    if(i < commands-1)

                        close(filedes[i][1]);

				}

	

			}

		}

		

		else if(pipeval == 2 || pipeval == 3){

			int filedes[pipeval + 1][2];

			

			for(int i = 0; i<=pipeval ; ++i){

				if(pipe(filedes[i]) == -1){

					printf("Error creating pipe\n");

					exit(1);

				}

			}



            commands = pipeval + 1;     //



			for(int i = 0; i< commands; ++i){

				pid_t child = fork();

				if(child == -1){

					printf("Error creating child\n");

					exit(1);

				}

				else if(child == 0){

					if(commstruct[i].opdir != NULL){

						close(1);

						int opfil = open(commstruct[i].opdir, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

						if(opfil == -1){

							printf("Error opening file for output redirection\n");

							exit(1);

						}

						dup(opfil);

					}

					else if(i == 0){

						close(filedes[i][0]);

						close(1);

						dup(filedes[i][1]);

					}

	

					if(commstruct[i].ipdir != NULL){

						close(0);

						int ipfil = open(commstruct[i].ipdir, O_RDONLY);

						if(ipfil == -1){

							printf("Error opening file for input redirection\n");

							exit(1);

						}

						dup(ipfil);

					}

					else if(i >= 1){

						close(filedes[i][1]);

						close(0);

						dup(filedes[i][0]);

					}

					

					char buffer[1000];

					run_which(buffer, 1000, q[i][0]);

					execv(buffer, q[i]);

					exit(0);

				}

				else{

                    waitpid(child, NULL, WUNTRACED | WCONTINUED);

                    if(verbose==1){

		    if(pipeval == 2)

                        printf("~> %dth child (%s) in double pipe executed with pid = %d!!\n", i, q[i][0], child);

                    else

                        printf("~> %dth child (%s) in triple pipe executed with pid = %d!!\n", i, q[i][0], child);





                    if(i >= 1)

                        printf("input pipe fd = %d\t", filedes[i][0]);

                    if(i==0)

                        printf("output pipe fd = %d\n", filedes[i][1]);

                    else

                        printf("\n");

                        

                    if(commstruct[i].ipdir != NULL)

                        printf("input redirection - %s\n", commstruct[i].ipdir);

                    if(commstruct[i].opdir != NULL)

                        printf("output redirection - %s\n", commstruct[i].opdir);

		    }

                    if(i==0){

                        char buffer[1000];

                        int msg_size = read(filedes[0][0], buffer, 1000);

                        

                        for(int j = 1; j <= pipeval; ++j){

                            write(filedes[j][1], buffer, msg_size);

                            close(filedes[j][1]);

                        }

                    }

				}

	

			}

		}



		exit(0);

	}



	else{

		int status;



		pid_t child = waitpid(childpid, &status, WUNTRACED | WCONTINUED);

	

	if(verbose ==1){	

		printf("pid - %d\t", child);

        p_stat[num_command%10] = status;

		if(WIFEXITED(status))

			printf("normal termination, exit status = %d\n", WEXITSTATUS(status));

		else if(WIFSIGNALED(status))

			printf("abnormal termination, signal number = %d\n", WTERMSIG(status));

		else if(WIFSTOPPED(status))

			printf("child stopped, signal number = %d\n", WSTOPSIG(status));

		else if(WIFCONTINUED(status))

			printf("child continued\n");

		printf("\n");

	}}

	if(num_command >=10)

	    head = (num_command + 1)%10;

	    

//	free(command);

    free(commstruct->ipdir);

    free(commstruct->opdir);

    free(commstruct);

  	for(int j= 0; j<commands; ++j)

  	    free(q[j]);

  	

  }

}

