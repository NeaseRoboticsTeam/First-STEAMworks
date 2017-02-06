#include <iostream>
#include <memory>
#include <string>
#include <RobotDrive.h>
#include <XboxController.h>
#include <Spark.h>
#include <Servo.h>
#include <math.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
bool A;
bool B;
double LServoDeg;
double RServoDeg;
double RTread; //declare RTread as a double
double LTread; //declare LTread as a double
double RStickY; // declare RStickY as a double
double LStickY; // declare LStickY as a double
int degChange = 2;
int RTrigP;
int LTrigP;
int FRP = 0; //initialize and declare FRP as an integer with a value 0
int FLP = 2; //initialize and declare FLP as an integer with a value 2
int BRP = 1; //initialize and declare BRP as an integer with a value 1
int BLP = 3; //initialize and declare BLP as an integer with a value 3
int LServoPort = 4;
int RServoPort = 5;
class Robot: public frc::IterativeRobot {
public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}
	void AutonomousInit() override {
		std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}
	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}
	void TeleopInit() {
	LServoDeg = LServo.GetAngle();//get left servo position
	RServoDeg = RServo.GetAngle();//get right servo position
	A = WExbox.GetAButton();//check if A button is pressed
	B = WExbox.GetBButton();//check if B buton is pressed
	LTrigP = WExbox.GetTriggerAxis((frc::GenericHID::JoystickHand)0);//get left trigger axis
	RTrigP = WExbox.GetTriggerAxis((frc::GenericHID::JoystickHand)1);//get right trigger axis
	LStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)0);//check y value of left stick
	RStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)1);//check y value of right stick
	LTread =pow(LStickY, 3)+(0.3*LStickY); //multiply by 3, cube, assign to LTread
	RTread =pow(RStickY, 3)+(0.3*RStickY); //multiply by 3, cube, assign to RTread
	}
	void TeleopPeriodic()
	{
		myRobot.TankDrive(-LTread, -RTread); //use TankDrive function
		if(LTrigP > 0)
		{	//if left trigger is pressed at all
		RServo.SetAngle(RServoDeg - degChange);
		LServo.SetAngle(LServoDeg + degChange);
		}
		if(RTrigP > 0)
		{	// if right trigger is pressed at all
			RServo.SetAngle(RServoDeg + degChange);
			LServo.SetAngle(LServoDeg - degChange);
		}
		if(A != 0)
		{	//of A is pressed
			RServo.SetAngle(0);
			LServo.SetAngle(300);
		}
		if(B != 0)
		{	//if B is pressed
			RServo.SetAngle(300);
			LServo.SetAngle(0);
		}
	}
	void TestPeriodic() {
		lw->Run();
	}
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	frc::RobotDrive myRobot { FLP, BLP, FRP, BRP};//constructor for myRobot, paramaters are ports
	frc::Servo LServo {LServoPort}; //constructor for left servo
	frc::Servo RServo {RServoPort}; // constructor for right servo
	frc::XboxController WExbox{0}; //constructor for xbox controller
};
START_ROBOT_CLASS(Robot)
