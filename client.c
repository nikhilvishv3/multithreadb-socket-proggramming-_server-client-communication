#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>





int main()
{
	int count,check,length;
	pthread_t thid[2];
	long long int ch=0;


	int sock_fd;

	struct sockaddr_in add;
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	length= sizeof(struct sockaddr_in);



	
	if(sock_fd==-1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	add.sin_family=AF_INET;
	add.sin_port=htons(5000);
	add.sin_addr.s_addr=inet_addr("127.0.0.1");
	check=connect(sock_fd,(struct sockaddr *)&add,length);
	if(check==-1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	

	check=read(sock_fd,&ch,sizeof(int));
	if(check==-1)
	{
		perror("initialization of client fails...!!");
		exit(EXIT_FAILURE);
	}
	printf("server says.....!!!------>%lld\n",ch);
	write(sock_fd,&ch,sizeof(int));
	return 0;

}





