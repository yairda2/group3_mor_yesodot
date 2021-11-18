#pragma once
#ifndef PATIENT_H
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
struct Patient { //Doctors struct 
	char un[SIZE];//user
	char pass[SIZE];//pass
	char ID[SIZE];//ID
	char name[SIZE];//name
	char last_n[SIZE];//last
	char gender[SIZE];//gender

}typedef Patient;

//Patient database Doctor Database Appointment --> doctorsID patientsID
//functions

int initiatePatient(Patient* p);//creates patient.
int registerPatient(const Patient* p);//registers patient. returns 1 if registed.
void printPatient(const Patient* p);//prints patient. 
Patient* sign_inP(Patient* p);//signs into system
int user_validation_P(const char* user);//validates user input
int password_validation(char* pass);//validates password input

#endif;