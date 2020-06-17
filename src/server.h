/* header file for server.c */

#ifndef _SERVER_H
#define _SERVER_H

typedef void (*ClientHandler)(int DataSocketFD);

//char *userAccount[10] ;
//char *userPass[10] ;

char *userAccount[10] ;
char *userPass[10] ;

const char *Program = NULL; // program name for descriptive diagnostic
int Shutdown = 0; 

//struct for accounts
typedef struct Accounts PROFILE;
typedef struct FriendList FLIST;

typedef struct {
	char username[20];
	char password[20];
	int friend_count;
	char friends[20][20];
} USER;

struct Accounts{
	char *user;
	char *pass;
	
	PROFILE *Next;
	PROFILE *Previous;
	FLIST *List;

};

struct FriendList{
	PROFILE *First;
	PROFILE *Last;
	int length;

};

struct Node {
	char id[99];
	char pass[99];

	struct Node *next;
};

struct Node *head = NULL;
//head = (struct Node*)malloc(sizeof(struct Node));
//head->next = NULL;

int newUser(char username[20], char password[20]);

int addFriend(char username[20], char friend[20]);

int authenticate(char username[20], char password[20]);

PROFILE *CreateAccountEntry(void);

void DeleteAccountEntry(PROFILE *entry);

FLIST *CreateFriendList(void);

void DeleteFriendList(FLIST *list);

void AppendAccounts(FLIST *list, PROFILE *login);

bool UserExists(char *user) ; 

// create a socket on this server
int MakeServerSocket(uint16_t PortNo);
// process a time request by a client 
void ProcessRequest(int DataSocketFD);
// print error diagnostics and abort
void FatalError(const char *ErrorMsg);
// the main loop server
void ServerMainLoop(int ServSocketFD, ClientHandler HandleClient);

#endif
