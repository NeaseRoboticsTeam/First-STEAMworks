#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <XboxController.h>
#include <Spark.h>

double LStick;
double RStick;

class Robot: public frc::IterativeRobot {
public:
	Robot() {
	myRobot.SetExpiration(0.1);
		timer.Start();
	}

private:
	//frc::RobotDrive myRobot { 0, 1 };  // Robot drive system
	//frc::Joystick stick { 0 };         // Only joystick
	frc::XboxController WExbox{0};
	frc::Spark Spark0{0};
	frc::Spark Spark1{1};
	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();
	frc::Timer timer;

	void AutonomousInit() override {
		timer.Reset();
		timer.Start();
	}

	void AutonomousPeriodic() override {
		// Drive for 2 seconds
		//if (timer.Get() < 2.0) {
			//myRobot.Drive(-0.5, 0.0);  // Drive forwards half speed
	//	} else {
		//	myRobot.Drive(0.0, 0.0);  // Stop robot
	//	}
	}

	void TeleopInit() override {

	}

	void TeleopPeriodic() override {
		// Drive with arcade style (use right stick)
		//myRobot.ArcadeDrive(stick);
		//myRobot.TankDrive(LStick, RStick)
		LStick = WExbox.GetY((frc::GenericHID::JoystickHand)0);
		RStick = WExbox.GetY((frc::GenericHID::JoystickHand)1);
		Spark1.Set(.5);
		Spark0.Set(.5);
	}

	void TestPeriodic() override {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
