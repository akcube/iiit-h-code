#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>

/////////////////////////////
#include <iostream>
#include <assert.h>
#include <tuple>
using namespace std;
/////////////////////////////

#include "thread_safe_queue.cpp"
#include "thread_safe_dict.cpp"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define ANSI_RESET "\x1b[0m"

typedef long long LL;

#define pb push_back
#define debug(x) cout << #x << " : " << x << endl
#define part cout << "-----------------------------------" << endl;

///////////////////////////////
#define MAX_CLIENTS 4
#define PORT_ARG 8001

vector<pthread_t> thread_pool;
thread_safe_queue<int> cqueue;
thread_safe_map<int, string> smap;

const int initial_msg_len = 256;

////////////////////////////////////

const LL buff_sz = 1048576;
///////////////////////////////////////////////////
pair<string, int> read_string_from_socket(const int &fd, int bytes)
{
    std::string output;
    output.resize(bytes);

    int bytes_received = read(fd, &output[0], bytes - 1);
    debug(bytes_received);
    if (bytes_received <= 0)
    {
        cerr << "Failed to read data from socket. \n";
        return {"", -1};
    }

    output[bytes_received] = 0;
    output.resize(bytes_received);
    // debug(output);
    return {output, bytes_received};
}

int send_string_on_socket(int fd, const string &s)
{
    // debug(s.length());
    int bytes_sent = write(fd, s.c_str(), s.length());
    if (bytes_sent < 0)
    {
        cerr << "Failed to SEND DATA via socket.\n";
    }

    return bytes_sent;
}

///////////////////////////////

void handle_connection(int client_socket_fd)
{
    // int client_socket_fd = *((int *)client_socket_fd_ptr);
    //####################################################

    int received_num, sent_num;

    /* read message from client */
    int ret_val = 1;

    while (true)
    {
        string cmd;
        tie(cmd, received_num) = read_string_from_socket(client_socket_fd, buff_sz);
        ret_val = received_num;
        // debug(ret_val);
        // printf("Read something\n");
        if (ret_val <= 0)
        {
            // perror("Error read()");
            printf("Server could not read msg sent from client\n");
            goto close_client_socket_ceremony;
        }
        // cout << "Client sent : " << cmd << endl;
        if (cmd == "exit")
        {
            cout << "Exit pressed by client" << endl;
            goto close_client_socket_ceremony;
        }
        
        auto iss = std::istringstream{cmd};
		auto str = std::string{};
		iss >> str;
		string k1s, temp;
		iss >> k1s;
		int k1 = stoll(k1s);

		string str_to_return = "";
		bool success;

		if(str == "insert"){
			iss >> temp;
			success = smap.insert_t({k1, temp});
			if(!success)
				str_to_return = "Key already exists";
			else 
				str_to_return = "Insertion successful";
		}
		else if(str == "concat"){
			iss >> temp;
			int k2 = stoll(temp);
			pair<bool, string> retval;
			retval = smap.cat_t(k1, k2);
			if(!retval.first)
				str_to_return = "Concat failed as at least one of the keys does not exist";
			else
				str_to_return = retval.second;
		}
		else if(str == "delete"){
			success = smap.erase_t(k1);
			if(!success)
				str_to_return = "No such key exists";
			else 
				str_to_return = "Deletion successful";
		}
		else if(str == "update"){
			iss >> temp;
			success = smap.update_t(k1, temp);
			if(!success)
				str_to_return = "Key does not exist";
			else
				str_to_return = temp;
		}
		else if(str == "fetch"){
			if(smap.exists(k1))
				str_to_return = smap.read_t(k1);
			else
				str_to_return = "Key does not exist";
		}


        ////////////////////////////////////////
        // "If the server write a message on the socket and then close it before the client's read. Will the client be able to read the message?"
        // Yes. The client will get the data that was sent before the FIN packet that closes the socket.

        pthread_t id = pthread_self();
        str_to_return = to_string(id) + ":" + str_to_return;
        int sent_to_client = send_string_on_socket(client_socket_fd, str_to_return);
        // debug(sent_to_client);
        if (sent_to_client == -1)
        {
            perror("Error while writing to client. Seems socket has been closed");
            goto close_client_socket_ceremony;
        }
    }

close_client_socket_ceremony:
    close(client_socket_fd);
    printf(BRED "Disconnected from client" ANSI_RESET "\n");
    // return NULL;
}

void *wait_on_client(void *arg){
	while(true){
		int client_socket_fd = cqueue.pop();
		pid_t tid = gettid();
		cout<<"Socket id: "<<client_socket_fd<<" Thread id: "<<tid<<endl;
		handle_connection(client_socket_fd);
	}
}

int main(int argc, char *argv[])
{

	if(argc != 2){
		cout<<"Usage ./server [number of worker threads in the thread pool]"<<endl;
		exit(1);
	}

	int num_threads = stoll(argv[1]);
	if(num_threads == -1){
		cout<<"Usage ./server [number of worker threads in the thread pool]"<<endl;
		exit(1);
	}

	thread_pool.resize(num_threads);
	smap.resize(101);

    int i, j, k, t, n;

    int wel_socket_fd, client_socket_fd, port_number;
    socklen_t clilen;

    struct sockaddr_in serv_addr_obj, client_addr_obj;
    /////////////////////////////////////////////////////////////////////////
    /* create socket */
    /*
    The server program must have a special door—more precisely,
    a special socket—that welcomes some initial contact 
    from a client process running on an arbitrary host
    */
    //get welcoming socket
    //get ip,port
    /////////////////////////
    wel_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (wel_socket_fd < 0)
    {
        perror("ERROR creating welcoming socket");
        close(wel_socket_fd);
        exit(-1);
    }

    //////////////////////////////////////////////////////////////////////
    /* IP address can be anything (INADDR_ANY) */
    bzero((char *)&serv_addr_obj, sizeof(serv_addr_obj));
    port_number = PORT_ARG;
    serv_addr_obj.sin_family = AF_INET;
    // On the server side I understand that INADDR_ANY will bind the port to all available interfaces,
    serv_addr_obj.sin_addr.s_addr = INADDR_ANY;
    serv_addr_obj.sin_port = htons(port_number); //process specifies port

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* bind socket to this port number on this machine */
    /*When a socket is created with socket(2), it exists in a name space
       (address family) but has no address assigned to it.  bind() assigns
       the address specified by addr to the socket referred to by the file
       descriptor wel_sock_fd.  addrlen specifies the size, in bytes, of the
       address structure pointed to by addr.  */

    //CHECK WHY THE CASTING IS REQUIRED
    if (bind(wel_socket_fd, (struct sockaddr *)&serv_addr_obj, sizeof(serv_addr_obj)) < 0)
    {
        perror("Error on bind on welcome socket: ");
        close(wel_socket_fd);
        exit(-1);
    }
    //////////////////////////////////////////////////////////////////////////////////////

    /* listen for incoming connection requests */

    listen(wel_socket_fd, MAX_CLIENTS);
    cout << "Server has started listening on the LISTEN PORT" << endl;
    clilen = sizeof(client_addr_obj);

    for(auto &x:thread_pool)
    	pthread_create(&x, NULL, wait_on_client, NULL);
    

    while (1)
    {
        /* accept a new request, create a client_socket_fd */
        /*
        During the three-way handshake, the client process knocks on the welcoming door
of the server process. When the server “hears” the knocking, it creates a new door—
more precisely, a new socket that is dedicated to that particular client. 
        */
        //accept is a blocking call
        printf("Waiting for a new client to request for a connection\n");
        client_socket_fd = accept(wel_socket_fd, (struct sockaddr *)&client_addr_obj, &clilen);
        if (client_socket_fd < 0)
        {
            perror("ERROR while accept() system call occurred in SERVER");
            close(wel_socket_fd);
            exit(-1);
        }

        printf(BGRN "New client connected from port number %d and IP %s \n" ANSI_RESET, ntohs(client_addr_obj.sin_port), inet_ntoa(client_addr_obj.sin_addr));
        cqueue.push(client_socket_fd);
        // handle_connection(client_socket_fd);
    }

    close(wel_socket_fd);
    return 0;
}