using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
/*
extern smartdrive Drivetrain;
extern motor ClawMotor;
extern motor ArmMotor;
*/
extern motor FrontLeft;
extern motor RearLeft;
extern motor FrontRight;
extern motor RearRight;

extern motor scissorlift;
extern motor ropelift1;
extern motor ropelift2;
extern motor_group ropelift;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );