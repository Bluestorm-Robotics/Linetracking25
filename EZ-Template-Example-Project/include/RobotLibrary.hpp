#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline const int DRIVE_SPEED = 15;
inline const int TURN_SPEED = 110; //not really used
inline const int SWING_SPEED = 40;

//inline const int lineWidthCM = 2_cm;


//int m = 1; //Motor Vector (obsolete)
/*int uTurnValue = 500;
int vpointTurn = 200; //point turn value
int speed = 5;
float turnSpeed = 10;//speed times direction (positive/negative)
float lineWidthCM = 4.0; //distance of tape line
float WheelDiamterCM = 7.4; //Stock ev3
float robotDiameterCM = 22.0;
int WallDistCM = 8;
float searchTime = 2;
*/
 
//throw functions below
/*void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}*/

/*void forwards(){ //default
	//setMultipleMotors(speed, motorB, motorC);
	motor[motorB] = speed;
	motor[motorC] = speed;
}
void forwards(int x){ //controled speed
	motor[motorB] = x;
	motor[motorC] = x;
}

void STP(){ //kinda irelivant with stopAllMotors();
	rsMotors();
	motor[motorB] = 0;
	motor[motorC] = 0;
}

float convertEncoderToCM(int encoderCounts){
	return(encoderCounts / 360.0)*(WheelDiamterCM * PI);
}
float CalcRadToDeg(float x){
	return x*(robotDiameterCM/WheelDiamterCM);
}
/*float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(WheelDiamterCM*PI)*360;
}
float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(PI*WheelDiamterCM)*360.0;
}

void moveCM(float y){ //move given distance in CM
	float x=convertCMToDegrees(y);
	rsMotors();
	setMotorTarget(motorB, x, speed);
	setMotorTarget(motorC, x, speed);
	waitUntilMotorStop(motorC);
}
*/
inline void leftPointTurn(){
    chassis.pid_drive_set(2, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_relative_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(2_cm, DRIVE_SPEED, true);
    chassis.pid_wait();
}

inline void rightPointTurn(){
    chassis.pid_drive_set(2, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_relative_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(2_cm, DRIVE_SPEED, true);
    chassis.pid_wait();
}

inline void uTurn(){
    chassis.pid_turn_relative_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();
}

inline void leftNudge(){
    chassis.pid_drive_set(0, 0);
	chassis.pid_drive_set(3.5_cm, DRIVE_SPEED, true);
	chassis.pid_wait();
    chassis.pid_turn_relative_set(-5_deg, TURN_SPEED, true);
    chassis.pid_wait();
}

inline void rightNudge(){
    chassis.pid_drive_set(0, 0);
	chassis.pid_drive_set(3.5_cm, DRIVE_SPEED, true);
	chassis.pid_wait();
    chassis.pid_turn_relative_set(5_deg, TURN_SPEED, true);
    chassis.pid_wait();
}

/*void leftNudge(){ old code
	STP();
	rsMotors();
	setMotorTarget(motorC, 10, 10);
	waitUntilMotorStop(motorC);
}

void rightNudge(){
	STP();
	rsMotors();
	setMotorTarget(motorB, 10, 10);
	waitUntilMotorStop(motorB);
}*/
/*
bool checkObstacle(){
	bool wall;
	if(getUSDistance(S3) < WallDistCM){
		wall = true;
		return wall;//incredible
	}
	else{
		wall = false;
		return wall;
	}
}

void searchRight(){
	motor[motorB] = turnSpeed;
	motor[motorC] = -turnSpeed;
}

void searchLeft(){
	motor[motorB] = -turnSpeed;
	motor[motorC] = turnSpeed;
}


void findLine(bool hold){
	while(hold == true){
		STP();
		playSound(soundException);
		moveCM(lineWidthCM);
		sleep(1000);
		if((getColorName(S1) == colorGreen) || (getColorName(S4) == colorGreen)){
			moveCM(lineWidthCM);
		}
		clearTimer(T1);
		while((time1[T1] < searchTime) && (getColorName(S1) != colorBlack)){
			searchRight();
		}
		while((time1[T1] > searchTime) && (getColorName(S4) != colorBlack)){
			searchLeft();
		}
		STP();
		hold=false;
	}
}

void findLeft(){
	STP();
	while ((getColorName(S1)==colorBlack)&&(getColorName(S4)!= colorBlack)){
		searchLeft();
	}
	/*if ((getColorName(S1)==colorBlack)&&(getColorName(S4)==colorBlack)){
		while(getColorName(S4)!= colorBlack){
			searchLeft();
		}
		moveCM(1.0);
	}
	sleep(500);
}
void findRight(){
	STP();
	while ((getColorName(S1)!=colorBlack)&&(getColorName(S4)==colorBlack)){
		searchRight();
	}
	/*if ((getColorName(S1)==colorBlack)&&(getColorName(S4)==colorBlack)){
		while(getColorName(S1) != colorBlack){
			searchRight();
		}
		moveCM(1.0);
	}
	sleep(500);
}

void storeArm(){
	motor[motorA] = 10;
	motor[motorD] = 10;
	sleep(2000);
	motor[motorA] = 0;
	motor[motorD] = 0;
	//resetMotorEncoder(motorA);
	//resetMotorEncoder(motorD);
}
//setproperties

void armDown(){
	setMotorTarget(motorA, 0, 15);
	setMotorTarget(motorD, 0, 15);
	waitUntilMotorStop(motorD);
	sleep(200);
}
task initDis(){//Initialize display(){
	int time = 4;
	repeat(4){
		time=time-1;
		displayCenteredBigTextLine(2, "Initializing: %d", time);
		displayCenteredBigTextLine(6, "Team Eclipse:");
		displayCenteredBigTextLine(8, "William S");
		displayCenteredBigTextLine(10, "Fredrick Wu");
		displayCenteredBigTextLine(12, "Justin Oh");
		sleep(1000);
	}
}
void setUTurn(int x){
	uTurnValue=x;
}

void setSpeed(int x){
	speed=x;
}

void setTurnSpeed(int x){
	turnSpeed=x;
}

void setTurnValue(int x){
	vpointTurn=x;
}

void setWheelDiamter(float x){
	WheelDiamterCM=x;
}

void setWallDist(float x){
	WallDistCM=x;
}

void setLineWidthCM(float x){
	lineWidthCM=x;
}

void setSearchTime(float x){
	searchTime=x;
}
void setRobotDiameterCM(float x){
	robotDiameterCM=x;
}

void coasting(bool coast){
	if(coast == false){
		bFloatDuringInactiveMotorPWM=true;
	}
	else if(coast == true){
		bFloatDuringInactiveMotorPWM=false;
	}
}*/