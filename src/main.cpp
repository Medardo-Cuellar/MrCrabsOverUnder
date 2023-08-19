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
        
    int Turn = 0;
    int Forwarde = 0;
    int Sideways = 0;
  
    Turn = ((Controller1.Axis1.position())*3)/2; //turn
    Forwarde = ((Controller1.Axis3.position())*3)/2; //forward
    Sideways = ((Controller1.Axis4.position())*3)/2; //sideways


    FrontRightSpeed = Forwarde + Sideways + Turn;
    FrontLeftSpeed = Forwarde - Sideways - Turn;
    RearRightSpeed = Forwarde - Sideways + Turn;
    RearLeftSpeed = Forwarde + Sideways - Turn;

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
