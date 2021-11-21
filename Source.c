/***********
* Group: 3 MOR			 *                			 *
*
Crew members:
Member 1:                     Member 2:                    Member 3:
Name: Tomer Burman            Name:maor hadad              Name: orel dandeker
Email: tomerburman@gmail.com  Email:maorhadad94@gmail.com  Email: orel.dandeker1@gmail.com

Member 4:                     Member 5:
Name:Adir Melker              Name: Yair Davidoff
Email:adirmelker1@gmai.com    Email: yairda2@gmail.com                         *
* Credits:                       *
************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MONTHS 12
#define SIZE 50
#define HALFSIZE 25
#define MROWS 8
#define MCOLS 2
#define SIZE_AVAILABLE 10
#define NUN_MEET 2
#define NAME 10
#define I 8
#define enum days { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };


void print_Start_Menu() //the first main log-in
{
	printf("Hi\nplease choose 1 opation\n");
	printf("1.Log-in\n");
	printf("2.View bulletin board\n");
	printf("3.Siggned-in\n");
	printf("4.Exit\n");
}

//structs:

struct Meeting {
	char name_of_doc[NAME];
	char d_timeMeet[HALFSIZE];//string by order 00:00, use strcmp to check, use matric 2*time work by hours
	char available[SIZE_AVAILABLE];//if available signed as 0, else (unavailable) changes to 1
	char meetingNumber[NUN_MEET];
}typedef Meeting;

struct Day {
	struct Meeting** meetings;
	char day_name[SIZE];
	int dayNumber;
}typedef Day;

struct WEEK {
	struct Day days[7];
}typedef WEEK;


struct Schedule {
	struct WEEK week;
}typedef Schedule;

struct Doc {
	char first_name[SIZE];//string
	char last_name[SIZE];//string
	char id[SIZE]; // 9 digits include 0
	char password[SIZE]; // contain valus between 5-20
	char gender[SIZE]; //1 for male 0 for female
	char Specialty[SIZE]; //what does the doctor
	struct Schedule* schedule;
	/*to do days and hours the doctor work
	//to do scedual of the doctor*/
}typedef Doc;
struct Patient {
	char* first_name;//string
	char* last_name;//string
	int id; // 9 digits include 0
	char* password; // contain valus between 5-20
	int gender; //1 for male 0 for female
	/*to do days and hours thr doctor work
	//to do scedual of the doctor*/
};
//init
struct Doc* Doc_init(struct Doc* d)
{

	d = (Doc*)malloc(1 * sizeof(Doc));
	if (!d) {
		printf("Error in allocation of doc_init");
		exit(1);
	}
}
Meeting** new_meet(struct Meeting** M)
{
	int i = 0, j = 0, k = 0, f = 0, counter = 1;
	char name_of_doc[NAME] = "Defulte";
	char available[NAME] = "Available";

	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 2; ++j)
		{
			char half[4] = ":30";
			char whole[4] = ":00";
			if (counter < 10)
			{
				char number = counter + '0';
				char meetingNumber[3] = { number };
				strcpy(M[i][j].meetingNumber, meetingNumber);
			}
			else if (counter >= 10)
			{
				f = counter - 10;
				char number = f + '0';
				char meetingNumber[4] = { '1',number };
				strcpy(M[i][j].meetingNumber, meetingNumber);
			}

			k = i + 8;
			if (k < 10)
			{

				char current_hour = k + '0';
				if (j == 0)
				{
					char part1_time[SIZE] = { current_hour };
					strcat(part1_time, whole);
					strcpy(M[i][j].d_timeMeet, part1_time);
				}
				else if (j == 1)
				{
					char part1_time[SIZE] = { current_hour };
					strcat(part1_time, half);
					strcpy(M[i][j].d_timeMeet, part1_time);

				}
				strcpy(M[i][j].name_of_doc, name_of_doc);
				strcpy(M[i][j].available, available);
				++counter;
			}


			else if (k >= 10)
			{
				f = k - 10;
				char current_hour = f + '0';
				if (j == 0)
				{
					char part1_time[SIZE] = { '1',{current_hour} };
					strcat(part1_time, whole);
					strcpy(M[i][j].d_timeMeet, part1_time);
				}
				else if (j == 1)
				{
					char part1_time[SIZE] = { '1',current_hour };
					strcat(part1_time, half);
					strcpy_s(M[i][j].d_timeMeet, NAME, part1_time);
				}
				strcpy(M[i][j].name_of_doc, name_of_doc);
				strcpy(M[i][j].available, available);
				/*puts(M[i][j].name_of_doc);
				puts(M[i][j].available);
				puts(M[i][j].meetingNumber);
				puts(M[i][j].d_timeMeet);*/
				++counter;
			}
		}
	}
	return M;
}//haft to be before S// haft to be before Schedule_init
void Schedule_init(struct Schedule* S)
{
	int i = 0, j = 0;
	S = (Schedule*)malloc(1 * sizeof(Schedule));
	if (!S)
	{
		printf("Error in Schedule alloc");
		exit(1);
	}
	for (i = 0; i < 7; ++i)
	{
		S->week.days[i].dayNumber = i + 1;

		S->week.days[i].meetings = (Meeting**)malloc(8 * sizeof(Meeting*));
		if (!S->week.days[i].meetings)
		{
			printf("Error in metting alloc");
			exit(1);
		}
		for (j = 0; j < 8; ++j)
		{
			S->week.days[i].meetings[j] = (Meeting*)malloc(2 * sizeof(Meeting));
		}
		S->week.days[i].meetings = new_meet(S->week.days[i].meetings);
	}
}
//adders
struct Doc* addedDoc_place(struct Doc* D)
{
	struct Doc* temp = NULL;
	if (D == NULL)
	{
		temp = Doc_init(D);
	}
	temp = (Doc*)malloc((strlen(D) + 1) * sizeof(Doc));
	if (!temp)
	{
		printf("Error in alloc of addedDoc_place func");
		exit(1);
	}
	for (size_t i = 0; i < (strlen(D)); ++i)
	{
		temp[i] = D[i];
	}
	remove(D);
	return temp;
}
struct Doc* addedDoc(struct Doc* D)
{
	D = addedDoc_place(D);
	char first_name[SIZE];//string
	char last_name[SIZE];//string
	char id[SIZE]; // 9 digits include 0
	char password[SIZE]; // contain valus between 5-20
	char gender[SIZE]; //1 for male 0 for female
	char Specialty[SIZE]; //what does the doctor
	printf("please input data by this order:\nfirst name,last_name,id,password,int gender,Specialty\n");
	getchar();
	gets_s(first_name, SIZE);
	strcpy_s(D->first_name, strlen(first_name) + 1, first_name);

	gets_s(last_name, SIZE);
	strcpy_s(D->last_name, strlen(last_name) + 1, last_name);

	gets_s(id, SIZE);
	strcpy_s(D->id, strlen(id) + 1, id);

	gets_s(password, SIZE);
	strcpy_s(D->password, strlen(password) + 1, password);

	gets_s(gender, SIZE);
	strcpy_s(D->gender, strlen(gender) + 1, gender);

	gets_s(Specialty, SIZE);
	strcpy_s(D->Specialty, strlen(Specialty) + 1, Specialty);
}
struct Doc* signAnavailebale(struct Doc* D, struct Schedule* S)
{
	int day = 1000, choose = 0, i = 0, j = 0;
	puts("wiche day you want to sign as anavalable?\nif its an hours first inter the day\n input number between 1-7\n");
	scanf_s("%d", &day);
	if (S->week.days[day - 1].dayNumber == day)
	{
		puts("if you won to sgin all the day as a anavalible input 1\n else if you won just 1 hour input 2\n");
		scanf_s("%d", &choose);
		switch (choose)
		{
			char unava[] = "unavailable";
		case 1:
		{
			for (i = 0; i < 8; ++i)
			{
				for (j = 0; j < 2; ++j)
				{
					strcpy(D->schedule->week.days->meetings[i][j].available, unava);
					break;
				}
			}
			break;
		}
		case 2:
		{
			puts("input hour to clear this option\nplease input in this order <00:00>");
			char hour_clear[HALFSIZE];
			gets_s(hour_clear, HALFSIZE);
			for (i = 0; i < 8; ++i)
			{
				for (j = 0; j < 2; ++j)
				{
					if (strcmp(D->schedule->week.days->meetings[i][j].d_timeMeet, hour_clear) == 0)
						strcpy(D->schedule->week.days->meetings[i][j].available, unava);
					break;

				}
			}
		}
		break;
		}
	}
}
void printSchedule_for_paitent(struct Day DA)
{
	int i = 0, j = 0;
	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 2; ++j)
		{
			if (strcmp(DA.meetings[i][j].available, "unavailable") != 0)
			{
				printf("%s", DA.meetings[i][j].d_timeMeet);
			}

		}
	}
	printf("\n");
}
struct Doc* paitentMeet(struct Doc* D, struct Schedule* S)
{
	int day = 1000, choose = 0, i = 0, j = 0;
	char unava[] = "unavailable";
	char name_doc[HALFSIZE];
	puts("wiche doctor do you won to meet?\n");
	gets_s(name_doc, HALFSIZE);
	for (size_t i = 0; i < strlen(D); i++)//complish shrche for doctor name and just then the day
	{

	}
	puts("wiche day do you want to meet the doctor?\n");
	scanf_s("%d", &day);
	if (S->week.days[day - 1].dayNumber == day)
	{
		printf("this are the times you can alloc\n");
		printSchedule_for_paitent(S->week.days[day - 1]);

		puts("wiche hour do you won to meet him\nplease input in this order <00:00>");
		char hour_choose[HALFSIZE];
		gets_s(hour_choose, HALFSIZE);
		for (i = 0; i < 8; ++i)
		{
			for (j = 0; j < 2; ++j)
			{
				if (strcmp(D->schedule->week.days->meetings[i][j].available, unava) == 0)
				{
					puts("its unvailable houre to alloc\n");
				}

			}
		}
	}
}


int main()
{
	struct Doc* D = NULL;
	struct Patient* P = NULL;
	struct Schedule* S = NULL;
	Schedule_init(&S);
	D = addedDoc(&D);
	D = signAnavailebale(&D, &S);
	int choose = 3;
	print_Start_Menu();
	scanf_s("%d", &choose);
	while (choose > 0 && choose < 4)
	{
		switch (choose)
		{
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			int choose1 = 0;
			puts("1 for doctor 2 for pation");
			scanf_s("%d", &choose1);
			switch (choose1)
			{
			case 1:
			{
				D = addedDoc(&D);
				break;
			}
			break;
			}

			break;
		}
		case 4:
		{
			break;
		}
	defulte:
		{
			printf("unvalid input please try again");
			break;
		}
		scanf_s("%d", &choose);
		}
	}

	return 0;
}
