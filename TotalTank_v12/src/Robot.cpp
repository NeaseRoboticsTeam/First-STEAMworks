#include <TotalTankIncludes.h> //one big include file
bool A; //declare A for a button
bool B; //declare B for B button
bool X; //declare X for X button
bool Y; //declare Y for Y button
bool LBump; //declare LBump for Left bumper
bool RBump; //declare RBump for Right Bumper
double LServoDeg; //declare LServoDeg as the current degree of left servo
double RServoDeg; //declare RServoDeg as the current degree of right servo
double RTread; //declare RTread as a double
double LTread; //declare LTread as a double
double RStickY; // declare RStickY as a double
double LStickY; // declare LStickY as a double
double LStickX; // declare LStickX as a double
int degChange = 2; //increment for degree change
int FRP = 0; //initialize and declare FRP as an integer with a value 0
int FLP = 2; //initialize and declare FLP as an integer with a value 2
int BRP = 1; //initialize and declare BRP as an integer with a value 1
int BLP = 3; //initialize and declare BLP as an integer with a value 3
int LServoPort = 4; //left servo port
int RServoPort = 5; //right servo port
const std::string autoNameMid = "Middle Auto";
const std::string autoNameLeft= "Left Auto";
const std::string autoNameRight = "Right Auto";
frc::SendableChooser<std::string> chooser;
std::string autoSelected;
class Robot: public frc::IterativeRobot{
public:
	void RobotInit() {
		std::cout<<"  _____     _        _ _____           _                       __   _____  \n";
		std::cout<<" |_   _|   | |      | |_   _|         | |                     /  | / __  \ \n";
		std::cout<<"   | | ___ | |_ __ _| | | | __ _ _ __ | | __           __   __`| | `' / /' \n";
		std::cout<<"   | |/ _ \| __/ _` | | | |/ _` | '_ \| |/ /           \ \ / / | |   / /   \n";
		std::cout<<"   | | (_) | || (_| | | | | (_| | | | |   <             \ V / _| |_./ /___ \n";
		std::cout<<"   \_/\___/ \__\__,_|_| \_/\__,_|_| |_|_|\_\             \_/  \___/\_____/ \n";
		std::cout<<"                                              ______                      \n";
		std::cout<<"                                             |______|                     \n";
		CameraServer::GetInstance()->StartAutomaticCapture();
	    chooser.AddDefault(autoNameMid, autoNameMid);
		chooser.AddObject(autoNameLeft, autoNameLeft);
		chooser.AddObject(autoNameRight, autoNameRight);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		myRobot.SetExpiration(10000);
		timer.Start();
	}
public:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::RobotDrive myRobot { FLP, BLP, FRP, BRP};//constructor for myRobot, paramaters are ports
	frc::Servo LServo {LServoPort}; //constructor for left servo
	frc::Servo RServo {RServoPort}; // constructor for right servo
	frc::XboxController WExbox{0}; //constructor for xbox controller
	frc::Timer timer;
	frc::Timer autoTimer;

	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		std::cout << "Auto selected: " << autoSelected << std::endl;
		timer.Reset(); //Set timer to 0
		timer.Start(); //Start timer
	}
	void AutoDrive(double Lval, double Rval, double time){
		double driveTime = autoTimer.Get() + time;
		autoTimer.Reset();
		autoTimer.Start();
		while(autoTimer.Get() < driveTime){
			myRobot.TankDrive(-Lval, -Rval);
		}
	}
	void AutoDrive(std::string dir, double time){
		double driveTime = autoTimer.Get() + time;
		if(dir == "fwd"){
			while(autoTimer.Get() < driveTime){
				myRobot.TankDrive(-.5,-.5);
			}
		}
		if(dir == "bck"){
			while(autoTimer.Get() < driveTime){
				myRobot.TankDrive(.5,.5);
			}
		}
	}
	void ramp(std::string pos){
		if(pos == "up"){
			RServo.SetAngle(130); //125
			LServo.SetAngle(170); //175
		}
		if(pos == "down"){
			RServo.SetAngle(250);
			LServo.SetAngle(60);
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameMid) {
			AutoDrive(.5,.5,  5);
			AutoDrive(-.5,.5, 9);
			AutoDrive(.3,.3, 12);
			ramp("up");
		}
		if(autoSelected == autoNameLeft) {
	//		AutoDrive(.5, 0, 10);
	//		AutoDrive();
	//		AutoDrive();

		}
		if(autoSelected == autoNameRight){
	//		AutoDrive(.5, 0, 10);
	//		AutoDrive();
	//		AutoDrive();
	//		AutoDrive();
		}
	}
	void TeleopInit() {
		LServoDeg = LServo.GetAngle();//get left servo position
		RServoDeg = RServo.GetAngle();//get right servo position
		A = WExbox.GetAButton();//check if A button is pressed
		B = WExbox.GetBButton();//check if B button is pressed
		X = WExbox.GetXButton();//check if X button is pressed
		Y = WExbox.GetYButton();//check if Y button is pressed
		RBump = WExbox.GetBumper((frc::GenericHID::JoystickHand)0);
		LBump = WExbox.GetBumper((frc::GenericHID::JoystickHand)1);
		LStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)0);//check y value of left stick
		RStickY =  WExbox.GetY((frc::GenericHID::JoystickHand)1);//check y value of right stick
		LTread = pow(LStickY, 3)+(0.3*LStickY); //multiply by 3, cube, assign to LTread
		RTread = pow(RStickY, 3)+(0.3*RStickY); //multiply by 3, cube, assign to RTread
	}
	void TeleopPeriodic()
	{

		myRobot.TankDrive(-LTread, -RTread); //use TankDrive function
		if(A != 0){
			RServo.SetAngle(130); //125
			LServo.SetAngle(170); //175
		}
		if(B != 0){
			RServo.SetAngle(250);
			LServo.SetAngle(60);
		}
		if(RBump != 0){
			myRobot.TankDrive(-.5, .5);
		}
		if(LBump != 0){
			myRobot.TankDrive(.5, -.5);
		}
		if(X != 0){
			myRobot.TankDrive(-.5, -.5);
		}
		if(Y != 0){
			myRobot.TankDrive(.5, .5);
		}
/*		if(LTrigP > 0){
			RServo.SetAngle(RServoDeg - degChange);
			LServo.SetAngle(LServoDeg + degChange);
		}
		if(RTrigP > 0){
			RServo.SetAngle(RServoDeg + degChange);
			LServo.SetAngle(LServoDeg - degChange);
		}*/
	}
	void TestPeriodic() {
		lw->Run();
	}
};
START_ROBOT_CLASS(Robot)
