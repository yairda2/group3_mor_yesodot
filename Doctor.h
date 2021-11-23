#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TOTAL_SIZE 350//size of doctor
#define DOCTOR_FILE "DoctorData.bin"
#define SIZE 50//size of normal string.
struct Doctor { //Doctors struct 
	char un[SIZE];//user
	char pass[SIZE];//pass
	char ID[SIZE];//ID
	char name[SIZE];//name
	char last_n[SIZE];//last
	char specialty[SIZE];//specialty
	char gender[SIZE];//gender

}typedef Doctor;

//functions 

int initiateDoctor(Doctor* d);//creating doctor struct, returns pointer to struct created.
int registerDoctor(Doctor* d);// registering a doctor returns 1 if successufuly registed.
void printDoctor(const Doctor* d);//printing doctor.
int user_validation_D(char* user_n);//validates the user input and that it's not already in the system
int password_validation(char* pass);//validates password input returns 1 if validated.
void doctor_Menu(Doctor* d);//Prints doctor menu
Doctor* sign_inD(Doctor* d);//signs in and returns a pointer to the struct.
int search_doctor_to_modify(const Doctor* d, FILE* fp);//modifies a doctor, returns 1 if successed. 0 if failed.
void editDoctor(Doctor* d);//Edits detail of doctor.

















#endif;