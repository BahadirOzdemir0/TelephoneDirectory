#include<stdio.h>
#include<string.h>
#include<windows.h>
//BAHADIR ÖZDEMÝR


void menu(); //creating menu graph
int writepeople();  //this function is writing people infos to screen
int addperson(); // person adding to array
void writefile(); //writing new array to file
int removeperson();//
void searchpeople();
void updatepeople();
char MWH[20]="";//status of number 

struct data
{
	char name[20];
	char surname[25];
	char number[12];
	int mwh;   //mobile=1 work=2 home=3 
}people[100];

void menu()
{
	
	printf("\n\n---------------------\n");
	printf("*  1-Add person     *\n");
	printf("*  2-Remove person  *\n");
	printf("*  3-Update person  *\n");
	printf("*  4-Search person  *\n");
	printf("*  5-Exit           *\n");
	printf("---------------------\n");
}

int writepeople()
{
	int people_count=1;
	FILE *file = fopen("people.txt","r");
	
	printf("Phone Dictinory:\n\n");
	if(file == NULL)
		return 0;
	
	while(fscanf(file,"%s %s %s %d",people[people_count].name,people[people_count].surname,people[people_count].number,&people[people_count].mwh) != EOF)
		people_count++;
	
	
	for(int i=1;i<people_count;i++)
	{
		switch(people[i].mwh)
		{
			case 1:
				strcpy(MWH,"MOBILE");
				break;
			case 2:
				strcpy(MWH,"WORK");
				break;
			case 3:
				strcpy(MWH,"HOME");
				break;
				
		}
		
		printf("%-2d-)%-9s  %-10s  %-10s  %-20s\n",i,people[i].name,people[i].surname,people[i].number,MWH);
			
	}
	
	fclose(file);
	
 	return people_count-1;
}

void writefile(int people_count)
{
	FILE *file = fopen("people.txt","w");
	
	for(int i = 1;i<people_count+1;i++)
	{
		fprintf(file,"%s %s %s %d\n",people[i].name,people[i].surname,people[i].number,people[i].mwh);
	}
	fclose(file);
}

int addperson(int people_count)
{
	printf("Name:");
	scanf("%s",people[people_count+1].name);
	printf("Surname:");
	scanf("%s",people[people_count+1].surname);
	printf("Number:");
	scanf("%s",people[people_count+1].number);
	printf("Number Status(1=MOBILE 2=WORK 3=HOME):");
	scanf("%d",&people[people_count+1].mwh);
	
	writefile(people_count+1);
	system("CLS");
	
	writepeople();	
	menu();
	
	return people_count+1;

}

int removeperson(int people_count)
{
	FILE *file = fopen("people.txt","r");
	int x=1;
	char name[20];
	printf("Who do you remove?:");
	scanf("%s",name);
	while(fscanf(file,"%s %s %s %d",people[x].name,people[x].surname,people[x].number,&people[x].mwh) != EOF)
	{
		if( !strcmp(people[x].name,name))
		{
			strcpy(people[x].name,people[people_count].name);
			strcpy(people[x].surname,people[people_count].surname);	
			strcpy(people[x].number,people[people_count].number);	
			people[x].mwh = people[people_count].mwh;		
			
			strcpy(people[people_count].name,"");
			strcpy(people[people_count].surname,"");
			strcpy(people[people_count].number,"");
			people[people_count].mwh=0;		
			people_count--;	
			
			writefile(people_count);
			system("CLS");
			writepeople();
			menu();	
			fclose(file);
			return people_count;
			
		}
		
		x++;	
	}
	printf("Person have not found...\n");
	return people_count;
	
}

void searchpeople()
{
	FILE *file = fopen("people.txt","r");
	int x=1;
	char MWH[10];
	char name[20];
	printf("Who do you want to find?:");
	scanf("%s",name);
	while(fscanf(file,"%s %s %s %d",people[x].name,people[x].surname,people[x].number,&people[x].mwh) != EOF)
	{
		if( !strcmp(people[x].name,name))
		{
			system("CLS");
			printf("\n\n--------------------\nname: %s\n",people[x].name);
			printf("surname: %s\n",people[x].surname);
			printf("number: %s\n",people[x].number);
			
			switch(people[x].mwh)
		{
			case 1:
				strcpy(MWH,"MOBILE");
				break;
			case 2:
				strcpy(MWH,"WORK");
				break;
			case 3:
				strcpy(MWH,"HOME");
				break;
				
		}
			printf("phone status: %s\n-------------------\n\n",MWH);	
			
			writepeople();
			menu();	
			fclose(file);
			return;
		}
		
		
		x++;
	}
	printf("Person have not found...\n");
}

void updatepeople(int people_count)
{
	char name[20];
	int x=1;
	printf("Who do you want to Update?:");
	scanf("%s",name);
	
	FILE *file = fopen("people.txt","r");
	while(fscanf(file,"%s %s %s %d",people[x].name,people[x].surname,people[x].number,&people[x].mwh) != EOF)
	{
		if( !strcmp(people[x].name,name))
		{
			printf("New Name:");
			scanf("%s",people[x].name);
			printf("New Surname:");
			scanf("%s",people[x].surname);
			printf("New Number:");
			scanf("%s",people[x].number);
			printf("New Number Status(1=MOBILE 2=WORK 3=HOME):");
			scanf("%d",&people[x].mwh);
			system("CLS");
			fclose(file);
			writefile(people_count);
			writepeople();
			menu();
		}
	x++;
	}
}



main()
{
	int choice=0;
	keybd_event(VK_MENU, 0x38, 0, 0); //Full Screen code
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    
	
	system("CLS");
	int people_count = writepeople();
	
	if(people_count == 0)
		printf("Empty...");
	menu();
	
	
	while(1)
	{
		printf("Choice:");
		scanf("%d",&choice);
		switch(choice)
			{
				case 1:
					people_count = addperson(people_count);
					break;
				case 2:
					people_count = removeperson(people_count);
					break;
				case 3:
					updatepeople(people_count);
					break;
				case 4:
					searchpeople();
					break;	
				case 5:
					return 0;
					break;
				default:
					printf("Type between 1-5\n");
			}
	}
}
