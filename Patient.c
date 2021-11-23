#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"

/*recieves a pointer to patient. takes input from user and puts into patient. if successfuly stored returns 1. else return 0 .*/
int initiatePatient(Patient* p) {
	system("cls");
	int flagU = 0, flagP = 0, tries = 3;//validation of username and password
	printf("Enter patient info:\n");
	do {
		if (tries == 0) {//tries to sign up.
			return 0;
		}
		tries--;
		printf("Please enter username:\n");//user
		scanf("%s", p->un);
		flagU = user_validation_P(p->un);
		if (!flagU) {
			continue;
		}
		printf("Please enter password:\n");
		scanf("%s", p->pass);
		flagP = password_validation(p->pass);
	} while (!(flagU && flagP));
	printf("Please enter ID:\n");//id
	scanf("%s", p->ID);
	printf("Please enter name:\n");//name
	scanf("%s", p->name);
	printf("Please enter last name:\n");//last name
	scanf("%s", p->last_n);
	printf("Please enter gender:\n");//gender
	scanf("%s", p->gender);
	return 1;
}


/*Prints patient*/
void printPatient(const Patient* p) {
	printf("Patient's info :\nID: %s\nUsername: %s\nPassword: %s\nFull name: %s %s\nGender: %s\n", p->ID, p->un, p->pass, p->name, p->last_n, p->gender);
}



/*Registers a patient to patients database file
storing in text file by the size of patient struct. */
int registerPatient(const Patient* p) {
	FILE* fp = fopen("PatientData.bin", "rb+");
	if (!fp) {
		perror("Cannot open file");
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
	printf("Please enter user name:[5-20 LENGTH, NUMBERS AND SIGNS ARE NOT ALLOWED]\n");
	scanf("%s", user);
	printf("Please enter password:\n");
	scanf("%s", pass);
	if (!p) {
		printf("Patient could not be allocated\n");
		return NULL;
	}
	FILE* fp = fopen("PatientData.bin", "rb");//opens patient database with read binary mode
	if (!fp) {
		perror("Cannot open file");
		return NULL;
	}
	while (fread(p, sizeof(Patient), 1, fp)) {//reads structrs of patients untill reached eof.
		if (!strcmp(p->un, user) && !strcmp(p->pass, pass))//checking match
			return p;
	}
	return NULL;//else
}

/*user validation - returns 1 if user is validated, else returns 0. */
int user_validation_P(const char* user_n) {
	FILE* fp = fopen("PatientData.bin", "rb");
	Patient p_test;
	int len = strlen(user_n);
	if (len >= 5 && len <= 20) {
		for (int i = 0; i < len; i++) {
			if ((user_n[i] >= 65 && user_n[i] <= 90) || (user_n[i] >= 97 && user_n[i] <= 122))
				continue;
			printf("Cannot validate user.\n");
			return 0;
		}
	}
	else//len is higher than 20 and lower than 5.
		return 0;
	while (fread(&p_test, sizeof(Patient), 1, fp))//continue validation
		if (!strcmp(p_test.un, user_n))
			return 0;
	printf("User validated.\n");//else
	fclose(fp);
	return 1;
}

/*Patient menu
Prints patient menu,uses printPatient/editPatient functions.
*/
void patient_Menu(Patient* p) {
	int choice;
	enum patient_menu { PRINT_PATIENT = 1, EDIT_PATIENT = 2,GO_BACK=3 };
	printf("Hello %s %s, How can we help you today?\n",p->name,p->last_n);
	do {
		printf("\n\n(1). Print my details.\n(2). Edit my profit\n(3).Return to main menu\n");
		scanf("%d", &choice);
		switch (choice) {
		case PRINT_PATIENT:
			printPatient(p);
			break;
		case EDIT_PATIENT:
			editPatient(p);
			break;
		case GO_BACK:
			printf("Returnning to main menu..\n");
			break;

		}
	} while (choice != GO_BACK);

}

void editPatient(Patient* p) {
	int choice,flag=0;
	char temp[SIZE];
	FILE* fp = fopen("PatientData.bin", "rb+");
	enum edit_menu { NAME = 1, LAST_NAME = 2, ID = 3, PASSWORD = 4, GO_BACK = 5 };
	printf("What would you like to change ?\n");
	printf("(1). Name\n(2). Last name\n(3). ID\n(4). Password\n(5). Go back to main menu");
	scanf("%d", &choice);
	switch (choice) {
	case NAME:
		printf("Please enter new name:\n");
		scanf("%s", temp);
		if (search_patient_to_modify(p,fp)) {
			strcpy(p->name, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			fclose(fp);
			flag++;
		}
		if (flag)
			printf("Name was changed.\n");
		else
			printf("Something went wrong");
		break;
	case LAST_NAME:
		printf("Please enter new last name:\n");
		scanf("%s", temp);
		if (search_patient_to_modify(p, fp)) {
			strcpy(p->last_n, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf("Last name was changed.\n");
		else
			printf("Something went wrong");
		break;
	case ID:
		printf("Please enter ID:\n");
		scanf("%s", temp);
		if (search_patient_to_modify(p, fp)) {
			strcpy(p->ID, temp);
			fwrite(p, sizeof(Patient), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf("ID was changed.\n");
		else
			printf("Something went wrong");
		break;
	case PASSWORD:
		printf("Please enter new password:\n");
		scanf("%s", temp);
		if (password_validation(temp))
			if (search_patient_to_modify(p, fp)) {
				strcpy(p->pass, temp);
				fwrite(p, sizeof(Patient), 1, fp);
				flag++;
				fclose(fp);
			}
		if (flag)
			printf("password was changed.\n");
		else {
			printf("Something went wrong");
			fclose(fp);
		}
		break;
	case GO_BACK:
			return;
	default:
		printf("You have entered a wrong choice. Redirecting to patient menu.\n");
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