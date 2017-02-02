#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <XboxController.h>
#include <Spark.h>
#include <Servo.h>
#include <math.h>
// All headers, sources, and includes go here
	double RTrigP;
	double LTrigP;
	double RTrig;
	double LTrig;
	double RTread; //declare RTread as a double
	double LTread; //declare LTread as a double
	double RStickY; // declare RStickY as a double
	double LStickY; // declare LStickY as a double
	int FRP = 0; //initialize and declare FRP as an integer with a value 0
	int FLP = 2; //initialize and declare FLP as an integer with a value 2
	int BRP = 1; //initialize and declare BRP as an integer with a value 1
	int BLP = 3; //initialize and declare BLP as an integer with a value 3
	int LServoPort = 4;
	int RServoPort = 5;
// Declare all global variables go here

class Robot: public frc::IterativeRobot {
public:
	Robot() {
		myRobot.SetExpiration(10000);
		timer.Start();
	}
private:
	frc::RobotDrive myRobot { FLP, BLP, FRP, BRP};  // Robot drive system uses ports 0-3
	frc::Servo LServo {LServoPort};
	frc::Servo RServo {RServoPort};
	frc::XboxController WExbox{0}; //Xbox controller is named WExbox and it goes in port 0
	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();
	frc::Timer timer;

//Objects go here

//Declare private variables go here

	void AutonomousInit() override {
		timer.Reset(); //Set timer to 0
		timer.Start(); //Start timer
	}
	void AutonomousPeriodic() override {
		if (timer.Get() < 5.0)// Drive for 5 seconds
		{
			myRobot.Drive(0.5, 0.0);  // Drive forwards half speed
		} else {
			myRobot.Drive(0.0, 0.0);  // Stop robot
		}
	}
	void TeleopInit() override {
		//don't need to worry about this yet
	}
	void TeleopPeriodic() override {

		//take amount trigger is pushed and assign it to these variables
		LTrigP = WExbox.GetTriggerAxis((frc::GenericHID::JoystickHand)0);
		RTrigP = WExbox.GetTriggerAxis((frc::GenericHID::JoystickHand)1);
		//take amount sticks are in the y and assign the these variables
		LStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)0);//check y value of left stick
		RStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)1);//check y value of right stick
		//manipulate stick values
		LTread =pow(LStickY, 3)+(0.3*LStickY); //multiply by 3, cube, assign to LTread
		RTread =pow(RStickY, 3)+(0.3*RStickY); //multiply by 3, cube, assign to RTread
		//robot controller
		myRobot.TankDrive(-LTread, -RTread); //use TankDrive function
		//servo controls
		LServo.Set(.90);
		RServo.Set(24);

	}
	void TestPeriodic() override {
			}
};
START_ROBOT_CLASS(Robot)
