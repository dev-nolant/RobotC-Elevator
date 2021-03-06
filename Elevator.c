#pragma config(Sensor, dgtl1,  Encoder1,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  Level1,         sensorDigitalIn)
#pragma config(Sensor, dgtl4,  Level2,         sensorDigitalIn)
#pragma config(Sensor, dgtl5,  Level3,         sensorDigitalIn)
#pragma config(Sensor, dgtl6,  EStop,          sensorDigitalIn)
#pragma config(Sensor, dgtl9,  light1,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, light2,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, light3,         sensorLEDtoVCC)
#pragma config(Motor,  port2,           main_shaft,    tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port3,           support_shaft, tmotorVex269_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
///////////////////////////////////////
//LEVEL HEIGHT DETERMINATION//
int level_one = 0;
int level_two = 2000;
int level_three = 3600;
//SPEED SELECTOR
int speed = 45;
//ELEVATOR DOWN COMMAND
void level_down(){
	if(SensorValue[EStop] == 1){
		startMotor(main_shaft, -speed);
		startMotor(support_shaft, speed);
	}
	else{
		
		stopMotor(main_shaft);
		stopMotor(support_shaft);
		stopAllTasks();
}
}
//ELEVATOR UP COMMAND
void level_up(){
	if(SensorValue[EStop] == 1){
		startMotor(main_shaft, speed);
		startMotor(support_shaft, -speed);
	}
	else{
		stopMotor(main_shaft);
		stopMotor(support_shaft);
		stopAllTasks();
}
}
//MAIN TASK HANDLER
task main()
{
	    //SNIPPET BELOW DETERMINES THE LIGHT VALUE, WILL TURN ON THE LIGHTS IT NEEDS TO AND TURN OFF THE OTHERS// LEVEL INDICATION
	turnLEDOff(light1);
	turnLEDOff(light2);
	turnLEDOff(light3);
    //RESETS THE ELEVATOR BACK TO LEVEL 1 IF IT WAS STOPPED IN THE MIDDLE OF ANOTHER PROCESS. // FAULT HANDLER

  //MAKES SURE THE EMERGENCY STOP IS NOT PRESSED//WHILE LOOP ENSURES THE PROGRAM CONTINUOUSLY RUNS
	while(SensorValue[EStop] == 1){
		if(SensorValue[Encoder1] > 100){
			clearTimer(T1);
		while(SensorValue[Encoder1] > 100){
			level_down();

			turnLEDOff(light3);
			turnLEDOff(light2);
			turnLEDOn(light1);
		stopMotor(main_shaft);
		stopMotor(support_shaft);
		clearTimer(T1);
	}
}
//WHEN FAULT FIXED, ELEVATOR BASE LEVEL IS SET AT THE CURRENT ENCODER READING.
	else{
		SensorValue[Encoder1] = 0;
	}
		//	SensorValue[Encoder1] = 0; // *IGNORE*
    //INITIATES TIMER
		clearTimer(T1);
  //ENSURES A TIME CHECK DURING THE PROCESS OF THE ELEVATOR RUNNING, NO COLLUSIONS OR COLLIDING PROCESSES

		while(time1[T1] <= 10000) {
			if(SensorValue[EStop] == 0){
				stopAllTasks();
			}
        //RAISE LEVEL CHECKING HANDLER - CHECKS IF DESIRED LEVEL IS HIGHER THAN CURRENT LEVEL AND IF SO, THEN THE ELEVATOR RAISES ITSELF TO DESIRED LEVEL
			if(SensorValue[Level1] == 0){

				if(SensorValue[Encoder1] < level_one){
					turnLEDOff(light3);
					turnLEDOff(light2);
					turnLEDOn(light1);
					clearTimer(T1);
					while(SensorValue[Encoder1] < level_one){
						level_up();
				}
			}
				else{
					stopMotor(main_shaft);
					stopMotor(support_shaft);
					clearTimer(T1);

			}
		}
			if(SensorValue[Level2] == 0){

				if(SensorValue[Encoder1] < level_two){
					turnLEDOff(light1);
					turnLEDOff(light3);
					turnLEDOn(light2);
					clearTimer(T1);
					while(SensorValue[Encoder1] < level_two){

						level_up();
				}
			}
				
					stopMotor(main_shaft);
					stopMotor(support_shaft);
					clearTimer(T1);

					
			}
		if(SensorValue[Level3] == 0){
			if(SensorValue[Encoder1] < level_three){
				turnLEDOff(light1);
				turnLEDOff(light2);
				turnLEDOn(light3);
				clearTimer(T1);
				while(SensorValue[Encoder1] < level_three){

					level_up();
			}
		}
				stopMotor(main_shaft);
				stopMotor(support_shaft);
				clearTimer(T1);
			
				}
		

//LOWER LEVEL CHECKING HANDLER - CHECKS IF THE DESIRED LEVEL IS BELOW CURRENT LEVEL AND IF IT IS IT LOWERS THE ELEVATOR TO DESIRED LEVEL
			if(SensorValue[Level1] == 0){

				if(SensorValue[Encoder1] > level_one){
					turnLEDOff(light3);
					turnLEDOff(light2);
					turnLEDOn(light1);
					clearTimer(T1);
					while(SensorValue[Encoder1] > level_one){
						level_down();
				}
			}
					stopMotor(main_shaft);
					stopMotor(support_shaft);
					clearTimer(T1);

		}

			if(SensorValue[Level2] == 0){

				if(SensorValue[Encoder1] > level_two){
					turnLEDOff(light1);
					turnLEDOff(light3);
					turnLEDOn(light2);
					clearTimer(T1);
					while(SensorValue[Encoder1] > level_two){

						level_down();
				}
			}
					stopMotor(main_shaft);
					stopMotor(support_shaft);
					clearTimer(T1);
					}
			}

			if(SensorValue[Level3] == 0){
				clearTimer(T1);
				if(SensorValue[Encoder1] > level_three){
					turnLEDOff(light1);
					turnLEDOff(light2);
					turnLEDOn(light3);
					while(SensorValue[Encoder1] > level_three){
						level_down();
				}
			}
					stopMotor(main_shaft);
					stopMotor(support_shaft);
					clearTimer(T1);

			}
//ELSE: IF THE TIMER IS OVER 10 SECONDS, THE LEVEL RESETS BACK TO LEVEL 1 (LEVEL 0/GROUND LEVEL)
	if(SensorValue[Encoder1] > level_one){
		turnLEDOff(light3);
		turnLEDOff(light2);
		turnLEDOn(light1);
		while(SensorValue[Encoder1] > level_one){
			level_down();
			}
		stopMotor(main_shaft);
		stopMotor(support_shaft);
		}
	else{
		stopMotor(main_shaft);
		stopMotor(support_shaft);
		clearTimer(T1);
		}
	stopMotor(main_shaft);
	stopMotor(support_shaft);

//WHILE STATEMENT BREAKS - IF THE WHILE STATEMENT IS NOT TRUE, THEN THIS IS WHAT HAPPENS; THE PROGRAM STOPS EVERYTHING INCLUDING THE MOTORS.
	stopAllTasks();
	stopMotor(main_shaft);
	stopMotor(support_shaft);
}
stopMotor(main_shaft);
stopMotor(support_shaft);
}
