#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"

/*recieves a pointer to patient. takes input from user and puts into patient. if successfuly stored returns 1. else return 0 .*/
int initiatePatient(Patient* p) {
	system("cls");
	p->counter = 0;//initiating appointments.
	int flagU = 0, flagP = 0, tries = 3;//validation of username and password
	printf(BOLDBLUE"				****Patient registration****\n\nEnter info[After 3 tries you will be redirected to main menu]:\n"RESET);
	printf(BOLDCYAN"Enter patient info:\n"RESET);
	do {
		if (tries == 0) {//tries to sign up.
			return 0;
		}
		printf(BOLDRED"try number %d\n"RESET, tries);
		tries--;
		printf(BOLDCYAN"Please enter username:\n"RESET);//user
		scanf("%s", p->un);
		flagU = user_validation_P(p->un);
		if (!flagU) {
			continue;
		}
		printf(BOLDCYAN"Please enter password:\n"RESET);
		scanf("%s", p->pass);
		flagP = password_validation(p->pass);
	} while (!(flagU && flagP));
	printf(BOLDCYAN"Please enter ID:\n"RESET);//id
	scanf("%s", p->ID);
	printf(BOLDCYAN"Please enter name:\n"RESET);//name
	scanf("%s", p->name);
	printf(BOLDCYAN"Please enter last name:\n"RESET);//last name
	scanf("%s", p->last_n);
	printf(BOLDCYAN"Please enter gender:\n"RESET);//gender
	scanf("%s", p->gender);
	init_appointments(p);
	return 1;
}


/*Prints patient*/
void printPatient(const Patient* p) {
	printf(BOLDYELLOW"Patient's info :\nID: %s\nUsername: %s\nPassword: %s\nFull name: %s %s\nGender: %s\n"RESET, p->ID, p->un, p->pass, p->name, p->last_n, p->gender);
}



/*Registers a patient to patients database file
storing in text file by the size of patient struct. */
int registerPatient(const Patient* p) {
	FILE* fp = fopen(PATIENT_FILE, "rb+");
	if (!fp) {
		perror(BOLDRED"Cannot open file"RESET);
		exit(1);
	}
	fwrite(p, sizeof(Patient), 1, fp);//writes patient to database.
	fclose(fp);
	return 1;//success
}

/*returns a patient pointer if we get a match to user and pass from Patient database
returns NULL if not found or something went wrong.*/
Patient* sign_inP(Patient* p) {
	system("cls");
	char user[SIZE];
	char pass[SIZE];
	printf(BOLDCYAN"Please enter user name:[5-20 LENGTH, NUMBERS AND SIGNS ARE NOT ALLOWED]\n"RESET);
	scanf("%s", user);
	printf(BOLDCYAN"Please enter password:\n"RESET);
	scanf("%s", pass);
	if (!p) {
		printf(BOLDRED"Patient could not be allocated\n"RESET);
		return NULL;
	}
	FILE* fp = fopen("PatientData.bin", "rb");//opens patient database with read binary mode
	if (!fp) {
		perror(BOLDRED"Cannot open file"RESET);
		exit(1);
	}
	while (fread(p, sizeof(Patient), 1, fp)) {//reads structrs of patients untill reached eof.
		if (!strcmp(p->un, user) && !strcmp(p->pass, pass))//checking match
			return p;
	}
	return NULL;//else
}

/*user validation - returns 1 if user is validated, else returns 0. */
int user_validation_P(const char* user_n) {
	FILE* fp = fopen(PATIENT_FILE, "rb");
	Patient p_test;
	int len = strlen(user_n);
	if (len >= 5 && len <= 20) {
		for (int i = 0; i < len; i++) {
			if ((user_n[i] >= 65 && user_n[i] <= 90) || (user_n[i] >= 97 && user_n[i] <= 122))
				continue;
			printf(BOLDRED"Cannot validate user.\n"RESET);
			return 0;
		}
	}
	else//len is higher than 20 and lower than 5.
		return 0;
	while (fread(&p_test, sizeof(Patient), 1, fp))//continue validation
		if (!strcmp(p_test.un, user_n))
			return 0;
	printf(BOLDGREEN"User validated.\n"RESET);//else
	fclose(fp);
	return 1;
}

/*Patient menu
Prints patient menu,uses printPatient/editPatient functions.
*/
void patient_Menu(Patient* p) {
	int choice;
	char c;//continue
	enum patient_menu { PRINT_PATIENT = 1, EDIT_PATIENT = 2,DISPLAY=3,BOOK_APPOINTMENT=4,EDIT_APPOINTMENT=5,GO_BACK=6 };
	printf(BOLDCYAN"Hello %s %s, How can we help you today?\n",p->name,p->last_n);
	do {
		printf(BOLDYELLOW"\n\n(1). Print my details.\n(2). Edit my profit\n(3). Display appointments\n(4). Book appointment\n(5).Edit appointment\n(6).Return to main menu\n"RESET);
		scanf("%d", &choice);
		getchar();
		switch (choice) {
		case PRINT_PATIENT:
			printPatient(p);
			break;
		case EDIT_PATIENT:
			editPatient(p);
			break;
		case DISPLAY:
			display_appointments(p);
			break;
		case BOOK_APPOINTMENT:
			if (schedule_appointment(p))
				puts("Appointment booked");
			break;
		case EDIT_APPOINTMENT:
			if (edit_appointment(p))
				puts("Appointment successfuly added");
		case GO_BACK:
			printf(BOLDCYAN"Returnning to main menu..\n"RESET);
			printf("Please enter any key to continue..\n");
			scanf("%c", &c);
			system("cls");
			
			break;

		}
	} while (choice != GO_BACK);

}

void editPatient(Patient* p) {
	int choice,flag=0;
	char temp[SIZE];
	FILE* fp = fopen(PATIENT_FILE, "rb+");
	if (!fp) {
		perror(BOLDRED"Cannot open file\n"RESET);
		exit(1);
	}
	enum edit_menu { NAME = 1, LAST_NAME = 2, ID = 3, PASSWORD = 4, GO_BACK = 5 };
	printf(BOLDCYAN"What would you like to change ?\n"RESET);
	printf(BOLDYELLOW"(1). Name\n(2). Last name\n(3). ID\n(4). Password\n(5). Go back to main menu"RESET);
	scanf("%d", &choice);
	switch (choice) {
	case NAME:
		printf(BOLDCYAN"Please enter new name:\n"RESET);
		scanf("%s", temp);
		if (search_patient_to_modify(p,fp)) {
			strcpy(p->name, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			fclose(fp);
			flag++;
		}
		if (flag)
			printf(BOLDGREEN"Name was changed.\n"RESET);
		else
			printf(BOLDRED"Something went wrong"RESET);
		break;
	case LAST_NAME:
		printf(BOLDCYAN"Please enter new last name:\n"RESET);
		scanf("%s", temp);
		if (search_patient_to_modify(p, fp)) {
			strcpy(p->last_n, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf(BOLDGREEN"Last name was changed.\n"RESET);
		else
			printf(BOLDRED"Something went wrong"RESET);
		break;
	case ID:
		printf(BOLDCYAN"Please enter ID:\n"RESET);
		scanf("%s", temp);
		if (search_patient_to_modify(p, fp)) {
			strcpy(p->ID, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf(BOLDGREEN"ID was changed.\n"RESET);
		else
			printf(BOLDRED"Something went wrong"RESET);
		break;
	case PASSWORD:
		printf(BOLDCYAN"Please enter new password:\n"RESET);
		scanf("%s", temp);
		if (password_validation(temp))
			if (search_patient_to_modify(p, fp)) {
				strcpy(p->pass, temp);
				fwrite(p, sizeof(Patient), 1, fp);
				flag++;
				fclose(fp);
			}
		if (flag)
			printf(BOLDGREEN"password was changed.\n"RESET);
		else {
			printf(BOLDRED"Something went wrong"RESET);
			fclose(fp);
		}
		break;
	case GO_BACK:
			return;
	default:
		printf(BOLDRED"You have entered a wrong choice. Redirecting to patient menu.\n"RESET);
	}

}
/*Searches patient in file, once found points file pointer 1 struct back
and returns 1, else returns 0. */
search_patient_to_modify(const Patient* p, FILE* fp) {
	Patient temp_P;
	while (fread(&temp_P, sizeof(Patient), 1, fp)) {
		if (!strcmp(p->un, temp_P.un)) {
			fseek(fp, -(int)sizeof(Patient), SEEK_CUR);
			return 1;//user found
		}
	}
	return 0;//failed to find username.
}

//inits appointments array for patient
int init_appointments(Patient* p) {
	for (int i = 0; i < MAX_APPOINTMENTS; i++) {
		strcpy(p->appointments[i].desc, DEFAULT_NAME);//initiating array of appointments.
		p->appointments[i].flag = 1;
		strcpy(p->appointments[i].d_name, DEFAULT_NAME);
	}
}
//prints patient appointments.
void display_appointments(const Patient* p) {
	int j = 0;
	puts(BOLDBLUE"			****Scehdule****"BOLDCYAN);
	for (int i = 0; i < MAX_APPOINTMENTS; i++) {
		if (p->appointments[i].flag == 1)//if he doesn't have an apppointment scheduled. 
			continue;
		printf("Appointment %d to Dr.%s on : %s\n", j+1,p->appointments[i].d_name, p->appointments[i].desc);
		j++;
	}
	printf(RESET);
}


