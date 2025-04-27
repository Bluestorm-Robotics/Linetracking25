#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline const int norm_DRIVE_SPEED = 17; //Default driving speed
inline const int norm_TURN_SPPEED = 110;
inline const int upHill_DRIVE_SPEED = 100; //uphill driving speed
inline const int upHill_TURN_SPEED = 110;
inline const int downHill_DRIVE_SPEED = 15;
inline const int SWING_SPEED = 40;

inline int DRIVE_SPEED = 30; //Editable variable
inline int TURN_SPEED = 110; //not really used

inline const int detectionDistance  = 180; //Obstacle detection distance for ultrasonic sensor
inline const int tiltFlag = 10; //10 degress downhill
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

inline void STP(){ //stop
	chassis.pid_drive_set(0, 0);
	pros::delay(50);
}

inline void leftPointTurn(){
    chassis.pid_drive_set(4_cm, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_relative_set(-90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(10_cm, TURN_SPEED, true);
    chassis.pid_wait();
}

inline void rightPointTurn(){
    chassis.pid_drive_set(4_cm, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_relative_set(90_deg, TURN_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(10_cm, TURN_SPEED, true);
    chassis.pid_wait();
}

inline void uTurn(){
    chassis.pid_turn_relative_set(180_deg, TURN_SPEED, true);
    chassis.pid_wait();
	chassis.pid_drive_set(6_cm, DRIVE_SPEED, true);
    chassis.pid_wait();
}

inline void leftNudge(){
	STP();
	chassis.pid_turn_relative_set(-5, TURN_SPEED, true); // turn left
	chassis.pid_wait();
	pros::delay(2);
}

inline void rightNudge(){
	STP();
	chassis.pid_turn_relative_set(5, TURN_SPEED, true); //turn right
	chassis.pid_wait();
	pros::delay(2);
}

inline void forwards(){
	chassis.drive_set(DRIVE_SPEED, DRIVE_SPEED);
	pros::delay(2);
}

inline void forwards(int x){
	chassis.drive_set(x, x);
	pros::delay(2);
}

inline void checkObstacle(){ //Checks front ultrasonic sensor for obstacles
	bool wall = false;
	if(ultrasonic.get() < detectionDistance){
		wall = true;
		while(wall == true){
			STP();
			chassis.pid_turn_relative_set(-90_deg, TURN_SPEED-50, true);
			chassis.pid_wait();
			while(sideUltrasonic.get() < detectionDistance){ //Keep moving forward until Obstalce is cleared
				forwards();
			}
			for(int i = 3; i > 0; i--){ //repeat 3 time
				chassis.pid_drive_set(18_cm, DRIVE_SPEED, true); //Clear the robot of the obstacle
				chassis.pid_wait();
				chassis.pid_turn_relative_set(90_deg, TURN_SPEED-50, true); //Now on 2nd side of obstacle
				chassis.pid_wait();
				while(sideUltrasonic.get() > detectionDistance){
					forwards();
				}
				while(sideUltrasonic.get() < detectionDistance){ //Keep moving forward until Obstalce is cleared
					forwards();
					if((leftLine.get_value() > colorBlack) || (rightLine.get_value() > colorBlack)){
						STP();
						wall = false;
						break;
					}
				}
			}
			STP(); //No solution found. give up
		}
	}
	else pros::delay(2);
}
inline void technicalChallenge(int x){
	int reflectTape = x;
	STP();
	chassis.pid_drive_set(15_cm, DRIVE_SPEED, true); //move to middle of the tile
	chassis.pid_wait();
	for(int i = 4; i > 0; i--){
		chassis.pid_drive_set(15_cm, DRIVE_SPEED, true);
		chassis.pid_wait();
		pros::delay(50);
		if((leftLine.get_value() > reflectTape) && (rightLine.get_value() > reflectTape)){
			chassis.pid_drive_set(5_cm, TURN_SPEED-50, true); //move to middle of the tile
			chassis.pid_wait();
			break;
		}
		else{
			chassis.pid_drive_set(-15_cm, DRIVE_SPEED, true);
			chassis.pid_wait();
			chassis.pid_turn_relative_set(90_deg, TURN_SPEED-50, true);
		}
	}
}

inline void tiltMonitor(){
	pros::delay(50);
	while(true){
		if(chassis.imu.get_pitch() < -tiltFlag){
			DRIVE_SPEED = upHill_DRIVE_SPEED;
			TURN_SPEED = upHill_TURN_SPEED;
		}
		else if(chassis.imu.get_pitch() > tiltFlag){
			DRIVE_SPEED = downHill_DRIVE_SPEED;
			TURN_SPEED = norm_TURN_SPPEED;
		}
		else {
			DRIVE_SPEED = norm_DRIVE_SPEED;
			TURN_SPEED = norm_TURN_SPPEED;
		}

		pros::delay(2);
	}
}

inline void resetSwitch(){
	while(true){
		if(resetBut.get_value() == 0){
			chassis.pid_targets_reset();                // Resets PID targets to 0
			chassis.drive_imu_reset();                  // Reset gyro position to 0
			chassis.drive_sensor_reset();
			STP();
			pros::delay(1000);
		}
		else pros::delay(2);
	}
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