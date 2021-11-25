#define _CRT_SECURE_NO_WARNINGS
#include "Doctor.h"
#include <stdio.h>
#include <stdlib.h>
#include "Patient.h"
void Menu();//Prints main menu
void registerMenu();//Prints register menu
void sign_in_Menu();//Prints sign in menu
void patient_Menu(Patient* p);//Prints patient menu
int flush_database();
int schedule_appointment(Patient* p);//schedule appointment
#define MAX_DOCTORS 10
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
/*schedule an appointment.*/
int schedule_appointment(Patient* p) {
	FILE* fp_d = fopen(DOCTOR_FILE, "rb+");//open file to write/read
	FILE* fp_p = fopen(PATIENT_FILE, "rb+");//open file to write/read
	int i = 0, choice;
	char temp[SIZE];
	int flag = 0;
	Doctor d_array[MAX_DOCTORS];//helper
	if (!fp_d) {//file failure.
		printf("File could not open\n");
		exit(1);
	}
	if (!fp_d) {//file failure.
		printf("File could not open\n");
		exit(1);
	}
	puts("Hello ! which doctor from the list would you like to appoint to ?\n");
	puts("Pick a doctor from the list, once you've picked a doctor his days of availability and appointments avaialable will pop up");
	while (fread(&d_array[i], sizeof(Doctor), 1, fp_d)) {//while not at end of file read 
		printf("(%d). Dr. %s %s Speciality : %s \n", i + 1, d_array[i].name, d_array[i].last_n, d_array[i].specialty);//displaying doctor by name and speciality.
		i++;
	}
	scanf("%d", &choice);
	display_schedule(&d_array[choice - 1]);//display schedule
	do {
		puts("Enter the day you want.");
		scanf("%d", &i);//day input
		if (i > 6 || i < 1)
			puts("Invalid input, please try again.");
	} while (i > 6 || i < 1);
		if (d_array[choice - 1].sched.days[i-1].counter != MAX_APPOINTMENTS) {//checking  if doctor day is not full
			puts("Enter time you want for the day. e.g [HH:MM]");
			scanf("%s", temp);
			for (int j = 0; j < MAX_APPOINTMENTS; j++) {
				if (!(strcmp(temp, d_array[choice - 1].sched.days[i-1].time_array[j])) && !(strcmp(d_array[choice - 1].sched.days[i-1].ID[j], DEFAULT_ID)) && p->counter != MAX_APPOINTMENTS) {//checking if time matches and if appointment is not taken
					strcpy(d_array[choice - 1].sched.days[i-1].ID[j], p->ID);//copying patient ID
					d_array[choice - 1].sched.days[i-1].counter++;//adding to appointments that day.
					fseek(fp_d, 0, SEEK_SET);//setting pointer to start of file
					if (search_doctor_to_modify(&d_array, fp_d)) {//if doctor found goes in
						for (int k = 0; k < MAX_APPOINTMENTS; k++) {
							if (p->appointments[k].flag) {//if patient is free that day.copying description
								puts("Enter description for appointment.");
								getchar();//get enter 
								gets(p->appointments[k].desc);//get description for patient
								strcat(p->appointments[k].desc, " ");//blankspace
								strcat(p->appointments[k].desc, d_array->sched.days[i-1].time_array[j]);//copying time from doctor description.
								p->appointments[k].flag = 0;//appointment is taken
								if (search_patient_to_modify(p, fp_p)) {//searches patient.
									fwrite(p, sizeof(Patient), 1, fp_p);//writes to patient
									fclose(fp_p);
									fwrite(&d_array[choice - 1], sizeof(Doctor), 1, fp_d);//writing doctor to file.
									fclose(fp_d);
									return 1;
								}

							}
						}
					}

				}
			}
		}
		puts("Something went wrong, please try rescheduling.");

}