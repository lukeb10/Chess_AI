#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdbool.h>

#include "server.h"
//char *userAccount[10] ;
//char *userPass[10] ;
//int test = 0;

USER users[100];

int user_count = 0;

char user_blocked[20];

int CONTACT_MAX = 10;
char *userAccount[10];
char *userPass[10];
//int test = 0;
//char *userAccount[10];
//char *userPass[10];
int test = 0;
//char *userAccount[10];
//char *userPass[10];
//int h =0;
//char *userAccount[10];
//char *userPass[10];
//int h =0;
/*	for(h=0; h<5; h++){
		userAccount[h]= (char*) malloc(sizeof(char)*99);
		userPass[h]= (char*) malloc(sizeof(char)*99);
	}	
=======
>>>>>>> 0e95025a096f7b7ff455816ad9aaac321e9773cf

<<<<<<< HEAD


char user_id[10][20];
char user_pass[10][20];




||||||| merged common ancestors
*/
int main(int argc, char *argv[])
{
	int ServSocketFD;	// socket file descriptor for service 
    	int PortNo;		// port number 
	
	int h =0;
	for(h=0; h<CONTACT_MAX; h++){
		userAccount[h]= (char*) malloc(sizeof(char)*99);
		userPass[h]= (char*) malloc(sizeof(char)*99);
	}
	//userAccount[0] = "david";
	//userPass[0] = "123";
	//test++;

	/*for (int i=0; i<10; i++)
	{
		userAccount[i] = "null";
		userPass[i] = "null";
	} */

	/*for (int i=0; i<10; i++)
	{
		user_id[i][0] = "@";
		user_pass[i][0] = "@";
	}*/
	
	
	Program = argv[0];	// publish program name (for diagnostics) 
	printf("%s: Starting...\n", Program);
	
	if (argc < 2)
    	{   
		fprintf(stderr, "Usage: %s port\n", Program);
		exit(10);
    	}
	
	PortNo = atoi(argv[1]);	// get the port number 
	if (PortNo <= 2000)
    	{   
		fprintf(stderr, "%s: invalid port number %d, should be >2000\n", Program, PortNo);
        	exit(10);
    	}
	
	printf("%s: Creating the server socket...\n", Program);
	ServSocketFD = MakeServerSocket(PortNo);
	
	ServerMainLoop(ServSocketFD, ProcessRequest);
	
	printf("\n%s: Shutting down.\n", Program);
	close(ServSocketFD);
	return 0;
}

int MakeServerSocket(uint16_t PortNo)
{
	int ServSocketFD;
    	struct sockaddr_in ServSocketName;
	
	// create the socket
	ServSocketFD = socket(PF_INET, SOCK_STREAM, 0);
	if (ServSocketFD < 0)
    	{   
		FatalError("service socket creation failed");
    	}
	// bind the socket to this server 
    	ServSocketName.sin_family = AF_INET;
    	ServSocketName.sin_port = htons(PortNo);
    	ServSocketName.sin_addr.s_addr = htonl(INADDR_ANY);
    	if (bind(ServSocketFD, (struct sockaddr*)&ServSocketName,sizeof(ServSocketName)) < 0)
    	{   
		FatalError("binding the server to a socket failed");
    	}
	// start listening to this socket 
    	if (listen(ServSocketFD, 5) < 0)	// max 5 clients in backlog 
    	{   
		FatalError("listening on socket failed");
    	}
	
	return ServSocketFD;
}

// server socket to wait on, client handler to call
void ServerMainLoop(int ServSocketFD, ClientHandler HandleClient)
{
	int DataSocketFD;	// socket for a new client 
	socklen_t ClientLen;
	struct sockaddr_in ClientAddress;	// client address we connect with 
	fd_set ActiveFDs;	// socket file descriptors to select from 
    	fd_set ReadFDs;		// socket file descriptors ready to read from 
	struct timeval TimeVal;
	int res, i;

	
	//head = (struct Node*)malloc(sizeof(struct Node));
	//head->next = NULL;
	//for (int x=0; x<99; x++)
	//{
	//	userAccount[x][0] = '\0';
	//	userPass[x][0] = '\0';
	//}
		
	
	
	FD_ZERO(&ActiveFDs);		// set of active sockets 
    	FD_SET(ServSocketFD, &ActiveFDs);	// server socket is active 
	
	
	while (!Shutdown)
	{
		ReadFDs = ActiveFDs;
		
		// block until input arrives on active sockets
		res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, NULL);
		if (res < 0)
		{
			FatalError("wait for input failed");
		}
		// some FDs have data ready to read
		if (res > 0)
		{
		int stop = 0;
			for(i=0; i<FD_SETSIZE; i++)
			{
				if (FD_ISSET(i, &ReadFDs))
				{
					if (i == ServSocketFD) // connection request on server socket
					{	
						printf("%s: Accepting new client...\n", Program);
						ClientLen = sizeof(ClientAddress);
						DataSocketFD = accept(ServSocketFD,(struct sockaddr*)&ClientAddress, &ClientLen);
						if (DataSocketFD < 0)
						{   
							FatalError("data socket creation (accept) failed");
						}
						printf("%s: New client connected from %s:%hu.\n",Program,inet_ntoa(ClientAddress.sin_addr), ntohs(ClientAddress.sin_port));
						FD_SET(DataSocketFD, &ActiveFDs);
					}
					else // active communication with a client
					{
						printf("%s: Dealing with client on FD%d...\n", Program, i);
						HandleClient(i);
						printf("%s: Closing client connection FD%d.\n", Program, i);
						close(i);
						FD_CLR(i, &ActiveFDs);
					}
				}
			}
		}
	}
}


void ProcessRequest(int DataSocketFD)
{
	int  l, n;
	char RecvBuf[256];	// message buffer for receiving a message 
    char SendBuf[256];	// message buffer for sending a response 
	char message[256];
	char temp_id[20];
	char temp_pass[20];		


	n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
	if (n < 0) 
    	{   
		FatalError("reading from data socket failed");
    	}
    	RecvBuf[n] = 0;
	printf("%s: click button is: %s\n", Program, RecvBuf);


	if (strcmp(RecvBuf, "CREATE ACCOUNT") == 0)
	{
		strcpy(SendBuf, "ok");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to data socket failed");
	
		// read userid
		n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n < 0)    
			FatalError("reading from data socket failed");
		RecvBuf[n] = 0;

		strcpy(temp_id, RecvBuf);
		strcpy(SendBuf, "ok");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to data socket failed");


		// read password
		n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n < 0)    
			FatalError("reading from data socket failed");
		RecvBuf[n] = 0;

		strcpy(temp_pass, RecvBuf);
		strcpy(SendBuf, "got the pass");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to data socket failed");
		printf("ID is %s, Pass is %s\n", temp_id, temp_pass);	

		strcpy(userAccount[test], temp_id);
		strcpy(userPass[test], temp_pass);
		test++;
			
		printf("Account added!\n");
	}
	else if (strcmp(RecvBuf, "SEND") == 0)
        {
                strcpy(SendBuf, "ok");
                l = strlen(SendBuf);

                n = write(DataSocketFD, SendBuf, l);
                if (n < 0)
                        FatalError("writing to data socket failed");

                n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
                if (n < 0)
                        FatalError("reading from data socket failed");
                RecvBuf[n] = 0;

                strcpy(message, RecvBuf);
                printf("%s: Received message: %s\n", Program, message);
        }
	else if (strcmp(RecvBuf, "REFRESH") == 0)
	{
		n = write(DataSocketFD, message, strlen(message));
		if (n < 0)
		{
			FatalError("writing to data socket failed");
		}
		printf("%s: Sending message: %s\n", Program, message);
	}
	else if (strcmp(RecvBuf, "BLOCK") == 0)
	{
		strcpy(SendBuf, "ok");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");

		n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n < 0)
			FatalError("error writing");
		RecvBuf[n] = 0;
	
		strcpy(user_blocked, RecvBuf);
		
		printf("%s USER IS BLOCKEDi\n", user_blocked);
	}
	else if (strcmp(RecvBuf, "DISPLAY FRIENDS") == 0)
	{
		strcpy(SendBuf, "gonna start sending");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");

		n = read(DataSocketFD, SendBuf, sizeof(RecvBuf)-1);
		if (n<0)
			FatalError("reading");
		RecvBuf[n] = 0;

		for (int i=0; i<10; i++)
		{
			//strcpy(SendBuf, user_id[i]);
			n = write(DataSocketFD, SendBuf, strlen(SendBuf));
			if (n<0)
				FatalError("writing");
			n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
			if (n<0)
				FatalError("reading");
			RecvBuf[n] = 0;
		}	

	}
	else if (strcmp(RecvBuf, "LOG IN") == 0)
	{
		printf("in log in\n");
		strcpy(SendBuf, "ok");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");
		
		n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n<0)
			FatalError("reading");
		RecvBuf[n] = 0;
		
		strcpy(temp_id, RecvBuf);
		
		strcpy(SendBuf, "ok");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");

		n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n<0)
			FatalError("reading");
		RecvBuf[n] = 0;
		
		strcpy(temp_pass, RecvBuf);

		for (int i=0; i<test; i++)
		{
			if (strcmp(userAccount[i], temp_id) == 0)
			{  
				if (strcmp(userPass[i], temp_pass) == 0)
				{
					strcpy(SendBuf, "logged in");
					n = write(DataSocketFD, SendBuf, strlen(SendBuf));
					if (n<0)
						FatalError("writing");
					break;
				}
			}
		}
		strcpy(SendBuf, "log in failed!");
		n = write(DataSocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");

		
	}
	

}

 
void FatalError(const char *ErrorMsg)
{
    	fputs(Program, stderr);
    	fputs(": ", stderr);
    	perror(ErrorMsg);
    	fputs(Program, stderr);
    	fputs(": Exiting!\n", stderr);
    	exit(20);
} 

/* 
PROFILE *CreateAccountEntry(char *userName, char *passWord)
{
	PROFILE *account= (PROFILE *) malloc(sizeof(PROFILE));
	
	if(!account){
		perror("Error. Account entry not created");
		return NULL;
	}
	

	account->user = (char*) malloc(sizeof(char));
	if(account -> user == NULL){
		free(account);
		return NULL;

	}
	
	account -> pass= (char*) malloc(sizeof(char));
	if(account->pass == NULL){
		free(account->user);
		free(account);
		return NULL;
	}	
	
	account-> List= NULL;

	account->Next= NULL;
	account->Previous=NULL;	


	return account;


}

void DeleteAccountEntry(PROFILE *account){
	assert(account);
	assert(account->user);
	assert(account->pass);
	
	free(account->user);
	free(account->pass);

	account->user=NULL;
	account->pass=NULL;

	free(account);
}
 

FLIST *CreateFriendList(void)
{
	FLIST *F;
	F = malloc(sizeof(FLIST));

	if(!F)
	{
		perror("Error! Friend list not created!");
		return NULL;
	}

	F->length=0;
	F->First= NULL;
	F->Last= NULL;

	return F;
}

void DeleteFriendList(FLIST *list)
{
	PROFILE *e, *n;

	assert(list);
	e=list->First;
	while(e)
	{
		n=e->Next;
		DeleteAccountEntry(e);
		e=n;
	}

	free(list);
}

void AppendAccounts(FLIST *list, char *userName, char *passWord){
	PROFILE *e = NULL;
	
	assert(list);
	assert(login);
	
	e= CreateAccountEntry();	
	
	e-> user = userName;
	e-> pass = passWord;
	
	if(list->Last){
		e->List = list;
		e->Next = NULL;
		e->Previous = list->Last
		list-> Last-> Next= e;
		list-> Last = e;
	}
	else{
		e->List= list;
		e->Next= NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last=e;
	}

	list->length++;
 
}
*/
/*
int newUser(char username[20], char password[20]) {
	int i;
	for (i = 0; i < user_count; i++) {
		if (strcmp(users[i].username, username) == 0) {
			printf("Username %s already exists ;(", username);
			return 1;
		}
	}
	strcpy(users[i].username, username);
	strcpy(users[i].password, password);
	users[i].friend_count = 0;

	user_count += 1;

	printf("New account created!\n");
	return 0;
}

int addFriend(char username[20], char friend[20]) {
	int i, j;
	for (i = 0; i < user_count; i++) {
		if (strcmp(users[i].username, friend) == 0) {
			for (j = 0; j < user_count; j++) {
				if (strcmp(users[j].username, username) == 0) {
					strcpy(users[j].friends[users[j].friend_count], friend);
					users[j].friend_count += 1;
					printf("%s was successfully added to %s's friend list!\n", friend, username);
					return 0;
				}
			}
		}
	}
	printf("Friend not added ;(\n");
	return 1;
}

int authenticate(char username[20], char password[20]) {
	int i;
	for (i = 0; i < user_count; i++) {
		if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
			printf("%s has logged in!", username);
			return 0;
		}
	}
	printf("the username %s does not exist!", username);
	return 1;
}

*/
