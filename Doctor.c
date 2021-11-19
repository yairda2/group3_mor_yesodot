#define _CRT_SECURE_NO_WARNINGS
#include "Doctor.h"
/*Registers a doctor to doctors database file.
storing in text file by the size of doctor struct..*/
int registerDoctor(Doctor* d1) {
	FILE* fp = fopen("DoctorData.bin", "ab");
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
	printf("Doctor's info :\nID: %s\nUsername: %s\nPassword: %s\nFull name: %s %s\nSpecialty: %s\nGender: %s\n", d->ID, d->un, d->pass, d->name, d->last_n, d->specialty, d->gender);

}


/*recieves a pointer to doctor and puts input from the user to doctor. returns 1 if successfuly registered.*/
int initiateDoctor(Doctor* d) {
	system("cls");
		int flagU = 0,flagP=0,tries=1;//validation of username and password
		printf("				****Doctor registration****\n\nEnter info[After 3 tries you will be redirected to main menu]:\n");
		do {
			if (tries == 4) {//tries to sign up.
				return 0;
			}
			printf("try %d:\n", tries++);
			printf("Please enter username:[5-20 LENGTH, NUMBERS/SIGNS ARE NOT ALLOWED]\n");//user
			scanf("%s", d->un);
			flagU = user_validation_D(d->un);
			if (!flagU){//if user was not validated
				continue;
		}
			printf("Please enter password:\n");
			scanf("%s", d->pass);
			flagP = password_validation(d->pass);
		} while (!(flagU && flagP));

		printf("Please enter ID:\n");//id
		scanf("%s", d->ID);
		printf("Please enter name:\n");//name
		scanf("%s", d->name);
		printf("Please enter last name:\n");//last name
		scanf("%s", d->last_n);
		printf("Please enter specialty:\n");
		scanf("%s", d->specialty);
		printf("Please enter gender:\n");//gender
		scanf("%s", d->gender);
		return 1;//success

}


/*password_validation - returns 1 if password is in the length of 5-20 and has atleast 1 capital
letter. else returns 0. */
int password_validation(char* pass) {
	int len = strlen(pass);
	if (strlen(pass) >= 5 && strlen(pass) <= 20)
		for (int i = 0; i < len; i++)
			if (pass[i] >= 65 && pass[i] <= 90) {
				printf("Password validated.\n");
				return 1;
			}
	printf("Cannot validate password. [ATLEAST 1 CAPITAL LETTER, 5-20 LENGTH]\n");
	return 0;
}


/*user validation - returns 1 if user is validated, else returns 0. */
int user_validation_D(char* user_n) {
	FILE* fp = fopen("DoctorData.bin", "rb+");
	Doctor* d_test = (Doctor*)malloc(sizeof(Doctor));
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
	while (fread(d_test, sizeof(Doctor), 1, fp))//continue validation
		if (!strcmp(d_test->un, user_n))
			return 0;
	printf("User validated.\n");//else
	return 1;
}


/*recieves user/password and pointer to doctor. if it finds a match prints logged in and returns the doctor, else prints false and returns null */
Doctor* sign_inD(Doctor* d) {
	system("cls");
	char user[SIZE];
	char pass[SIZE];
	printf("Please enter Username:\n");
	scanf("%s", user);
	printf("Please enter Password:\n");
	scanf("%s", pass);
	FILE* fp = fopen("DoctorData.bin", "rb+");//opening file for binary read
	if (!fp) {//file not open. 
		perror("Cannot open file\n");
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
	FILE* fp = fopen("DoctorData.bin", "rb+");
	if (!fp) {
		perror("Cannot open file");
		exit(1);
	}
	printf("What would you like to edit/remove?\n");
	printf("(1). Name\n(2). Last name\n(3). ID\n(4). SPECIALTY\n(5). PASSWORD\n(6). Go back\n");
	scanf("%d", &choice);
	switch (choice) {
	case NAME:
		printf("Enter new name:\n");
		scanf("%s", temp);
			if (search_doctor_to_modify(d, fp)) {
				strcpy(d->name, temp);
				fwrite(d, sizeof(Doctor), 1, fp);
				fclose(fp);
				flag++;
			}
		if (flag)
			printf("Name changed.\n");
		else
			printf("Something went wrong.\n");
		break;


	case LAST_NAME:
		printf("Enter new last name:\n");
		scanf("%s", temp);
			if (search_doctor_to_modify(d, fp)) {
				strcpy(d->last_n, temp);
				fwrite(d, sizeof(Doctor), 1, fp);
				fclose(fp);
				flag++;
			}
		if (flag)
			printf("Last name changed.\n");
		else 
			printf("Something went wrong.\n");
		break;


	case ID:
		printf("Enter new ID\n");
		scanf("%s", temp);
		if (search_doctor_to_modify(d, fp)) {
			strcpy(d->ID, temp);
			fwrite(d, sizeof(Doctor), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf("ID changed.\n");
		else
			printf("Something went wrong.\n");
		break;

	case SPECIALTY:
		printf("Enter new specialty:\n");
		scanf("%s", temp);
		if (search_doctor_to_modify(d, fp)) {
			strcpy(d->specialty, temp);
			fwrite(d, sizeof(Doctor), 1, fp);
			flag++;
			fclose(fp);
		}
		if (flag)
			printf("Speciality changed.\n");
		else
			printf("Something went wrong.\n");
		break;

	case PASSWORD:
		printf("Enter new password[Notice you will be reffered to main menu once you change your password.]\n");
		scanf("%s", temp);
		if (password_validation(temp)) {
			if (search_doctor_to_modify(d, fp)) {
				strcpy(d->pass, temp);
				fwrite(d, sizeof(Doctor), 1, fp);
				flag++;
				fclose(fp);
			}
			if (flag)
				printf("Password changed.\n");
		}

		break;
	case GO_BACK:
		break;
	default:
		printf("You entered a wrong input. Please try again\n");
		break;

	}

}

void doctor_Menu(Doctor* d) {
	enum doctor_Menu { PRINT_DOCTOR = 1, EDIT_DOCTOR = 2,GO_BACK=3 };
	int choice;
	printf(		"Hello dr.%s %s!\n\n What would you like to do ?", d->name, d->last_n);
	do {
	printf("\n\n(1).Look at my info.\n(2). Edit info\n(3).Sign out\n");
	scanf("%d", &choice);
		switch (choice) {
		case PRINT_DOCTOR:
			printDoctor(d);
			break;
		case EDIT_DOCTOR:
			editDoctor(d);
			break;
		case GO_BACK:
			printf("Good bye Dr. %s !\n Signing out..\n",d->name);
			break;
		default:
			printf("You have entered an invalid choice, Please try again.\n ");
		}
	} while (choice != GO_BACK);
}

int search_doctor_to_modify(const Doctor* d, FILE* fp) {
	Doctor temp_D;
	while (fread(&temp_D, sizeof(Doctor), 1, fp)) {
		if (!strcmp(d->un, temp_D.un)) {
			fseek(fp, -TOTAL_SIZE, SEEK_CUR);
			return 1;//user found
		}
	}
	return 0;//failed to find username.
}