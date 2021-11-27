#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H
#define DOCTOR_FILE "DoctorData.bin"
#define DEFAULT_ID ""
#define MAX_APPOINTMENTS 8
#define DAYS_IN_WEEK 6
#define APPOINTMENT_HOURS 6
#define SIZE_FOR_DAY 10
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Colors.h"
#define SIZE 50//size of normal string.


typedef struct {
	char ID[MAX_APPOINTMENTS][SIZE];//2 dim array of 8 appointments, saved by ID's.
	char time_array[MAX_APPOINTMENTS][DAYS_IN_WEEK];
	int counter;//represents appointments in a day 
}day;

typedef struct {
	day days[DAYS_IN_WEEK];//6 days struct.
	int available[DAYS_IN_WEEK];//array of 1's, when a doctor is fully booked we set the day to 0.
}schedule;


struct Doctor { //Doctors struct 
	char un[SIZE];//user
	char pass[SIZE];//pass
	char ID[SIZE];//ID
	char name[SIZE];//name
	char last_n[SIZE];//last
	char specialty[SIZE];//specialty
	char gender[SIZE];//gender
	schedule sched;//doctor schedule
}typedef Doctor;



//functions for doctor 

int initiateDoctor(Doctor* d);//creating doctor struct, returns pointer to struct created.
int registerDoctor(Doctor* d);// registering a doctor returns 1 if successufuly registed.
void printDoctor(const Doctor* d);//printing doctor.
int user_validation_D(char* user_n);//validates the user input and that it's not already in the system
int password_validation(char* pass);//validates password input returns 1 if validated.
void doctor_Menu(Doctor* d);//Prints doctor menu
Doctor* sign_inD(Doctor* d);//signs in and returns a pointer to the struct.
int search_doctor_to_modify(const Doctor* d, FILE* fp);//modifies a doctor, returns 1 if successed. 0 if failed.
void editDoctor(Doctor* d);//Edits detail of doctor.




//schedule functions :
int init_schedule(Doctor* d);//returns initiated schedule

int check_availability(schedule d_schedule,int day);//returns 1 if day is available.
void display_schedule(const Doctor* d);

#endif;