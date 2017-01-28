#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <XboxController.h>
#include <Spark.h>

//^^^^^ All libraries go here ^^^^^\\

double RStick;
double LStick;

int FRP = 3;
int FLP = 2;
int BRP = 0;
int BLP = 1;

//^^^^^ Declare all global variables here ^^^^^\\

class Robot: public frc::IterativeRobot {
public:
	Robot() {
		myRobot.SetExpiration(0.1);
		timer.Start();
	}

private:
	frc::RobotDrive myRobot { 0, 1, 2, 3};  // Robot drive system uses ports 0-3
	frc::XboxController WExbox{0}; //Xbox controller is named WExbox and it goes in port 0
	frc::Spark FR{FRP}; //Declare FR as the Spark controlling the FRP
	frc::Spark FL{FLP}; //Declare FL as the Spark controlling the FLP
	frc::Spark BL{BLP}; //Declare BL as the Spark controlling the BLP
	frc::Spark BR{BRP}; //declare BR as the spark controlling the BRP

	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();
	frc::Timer timer;

	void AutonomousInit() override {
		timer.Reset(); //Set timer to 0
		timer.Start(); //Start timer
	}

	void AutonomousPeriodic() override {
		if (timer.Get() < 5.0)// Drive for 5 seconds
		{
			myRobot.Drive(-0.5, 0.0);  // Drive forwards half speed (this is stock, we need to test it.)
		} else {
			myRobot.Drive(0.0, 0.0);  // Stop robot
		}
	}

	void TeleopInit() override {
		//don't need to worry about this yet
	}

	void TeleopPeriodic() override {
		LStick = WExbox.GetY((frc::GenericHID::JoystickHand)0); //check y value of left stick, assign to variable LStick
		RStick = WExbox.GetY((frc::GenericHID::JoystickHand)1); //check y value of right stick, assign to variable RStick
		FR.Set(RStick); //set Front right spark to right stick
		BR.Set(RStick); //set Back right spark to right stick
		FL.Set(LStick); //set front left spark to left stick
		BL.Set(LStick); //set back left spark to left stick
	}


	void TestPeriodic() override {
		lw->Run();//dont worry about it
	}
};

START_ROBOT_CLASS(Robot)
