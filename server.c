#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

long long int count=0;
void *(server_thread)();
void *(client_th)(void *);
extern int i;
int i =0;
int ch=0;
/* ##############################################################>>this is main thread<<################################################################*/
int main()
{
	int check,id;
	pthread_t thid[1];
	id=pthread_create(&thid[0],0,server_thread,NULL);
	if(id==0)
	{
		printf("###################>>SERVER START RUNNING<<####################\n");
	}
	else
	{
		perror("thread failed");
		exit(0);
	}
	while(1)
	{

	}
	return 0;
}
/* ##############################################################>>this is server thread<<################################################################*/

void* server_thread()
{
	  int check,fds,length,m=0;
          char ch;
//	 int new_fd;
	  int id;
	  int *fd;
	  fd = (int *)malloc(sizeof(int)*100);
	  memset(fd,0,100);

	  pthread_t *thid;



	  thid=(pthread_t*)malloc(sizeof(pthread_t)*1); /* memory initialization for store the identity of threads */
          int sock_fd,on=1;
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
          add.sin_addr.s_addr=htonl(INADDR_ANY);
	  setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)); /* it is used for readdressing the server used (bind: address already in use)*/
	  check=bind(sock_fd,(struct sockaddr *)&add,length);
          if(check==-1)
          {
                  perror("bind");
                  exit(EXIT_FAILURE);
          }
 	  check=listen(sock_fd,1000);
          if(check==-1)
          {
                  perror("listen");
                  exit(EXIT_FAILURE);
          }

	  while(1)
	{
		if(i==99)
		i=0;
	///	printf("hello..stuck here\n");
	  	fds=accept(sock_fd,(struct sockaddr *)&add,&length);
		if(fds!=-1)
		{
			count++;
			++i;
			*(fd+i-1)=fds;
		//	fd=fds;
//			printf("no. of clients running till now...!!!\n",i);
			thid=realloc(thid,sizeof(pthread_t)*i);
			if(!thid)
			{
				perror("realloc fails");
				exit(0);
			}

	//		printf("m here....!!!\n");
			id=pthread_create((thid+i-1),0,client_th,(void*)(fd+i-1));
	//		printf("m here....!!!\n");

			if(id==0)
			{
				printf("new_client no. %lld connected to the server\n",count);
			}
			else
			{
				perror("pthread_t create failes...!!\n");
				exit(0);
			}

		}

		else
          	{
          	        perror("socket");
          	        exit(EXIT_FAILURE);
          	}
		

	}
}

/* ###########################################################>>this is communication(Antena) thread<<############################################################*/
void *client_th(void *arg)
{
	void *retval;
	int i,fdd;
//	arg = (int*)arg;
	fdd = *(int *)arg;
//	char ch = 'a';
//	int ch = 0;	



//	fdd=*arg;
	printf("this is thread id passed-->%d \n",fdd);
	ch++;
	write(fdd,&ch,sizeof(int));
	read(fdd,&ch,sizeof(int));
	printf("client says.......!!!--->%d\n",ch);


	

	close(fdd);
	pthread_detach(pthread_self());
}
