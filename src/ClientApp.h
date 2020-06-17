/* header file for ClientApp.c */

#ifndef _CLIENTAPP_H
#define _CLIENTAPP_H

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 440
#define MAX_LOGLEN 64
#define MAX_MSGLEN 256


/* external function declarations */

// function that links widgets in ClientApp.c with widgets from Glade XML file
// returns an int that represents different status/error flags
// success = 0 | error = 1
int LinkWidgets() ;

// where all the events/signals call upon their callback functions
void Callbacks() ;

// convert gchar to char
void convert(const gchar *src, char dest[]) ;
/* follows model:
 * char buffer[256] ;
 * convert(username, buffer) ;
 */

/* callback function declarations */

// logs in with the username/password information and enters the friends list window
static void click_login(GtkWidget *widget, gpointer data) ;

// creates a new account with the username/password information and enters the friends list window
static void click_create(GtkWidget *widget, gpointer data) ;

// switches to chat room window
static void click_chat(GtkWidget *widget, gpointer data) ;

// switches to friends list window
static void click_friends(GtkWidget *widget, gpointer data) ;

// checks if user doesn't exist or is already added, if not add user
//static void click_add(GtkWidget *widget, gpointer data) ;

// checks if user is on the friends list, if so delete user
//static void click_delete(GtkWidget *widget, gpointer data) ;

// blocks user from friends lobby
static void click_block(GtkWidget *widget, gpointer data) ;

// sends the message in chat
static void click_send(GtkWidget *widget, gpointer data) ;

// refreshes the chat
static void click_refresh(GtkWidget *widget, gpointer data) ;

// displays friends in friends list (called whenever switching to friends list window)
//static void display_friends();//char *friends[]) ;
//static void display_friends(char *friends[]) ;
static void display_friends(GtkWidget *widget, gpointer data) ;

/////////////////////////////////////////////////////////////////
// test function for displaying messages from other users in chat
//static void test(GtkWidget *widget, gpointer data) ;


/* TODO: 
 * implement recieving messages in chat display
 * add username to chat once user struct is setup
 * display_friends parameter to match user struct once setup
 * login/create acc functionality
 * add/delete acc functionality
 */
//Account
struct account
{
	char uname[256];
	char pword[256];

};
typedef struct account ACCOUNT;

//Allocate a new user login
ACCOUNT *NewAccount(char *uname, char *pword);

//Delete Account
void DeleteAccount(ACCOUNT *a);

/***********************************/
/* need to implement the following */
// friends list display
// chat display
// SEND button
// add scroll bars to friends_display and chat_display
// login/create acc functionality
// add/delete acc functionality
/***********************************/

// callback function for either the logout button or the exit button (top right corner)
static gboolean EndProgram(GtkWidget *widget, GdkEvent *event, gpointer data) ;

#endif
