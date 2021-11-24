#pragma once
#ifndef PATIENT_H
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATIENT_FILE "PatientData.bin"
#define DEFAULT_NAME ""
#define TOTAL_SIZE_P 300
#define DESCRIPTION 100
#define MAX_APPOINTMENTS 8
#define SIZE 50

typedef struct {
	int flag;//mark appointments if equal to 0 appointment already has an appointment
	char desc[DESCRIPTION];//description for meeting..
}appointment;

struct Patient { //Doctors struct 
	char un[SIZE];//user
	char pass[SIZE];//pass
	char ID[SIZE];//ID
	char name[SIZE];//name
	char last_n[SIZE];//last
	char gender[SIZE];//gender
	appointment appointments[MAX_APPOINTMENTS];//appointment array, 8 appointments for patient.
	int counter;//counter for appointments.
}typedef Patient;


//functions

int initiatePatient(Patient* p);//creates patient.
int registerPatient(const Patient* p);//registers patient. returns 1 if registed.
void printPatient(const Patient* p);//prints patient. 
Patient* sign_inP(Patient* p);//signs into system
int user_validation_P(const char* user);//validates user input
int password_validation(char* pass);//validates password input
void patient_Menu(Patient* p);//Prints patient menu
int search_patient_to_modify(const Patient* p, FILE* fp);//modifies patient, returns 1 if successfuly modified.
void editPatient(Patient* p);

int init_appointments(Patient* p);
void display_appointments(const Patient* p);
#endif;