#define _CRT_SECURE_NO_WARNINGS
#include "Doctor.h"
#include <stdio.h>
#include "Patient.h"
void Menu();//Prints main menu
void registerMenu();//Prints register menu
void sign_in_Menu();//Prints sign in menu
void patient_Menu(Patient* p);//Prints patient menu
int flush_database();
//check if IDs between doctor and patient are same



int main() { 

	Menu();
	return 0;
}
/*Menu function - prints menu*/
void Menu() {
	enum choice { REGISTER = 1, SIGN_IN = 2, EXIT = 3, DELETE_DATA = 4 };
	int choice;
	char temp_key;
	do{
		system("cls");
	printf("				****Main menu****\n\n");
	printf("(1). Register\n(2). Sign in\n(3). Exit the system\n(4). Delete data\n");
	scanf("%d", &choice);
		switch (choice) {
		case REGISTER:
			registerMenu();
			break;
		case SIGN_IN:
			sign_in_Menu();
			break;
		case EXIT:
			printf("Goodbye ! :)\n");
			break;
		case DELETE_DATA:
			flush_database();//deletes all content on files.
			break;
		default:
			printf("You entered a wrong input. Please try again\n");
			break;
		}
		printf("Press any key to continue...");
		getchar();
		scanf("%c", &temp_key);
	} while (choice != EXIT);

}

/*Registeration menu - prints registeration methods :
uses initiateDoctor and registerDoctor. allocates and releases memory.*/
void registerMenu() {
	system("cls");
	enum registeration { DOCTOR = 1, PATIENT = 2, GO_BACK = 3 };
	int choice,flag=0;
	Patient p;
	Doctor d;
	do {
		printf("				****Registration****\n\nRegister as:\n");
		printf("(1). Doctor\n(2). Patient\n(3). Go back\n");
		scanf("%d", &choice);
		switch (choice) {
		case DOCTOR:
			flag = initiateDoctor(&d);
			if (flag) {
				if (registerDoctor(&d))
					printf("You have registered! \n");
			}
			break;
		case PATIENT:
			flag = initiatePatient(&p);
			if (flag)
				if (registerPatient(&p))
					printf("You have registered! \n");
			break;
		case GO_BACK:
			break;
		default:
			printf("You entered a wrong input. please try again.\n");
			break;
		}
	} while (choice > GO_BACK || choice <DOCTOR);
}

/*Sign in menu - prints sign in methods : 
uses sign_in function and menu functions, allocates and releases memory. */
void sign_in_Menu() {
	system("cls");
	enum sign_in { DOCTOR = 1, PATIENT = 2, GO_BACK = 3 };
	int choice;
	Doctor* d;
	Patient* p;
	do {
		printf("				****Sign up****\n\nSign in as:\n");
		printf("(1). Doctor\n(2). Patient\n(3). Go back\n");
		scanf("%d", &choice);
		switch (choice) {
		case DOCTOR:
			d = (Doctor*)malloc(sizeof(Doctor));
			d = sign_inD(d);
			if(!d)//incase of null
				printf("Could not sign in. Please make sure you're using a valid username and password.\n");
			if (d) {
				system("cls");//clean output
				doctor_Menu(d);
			}
			free(d);
			break;
		case PATIENT:
			p = (Patient*)malloc(sizeof(Patient));
			p = sign_inP(p);//returns pointer if signed in successfuly
			if(!p)//incase of null
				printf("Could not sign in. Please make sure you're using a valid username and password.\n");
			if (p)
				patient_Menu(p);
			free(p);
		case GO_BACK:
			break;
		default:
			printf("You entered a wrong choice. Please try again.\n");
			break;
		}
	} while (choice>GO_BACK || choice<DOCTOR);
}


int flush_database() {
	FILE* fp = fopen("DoctorData.bin", "wb+");
	if (!fp) {
		perror("Error flushing\n");
		return 0;
	}
	fclose(fp);
	fp = fopen("PatientData.bin", "wb+");
	if (!fp) {
		perror("Error flushing\n");
		return 0;
	}
	fclose(fp);
	return 1;
}