#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"

/*recieves a pointer to patient. takes input from user and puts into patient. if successfuly stored returns 1. else return 0 .*/
int initiatePatient(Patient* p) {
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
	FILE* fp = fopen("PatientData.dat", "ab");
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
	char user[SIZE];
	char pass[SIZE];
	printf("Please enter user name:\n");
	scanf("%s", user);
	printf("Please enter password:\n");
	scanf("%s", pass);
	if (!p) {
		printf("Patient could not be allocated\n");
		return NULL;
	}
	FILE* fp = fopen("PatientData.dat", "rb");//opens patient database with read binary mode
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
	FILE* fp = fopen("PatientData.dat", "rb");
	Patient* p_test = malloc(sizeof(Patient));
	int len = strlen(user_n);
	if (len >= 5 && len <= 20) {
		for (int i = 0; i < len; i++) {
			if ((user_n[i] >= 65 && user_n[i] <= 90) || (user_n[i] >= 97 && user_n[i] <= 122))
				continue;
			printf("Cannot validate user.\n");
			return 0;
			/*if ((user_n[i] >= 0 && user_n[i] <= 47) || (user_n[i] >= 58 && user_n[i] <= 64) || (user_n[i] >= 91 && user_n[i] <= 96) || user_n[i] >= 123) {
				printf("Cannot validate username[LEGNTH 5-20, NO SIGNS ALLOWED.\n");
				return 0;*/
		}
	}
	else//len is higher than 20 and lower than 5.
		return 0;
	while (fread(p_test, sizeof(Patient), 1, fp))//continue validation
		if (!strcmp(p_test->un, user_n))
			return 0;
	printf("User validated.\n");//else
	return 1;
}
