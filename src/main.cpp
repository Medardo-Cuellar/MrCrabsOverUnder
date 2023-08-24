/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#define PI 3.14159265

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    int deadband = 15;
    int FrontLeftSpeed = 0;
    int RearLeftSpeed = 0;
    int FrontRightSpeed = 0;
    int RearRightSpeed = 0;
    
    int x=0, y=0, volteo=0;
    double theta = 0, fuerza = 0, seno = 0, coseno = 0, maximo = 0;

    x=Controller1.Axis4.position();
    y=Controller1.Axis3.position();
    volteo = Controller1.Axis1.position();
    
    
    theta = atan2(y,x);
    fuerza = hypot(x,y);
    seno = sin(theta - PI/4);
    coseno = cos(theta - PI/4);
    maximo = fmax(abs(seno),abs(coseno));


    FrontRightSpeed = (fuerza * (coseno/maximo)) + volteo;
    FrontLeftSpeed = (fuerza * (seno/maximo)) - volteo;
    RearRightSpeed = (fuerza * (seno/maximo)) + volteo;
    RearLeftSpeed = (fuerza * (coseno/maximo)) - volteo;

/*
    FrontRightSpeed = (fuerza * (coseno/maximo)) + volteo;
    FrontLeftSpeed = (fuerza * (seno/maximo)) - volteo;
    RearRightSpeed = (fuerza * (seno/maximo)) + volteo;
    RearLeftSpeed = (fuerza * (coseno/maximo)) - volteo;

    if((fuerza + abs(volteo)) > 1)
    {
      FrontRightSpeed /= fuerza + volteo;
      FrontLeftSpeed /= fuerza + volteo;
      RearRightSpeed /= fuerza + volteo;
      RearLeftSpeed /= fuerza + volteo;
    }
 */   

    //deadband check and speed setting

    if (abs(FrontLeftSpeed) < deadband) {
      // Set the speed to zero.
      FrontLeft.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      FrontLeft.setVelocity(FrontLeftSpeed, percent);
    }
        if (abs(RearLeftSpeed) < deadband) {
      // Set the speed to zero.
      RearLeft.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      RearLeft.setVelocity(RearLeftSpeed, percent);
    }
    
    if (abs(FrontLeftSpeed) < deadband) {
      // Set the speed to zero.
      FrontRight.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      FrontRight.setVelocity(FrontRightSpeed, percent);
    }
    
    if (abs(FrontLeftSpeed) < deadband) {
      // Set the speed to zero.
      RearRight.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      RearRight.setVelocity(RearRightSpeed, percent);
    }

    FrontLeft.spin(forward);
    RearLeft.spin(forward);
    FrontRight.spin(forward);
    RearRight.spin(forward);
/**/
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    if(Controller1.ButtonX.pressing())
    {
      lifter.spin(forward);
    }
    else if(Controller1.ButtonB.pressing())
    {
      lifter.spin(reverse);
    }
    else
    {
      lifter.stop(brakeType::hold);
    
    }

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,2);
    Controller1.Screen.print("L %d",FrontLeftSpeed);
    Controller1.Screen.newLine();
    Controller1.Screen.print("L %d",RearLeftSpeed);
    Controller1.Screen.newLine();
    Controller1.Screen.print("L %d",FrontRightSpeed);
    Controller1.Screen.newLine();
    Controller1.Screen.print("L %d",RearRightSpeed);
    Controller1.Screen.newLine();


    //Controller1.Screen.print(" %d    %d    %d ", x , y, volteo);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
