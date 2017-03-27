/******************************************************************/
// Project : Cache Managemment
// Group   : 17
// Date    : 7th December,2016
// Sem     : 5
/******************************************************************/

/******************************************************************/
// GROUP MEMBERS
// 1. Amee Bhuva (1401009)      
// 2. Subhashi Dobariya (1401012)
// 3. Twinkle Vaghela (1401106)
// 4. Himani Patel (1401111)
/******************************************************************/

/******************************************************************/
// ALGORITHMS
// 1. Most Recently Used (MRU)
// 2. Most Frequently Used (MFU)
// 3. First In First Out (FIFO)
// 4. Least Frequently Used (LFU)
/******************************************************************/

/*=================================*/
// HEADER FILES 
/*=================================*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#define MAX 10
#define NUM_THREADS 4
#include <string.h>
#include <time.h>
#include <signal.h>

/*=================================*/
// GLOBAL VARIABLES
/*=================================*/
char str[100];
int number[50];
int numbers[50];
time_t sec;
char array[100];
char cacheStr[10];
char newStr[10];
float hit=0;
float miss=0;
float total_char=0;

/*=================================*/
// FUNCTIONS  
/*=================================*/
void *main1(void *);
void *main2(void *);
void *main3(void *);
void *main4(void *);
void quitproc(int);
void sigintHandler(int);
int findUnique(char arr[]);
int inverse(char str[]);
time_t t1;
FILE *logFile;

/*=================================*/
// STRUCTURE  
/*=================================*/
typedef struct _thread_data_t 
{
	int tid;
  	double stuff;
} thread_data_t;

/*=================================*/
// MAIN FUNCTION 
/*=================================*/
int main(int argc, char *argv[])
{
	t1 = time(NULL);
	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Execution Started\n\n",ctime(&t1));
	}
	fclose(logFile);
  	//Call sigproc and quitproc
  	signal(SIGINT, sigintHandler);
  	signal(SIGQUIT,quitproc);

  	printf("\n********************************************************");
  	printf("\nCAUTION ! Ctrl-C is disabled..!! Use Ctrl+Z to quit..");
  	printf("\n********************************************************");
	printf("\n");
  	int i,rc, status, *status_ptr = &status; 
  	pthread_t thread[NUM_THREADS];  

  	//Create a thread_data_t argument array 
  	thread_data_t thr_data[NUM_THREADS];	
  
  	//This loop runs four times which is the number of theads in the program
  	for (i = 0; i < NUM_THREADS; ++i) 
  	{
    	thr_data[i].tid = i;

    	if(i==0)
    	{
    		if ((rc = pthread_create(&thread[i], NULL, main1, &thr_data[i]))) 
    		{
      			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      			logFile=fopen("log_file.txt","a+");
			if(logFile==NULL)
			{
				printf("Error");
				exit(1);
			}
			else
			{
				fprintf(logFile,"%s: Thread create Error\n\n",ctime(&t1));
			}
			fclose(logFile);
      			return EXIT_FAILURE;
    		}
    	}
    
    	else if(i==1)
    	{
    		if ((rc = pthread_create(&thread[i], NULL, main2, &thr_data[i]))) 
    		{
      			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      			logFile=fopen("log_file.txt","a+");
			if(logFile==NULL)
			{
				printf("Error");
				exit(1);
			}
			else
			{
				fprintf(logFile,"%s: Thread create Error\n\n",ctime(&t1));
			}
			fclose(logFile);
      			return EXIT_FAILURE;
    		}
    	}

    	else if(i==2)
    	{
    		if ((rc = pthread_create(&thread[i], NULL, main3, &thr_data[i]))) 
    		{
      			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      			logFile=fopen("log_file.txt","a+");
			if(logFile==NULL)
			{
				printf("Error");
				exit(1);
			}
			else
			{
				fprintf(logFile,"%s: Thread create Error\n\n",ctime(&t1));
			}
			fclose(logFile);
      			return EXIT_FAILURE;
    		}
    	}

    	else if(i==3)
    	{
    		if ((rc = pthread_create(&thread[i], NULL, main4, &thr_data[i]))) 
    		{
      			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			logFile=fopen("log_file.txt","a+");
			if(logFile==NULL)
			{
				printf("Error");
				exit(1);
			}
			else
			{
				fprintf(logFile,"%s: Thread create Error\n\n",ctime(&t1));
			}
			fclose(logFile);
      			return EXIT_FAILURE;
    		}
    	}
  	}

  	//Block until all threads complete 
  	for (i = 0; i < NUM_THREADS; ++i) 
  	{
    	pthread_join(thread[i], NULL);
  	}
 
	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Execution Completed\n\n",ctime(&t1));
	}
	fclose(logFile);
  	return EXIT_SUCCESS; 
}

//THREAD 1 : Implements MFU
void *main1(void *arg)
{
	
    //To get tid for itself 
	pthread_t tid = pthread_self();      

	int i=0;
  	int as =1;
	int aa=1;
	int k=0;
	char ch,a[100]; 
	FILE *fp,*fn;
	int j=0, n=0, count=0;
	int frequency[50];
	int count_i[26]={0},mn=0,l=0;
    int timer[100]={0},char_count=0;
    clock_t start,stop;
     
	//INS.txt : Opened for fetching variables
	//Cache_MFU.txt : Opened for storing cached variables
	fp = fopen("INS.txt","r");
	fn = fopen("Cache_MFU.txt","w");

      	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 1 started\n: Cache_MFU created\n\n",ctime(&t1));
	}
	fclose(logFile);
	if ( fp != NULL )
   	{
         //Starting the timer for keeping track of arrival of variables
         start = clock();
         ch = fgetc(fp); 
  	 	while (ch!=EOF)
    	{       
        	
        	if(ch >= 'a' && ch <= 'z')
        	{
				sec = time(NULL);
				//For printing the character and the time at which the character has arrived
	            printf ("Character : %c\tTime : %.8f sec\n",ch,((double)(stop - start)/CLOCKS_PER_SEC));
				a[l]=ch;
				l++;
				timer[mn]=sec;
            	count_i[ch - 'a']++;
				mn++;
				char_count++;
            }

        	//Sleep is added so that a bit difference in the arrival of the characters can be noticed
			usleep(50000);

        	//Stop the timer 
        	stop = clock(); 

        	//Get next character from the file     
			ch = fgetc(fp);
    	}
    	printf("\nString : %s \n",a);
    	findUnique(a);
    	int tt;
    	printf("\n-----------------------");
    	printf("\nVariable     Frequency\n");
    	printf("-----------------------\n");
    	for(int i = 0;i < 26;i++)
    	{
    		if(count_i[i]>0)
		{
	 		for (int k = 0; k < char_count+2; ++k)
	 		{
        		for (j = k + 1; j < char_count+2; ++j)
				{
	            	if (count_i[k] < count_i[j])
            	    {
                		tt = count_i[k];
	                	count_i[k] = count_i[j];
	                	count_i[j] = tt;
            	    }
            	}
	        }
			if(i>=0 && i<5)
			{
				fprintf(fn,"%c\n",newStr[i]);
			}
			printf("%c\t\t%d\n",newStr[i],count_i[i]);
		}
    }

	}
   	else
   	{
		//Why didn't the file open? 
      		perror ("INS.txt"); 
   	}

	//Closing the previously opened files
   	fclose (fp);
	fclose (fn);

	//Prints ID of the thread
	printf("\nThread ID (MRU) : %lu\n",tid);
	
	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 1 Executed\n: Cache_MFU modified and closed\n\n",ctime(&t1));
	}
	fclose(logFile);
	pthread_exit(NULL);
}

//THREAD 2 : Implements MRU
void *main2(void *arg)
{
	//To get tid for itself 
	pthread_t tid = pthread_self();      

	int i=0;
  	int as =1;
	int aa=1;
	int k=0;
	char line [20],ch,a[100]; 
	FILE *fp,*fn;
	int j=0, n=0, count=0;
	int frequency[50];
	char txt[256], var[100][256], temp[256];
	int count_i[26]={0},mn=0,l=0;
        int timer[100]={0},char_count=0;


	//INS.txt : Opened for fetching variables
	//Cache_MRU.txt : Opened for storing cached variables
	fp = fopen("INS.txt","r");
	fn = fopen("Cache_MRU.txt","w");
      	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 2 started\n: Cache_MRU created\n\n",ctime(&t1));
	}
	fclose(logFile);
	if ( fp != NULL )
   	{
         ch = fgetc(fp); 
  	 while (ch!=EOF)
    	{       
        	if(ch >= 'a' && ch <= 'z')
        	{
				sec = time(NULL);	
				a[l]=ch;
				l++;
				timer[mn]=sec;
            	count_i[ch - 'a']++;
				mn++;
				char_count++;
        	}
			//For proper synchronisation between threads
			usleep(60000);

			//Get next character from the file        
			ch = fgetc(fp);
    	}
    	findUnique(a);
    	int tt;
    	for(int i = 0;i < 26;i++)
    	{
    		if(count_i[i]>0)
			{
	 			for (int k = 0; k < char_count+2; ++k)
	 			{
        			for (j = k + 1; j < char_count+2; ++j)
					{
	            		if (count_i[k] < count_i[j])
            	    	{
                			tt = count_i[k];
	                		count_i[k] = count_i[j];
	                		count_i[j] = tt;
            	    	}
					}
				}
			}
    	}
    }
   	else
   	{
		//Why didn't the file open? 
      	perror ("INS.txt"); 
   	}
   	
 	inverse(newStr);
	for(int i=0;i<6;i++)
	{
			fprintf(fn,"%c\n",cacheStr[i]);		
	}

	//Closing the previously opened files
	fclose (fp);
	fclose (fn);

	//Prints ID of the thread
	printf("\nThread ID (MFU): %lu\n",tid);
	
	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 2 executed\n: Cache_MRU modified and closed\n\n",ctime(&t1));
	}
	fclose(logFile);
	pthread_exit(NULL);
}

//THREAD 3 : Implements FIFO
void *main3(void *arg)
{
	pthread_t tid = pthread_self();      /* to get tid for itself */
	char ch,a[5]; 
	FILE *fp,*fn,*log;
	char txt[256], var[100][256];
	int i=0,j;
	char temp;
     
	//INS.txt : Opened for fetching variables
	//Cache_FIFO.txt : Opened for storing cached variables
	fp = fopen("INS.txt","r");
	fn = fopen("Cache_FIFO.txt","w");
	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 3 started\n: Cache_FIFO created\n\n",ctime(&t1));
	}
	fclose(logFile);
	
	//For proper synchronisation between the threads
	sleep(3);

	if ( fp != NULL )
   	{
   	log=fopen("log_file.txt","a+");
	 //Get next character from the file
         ch = fgetc(fp); 
  	 while (ch!=EOF)
    	{       
        	if(ch >= 'a' && ch <= 'z')
        	{
        	    total_char++;
        		if(i<5)
        		{
        			a[i]=ch;
        			i++;
        			miss++;
        			fprintf(log,"%s: Cache Miss : %0.0f\n\n",ctime(&t1),miss);
        		}
        		else if(i==5)
        		{
				//Checks whether the arrived character exists in the cached data
        			if(a[0]!=ch && a[1]!=ch && a[2]!=ch && a[3]!=ch && a[4]!=ch)
        			{
        				miss++;
        				fprintf(log,"%s: Cache Miss : %0.0f\n\n",ctime(&t1),miss); 	
        				for(j=0;j<5;j++)
        				{
        					temp=a[0];
        					a[j]=a[j+1];
        				}
        				a[4]=ch;
        			}
        			else
        			{
        				hit++;
        				fprintf(log,"%s: Cache Hit : %0.0f\n\n",ctime(&t1),hit);
        			}
        		}
            }
            		//For proper synchronisation between threads
			usleep(50000);        
			ch = fgetc(fp);
    	}
    	printf("This is FIFO : %s",a);
    	printf("\nNo. of Cache Hits : %f\nNo. of Cache Miss : %f",hit,miss);
    	printf("\nHit Rate : %0.2f\nMiss Rate : %0.2f",(hit/total_char),(miss/total_char));
      }
   	  else
   	{
		//Why didn't the file open? 
      		perror ("INS.txt"); 
   	}
   	for(i=0;i<5;i++)
   	{
   		fprintf(fn,"%c\n",a[i]);
   	}

	//Closing the previously opened files
   	fclose (fp);
	fclose (fn);
	fclose(log);

	//Prints ID of the thread
	printf("\nThread ID (FIFO): %lu\n",tid);

	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 3 executed\n: Cache_FIFO modified and closed\n\n",ctime(&t1));
	}
	fclose(logFile);
	pthread_exit(NULL);
}

//THREAD 4 : Implements LFU
void *main4(void *arg)
{
	 //To get tid for itself 
	pthread_t tid = pthread_self();     

	int i=0;
	
	char ch,a[100]; 
	FILE *fp,*fn,*fh;
	int j=0, count=0;
	
	int count_i[26]={0};
	int k=0,mn=0,l=0;
    int timer[100]={0},char_count=0;


	//INS.txt : Opened for fetching variables
	//Cache_LFU.txt : Opened for storing cached variables
	fp = fopen("INS.txt","r");
	fn = fopen("Cache_LFU.txt","w");
      	logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 4 started\n: Cache_LFU created\n\n",ctime(&t1));
	}
	fclose(logFile);

	//For proper synchronisation between threads
	sleep(4);

	if ( fp != NULL )
   	{ 
	  	while ((ch = fgetc(fp))!=EOF)
	    	{       
			//for parsing the line of the file
			if((ch >= 'a' && ch <= 'z') )
			{
				sec = time(NULL);
				a[char_count++]=(char)ch;
				timer[mn++]=sec;
		    	count_i[ch - 'a']++;
			}
			
	    	}
		a[char_count]='\0';
		//Printing the characters 
	    printf("\nString : %s \n",a);
	    findUnique(a);
	    //Printing the characters without duplicate
	    printf("\nString : %s \n",newStr);
	    int tt;
	    
	    printf("\n-----------------------");
	    printf("\nVariable     Frequency\n");
	    printf("-----------------------");
		 
		for ( k = 0; k < strlen(newStr); k++)
		{
			for (j = k+1; j < strlen(newStr); j++)
			{
				if(count_i[newStr[k]-97]>count_i[newStr[j]-97])
				{
					tt=newStr[k];
					newStr[k]=newStr[j];
					newStr[j]=(char)tt;
				}	
			}
		}
		//printing the first five least frequency words in the cache file.
		for( i = 0;i < strlen(newStr);i++)
	    	{
			if(i>=0 && i<5)
			{
				fprintf(fn,"%c\n",newStr[i]);
			}
			printf("\n %c%15d ",newStr[i],count_i[newStr[i]-97]);
	    	}
	}
   	else
   	{
		//Why didn't the file open? 
      	perror ("INS.txt"); 
   	}

	//Closing the previously opened files
   	fclose (fp);
	fclose (fn);

	//Prints ID of the thread
	printf("\nThread ID (LFU): %lu\n",tid);

 	//return (void *)NULL;
	
    logFile=fopen("log_file.txt","a+");
	if(logFile==NULL)
	{
		printf("Error");
		exit(1);
	}
	else
	{
		fprintf(logFile,"%s: Thread 4 executed\n: Cache_LFU modified and closed\n\n",ctime(&t1));
	}
	fclose(logFile);
	pthread_exit(NULL);
}

/*=================================*/
// FUNCTION FOR INVERTING STRING 
/*=================================*/
int inverse(char str[25])
{
    	//length of the string
    	int a = strlen(str);
	int i=0,k=0;
	
	for(i=a-1;i>=0;i--)
	{
		//inverting array
		cacheStr[k]=str[i];
		k++;
	}
	printf("Inversed String: %s\n",cacheStr);

return 0;
}

/*=================================*/
// FUNCTION TO REMOVE DUPLICATES 
/*=================================*/
int findUnique(char str[50])
{
	int i=0,j=0;
	int k=0;
	int count=0;
	int a = strlen(str);
	
	//removing all repeated variables
	for(i=0;i<a;i++)
	{
		if(str[i]==' ')
		{
			i++;
		}
		
		//including non repeated variables
		for(j=0;j<i;j++)
		{
			if(str[i]==str[j])
			{
				count++;
			}
		}
		if(count==0)
		{
			newStr[k] = str[i];
			k++;
		}
		count=0;
	}
	
	//printing unique variables (characters in string)
	printf("Unique String is: %s\n",newStr);
	return 0;
}

void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C \n");
}
 
void quitproc(int sig_num)
{
	exit(0);
}





