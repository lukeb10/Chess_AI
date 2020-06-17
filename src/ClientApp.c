/* source code file for client gui */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>




// for client
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>


//#include "server.h"


#include "ClientApp.h"

/* GLOBAL GTK WIDGETS */
/* login/register window */
GtkWidget *login_window ;
GtkWidget *login_vbox ;
GtkWidget *logo ; // queen chess icon
GtkWidget *username_label ;
GtkWidget *username_entry ; // if username DNE or password incorrect, display message here
GtkWidget *password_label ;
GtkWidget *password_entry ;
GtkWidget *login_btn ; // login button
GtkWidget *or_label ;
GtkWidget *create_btn ; // create new account button

/* friends list window */
GtkWidget *friends_window ;
GtkWidget *friends_vbox ;
GtkWidget *friends_hbox1 ; // top two buttons [chat, logout]
GtkWidget *friends_hbox2 ; 
GtkWidget *chat_btn ;
GtkWidget *block_btn ;
GtkWidget *show_btn ;
GtkWidget *logout_btn1 ; // logout_btn2 in chat room window
GtkWidget *friends_label ;
GtkWidget *friends_display ;
GtkWidget *friends_entry ;
//GtkWidget *add_btn ;
//GtkWidget *delete_btn ;
GtkTextBuffer *friends_buffer ;
GtkWidget *friends_scroll ;

/* chat room window */
GtkWidget *chat_window ;
GtkWidget *chat_vbox ;
GtkWidget *chat_hbox1 ;
GtkWidget *chat_hbox2 ;
GtkWidget *chat_label ;
GtkWidget *friends_btn ;
GtkWidget *logout_btn2 ; // logout_btn1 in friends list window
GtkWidget *chat_display ;
GtkWidget *chat_entry ;
GtkWidget *send_btn ;
GtkWidget *refresh_btn ;
GtkTextBuffer *chat_buffer ;
GtkWidget *chat_scroll ;



#define BUFFSIZE 256

int SocketFD, PortNo, n;
struct sockaddr_in ServerAddress;
struct hostent *Server;
char SendBuf[256];
char RecvBuf[256];
const char *Program = NULL;
 

void FatalError(const char *ErrorMsg);
void write_socket();
void read_socket();
void close_session();
char *blockName[9];
static int blocked=0;

char friends[10][20];

gchar *u = NULL;


/* main program */
int main (int argc, char *argv[]) {
	
	int h;
	for(h=0; h<9; h++){
		blockName[h] = (char*) malloc(sizeof(char) *99);
	}


	for (int i=0; i<10; i++)
	{
		friends[i][0] = '\0';
	}	


	Program = argv[0];
    	printf("%s: Starting...\n", argv[0]);
    	if (argc < 3)
    	{   
		fprintf(stderr, "Usage: %s hostname port\n", Program);
		exit(10);
    	}

    	Server = gethostbyname(argv[1]);
    	if (Server == NULL)
    	{   
		fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        	exit(10);
    	}

    	PortNo = atoi(argv[2]);
    	if (PortNo <= 2000)
    	{   
		fprintf(stderr, "%s: invalid port number %d, should be > 2000\n", Program, PortNo);
          	exit(10);
    	}

    	ServerAddress.sin_family = AF_INET;
    	ServerAddress.sin_port = htons(PortNo);
    	ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];

	
	/*SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{
		FatalError("socket creation failed");
	}
	
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)
    	{   
		FatalError("connecting to server failed");
    	}
	
	close_session();*/
	


    // GTK

    char msg[MAX_MSGLEN] ; // for chat interface
    
    // TESTING //
    int t = 0;
    gtk_init(&argc, &argv) ; // initialize GTK libraries
    t = LinkWidgets() ;
    //char *friends[5] = {"Brian", "Nathan", "Luke", "Josh", "David"} ;
    //display_friends(friends) ;
    if (t == 1) {
        exit(0) ;
    }
    Callbacks() ;
    gtk_widget_show(login_window) ; 
    gtk_main() ; // wait for events

    //free(blockName);
    return 0 ;
}


/* external function declarations */
int LinkWidgets() { // return 0 for success, 1 for error
    GtkBuilder *login, *chat, *friends ; // three different glade files
    GError *error = NULL ;

    /* build/link from login.glade file */
    login = gtk_builder_new() ;
    if (!gtk_builder_add_from_file(login, "../src/login.glade", &error)) {
        g_warning("%s", error->message) ;
        g_free(error) ;
        return 1 ;
    }
    login_window = GTK_WIDGET(gtk_builder_get_object(login, "login_window")) ;
    gtk_window_set_modal(GTK_WINDOW(login_window), true) ;
    gtk_widget_set_size_request(GTK_WIDGET(login_window), WINDOW_WIDTH, WINDOW_HEIGHT) ;
    gtk_builder_connect_signals(login, NULL) ;
    login_vbox = GTK_WIDGET(gtk_builder_get_object(login, "login_vbox")) ;
    logo = GTK_WIDGET(gtk_builder_get_object(login, "logo")) ;
    username_label = GTK_WIDGET(gtk_builder_get_object(login, "username_label")) ;
    username_entry = GTK_WIDGET(gtk_builder_get_object(login, "username_entry")) ;
    password_label = GTK_WIDGET(gtk_builder_get_object(login, "password_label")) ;
    password_entry = GTK_WIDGET(gtk_builder_get_object(login, "password_entry")) ;
    login_btn = GTK_WIDGET(gtk_builder_get_object(login, "login_btn")) ;
    or_label = GTK_WIDGET(gtk_builder_get_object(login, "or_label")) ;
    create_btn = GTK_WIDGET(gtk_builder_get_object(login, "create_btn")) ;
    g_object_unref(login) ;
    error = NULL ;
    
    /* build/link from friends.glade file */
    friends = gtk_builder_new() ;
    if (!gtk_builder_add_from_file(friends, "../src/friends.glade", &error)) {
        g_warning("%s", error->message) ;
        g_free(error) ;
        return 1 ;
    }
    friends_window = GTK_WIDGET(gtk_builder_get_object(friends, "friends_window")) ;
    gtk_window_set_modal(GTK_WINDOW(friends_window), true) ;
    gtk_widget_set_size_request(GTK_WIDGET(friends_window), WINDOW_WIDTH, WINDOW_HEIGHT) ;
    gtk_builder_connect_signals(friends, NULL) ;
    friends_vbox = GTK_WIDGET(gtk_builder_get_object(friends, "friends_vbox")) ;
    friends_hbox1 = GTK_WIDGET(gtk_builder_get_object(friends, "friends_hbox1")) ;
    friends_hbox2 = GTK_WIDGET(gtk_builder_get_object(friends, "friends_hbox2")) ;
    friends_label = GTK_WIDGET(gtk_builder_get_object(friends, "friends_label")) ;
    friends_scroll = GTK_WIDGET(gtk_builder_get_object(friends, "friends_scroll")) ;
    friends_display = GTK_WIDGET(gtk_builder_get_object(friends, "friends_display")) ;
    gtk_text_view_set_editable(GTK_TEXT_VIEW(friends_display), false) ; // make friends list read-only
    friends_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(friends_display)) ;
    friends_entry = GTK_WIDGET(gtk_builder_get_object(friends, "friends_entry")) ;
    show_btn = GTK_WIDGET(gtk_builder_get_object(friends, "show_btn")) ;
    //delete_btn = GTK_WIDGET(gtk_builder_get_object(friends, "delete_btn")) ;
    block_btn = GTK_WIDGET(gtk_builder_get_object(friends, "block_btn")) ;
    chat_btn = GTK_WIDGET(gtk_builder_get_object(friends, "chat_btn")) ;
    logout_btn1 = GTK_WIDGET(gtk_builder_get_object(friends, "logout_btn1")) ;
    g_object_unref(friends) ;
    error = NULL ;

    /* build/link from chat.glade file */
    chat = gtk_builder_new() ;
    if (!gtk_builder_add_from_file(chat, "../src/chat.glade", &error)) {
        g_warning("%s", error->message) ;
        g_free(error) ;
        return 1 ;
    }
    chat_window = GTK_WIDGET(gtk_builder_get_object(chat, "chat_window")) ;
    gtk_window_set_modal(GTK_WINDOW(chat_window), true) ;
    gtk_widget_set_size_request(GTK_WIDGET(chat_window), WINDOW_WIDTH, WINDOW_HEIGHT) ;
    gtk_builder_connect_signals(chat, NULL) ;
    chat_vbox = GTK_WIDGET(gtk_builder_get_object(chat, "chat_vbox")) ;
    chat_hbox1 = GTK_WIDGET(gtk_builder_get_object(chat, "chat_hbox1")) ;
    chat_hbox2 = GTK_WIDGET(gtk_builder_get_object(chat, "chat_hbox2")) ;
    chat_label = GTK_WIDGET(gtk_builder_get_object(chat, "chat_label")) ;
    chat_scroll = GTK_WIDGET(gtk_builder_get_object(chat, "chat_scroll")) ;
    chat_display = GTK_WIDGET(gtk_builder_get_object(chat, "chat_display")) ;
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_display), false) ; // make chat display read-only
    chat_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_display)) ;
    chat_entry = GTK_WIDGET(gtk_builder_get_object(chat, "chat_entry")) ;
    send_btn = GTK_WIDGET(gtk_builder_get_object(chat, "send_btn")) ;
    refresh_btn = GTK_WIDGET(gtk_builder_get_object(chat, "refresh_btn")) ;
    friends_btn = GTK_WIDGET(gtk_builder_get_object(chat, "friends_btn")) ;
    logout_btn2 = GTK_WIDGET(gtk_builder_get_object(chat, "logout_btn2")) ;
    g_object_unref(chat) ;
    error = NULL ;

    return 0 ;
}

/* instantiate all event callbacks */
void Callbacks() {
    /* login/register window callbacks */
    g_signal_connect(login_btn, "clicked", G_CALLBACK(click_login), NULL) ;
    g_signal_connect(create_btn, "clicked", G_CALLBACK(click_create), NULL) ;
    g_signal_connect(login_window, "destroy", G_CALLBACK(EndProgram), NULL) ;
    /* friends list window callbacks */
    g_signal_connect(chat_btn, "clicked", G_CALLBACK(click_chat), NULL) ;
    g_signal_connect(logout_btn1, "clicked", G_CALLBACK(EndProgram), NULL) ;
    g_signal_connect(block_btn, "clicked", G_CALLBACK(click_block), NULL) ;
    //g_signal_connect(add_btn, "clicked", G_CALLBACK(click_add), NULL) ;
    //g_signal_connect(delete_btn, "clicked", G_CALLBACK(click_delete), NULL) ;
    g_signal_connect(friends_window, "destroy", G_CALLBACK(EndProgram), NULL) ;

    /* chat room window callbacks */
    g_signal_connect(friends_btn, "clicked", G_CALLBACK(click_friends), NULL) ;
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(click_refresh), NULL) ;
    g_signal_connect(show_btn, "clicked", G_CALLBACK(display_friends), NULL) ;
    g_signal_connect(logout_btn2, "clicked", G_CALLBACK(EndProgram), NULL) ;
    g_signal_connect(send_btn, "clicked", G_CALLBACK(click_send), NULL) ;
    g_signal_connect(chat_window, "destroy", G_CALLBACK(EndProgram), NULL) ;
}

/* conversion function from gchar to char */
void convert(const gchar *src, char dest[]) {sprintf(dest, "%s", src) ; }


/* callback function definitions */

static void display_friends(GtkWidget *widget, gpointer data) { // need to change this function once user struct is complete
 /*   int size ;
    gchar *temp = NULL;
    //for (size = 0; friends[size][0] != NULL; size++);
	
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
		FatalError("socket creation failed");
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)  
		FatalError("connecting to server failed");

	strcpy(SendBuf, "DISPLAY FRIENDS");
	n = write(SocketFD, SendBuf, strlen(SendBuf));
	if (n < 0)
		FatalError("writing");

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
	if (n<0)
		FatalError("reading");
	RecvBuf[n] = 0;
	
	strcpy(SendBuf, "ok");
	n = write(SocketFD, SendBuf, strlen(SendBuf));
	if (n<0)
		FatalError("writing");

	int index = 0;
	for (int i=0; i<10; i++)
	{
		n = read(SocketFD, RecvBuf, BUFFSIZE-1);
		if (n<0)
			FatalError("reading");
		RecvBuf[n] = 0;
		if (strcmp(RecvBuf, "@") != 0)
		{
			if (index == 10)
				index = 0;

			strcpy(friends[index], RecvBuf);
			index++;		
		}
		strcpy(SendBuf, "got it");
		n = write(SocketFD, SendBuf, strlen(SendBuf));
		if (n<0)
			FatalError("writing");
	}

	close(SocketFD);
	*/	
	/*bool flag;

    for (int i = 0; i < size; i++) {
	flag = true;
       	temp = g_malloc(sizeof(friends[i])) ;
       	g_stpcpy(temp, friends[i]) ;
	for(int j= 0; j<9; j++){
			if(strcmp(friends[i], blockName[j])==0){
				flag = false;
			}
	}
	if (flag)
	{
	        gtk_text_buffer_insert_at_cursor(friends_buffer, temp, (gint) strlen(temp)) ;
       		gtk_text_buffer_insert_at_cursor(friends_buffer, "\n", 1) ;
	}
        temp[0] = '\0' ;
        g_free(temp) ;
    }*/
  /*  int size ;
    gchar *temp = NULL;
    for (size = 0; friends[size] != NULL; size++);
	
	bool flag;

    for (int i = 0; i < size; i++) {
	flag = true;
       	temp = g_malloc(sizeof(friends[i])) ;
       	g_stpcpy(temp, friends[i]) ;
	for(int j= 0; j<9; j++){
			if(strcmp(friends[i], blockName[j])==0){
				flag = false;
			}
	}
	if (flag)
	{
	        gtk_text_buffer_insert_at_cursor(friends_buffer, temp, (gint) strlen(temp)) ;
       		gtk_text_buffer_insert_at_cursor(friends_buffer, "\n", 1) ;
	}
        temp[0] = '\0' ;
        g_free(temp) ;
    }*/


    //gtk_text_buffer_insert_at_cursor(friends_buffer, u, (gint) strlen(u)) ;
    //gtk_text_buffer_insert_at_cursor(friends_buffer, "\n", 1) ;
}


static void click_login(GtkWidget *widget, gpointer data) { // clicking "Existing User: LOGIN" button
    /* check if username/password are valid
     * if invalid, ask user to try again
     * if valid, log in account, close login window, open friends list window
     */
    const gchar *username, *password ;
    bool uname, pword ; // whether or not username exists | whether or not password is correct
    username = gtk_entry_get_text(GTK_ENTRY(username_entry)) ;
    password = gtk_entry_get_text(GTK_ENTRY(password_entry)) ;

	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
		FatalError("socket creation failed");
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)  
		FatalError("connecting to server failed");
	
	strcpy(SendBuf, "LOG IN");
    	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
		FatalError("writing to socket failed");	

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0)   
		FatalError("reading from socket failed");	
    	RecvBuf[n] = 0;
	printf("%s\n", RecvBuf);
	
	convert(username, SendBuf);
	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
		FatalError("writing to socket failed");

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0)   
		FatalError("reading from socket failed");	
    	RecvBuf[n] = 0;

	convert(password, SendBuf);
	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
		FatalError("writing to socket failed");

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0)   
		FatalError("reading from socket failed");	
    	RecvBuf[n] = 0;

	if (strcmp(RecvBuf, "logged in") == 0)
	{
		close(SocketFD);
		gtk_widget_show(friends_window) ;
        	//display_friends(friends) ;
        	gtk_widget_hide(login_window) ;
	}
	else
	{
		close(SocketFD);
		gtk_entry_set_text(GTK_ENTRY(username_entry), "Password or Id is incorrect. Please try again.") ; 
        	gtk_editable_select_region(GTK_EDITABLE(username_entry), 0, GTK_ENTRY(username_entry)->text_length) ;
	}


/*    uname = true ; // testing
    pword = false ; // testing
||||||| merged common ancestors
    uname = true ; // testing
    pword = false ; // testing
=======
    uname = true ; // testing
    pword = true ; // testing
>>>>>>> 0e95025a096f7b7ff455816ad9aaac321e9773cf
    // run functions to see if username exists OR if password is correct
    if (uname && pword) { // valid
        // //Check user login by entering username and password feilds
	//if (strcpy(uname, XXX) == 0 && strcpy(pword, XXX) == 0){}
	
        gtk_widget_show(friends_window) ;
        //display_friends(friends) ;
        gtk_widget_hide(login_window) ;
    } else if (uname && !pword) { // password is incorrect
        gtk_entry_set_text(GTK_ENTRY(username_entry), "Password is incorrect. Please try again.") ; 
        gtk_editable_select_region(GTK_EDITABLE(username_entry), 0, GTK_ENTRY(username_entry)->text_length) ;
    } else if (!uname) { // username doesn't exist
        gtk_entry_set_text(GTK_ENTRY(username_entry), "Username does not exist. Please try again.") ;
        gtk_editable_select_region(GTK_EDITABLE(username_entry), 0, GTK_ENTRY(username_entry)->text_length) ;
<<<<<<< HEAD
    } */
    //}
    //}



   //g_strlcpy(u, username, strlen(username)) ;
}

static void click_create(GtkWidget *widget, gpointer data) { // clicking "New User: CREATE ACCOUNT" button
    /* check if username exists
     * if exists, ask user to try again
     * if doesn't exist, create account, close login window, open friends list window
     */
    const gchar *username, *password ;
    bool uname ; // whether or username exists 
    username = gtk_entry_get_text(GTK_ENTRY(username_entry)) ;
    password = gtk_entry_get_text(GTK_ENTRY(password_entry)) ;
	// check if username exists
    //uname = false ; // testing
    /*if (!uname) {

        // create account function
        
        gtk_widget_show(friends_window) ;
        // display_friends()
        gtk_widget_hide(login_window) ;

    } else {
        gtk_entry_set_text(GTK_ENTRY(username_entry), "Username already exists. Please try again.") ;
        gtk_editable_select_region(GTK_EDITABLE(username_entry), 0, GTK_ENTRY(username_entry)->text_length) ;
    } */
    
	

	
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
		FatalError("socket creation failed");
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)  
		FatalError("connecting to server failed");
    



	strcpy(SendBuf, "CREATE ACCOUNT");
    	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
		FatalError("writing to socket failed");	

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0)   
		FatalError("reading from socket failed");	
    	RecvBuf[n] = 0;
	
	printf("%s\n", RecvBuf);
    	//printf("%s: response from server: %s\n", Program, RecvBuf);
	if (strcmp(RecvBuf, "ok") == 0)
	{
			
		convert(username, SendBuf);
		printf("%s\n", SendBuf);
		n = write(SocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to socket failed");

		n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    		if (n < 0)   
			FatalError("reading from socket failed");
		RecvBuf[n] = 0;
	
		if (strcmp(RecvBuf, "ok") == 0)
		{
			printf("id send successfully\n");
		}
				
		convert(password, SendBuf);
		n = write(SocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to socket failed");
		n = read(SocketFD, RecvBuf, BUFFSIZE-1);
		// already sent the id and pass

    		if (n < 0)   
			FatalError("reading from socket failed");
		RecvBuf[n] = 0;


		n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    		if (n < 0)   
			FatalError("reading from socket failed");
		RecvBuf[n] = 0;
		
		printf("server returned... %s\n", RecvBuf);	

		strcpy(SendBuf, "ok");
		n = write(SocketFD, SendBuf, BUFFSIZE-1);	
		if (n<0)
			FatalError("writing");

			printf("closing connection\n");
			close(SocketFD);
        		gtk_widget_show(friends_window) ;
        		//display_friends();//userAccount[10]);
        		gtk_widget_hide(login_window) ;
		/*if (strcmp(RecvBuf, "ACCOUNT ADDED") == 0)
		{
			printf("inside account added\n");
			printf("closing connection\n");
			close(SocketFD);
        		gtk_widget_show(friends_window) ;
        		//display_friends();//userAccount[10]);
        		gtk_widget_hide(login_window) ;
			//display_friends();

		}
		else
		{
			
			printf("%s: Closing the connection...\n", Program);
    			close(SocketFD);	
        		gtk_entry_set_text(GTK_ENTRY(username_entry), "Username already exists. Please try again.") ;
        		gtk_editable_select_region(GTK_EDITABLE(username_entry), 0, GTK_ENTRY(username_entry)->text_length) ;
		}*/
		
	}
	
	//printf("%s: Closing the connection...\n", Program);
    	//close(SocketFD);	

    //g_strlcpy(u, username, strlen(username)) ;
}



static void click_chat(GtkWidget *widget, gpointer data) {
    bool flag ;
    /* user is on friends list = TRUE
     * user is NOT on friends list = FALSE
     */
    const gchar *username ;
    username = gtk_entry_get_text(GTK_ENTRY(username_entry)) ;
    if (strlen(username) == 0) { // if the user forgets to input a username
        gtk_entry_set_text(GTK_ENTRY(friends_entry), "Please input a username to ADD/DELETE/CHAT.") ;
        gtk_editable_select_region(GTK_EDITABLE(friends_entry), 0, GTK_ENTRY(friends_entry)->text_length) ;
    }
    // run delete function to get a value for flag
    flag = true ; // testing
    if (flag) {
        // connect to other client to chat
        gtk_widget_show(chat_window) ;
        gtk_entry_set_text(GTK_ENTRY(chat_entry), "Max characters 0/256.") ;
        gtk_widget_hide(friends_window) ;
    } else {
        gtk_entry_set_text(GTK_ENTRY(friends_entry), "Please input a username that is on your friends list.") ;
        gtk_editable_select_region(GTK_EDITABLE(friends_entry), 0, GTK_ENTRY(friends_entry)->text_length) ;
    }
}

static void click_friends(GtkWidget *widget, gpointer data) {
    gtk_widget_show(friends_window) ;
    //display_friends(friends) ;
    gtk_widget_hide(chat_window) ;
}


static void click_block(GtkWidget *widget, gpointer data) {
    const gchar *block ;
    char *converter; 
    block = gtk_entry_get_text(GTK_ENTRY(friends_entry)) ;
    if (strlen(block) == 0) { // if the user forgets to input a username
        gtk_entry_set_text(GTK_ENTRY(friends_entry), "Please input a username to BLOCK.") ;
        gtk_editable_select_region(GTK_EDITABLE(friends_entry), 0, GTK_ENTRY(friends_entry)->text_length) ;
    }

	//convert(block, converter);
	//strcpy(blockName[blocked],converter);
	//blocked++; 
    // send block to the server
	
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
		FatalError("socket creation failed");
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)  
		FatalError("connecting to server failed");

	strcpy(SendBuf, "BLOCK");
	n = write(SocketFD, SendBuf, strlen(SendBuf));
	if (n < 0)
		FatalError("writing to datasocket failed");

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0)   
		FatalError("reading from socket failed");
	RecvBuf[n] = 0;


	convert(block, SendBuf);
	n = write(SocketFD, SendBuf, strlen(SendBuf));
	if (n < 0)
		FatalError("writing to datasocket failed");

	printf("%s: Closing the connection...\n", Program);
    	close(SocketFD);


}

static void click_send(GtkWidget *widget, gpointer data) {
    const gchar *message ;
    message = gtk_entry_get_text(GTK_ENTRY(chat_entry)) ;
    if (strlen(message) == 0) { // if message is empty
        gtk_entry_set_text(GTK_ENTRY(chat_entry), "Please enter a valid message to send.") ;
        gtk_editable_select_region(GTK_EDITABLE(chat_entry), 0, GTK_ENTRY(chat_entry)->text_length) ;
    }




    // send message to server function 
   	//convert(message, SendBuf);
	//write_socket();





	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{
		FatalError("socket creation failed");
	}
	
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)
    	{   
		FatalError("connecting to server failed");
    	}
	strcpy(SendBuf, "SEND");
    	printf("%s: button is '%s'...\n", Program, SendBuf);
    	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
    	{   
		FatalError("writing to socket failed");
    	}	

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0) 
    	{   
		FatalError("reading from socket failed");
    	}
    	RecvBuf[n] = 0;
    	printf("%s: Received response: %s\n", Program, RecvBuf);
	if (strcmp(RecvBuf, "ok") == 0)
	{
		convert(message, SendBuf);
		printf("sending message\n");
		n = write(SocketFD, SendBuf, strlen(SendBuf));
		if (n < 0)
			FatalError("writing to socket failed");
	}

	printf("%s: Closing the connection...\n", Program);
    	close(SocketFD);





	
	
    // gtk_entry_set_text(GTK_ENTRY(chat_display), "%s: ", username) ;
    //gtk_text_buffer_insert_at_cursor(chat_buffer, u, (gint) strlen(u)) ;
    gtk_text_buffer_insert_at_cursor(chat_buffer, message, (gint) strlen(message)) ;
    gtk_text_buffer_insert_at_cursor(chat_buffer, "\n", 1) ;
    //gtk_text_view_set_buffer(GTK_TEXT_VIEW(chat_display), buffer) ; // not needed?	
}

static void click_refresh(GtkWidget *widget, gpointer data) {
    const gchar *message ;



    // get message from server
    // convert char to gchar
	//read_socket();



	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{
		FatalError("socket creation failed");
	}
	
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)
    	{   
		FatalError("connecting to server failed");
    	}
		
	strcpy(SendBuf, "REFRESH");

    	printf("%s: button is '%s'...\n", Program, SendBuf);
    	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
    	{   
		FatalError("writing to socket failed");
    	}	

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0) 
    	{   
		FatalError("reading from socket failed");
    	}
    	RecvBuf[n] = 0;
    	printf("%s: Received response: %s\n", Program, RecvBuf);

	printf("%s: Closing the connection...\n", Program);
    	close(SocketFD);






	
	message = g_malloc(sizeof(RecvBuf));
	g_stpcpy(message, RecvBuf);
	



    gtk_text_buffer_insert_at_cursor(chat_buffer, message, (gint) strlen(message)) ;
    gtk_text_buffer_insert_at_cursor(chat_buffer, "\n", 1) ;

	g_free(message);
}

static gboolean EndProgram(GtkWidget *widget, GdkEvent *event, gpointer data) {

    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     *
     * This is useful for popping up 'are you sure you want to quit?'
     * type diaglogs.
     */

    /*gtk_widget_destroy(login_window) ;
    gtk_widget_destroy(friends_window) ;
    gtk_widget_destroy(chat_window) ;*/
    gtk_main_quit() ;
    return TRUE ;
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
void write_socket()
{
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{
		FatalError("socket creation failed");
	}
	
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)
    	{   
		FatalError("connecting to server failed");
    	}

    	printf("%s: Sending message '%s'...\n", Program, SendBuf);
    	n = write(SocketFD, SendBuf, strlen(SendBuf));
    	if (n < 0)
    	{   
		FatalError("writing to socket failed");
    	}	

	close_session();
}
void read_socket()
{
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{
		FatalError("socket creation failed");
	}
	
	printf("%s: Connecting to the server at port %d...\n", Program, ntohs(ServerAddress.sin_port));
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in)) < 0)
    	{   
		FatalError("connecting to server failed");
    	}
	printf("connected\n");

	n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    	if (n < 0) 
    	{   
		FatalError("reading from socket failed");
    	}
    	//RecvBuf[n] = 0;
    	printf("%s: Received response: %s\n", Program, RecvBuf);

	close_session();
}
void close_session()
{
	printf("%s: Closing the connection...\n", Program);
    	close(SocketFD);
}





