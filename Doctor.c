#define _CRT_SECURE_NO_WARNINGS
#include "Doctor.h"
/*Registers a doctor to doctors database file.
storing in text file by the size of doctor struct..*/
int registerDoctor(Doctor* d1) {
	FILE* fp = fopen(DOCTOR_FILE, "ab");
	if (fp == NULL) {
		perror("Cannot open file");
		exit(1);
	}
	fwrite(d1, sizeof(Doctor), 1, fp);
	fclose(fp);
	return 1;//success
}

/*Print doctor */
void printDoctor(const Doctor* d) {
	printf(BOLDYELLOW"Doctor's info :\nID: %s\nUsername: %s\nPassword: %s\nFull name: %s %s\nSpecialty: %s\nGender: %s\n"RESET, d->ID, d->un, d->pass, d->name, d->last_n, d->specialty, d->gender);

}


/*recieves a pointer to doctor and puts input from the user to doctor. returns 1 if successfuly registered.*/
int initiateDoctor(Doctor* d) {
	system("cls");
		int flagU = 0,flagP=0,tries=1;//validation of username and password
		printf(BOLDBLUE"				****Doctor registration****\n\nEnter info[After 3 tries you will be redirected to main menu]:\n"RESET);
		do {
			if (tries == 4) {//tries to sign up.
				return 0;
			}
			printf(BOLDRED"try %d:\n"RESET, tries++);
			printf(BOLDCYAN"Please enter username:[5-20 LENGTH, NUMBERS/SIGNS ARE NOT ALLOWED]\n"RESET);//user
			scanf("%s", d->un);
			flagU = user_validation_D(d->un);
			if (!flagU){//if user was not validated
				continue;
		}
			printf(BOLDCYAN"Please enter password:\n"RESET);
			scanf("%s", d->pass);
			flagP = password_validation(d->pass);
		} while (!(flagU && flagP));

		printf(BOLDCYAN"Please enter ID:\n"RESET);//id
		scanf("%s", d->ID);
		printf(BOLDCYAN"Please enter name:\n"RESET);//name
		scanf("%s", d->name);
		printf(BOLDCYAN"Please enter last name:\n"RESET);//last name
		scanf("%s", d->last_n);
		printf(BOLDCYAN"Please enter specialty:\n"RESET);
		scanf("%s", d->specialty);
		printf(BOLDCYAN"Please enter gender:\n"RESET);//gender
		scanf("%s", d->gender);
		if(init_schedule(d))
		return 1;//success

}


/*password_validation - returns 1 if password is in the length of 5-20 and has atleast 1 capital
letter. else returns 0. */
int password_validation(char* pass) {
	int len = strlen(pass);
	if (strlen(pass) >= 5 && strlen(pass) <= 20)
		for (int i = 0; i < len; i++)
			if (pass[i] >= 65 && pass[i] <= 90) {
				printf(BOLDGREEN"Password validated.\n"RESET);
				return 1;
			}
	printf(BOLDRED"Cannot validate password. [ATLEAST 1 CAPITAL LETTER, 5-20 LENGTH]\n"RESET);
	return 0;
}


/*user validation - returns 1 if user is validated, else returns 0. */
int user_validation_D(char* user_n) {
	FILE* fp = fopen(DOCTOR_FILE, "rb+");
	Doctor* d_test = (Doctor*)malloc(sizeof(Doctor));
	int len = strlen(user_n);
	if (len >= 5 && len <= 20) {
		for (int i = 0; i < len; i++) {
			if ((user_n[i] >= 65 && user_n[i] <= 90) || (user_n[i] >= 97 && user_n[i] <= 122))
				continue;
			printf(BOLDRED"Cannot validate user.\n"BOLDBLUE);
			return 0;
			/*if ((user_n[i] >= 0 && user_n[i] <= 47) || (user_n[i] >= 58 && user_n[i] <= 64) || (user_n[i] >= 91 && user_n[i] <= 96) || user_n[i] >= 123) {
				printf("Cannot validate username[LEGNTH 5-20, NO SIGNS ALLOWED.\n");
				return 0;*/
		}
	}
	else//len is higher than 20 and lower than 5.
		return 0;
	while (fread(d_test, sizeof(Doctor), 1, fp))//continue validation
		if (!strcmp(d_test->un, user_n))
			return 0;
	printf(BOLDGREEN"User validated.\n"RESET);//else
	return 1;
}


/*recieves user/password and pointer to doctor. if it finds a match prints logged in and returns the doctor, else prints false and returns null */
Doctor* sign_inD(Doctor* d) {
	system("cls");
	char user[SIZE];
	char pass[SIZE];
	printf(BOLDCYAN"Please enter Username:\n"RESET);
	scanf("%s", user);
	printf(BOLDCYAN"Please enter Password:\n"RESET);
	scanf("%s", pass);
	FILE* fp = fopen(DOCTOR_FILE, "rb+");//opening file for binary read
	if (!fp) {//file not open. 
		perror(BOLDRED"Cannot open file\n"RESET);
		exit(1);
	}
	while (fread(d, sizeof(Doctor), 1, fp)) {//reads from file till eof reaches end.
		if (!strcmp(d->un, user) && !strcmp(d->pass, pass)) {//checking match
			fclose(fp);
			return d;
		}
	}
	fclose(fp);
	return NULL;

}



/*recieves a doctor pointer., opens a file to read/write in binary mode
prints a menu of the data you can edit
it updates the file with input from user.*/
void editDoctor(Doctor* d) {
	system("cls");
	enum edit { NAME = 1, LAST_NAME = 2,ID=3,SPECIALTY=4,PASSWORD=5,GO_BACK=6 };
	int choice, flag = 0;
	char temp[50];
	FILE* fp = fopen(DOCTOR_FILE, "rb+");
	if (!fp) {
		perror(BOLDRED"Cannot open file"RESET);
		exit(1);
	}
	printf(BOLDCYAN"What would you like to edit/remove?\n"RESET);
	printf(BOLDYELLOW"(1). Name\n(2). Last name\n(3). ID\n(4). SPECIALTY\n(5). PASSWORD\n(6). Go back\n"RESET);
	scanf("%d", &choice);
	switch (choice) {
	case NAME:
		printf(BOLDCYAN"Enter new name:\n"RESET);
		scanf("%s", temp);
			if (search_doctor_to_modify(d, fp)) {//if doctor found enters 
				strcpy(d->name, temp);//copying name 
				fwrite(d, sizeof(Doctor), 1, fp);//writing to file 
				fclose(fp);//closin file
				flag++;//raise flag
			}
		if (flag)
			printf(BOLDGREEN"Name changed.\n"RESET);
		else
			printf(BOLDRED"Something went wrong.\n"RESET);
		break;


	case LAST_NAME:
		printf(BOLDCYAN"Enter new last name:\n"RESET);
		scanf("%s", temp);
			if (search_doctor_to_modify(d, fp)) {//if doctor found enters
				strcpy(d->last_n, temp);//copying data
				fwrite(d, sizeof(Doctor), 1, fp);//writing to file
				fclose(fp);
				flag++;
			}
		if (flag)
			printf(BOLDGREEN"Last name changed.\n"RESET);
		else 
			printf(BOLDRED"Something went wrong.\n"RESET);
		break;


	case ID:
		printf(BOLDCYAN"Enter new ID\n"RESET);
		scanf("%s", temp);
		if (search_doctor_to_modify(d, fp)) {
			strcpy(d->ID, temp);
			fwrite(d, sizeof(Doctor), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf(BOLDGREEN"ID changed.\n"RESET);
		else
			printf(BOLDRED"Something went wrong.\n"RESET);
		break;

	case SPECIALTY:
		printf(BOLDCYAN"Enter new specialty:\n"RESET);
		scanf("%s", temp);
		if (search_doctor_to_modify(d, fp)) {
			strcpy(d->specialty, temp);
			fwrite(d, sizeof(Doctor), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf(BOLDGREEN"Speciality changed.\n"RESET);
		else
			printf(BOLDRED "Something went wrong.\n"RESET);
		break;

	case PASSWORD:
		printf(BOLDCYAN"Enter new password[Notice you will be reffered to main menu once you change your password.]\n"RESET);
		scanf("%s", temp);
		if (password_validation(temp)) {
			if (search_doctor_to_modify(d, fp)) {
				strcpy(d->pass, temp);
				fwrite(d, sizeof(Doctor), 1, fp);
				flag++;
				fclose(fp);
			}
			if (flag)
				printf(BOLDGREEN"Password changed.\n"RESET);
		}

		break;
	case GO_BACK:
		break;
	default:
		printf(BOLDRED"You entered a wrong input. Please try again\n"RESET);
		break;

	}

}
/*Doctor menu - prints doctor menu 
uses printDoctor and editDoctor functions */
void doctor_Menu(Doctor* d) {
	enum doctor_Menu { PRINT_DOCTOR = 1, EDIT_DOCTOR = 2,VIEW_APPOINTMENTS=3,GO_BACK=4 };//enum choices
	int choice;
	printf(BOLDCYAN"Hello dr.%s %s!\n\nWhat would you like to do ?"RESET, d->name, d->last_n);
	do {
	printf(BOLDYELLOW"\n\n(1). Look at my info.\n(2). Edit info\n(3). View appointments\n(4).Go back\n"RESET);
	scanf("%d", &choice);
		switch (choice) {
		case PRINT_DOCTOR:
			printDoctor(d);
			break;
		case EDIT_DOCTOR:
			editDoctor(d);
			break;
		case VIEW_APPOINTMENTS:
			display_schedule(d);
			break;
		case GO_BACK:
			printf(BOLDCYAN"Good bye Dr. %s !\n Signing out..\n"RESET,d->name);
			break;
		default:
			printf(BOLDRED"You have entered an invalid choice, Please try again.\n "BOLDRED);
		}
	} while (choice != GO_BACK);
}

/*Searches doctor in file, once found points file pointer 1 struct back
and returns 1, else returns 0. */

//search_doc
int search_doctor_to_modify(const Doctor* d, FILE* fp) {
	Doctor temp_D;
	while (fread(&temp_D, sizeof(Doctor), 1, fp)) {
		if (!strcmp(d->un, temp_D.un)) {
			fseek(fp,-(int)sizeof(Doctor), SEEK_CUR);
			return 1;//user found
		}
	}
	return 0;//failed to find username.
}


/*inits a schedule, sets availability array in the day where the doctor wishes to work to 1.*/
int init_schedule(Doctor* d) {
	int	counter=0,choice;//number of days doctor can work.
	char* time_array[MAX_APPOINTMENTS] = { "08:00","09:00","10:00","11:00","12:00","13:00","14:00","15:00" };

	for (int i = 0; i < DAYS_IN_WEEK; i++) {//initiating avialability to unavialable
		d->sched.available[i] = 0;//default unavailable
		for (int j = 0; j < MAX_APPOINTMENTS; j++) {//setting IDs in schedule to 000000000
			strcpy(d->sched.days[i].ID[j], DEFAULT_ID);
			strcpy(d->sched.days[i].time_array[j], time_array[j]);
		}
	}
	printf(BOLDYELLOW"Enter which days can you work in.\n Do not repeat days. TO EXIT ENTER 7 \n");
	printf("(1).Sunday\n(2).Monday\n(3).Tuesday\n(4).Wednsday\n(5).Thursday\n(6).Friday\n"RESET);
	do {//loop that makes the day available
		scanf("%d", &choice);
		if (choice == 7)
			break;
		d->sched.available[choice-1] = 1;//activating availability
		d->sched.days[choice-1].counter = 0;
	} while (choice != 7);
	printf(BOLDGREEN"Schedule initiated.\n"RESET);
	return 1;//success

}


//checks if doctors day is available.
int check_availability(schedule d_schedule,int day) {
	if (d_schedule.available[day] == 1 && d_schedule.days[day].counter != MAX_APPOINTMENTS )//if day is not full and available returns 1.
		return 1;
	return 0;
}

//prints schedule
void display_schedule(const Doctor* d) {
	enum{SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY};
	int i = 0;
	printf(BOLDBLUE"		%s work schedule for this week:\n", d->name);
	printf(BOLDYELLOW"\n	-------------------------------------------------------\n");
	do {
		if (d->sched.available[i] == 0) {
			i++;
			continue;
		}
		switch (i) {
		case SUNDAY:
			printf("			****Sunday****:\n");
			break;
		case MONDAY:
			printf("			****Monday****:\n");
			break;
		case TUESDAY:
			printf("			****Tuesday****:\n");
			break;
		case WEDNESDAY:
			printf("			****Wednesday****:\n");
			break;
		case THURSDAY:
			printf("			****Thursday****:\n");
			break;
		case FRIDAY:
			printf("			****Friday****:\n");
			break;
		}
		for (int j = 0; j < MAX_APPOINTMENTS; j++)
			printf("%s Appointment %d:patient ID: %s	\n",d->sched.days[i].time_array[j], j + 1, d->sched.days[i].ID[j]);
		printf("\n	-------------------------------------------------------\n");
		i++;
	} while (i < DAYS_IN_WEEK);
	printf(RESET);
}

