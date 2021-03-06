
#include "Robot.h"
#include <iostream>
//#include <frc/smartdashboard/SmartDashboard.h>
//frc::Preferences *prefs;
void Robot::RobotInit() {

std::cout << "Robot Init called" << std::endl;
  //prefs = frc::Preferences::GetInstance();
  //rotationsLeftMotors[1] = prefs->GetInt("ArmUpPosition", 1);
  


  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //frc::Color detectedColor = m_colorSensor.GetColor();m_colorMatcher.AddColorMatch(kBlueTarget);

  //m_colorMatcher.AddColorMatch(kGreenTarget);
  //m_colorMatcher.AddColorMatch(kRedTarget);
  //m_colorMatcher.AddColorMatch(kYellowTarget);

  // ECODERS
  shoot1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, kTimeoutMs);
  shoot1->ConfigPeakOutputForward(1);
  shoot1->ConfigPeakOutputReverse(-1);
  shoot1->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
  shoot1->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
  shoot1->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  shoot1->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
  shoot1->SetSensorPhase(false);
  shoot1->SetInverted(false);
  
  shoot2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, kTimeoutMs);
  shoot2->ConfigPeakOutputForward(1);
  shoot2->ConfigPeakOutputReverse(-1);
  shoot2->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
  shoot2->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
  shoot2->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
  shoot2->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
  shoot2->SetSensorPhase(false);
  shoot2->SetInverted(false);

  
  climbPID.SetP(CkPe);
  climbPID.SetI(CkI);
  climbPID.SetD(CkD);
  climbPID.SetIZone(CkIz);
  climbPID.SetFF(CkFF);
  climbPID.SetOutputRange(kMinOutput, kMaxOutput);
  


  T1.Start();
  T2.Start();



  frc::CameraServer::GetInstance()->StartAutomaticCapture();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc::SmartDashboard::PutNumber("rearLeftEncoder", rearLeftEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("frontLeftEncoder", frontLeftEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("rearRightEncoder", rearRightEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("frontRightEncoder", frontRightEncoder1.GetPosition());

  frc::SmartDashboard::PutBoolean("ballIn", ballSwitch.Get());
  frc::SmartDashboard::PutNumber("frontRightEncoder", frontRightEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("frontLeftEncoder", frontLeftEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("rearRightEncoder", rearRightEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("rearLeftEncoder", rearLeftEncoder1.GetPosition());
  frc::SmartDashboard::PutNumber("climber", climbEnc.GetPosition());
  frc::SmartDashboard::PutNumber("climberSetPos", pos);
  
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here

      kPe = frc::SmartDashboard::GetNumber("DB/Slider 0", 0.03);
      kI = frc::SmartDashboard::GetNumber("DB/Slider 1", 0);
      kD = frc::SmartDashboard::GetNumber("DB/Slider 2", 0);
      kIz = frc::SmartDashboard::GetNumber("DB/Slider 3", 0);
      


      
      
      /*
      frontLeftPID1.SetP(kPe);
      frontLeftPID1.SetI(kI);
      frontLeftPID1.SetD(kD);
      frontLeftPID1.SetIZone(kIz);
      frontLeftPID1.SetFF(kFF);
      frontLeftPID1.SetOutputRange(kMinOutput, kMaxOutput);
      frontLeftPID1.SetSmartMotionMaxVelocity(kMaxVel);
      frontLeftPID1.SetSmartMotionMinOutputVelocity(kMinVel);
      frontLeftPID1.SetSmartMotionMaxAccel(kMaxAcc);
      frontLeftPID1.SetSmartMotionAllowedClosedLoopError(kAllErr);

      frontLeftPID2.SetP(kPe);
      frontLeftPID2.SetI(kI);
      frontLeftPID2.SetD(kD);
      frontLeftPID2.SetIZone(kIz);
      frontLeftPID2.SetFF(kFF);
      frontLeftPID2.SetOutputRange(kMinOutput, kMaxOutput);
      frontLeftPID2.SetSmartMotionMaxVelocity(kMaxVel);
      frontLeftPID2.SetSmartMotionMinOutputVelocity(kMinVel);
      frontLeftPID2.SetSmartMotionMaxAccel(kMaxAcc);
      frontLeftPID2.SetSmartMotionAllowedClosedLoopError(kAllErr);

      frontRightPID1.SetP(kPe);
      frontRightPID1.SetI(kI);
      frontRightPID1.SetD(kD);
      frontRightPID1.SetIZone(kIz);
      frontRightPID1.SetFF(kFF);
      frontRightPID1.SetOutputRange(kMinOutput, kMaxOutput);
      frontRightPID1.SetSmartMotionMaxVelocity(kMaxVel);
      frontRightPID1.SetSmartMotionMinOutputVelocity(kMinVel);
      frontRightPID1.SetSmartMotionMaxAccel(kMaxAcc);
      frontRightPID1.SetSmartMotionAllowedClosedLoopError(kAllErr);

      frontRightPID2.SetP(kPe);
      frontRightPID2.SetI(kI);
      frontRightPID2.SetD(kD);
      frontRightPID2.SetIZone(kIz);
      frontRightPID2.SetFF(kFF);
      frontRightPID2.SetOutputRange(kMinOutput, kMaxOutput);
      frontRightPID2.SetSmartMotionMaxVelocity(kMaxVel);
      frontRightPID2.SetSmartMotionMinOutputVelocity(kMinVel);
      frontRightPID2.SetSmartMotionMaxAccel(kMaxAcc);
      frontRightPID2.SetSmartMotionAllowedClosedLoopError(kAllErr);


      rearLeftPID1.SetP(kPe);
      rearLeftPID1.SetI(kI);
      rearLeftPID1.SetD(kD);
      rearLeftPID1.SetIZone(kIz);
      rearLeftPID1.SetFF(kFF);
      rearLeftPID1.SetOutputRange(kMinOutput, kMaxOutput);
      rearLeftPID1.SetSmartMotionMaxVelocity(kMaxVel);
      rearLeftPID1.SetSmartMotionMinOutputVelocity(kMinVel);
      rearLeftPID1.SetSmartMotionMaxAccel(kMaxAcc);
      rearLeftPID1.SetSmartMotionAllowedClosedLoopError(kAllErr);

      rearLeftPID2.SetP(kPe);
      rearLeftPID2.SetI(kI);
      rearLeftPID2.SetD(kD);
      rearLeftPID2.SetIZone(kIz);
      rearLeftPID2.SetFF(kFF);
      rearLeftPID2.SetOutputRange(kMinOutput, kMaxOutput);
      rearLeftPID2.SetSmartMotionMaxVelocity(kMaxVel);
      rearLeftPID2.SetSmartMotionMinOutputVelocity(kMinVel);
      rearLeftPID2.SetSmartMotionMaxAccel(kMaxAcc);
      rearLeftPID2.SetSmartMotionAllowedClosedLoopError(kAllErr);

      rearRightPID1.SetP(kPe);
      rearRightPID1.SetI(kI);
      rearRightPID1.SetD(kD);
      rearRightPID1.SetIZone(kIz);
      rearRightPID1.SetFF(kFF);
      rearRightPID1.SetOutputRange(kMinOutput, kMaxOutput);
      rearRightPID1.SetSmartMotionMaxVelocity(kMaxVel);
      rearRightPID1.SetSmartMotionMinOutputVelocity(kMinVel);
      rearRightPID1.SetSmartMotionMaxAccel(kMaxAcc);
      rearRightPID1.SetSmartMotionAllowedClosedLoopError(kAllErr);
      
      rearRightPID2.SetP(kPe);
      rearRightPID2.SetI(kI);
      rearRightPID2.SetD(kD);
      rearRightPID2.SetIZone(kIz);
      rearRightPID2.SetFF(kFF);
      rearRightPID2.SetOutputRange(kMinOutput, kMaxOutput);
      rearRightPID2.SetSmartMotionMaxVelocity(kMaxVel);
      rearRightPID2.SetSmartMotionMinOutputVelocity(kMinVel);
      rearRightPID2.SetSmartMotionMaxAccel(kMaxAcc);
      rearRightPID2.SetSmartMotionAllowedClosedLoopError(kAllErr);

      frontLeftEncoder1.SetPosition(0);
      frontLeftEncoder2.SetPosition(0);
      frontRightEncoder1.SetPosition(0);
      frontRightEncoder2.SetPosition(0);
      rearLeftEncoder1.SetPosition(0);
      rearLeftEncoder2.SetPosition(0);
      rearRightEncoder1.SetPosition(0);
      rearRightEncoder2.SetPosition(0);

      */

      rotationsLeftMotors.clear();
      rotationsRightMotors.clear();
      autoCount = 0;
      
      //afterCount1 = val11.find(",", beforeCount1) != std::string::npos
      float addVal1 = 0;
      float lastVal1 = 0;

      val11 = frc::SmartDashboard::GetString("DB/String 0", " ");
      beforeCount1 = 0;
      for(int i = 0; i < 100; i++)
      {      
        afterCount1 = val11.find(",", beforeCount1);
        val12 = val11.substr(beforeCount1, afterCount1);
        beforeCount1 = afterCount1 + 1;
        addVal1 = (atof(val12.c_str()));
        rotationsLeftMotors.push_back(addVal1); 
        //lastVal1 = (addVal1 + lastVal1);
        if(afterCount1 == std::string::npos){
          break;
        }
      }

      val21 = frc::SmartDashboard::GetString("DB/String 1", " ");
      beforeCount2 = 0;
      float addVal2 = 0;
      float lastVal2 = 0;
      for(int i = 0; i < 100; i++)
      {       
        afterCount2 = val21.find(",", beforeCount2);
        val22 = val21.substr(beforeCount2, afterCount2);
        beforeCount2 = afterCount2 + 1;
        addVal2 = (atof(val22.c_str()) * -1); 
        rotationsRightMotors.push_back(addVal2);
        //lastVal2 = (addVal2 + lastVal2);
        if(afterCount2 == std::string::npos){
          break;
        }
      }
      double currentRight;
      double currentLeft;

      newSetRight = rotationsRightMotors[2];
      newSetLeft = rotationsLeftMotors[2];

      autoTimer.Start();
      timeUp = false;

      T1.Reset();
      shooterTargetSpeed = 11000;
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here


  } 
  else {
    // Default Auto goes here
    
      //autoCount = 0;
      //T2.Reset();
      
      frc::SmartDashboard::PutNumber("length of rotations", rotationsLeftMotors.size());
      frc::SmartDashboard::PutString("val11", val11);
      frc::SmartDashboard::PutString("val12", val12);
      frc::SmartDashboard::PutString("val22", val22);
      frc::SmartDashboard::PutNumber("LeftSetVal", newSetLeft);
      frc::SmartDashboard::PutNumber("RightSetVal", newSetRight);
      frc::SmartDashboard::PutNumber("autoCount", autoCount);
      frc::SmartDashboard::PutNumber("deadzone", encoderDead);
      frc::SmartDashboard::PutNumber("T1", T1.Get());
      //rotationsLeftMotors.push_back(10);
      //rotationsRightMotors.push_back(-10);

      
        /*if(autoCount %2 == 0){
          encoderDead = encoderDeadStraight;
        }
        else{
          encoderDead = encoderDeadTurn;
        }*/
      
        if(autoCount == 0){
          intakeRun->Set(ControlMode::PercentOutput, 1);
          //kPe = .03;
          if(T1.Get() >= 1){
            autoCount++;
          }
        }
        else{
          intakeRun->Set(ControlMode::PercentOutput, 0);
        }
        
        if(autoCount == 1){        
          shoot2->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
          shoot1->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
          shoot1->Set(ControlMode::Velocity, shooterTargetSpeed); 
          shoot2->Set(ControlMode::Velocity, shooterTargetSpeed * -1);
          ballUp->Set(ControlMode::PercentOutput, 1); 
          index->Set(ControlMode::PercentOutput, -.3f);
          if(T1.Get() >= timeToShoot){
            autoCount++;
          }
        }
        else{
          shoot2->Config_kP(kPIDLoopIdx, 0.01, kTimeoutMs);
          shoot1->Config_kP(kPIDLoopIdx, 0.01, kTimeoutMs);
          shoot1->Set(ControlMode::Velocity, 0); 
          shoot2->Set(ControlMode::Velocity, 0); 
          ballUp->Set(ControlMode::PercentOutput, 0);
          index->Set(ControlMode::PercentOutput, 0);
        }
        
        if(autoCount >= 2){
          /*if(((fabs(rearLeftEncoder1.GetPosition() - newSetLeft) >= encoderDead 
          || fabs(rearRightEncoder1.GetPosition() - newSetRight) >= encoderDead) || autoCount == 2) && timeUp == false && quitLoop == false)
          {        
            frontLeftPID1.SetReference(newSetLeft, rev::ControlType::kPosition);
            frontRightPID1.SetReference(newSetRight, rev::ControlType::kPosition);
            rearLeftPID1.SetReference(newSetLeft, rev::ControlType::kPosition);
            rearRightPID1.SetReference(newSetRight, rev::ControlType::kPosition);
            frontLeftPID2.SetReference(newSetLeft, rev::ControlType::kPosition);
            frontRightPID2.SetReference(newSetRight, rev::ControlType::kPosition);
            rearLeftPID2.SetReference(newSetLeft, rev::ControlType::kPosition);
            rearRightPID2.SetReference(newSetRight, rev::ControlType::kPosition);
            if(autoTimer.Get() > 5){
              timeUp = true;
            }
            if(rotationsRightMotors[autoCount] == 0)
            {
              quitLoop = true;
            }
          }
          
          else if(autoCount < rotationsLeftMotors.size() - 1 && autoCount < rotationsRightMotors.size() - 1)
          {
            autoCount++;            
            newSetLeft = rearLeftEncoder1.GetPosition() + rotationsLeftMotors[autoCount];
            newSetRight = rearRightEncoder1.GetPosition() + rotationsRightMotors[autoCount]; 
            autoTimer.Reset();
            timeUp = false;
          } */

          m_left.Set(-.05 * -1);
          m_right.Set(-.05);
        }
            
      
    
  }
}

void Robot::TeleopInit() {
 climbEnc.SetPosition(0);
}

void Robot::TeleopPeriodic() {

  //ColorPizza();
  Drive();
  Shooter();
  Intake();
  Climber();
  Index();
  LED();
  //Testing();

  print hello;

  

  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetArea = table->GetNumber("ta",0.0);

}

  /*void Robot::ColorPizza() {
    double confidence = 0.0;
    frc::Color detectedColor = m_colorSensor.GetColor();
    std::string colorString;
    std::string seenColor;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);
    
    
    if (matchedColor == kBlueTarget) {
      colorString = "Red";
      seenColor = "blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Blue";
      seenColor = "red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Yellow";
      seenColor = "green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Green";
      seenColor = "yellow";
    } else {
      colorString = "Unknown";
    }

    

    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    if(gameData.length() > 0){
      switch (gameData[0]){
        case 'B' :
          //Blue case code
          break;
        case 'G' :
          //Green case code
          break;
        case 'R' :
          //Red case code
          break;
        case 'Y' :
          //Yellow case code
          break;
        default :
          //This is corrupt data
          break;
      }
    } 
    else {
      //Code for no data received yet
    }
    if(buttonBoard.GetRawButton(8)){
      if(gameData == "G"){
        // Checks green---------
        if(colorString == "Green" || haveHitColor == true){ 
          haveHitColor = true;
          if(seenColor == "blue"){
            barDrive->Set(ControlMode::PercentOutput, -.25);
          }
          else if(seenColor == "red"){
            barDrive->Set(ControlMode::PercentOutput, .25);
          }
          else if(seenColor == "yellow"){
            barDrive->Set(ControlMode::PercentOutput, 0);
          }
          else{
            haveHitColor = false;
          }
        }
        
        else{
          barDrive->Set(ControlMode::PercentOutput, -.75);
        }
      }

      else if (gameData == "R"){
        // Checks red---------
        if(colorString == "Red" || haveHitColor == true){ 
          haveHitColor = true;
          if(seenColor == "green"){
            barDrive->Set(ControlMode::PercentOutput, -.25);
          }
          else if(seenColor == "yellow"){
            barDrive->Set(ControlMode::PercentOutput, .25);
          }
          else if(seenColor == "blue"){
            barDrive->Set(ControlMode::PercentOutput, 0);
          }
          else{
            haveHitColor = false;
          }
        }
        else{
          barDrive->Set(ControlMode::PercentOutput, -.75);
        }
      }
      else if (gameData == "B"){
        // Checks blue---------
        if(colorString == "Blue" || haveHitColor == true){ 
          haveHitColor = true;
          if(seenColor == "yellow"){
            barDrive->Set(ControlMode::PercentOutput, -.25);
          }
          else if(seenColor == "green"){
            barDrive->Set(ControlMode::PercentOutput, .25);
          }
          else if(seenColor == "red"){
            barDrive->Set(ControlMode::PercentOutput, 0);
          }
          else{
            haveHitColor = false;
          }
        }
        else{
          barDrive->Set(ControlMode::PercentOutput, -.75);
        }
      }
      else if (gameData == "Y"){
        // Checks yellow---------
        if(colorString == "Yellow" || haveHitColor == true){ 
          haveHitColor = true;
          if(seenColor == "red"){
            barDrive->Set(ControlMode::PercentOutput, -.25);
          }
          else if(seenColor == "blue"){
            barDrive->Set(ControlMode::PercentOutput, .25);
          }
          else if(seenColor == "green"){
            barDrive->Set(ControlMode::PercentOutput, 0);
          }
          else{
            haveHitColor = false;
          }
        }
        else{
          barDrive->Set(ControlMode::PercentOutput, -.75);
        }
      }
    }
    else{
      barDrive->Set(ControlMode::PercentOutput, 0);
    }
    frc::SmartDashboard::PutString("Detected color", colorString);
    frc::SmartDashboard::PutString("Target color", gameData);
    //frc::SmartDashboard::PutNumber("time", T1.Get());
    /*if(T1.Get() == .15){
      T1.Reset();
      
      if(seenColor == "yellow" && isYellow == false){
        rotations += 1;
        isYellow = true;
      }
      else if(seenColor != "yellow" && isYellow == true){
        isYellow == false;
      }
    }
    if(rotations >= 8){
      frc::SmartDashboard::PutBoolean("rotations", true);
    }
    else{
      frc::SmartDashboard::PutBoolean("rotations", false);
    }
  }*/

  void Robot::Intake() {
    /*
    bool up = upSwitch.Get();
    bool down = downSwitch.Get();
    if(up == true){
      frc::SmartDashboard::PutString("Intake is", "UP");
    }
    else if(down == true){
      frc::SmartDashboard::PutString("Intake is", "DOWN");
    }
    else{
      frc::SmartDashboard::PutString("Intake is", "In Between");
    }
    

    // upSwitch = 1 when intake is up
    // downSwitch = 1 when intake is down

    if(buttonBoard.GetRawButton(1) == 1 && up == false){
      intakeMove->Set(ControlMode::PercentOutput, -.6);
    }
    else if(buttonBoard.GetRawButton(5) == 1 && down == false){
      intakeMove->Set(ControlMode::PercentOutput, .2);
    }
    else{
      intakeMove->Set(ControlMode::PercentOutput, 0);
    }
    */
    if(buttonBoard.GetRawButtonReleased(9)){  //Has intake button been pushed?
      if(buttonPressed == false){
        buttonPressed = true;
        if(isRun == false){
          isRun = true;
        }
        else{
          isRun = false;
        }
      }
      else{
        buttonPressed = false;
      } 
    }

    if(buttonBoard.GetRawButton(10) == false){ //over ride if going backward

      
      if(buttonPressed){
        intakeRun->Set(ControlMode::PercentOutput, -.8);
      }
      else{
        intakeRun->Set(ControlMode::PercentOutput, 0);
      }
      
      
    }
    else if(buttonBoard.GetRawButton(10)){
      intakeRun->Set(ControlMode::PercentOutput, 1);
    }
    
    
  }

  void Robot::Drive() {
    LBd = JLeft.GetY();
    RBd = JRight.GetY();

    if (buttonBoard.GetRawButton(10) == 0){

      //Left deadZone
      if (LBd > deadZone){
        Ld = ((LBd - deadZone) * (1 / (1 - deadZone)));
      }
      else if (LBd < - deadZone){
        Ld = ((LBd + deadZone) * (-1 / (-1 + deadZone)));
      }
      else{
        Ld = 0;
      }

      //Right deadZone
      if (RBd > deadZone){
        Rd = ((RBd - deadZone) * (1 / (1 - deadZone)));
      }
      else if (RBd < - deadZone){
        Rd = ((RBd + deadZone) * (-1 / (-1 + deadZone)));
      }
      else{
        Rd = 0;
      }
    }

    

    //Aiming-
    /*std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
    float tx = table->GetNumber("tx",0.0);
    //double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
    //double targetArea = table->GetNumber("ta",0.0);
    //double targetSkew = table->GetNumber("ts",0.0);

    if (buttonBoard.GetRawButton(10)){
      float heading_error = -tx;
      float steering_adjust = 0.0f;
      if (tx > 1.0){
              steering_adjust = Kp*heading_error - min_command;
      }
      else if (tx < 1.0){
              steering_adjust = Kp*heading_error + min_command;
      }
      Ld -= steering_adjust ;
      Rd += steering_adjust;
      frc::SmartDashboard::PutNumber("steering", steering_adjust);
      frc::SmartDashboard::PutNumber("tx", tx);
    }
    if(tx < .1 && tx > -.1){
      aimed = true;
    }
    else{
      aimed = false;
    }
    
    angleOfCameraFromTarget = targetOffsetAngle_Vertical;
    distanceFromTarget = 500; // (hightOfTarget - hightOfCamera) / tan(angleOfCamera + angleOfCameraFromTarget);

    frc::SmartDashboard::PutNumber("Distance From Target", distanceFromTarget); 
    */

    if(JLeft.GetRawButton(1) == 1){
      Ld = Ld;
    }
    else{
      Ld = Ld * .5;
    }
    if(JRight.GetRawButton(1) == 1){
      Rd = Rd;
    }
    else{
      Rd = Rd * .5;
    }

    if(JRight.GetRawButton(3) == 1 || JLeft.GetRawButton(3) == 1){
      if(straightStarted == false){
        straightVal = Rd;
        straightStarted = true;
      }
      else{
        m_left.Set(straightVal * -1);
        m_right.Set(straightVal);
      }
      

    }
    else{
      m_left.Set(Ld * -1);
      m_right.Set(Rd);
    }


    

  }

  void Robot::Shooter(){

    //////////////////////////////////////
    //    Code for accuracy challenge   //
    //////////////////////////////////////


    /*frc::SmartDashboard::PutBoolean("isFrontBack", isFrontBack);
    frc::SmartDashboard::PutBoolean("isMiddle", isMiddle);

    
    float speedFrontBack = frc::SmartDashboard::GetNumber("DB/Slider 0", 1.4E+4);
    float speedMid = frc::SmartDashboard::GetNumber("DB/Slider 1", 7E+3);
    float speedMidBack = frc::SmartDashboard::GetNumber("DB/Slider 2", 1.4E+4);


    if(buttonBoard.GetRawButton(3)){
      isFrontBack = true;
      isMiddle = false;
      isBackMiddle = false;
    }
    else if(buttonBoard.GetRawButton(7)){
      isFrontBack = false;
      isMiddle = true;
      isBackMiddle = false;
    }
    else if(buttonBoard.GetRawButton(8)){
      isFrontBack = false;
      isMiddle = false;
      isBackMiddle = true;
    }

    if(isFrontBack == true){
      shooterTargetSpeed = speedFrontBack;
    }
    else if(isMiddle == true){
      shooterTargetSpeed = speedMid;
    }
    else if(isBackMiddle == true){
      shooterTargetSpeed = speedMidBack;
    }
    */

    //shooterTargetSpeed = speed; //distanceFromTarget; // * some number;

    float shooterSlowSpeed = 7000;
    float shooterHighSpeed = 14000;
    float varShooterSpeed = JLeft.GetZ() * -1;
    float shooterNewMin = 6000;
    float shooterOldRange = (1 - 0);  // old max - old min
    float shooterNewRange = (shooterHighSpeed - shooterNewMin); // new max - new min

    if(buttonBoard.GetRawButton(1)){  // low speed
      shooterTargetSpeed = shooterSlowSpeed;
    }
    else if(buttonBoard.GetRawButton(5)){
      shooterTargetSpeed = shooterHighSpeed;
    }
    else if(buttonBoard.GetRawButton(8)){     
      shooterTargetSpeed = (((varShooterSpeed - 0) * shooterNewRange) / shooterOldRange) + shooterNewMin;
    }

    shooterActualSpeed = shoot1->GetSelectedSensorVelocity();
    shooterActualSpeed2 = shoot2->GetSelectedSensorVelocity();
    frc::SmartDashboard::PutNumber("Shooter Actual Speed", shooterActualSpeed);

    if(buttonBoard.GetRawButton(11)){
      shoot2->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
      shoot1->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
      shoot1->Set(ControlMode::Velocity, shooterTargetSpeed); 
      shoot2->Set(ControlMode::Velocity, shooterTargetSpeed * -1);
      ballUp->Set(ControlMode::PercentOutput, 1); 
      if(shooterActualSpeed < (shooterTargetSpeed + shooterdeadzone) && shooterActualSpeed > (shooterTargetSpeed - shooterdeadzone)){
        shooterIsRunning = true;
      }
      else{
        shooterIsRunning = false;
      }
    }
    else{
      shoot2->Config_kP(kPIDLoopIdx, 0.01, kTimeoutMs);
      shoot1->Config_kP(kPIDLoopIdx, 0.01, kTimeoutMs);
      shoot1->Set(ControlMode::Velocity, 0); 
      shoot2->Set(ControlMode::Velocity, 0); 
      ballUp->Set(ControlMode::PercentOutput, 0);
      shooterIsRunning = false;
    }
    frc::SmartDashboard::PutNumber("Shooter Target Speed", shooterTargetSpeed);
    if(shooterIsRunning == true){
      frc::SmartDashboard::PutBoolean("Shooter Is Shooting", true);
    }
    else{
      frc::SmartDashboard::PutBoolean("Shooter Is Shooting", false);
    }
  }

  void Robot::Climber(){
    bool goUp = buttonBoard.GetRawButton(2);
    bool goDown = buttonBoard.GetRawButton(6);

    
    if(goUp == 1){
      climber.Set(.5);  //pos += 10; //posUp;
    }
    else if(goDown == 1){
    
      climber.Set(-.5); //pos -= 1; //posDown;
    }
    else
    {
      climber.Set(0);
    }
    
   

    if(buttonBoard.GetRawButton(3)){
      barDrive->Set(ControlMode::PercentOutput, -1);
    }
    else if(buttonBoard.GetRawButton(7)){
      barDrive->Set(ControlMode::PercentOutput, 1);
    }
    else{
      barDrive->Set(ControlMode::PercentOutput, 0);
    }

    //climbPID.SetReference(pos, rev::ControlType::kPosition);
    
    //climber.Set(testJ.GetY());

  }

  void Robot::Index(){
    
    if(buttonBoard.GetRawButtonPressed(4)){
      T2.Reset();
      indexShift = true;
    }
    
    
    if (indexShift == true) {
      
      if(indexClick.Get() && T2.Get() > .5){
        indexShift = false;
      }
      else{
        index->Set(ControlMode::PercentOutput, -.4f); 
      }
    }  
    else if (buttonBoard.GetRawButton(11) == true){
      index->Set(ControlMode::PercentOutput, -.3); 
    } 
    else if (JLeft.GetRawButton(7)){
      index->Set(ControlMode::PercentOutput, .3);  //reverse
    }
    else{
      index->Set(ControlMode::PercentOutput, 0); // 0
    }
  }

  void Robot::LED(){
    
    if(aimed == true){
      LEDcontrol.Set(-0.91);
      frc::SmartDashboard::PutBoolean("Aimed", true);
    }
    else{
      LEDcontrol.Set(-0.79);
      frc::SmartDashboard::PutBoolean("Aimed", false);
    }

  }

  

void Robot::TestPeriodic() {
  
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
