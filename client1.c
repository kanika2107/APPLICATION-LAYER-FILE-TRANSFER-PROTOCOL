#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

struct node
{
	char date[12];
	char times[7];
	char name[10];
	char type[20];
	char size[100];
};
void FileHashChanges(char buffer[],int i);
void IndexgetChanges(char buffer[],int i);
char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}
void spacedec(char input[])
{
	int i=0,n=strlen(input),j;
	while (i < n)
    {
        if(input[i]==' ' && (input[i+1]==' ' || input[i-1]==' '))
        {
            for(j=i;j<n;j++)
            input[j]=input[j+1];
            n--;
        }
        else
        {
            i++;
        }
    }
}
void concatenate_string(char *original, char *add)
{
   while(*original)
      original++;
 
   while(*add)
   {
      *original = *add;
      add++;
      original++;
   }
   *original = '\0';
}


void FileDownloadChanges(char buffer[],int i)
{
	//system()
	//Client's request to ie server to client code here
	while(buffer[i]==' ')
	{
		i++;
	}
	char flag[100];int k=0;
	while(buffer[i]!=' ' && buffer[i]!='\n')
	{
		flag[k++]=buffer[i++];
	}
	if(strcmp(flag,"--TCP")==0)
	{
		k=0;
		char filename[100];
	i++;
	while(buffer[i]!=' ' && buffer[i]!='\n')
	{
		filename[k++]=buffer[i++];
	}
	filename[k]='\0';
	//printf("k%skkkkkkkkkkkkkkkkkkkkkk\n",filename);
	
	int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    int numrv;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5010);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  //  printf("ola");
    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
      //  return -1;
    }
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            printf("File opern error");
        //    return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            //system("cat a.c");
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
             //   printf("%s\n",buff);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
       
        }

        close(connfd);
        close(listenfd);

	}
	else if(strcmp(flag,"--UDP")==0)
	{

	}
	return;
}


void FileUploadChanges(char buffer[],int i)
{
	char final[121];
	
		while(buffer[i]==' ')
	{
		i++;
	}
	char flag[100];int k=0;
	while(buffer[i]!=' ' && buffer[i]!='\n')
	{
		flag[k++]=buffer[i++];
	}
	if(strcmp(flag,"--TCP")==0)
	{
		k=0;
		char filename[100];
	i++;
	while(buffer[i]!=' ' && buffer[i]!='\n')
	{
		filename[k++]=buffer[i++];
	}
	filename[k]='\0';



//	char final[121];
	//final[0]='.',final[1]='.',final[2]='/' ;
	//concatenate_string(final,filename);
	//printf("k%skkkkkkkkkkkkkkkkkkkkkk\n",filename);
	
	int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    int numrv;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8020);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  //  printf("ola");
    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
      //  return -1;
    }
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            printf("File opern error");
        //    return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            //system("cat a.c");
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
             //   printf("%s\n",buff);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
       
        }

        close(connfd);
        close(listenfd);

	}
	else if(strcmp(flag,"--UDP")==0)
	{

	}
	return;
}








int main(int argc, char *argv[])
{
int p;
printf("Enter 0 for UDP and 1 for TCP");
scanf("%d",&p);
if(p==1)
{
	
	int listenSocket = 0;	// This is my server's socket which is created to 
							//	listen to incoming connections
	int connectionSocket = 0;

	struct sockaddr_in serv_addr;		// This is for addrport for listening

	// Creating a socket

	listenSocket = socket(AF_INET,SOCK_STREAM,0);
	if(listenSocket<0)
	{
		printf("ERROR WHILE CREATING A SOCKET\n");
		return 0;
	}
	else
		printf("[SERVER] SOCKET ESTABLISHED SUCCESSFULLY\n\n");

	// Its a general practice to make the entries 0 to clear them of malicious entry

	bzero((char *) &serv_addr,sizeof(serv_addr));

	// Binding the socket

	int portno = 5005;
	serv_addr.sin_family = AF_INET;	//For a remote machine
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(portno);

	if(bind(listenSocket,(struct sockaddr * )&serv_addr,sizeof(serv_addr))<0)
		printf("ERROR WHILE BINDING THE SOCKET\n");
	else
		printf("[SERVER] SOCKET BINDED SUCCESSFULLY\n");

	// Listening to connections

	if(listen(listenSocket,10) == -1)	//maximum connections listening to 10
	{
		printf("[SERVER] FAILED TO ESTABLISH LISTENING \n\n");
	}
	printf("[SERVER] Waiting fo client to connect....\n" );

	// Accepting connections
	while((connectionSocket=accept(listenSocket , (struct sockaddr*)NULL,NULL))<0);

	// NULL will get filled in by the client's sockaddr once a connection is establised

	printf("[CONNECTED]\n");

	char buffer[1024];

	while(1)
	{
	bzero(buffer,1024);
	if(recv(connectionSocket,buffer,1023,0)<0)
		printf("ERROR whiile reading from Client\n");
	//printf("serverrec%s\n",buffer);
	int i=0;
		char command[100];
		spacedec(buffer);
		while(buffer[i]!=' ')
		{
			command[i]=buffer[i];
			i++;

		}
		command[i]='\0';
		printf(">>");
		if(strcmp(command,"IndexGet")==0)
		{
			IndexgetChanges(buffer,i);
		}
		if(strcmp(command,"FileHash")==0)
		{
			FileHashChanges(buffer,i);
		}
		if(strcmp(command,"FileDownload")==0)
		{
			FileDownloadChanges(buffer,i);
		}
		if(strcmp(command,"FileUpload")==0)
		{
			FileUploadChanges(buffer,i); 
		} 
	//	printf("%s\n",buffer);
	bzero(buffer,1023);
	int flagD=0;
	int flagU=0;
	//printf("Reply to Client: ");
	printf(">>");
	fgets(buffer,1023,stdin);
	char Filename[100];
		if((buffer[0]=='F' && buffer[1]=='i' && buffer[2]=='l' && buffer[3]=='e' && buffer[4]=='D' && buffer[5]=='o' && buffer[6]=='w' && buffer[7]=='n' && buffer[8]=='l' && buffer[9]=='o' && buffer[10]=='a' && buffer[11]=='d' )  )
		{
				flagD=1;

		int counts=0;
		int i=0;
		while(counts!=2)
		{
			if(buffer[i]==' ')
			{
				counts++;
			}
			i++;
		}
		int k=0;
		while(buffer[i]!='\n' && buffer[i]!=' ' && buffer[i]!='\0')
		{
			Filename[k++]=buffer[i];
			i++;
		}
		Filename[k]='\0';
	}
	else if((buffer[0]=='F' && buffer[1]=='i' && buffer[2]=='l' && buffer[3]=='e' && buffer[4]=='U' && buffer[5]=='p' && buffer[6]=='l' && buffer[7]=='o' && buffer[8]=='a' && buffer[9]=='d'))
	{

		flagU=1;
		int counts=0;
		int i=0;
		while(counts!=2)
		{
			if(buffer[i]==' ')
			{
				counts++;
			}
			i++;
		}
		int k=0;
		while(buffer[i]!='\n' && buffer[i]!=' ' && buffer[i]!='\0')
		{
			Filename[k++]=buffer[i];
			i++;
		}
		Filename[k]='\0';


	}

	send(connectionSocket,buffer,strlen(buffer),0);
	if(flagD==1)
	{

					//system("cd ./");
				    int sockfd1 = 0;
				    int bytesReceived1 = 0;
				    char recvBuff1[256];
				    memset(recvBuff1, '0', sizeof(recvBuff1));
				    struct sockaddr_in serv_addr1;
				    //printf("yay");

				    /* Create a socket first */
				    if((sockfd1 = socket(AF_INET, SOCK_STREAM, 0))< 0)
				    {
				        printf("\n Error : Could not create socket \n");
				        //return 1;
				    }

				    /* Initialize sockaddr_in data structure */
				    serv_addr1.sin_family = AF_INET;
				    serv_addr1.sin_port = htons(5020); // port
				    serv_addr1.sin_addr.s_addr = inet_addr("127.0.0.1");

				    /* Attempt a connection */
				    while(connect(sockfd1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1))<0);
				    /* Create file where data will be stored */
				    FILE *fp1;
				    fp1 = fopen(Filename, "ab"); 
				    if(NULL == fp1)
				    {
				        printf("Error opening file");
				        return 1;
				    }

				    /* Receive data in chunks of 256 bytes */
				    while((bytesReceived1 = read(sockfd1, recvBuff1, 256)) > 0)
				    {
				    	//printf("%s",recvBuff1);
				        printf("Bytes received %d\n",bytesReceived1);    
				        // recvBuff[n] = 0;
				        fwrite(recvBuff1, 1,bytesReceived1,fp1);
				        // printf("%s \n", recvBuff);
				    }

				    if(bytesReceived1 < 0)
				    {
				    	//system("cd C/.");
				        printf("\n Read Error \n");
				    
				    }
				    close(sockfd1);



		}

		if(flagU==1)

		{
			char final[121];
			final[0]='C';
			final[1]='/';
			concatenate_string(final,Filename);
				//system("cd /./");
				    int sockfd1 = 0;
				    int bytesReceived1 = 0;
				    char recvBuff1[256];
				    memset(recvBuff1, '0', sizeof(recvBuff1));
				    struct sockaddr_in serv_addr1;
				    //printf("yay");

				    /* Creana;,te a socket first */
				    if((sockfd1 = socket(AF_INET, SOCK_STREAM, 0))< 0)
				    {
				        printf("\n Error : Could not create socket \n");
				        //return 1;
				    }

				    /* Initialize sockaddr_in data structure */
				    serv_addr1.sin_family = AF_INET;
				    serv_addr1.sin_port = htons(7020); // port
				    serv_addr1.sin_addr.s_addr = inet_addr("127.0.0.1");

				    /* Attempt a connection */
				    while(connect(sockfd1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1))<0);
				    /* Create file where data will be stored */
				    FILE *fp1;
				    fp1 = fopen(final, "ab"); 
				    if(NULL == fp1)
				    {
				        printf("Error opening file");
				        return 1;
				    }

				    /* Receive data in chunks of 256 bytes */
				    while((bytesReceived1 = read(sockfd1, recvBuff1, 256)) > 0)
				    {
				    	//printf("%s",recvBuff1);
				        printf("Bytes received %d\n",bytesReceived1);    
				        // recvBuff[n] = 0;
				        fwrite(recvBuff1, 1,bytesReceived1,fp1);
				        // printf("%s \n", recvBuff);
				    }

				    if(bytesReceived1 < 0)
				    {
				        printf("\n Read Error \n");
				    
				    }
				    close(sockfd1);			
		}



	//printf("serversend %s\n",buffer);

}

	printf("\nClosing connection\n");
	close(connectionSocket);
	close(listenSocket);
	return 0;
}
else
{
	
}
}
void IndexgetChanges(char buffer[],int i)
{
	//printf("%s",buffer);
	i++;
	int k=0;
	char flag[20];
	while(buffer[i]!=' ')
	{
		flag[k++]=buffer[i++];
		
	}
	int ha = i;
	flag[k]='\0';
	//printf("%s\n",flag);
	//printf("%s",flag);

	if(strcmp(flag,"--shortlist")==0)
	{
	//	printf("yay");
		//2005-10-30 T 10:45 UTC
	//	for(k=0;k<10;k++)
		char startdate[11],starttime[10],enddate[11],endtime[10];
		for(k=0;k<10;k++)
		{
				startdate[k]=buffer[++i];
		}
		i++;
		startdate[k]='\0';
		for(k=0;k<5;k++)
		{
				starttime[k]=buffer[++i];
		}	
		starttime[k]='\0';
		i++;
		for(k=0;k<10;k++)
		{
				enddate[k]=buffer[++i];
		}	
		enddate[k]='\0';
		i++;
		for(k=0;k<5;k++)
		{
				endtime[k]=buffer[++i];
		}	
		endtime[k]='\0';

		FILE *fp;
		char path[100000];
		
		struct node details[100];
		k=0;
		int count;

		///////////////////////////////////////////////////
			
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f1", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[10]='\0';
				strcpy(details[count++].date ,path);
			//	printf("%s",details[count-1].date);			
			}

			pclose(fp);
		////////////////////////////////////////////////////

			count=0;
			fp = popen("cd ./ ; stat -c %s *", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[100]='\0';
				strcpy(details[count++].size ,path);
			//	printf("%s",details[count-1].date);			
			}

			pclose(fp);

			//////////////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f2", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[5]='\0';
				strcpy(details[count++].times ,path);			

			}
			pclose(fp);

		////////////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; ls ", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].name ,path);			
			}
			for(i=0;i<count;i++)
			{
				spacedec(details[i].name);
				details[i].name[strlen(details[i].name)-1]='\0';
			}
		pclose(fp);

/////////////////////////////////////////////////////
		count =0;
			fp = popen("cd ./ ; stat -c %F * ", "r");

			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].type ,path);			

			}
			for(i=0;i<count;i++)
			{
				details[i].type[strlen(details[i].type)-1]='\0';
			}
			pclose(fp);

			printf("\n");
			//////////////////////////////////////////////
			for(i=0;i<count;i++)
			{
				if(strcmp(startdate,details[i].date) <= 0 && strcmp(enddate,details[i].date) >= 0)
				{
					if((startdate == details[i].date && strcmp(starttime,details[i].times) > 0) ||(enddate == details[i].date && strcmp(endtime,details[i].times)) < 0)
					{
						continue;
					}
					else
					{
						printf("%s %s %s %s %s\n",details[i].name ,details[i].date,details[i].type,details[i].times,details[i].size);
					}

				}
			}
			return ;
	}
	printf("\n");
	
	if(strcmp(flag,"--regex")==0)
	{
//	printf("yaya");
	char regex[200];
	k=0;
	ha++;
	while(buffer[ha]!='\n')
	{
		regex[k++]=buffer[ha++];
		
	}
//	printf("%s",regex);

	regex[k]='\0';
	FILE *fp;
		char path[100000];
		k=0;
		int count;
		struct node details[100];

		///////////////////////////////////////////////////
			
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f1", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[10]='\0';
				strcpy(details[count++].date ,path);
			//	printf("%s",details[count-1].date);			
			}

			pclose(fp);
		////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f2", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[5]='\0';
				strcpy(details[count++].times ,path);			

			}
			pclose(fp);

		////////////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; ls ", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].name ,path);			
			}
			for(i=0;i<count;i++)
			{
				spacedec(details[i].name);
				details[i].name[strlen(details[i].name)-1]='\0';
			}
		pclose(fp);

/////////////////////////////////////////////////////
		count =0;
			fp = popen("cd ./ ; stat -c %F * ", "r");

			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].type ,path);			

			}
			for(i=0;i<count;i++)
			{
				details[i].type[strlen(details[i].type)-1]='\0';
			}
			pclose(fp);

			count=0;
			fp = popen("cd ./ ; stat -c %s *", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[100]='\0';
				strcpy(details[count++].size ,path);
			//	printf("%s",details[count-1].date);			
			}
			for(i=0;i<count;i++)
			{
				details[i].size[strlen(details[i].size)-1]='\0';
			}

			pclose(fp);

			for(i=0;i<count;i++)
			{
	//			printf("%s",strstr(details[i].name,regex));
	//			printf("%d %s %s\n",strlen(regex),regex,details[i].name);
				if(strstr(details[i].name,regex)!=NULL)
				{
					//printf("hey");
					printf("%s %s %s %s %s\n",details[i].name ,details[i].date,details[i].type,details[i].times,details[i].size);		
				}
			}
//	printf("%s\n",regex);
			return ;

	}
	//printf("hu\n");
	if(1==1)
	{
	//	printf("hu\n");
		FILE *fp;
		char path[100000];
		k=0;
		int count;
		struct node details[100];

		///////////////////////////////////////////////////
			
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f1", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[10]='\0';
				strcpy(details[count++].date ,path);
			//	printf("%s",details[count-1].date);			
			}

			pclose(fp);
		////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; stat -c %y * | cut -d ' ' -f2", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[5]='\0';
				strcpy(details[count++].times ,path);			

			}
			pclose(fp);

		////////////////////////////////////////////////////////////
			count=0;
			fp = popen("cd ./ ; ls ", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].name ,path);			
			}
			for(i=0;i<count;i++)
			{
				spacedec(details[i].name);
				details[i].name[strlen(details[i].name)-1]='\0';
			}
		pclose(fp);

/////////////////////////////////////////////////////
		count =0;
			fp = popen("cd ./ ; stat -c %F * ", "r");

			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				strcpy(details[count++].type ,path);			

			}
			for(i=0;i<count;i++)
			{
				details[i].type[strlen(details[i].type)-1]='\0';
			}
			pclose(fp);


			count=0;
			fp = popen("cd ./ ; stat -c %s *", "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[100]='\0';
				strcpy(details[count++].size ,path);
			//	printf("%s",details[count-1].date);			
			}
			for(i=0;i<count;i++)
			{
				details[i].size[strlen(details[i].size)-1]='\0';
			}

			pclose(fp);
			for(i=0;i<count;i++)
			{
				printf("%s %s %s %s %s\n",details[i].name ,details[i].date,details[i].type,details[i].times,details[i].size);
			}
		
	}
	return ;
}
void FileHashChanges(char buffer[],int i)
{
	char path[100000];
		
		struct node details[100];
	while(buffer[i]==' ')
	{
		i++;//+;
	}
	char flag[100];int k=0;
	while(buffer[i]!=' ' && buffer[i]!='\n')
	{
		flag[k++]=buffer[i++];
	}
	if(strcmp(flag,"--verify")==0)
	{
		i++;
		k=0;char filename[100];
		while(buffer[i]!='\n')
		{
			filename[k++]=buffer[i++];
		}
		filename[k]='\0';
		FILE* fp;
			//printf("%s ",filename);
			int count=0;
			char *cksum ="cd ./ ; cksum ";
			char cksum1[100];
			strcpy(cksum1,cksum);
			concatenate_string(cksum1,filename);
			concatenate_string(cksum1," | cut -d ' ' -f1");

			fp = popen(cksum1, "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[strlen(path)-1]='\0';
				printf("%s ",path);			
			}
			pclose(fp);

			char* stat = "cd ./ ; stat ";
			char stat1[1000];
			strcpy(stat1,stat);
			concatenate_string(stat1,filename);
			concatenate_string(stat1,"| grep Modify | cut -d ' ' -f2");
			fp = popen(stat1, "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				printf("%s",path);			
			}
			
			pclose(fp);
			return;

	}
	if(strcmp(flag,"--checkall")==0)
	{
		char filename[1000];
		FILE* fp1;
		char path1[1000];
		fp1 = popen("cd ./ ; ls", "r");
		while (fgets(path1, sizeof(path1)-1, fp1) != NULL)
		{
			path1[strlen(path1)-1]='\0';
			//	printf("%s ",path);
			strcpy(filename,path1);
			FILE* fp;
			printf("%s ",filename);
			int count=0;
			char *cksum ="cd ./ ; cksum ";
			char cksum1[100];
			strcpy(cksum1,cksum);
			concatenate_string(cksum1,filename);
			concatenate_string(cksum1," | cut -d ' ' -f1");

			fp = popen(cksum1, "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				path[strlen(path)-1]='\0';
				printf("%s ",path);			
			}
			pclose(fp);

			char* stat = "cd ./ ; stat ";
			char stat1[1000];
			strcpy(stat1,stat);
			concatenate_string(stat1,filename);
			concatenate_string(stat1,"| grep Modify | cut -d ' ' -f2");
			fp = popen(stat1, "r");
			while (fgets(path, sizeof(path)-1, fp) != NULL)
			{
				printf("%s",path);			
			}
			
			pclose(fp);			
		

	}
	pclose(fp1);
}
	
}
