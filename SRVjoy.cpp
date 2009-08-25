/*
 * SRVjoy.cpp
 *
 *  Created on: Aug 18, 2009
 *      Author: carlos
 */

#include <QtGui>


#include "SRVjoy.h"
#include <iostream>
//#include <errno.h>
//#include <assert.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <sys/ioctl.h>
//#include <termios.h>
//#include <math.h>
#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <sys/time.h>
//#include <time.h>
//#include <string.h>

using namespace PlayerCc;

SRVjoy::SRVjoy(QWidget *parent)
    : QWidget(parent)
{
   createActions();
}

void SRVjoy::createActions()
{
   m_bConnected = false;   // Robot is not connected yet

   m_ConnectButton = new QPushButton(tr("&Connect"));
   m_ConnectButton->setDefault(true);
   m_ConnectButton->setEnabled(true);
   connect(m_ConnectButton, SIGNAL(pressed()),
           this, SLOT(connectToRobot()));

   m_Label = new QLabel(tr("Linear &Speed:"));
//    lineEdit = new QLineEdit;
//    label->setBuddy(lineEdit);

   // Initialize Control Buttons:

   m_ForwardLeftButton = new QToolButton(this);
//   m_ForwardLeftButton->adjustSize();
   m_ForwardLeftButton->setIcon(QIcon(":/images/buttons/fwdleft.png"));

   m_ForwardButton = new QToolButton(this);
   m_ForwardButton->setIcon(QIcon(":/images/buttons/forward.png"));

   m_ForwardRightButton = new QToolButton(this);
   m_ForwardRightButton->setIcon(QIcon(":/images/buttons/fwdright.png"));

   m_TurnLeftButton = new QToolButton(this);
   m_TurnLeftButton->setIcon(QIcon(":/images/buttons/ccw.png"));

   m_CameraSnapshotButton = new QToolButton(this);
   m_CameraSnapshotButton->setIcon(QIcon(":/images/buttons/camera-photo.png"));

   m_TurnRightButton = new QToolButton(this);
   m_TurnRightButton->setIcon(QIcon(":/images/buttons/cw.png"));

   m_BackwardLeftButton = new QToolButton(this);
   m_BackwardLeftButton->setIcon(QIcon(":/images/buttons/backleft.png"));

   m_BackwardButton = new QToolButton(this);
   m_BackwardButton->setIcon(QIcon(":/images/buttons/backward.png"));

   m_BackwardRightButton = new QToolButton(this);
   m_BackwardRightButton->setIcon(QIcon(":/images/buttons/backright.png"));

   enableButtons(false);   // Start with disabled Joystick buttons

   // Speed Control Sliders
   m_LinearSpeedSlider = new QSlider(Qt::Vertical);
   m_LinearSpeedSlider->setRange(5, 50);  // To be use with values from 0.05 to 0.50

   // Layouts:
   layoutConnect = new QHBoxLayout;
   layoutConnect->addWidget(m_ConnectButton);

   layoutJoystick = new QGridLayout;
   layoutJoystick->addWidget(m_ForwardLeftButton, 0, 0);
   layoutJoystick->addWidget(m_ForwardButton, 0, 1);
   layoutJoystick->addWidget(m_ForwardRightButton, 0, 2);
   layoutJoystick->addWidget(m_TurnLeftButton, 1, 0);
   layoutJoystick->addWidget(m_CameraSnapshotButton, 1, 1);
   layoutJoystick->addWidget(m_TurnRightButton, 1, 2);
   layoutJoystick->addWidget(m_BackwardLeftButton, 2, 0);
   layoutJoystick->addWidget(m_BackwardButton, 2, 1);
   layoutJoystick->addWidget(m_BackwardRightButton, 2, 2);
   layoutJoystick->addWidget(m_LinearSpeedSlider, 0, 3, 3, 1); // spans 3 rows

   centralLayout = new QVBoxLayout;
   centralLayout->addLayout(layoutConnect);
   centralLayout->addLayout(layoutJoystick);
   centralLayout->setStretchFactor(layoutJoystick,2);
    setLayout(centralLayout);

    setWindowTitle(tr("Surveyor GUI (Player/Stage)"));
    setFixedHeight(sizeHint().height());
    setWindowIcon(QIcon(":player_icon"));
}

void SRVjoy::connectToRobot()
{
   if(!m_bConnected)
      {
      try
      {
         // Create Robot
//         m_pRobot = new PlayerClient("localhost");
         m_pRobot = new PlayerClient(gHostname, gPort);
         std::cout << "\nDone Creating robot as PlayerClient\n";

         // Create Position2D Proxy
         m_pPos2dProxy = new Position2dProxy(m_pRobot,0);
         m_pPos2dProxy->SetMotorEnable(true);

         // Default Speeds to begin with:
         setTurnrateInDegrees(90.0);   // Start with 90 degrees per second
         m_dSpeed = 0.10;  // Start at 0.10 meters per second


         // Set m_LinearSpeedSlider to the current speed:
         m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_dSpeed));
         connect(m_LinearSpeedSlider, SIGNAL(valueChanged(int)),
               this, SLOT(setLinearSpeed(int)));

         // Joystick buttons Signal/Slot connections:

         connect(m_ForwardLeftButton, SIGNAL(pressed()),
               this, SLOT(moveForwardLeft()));
         connect(m_ForwardLeftButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_ForwardButton, SIGNAL(pressed()),
               this, SLOT(moveForward()));
         connect(m_ForwardButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_ForwardRightButton, SIGNAL(pressed()),
               this, SLOT(moveForwardRight()));
         connect(m_ForwardRightButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_TurnLeftButton, SIGNAL(pressed()),
               this, SLOT(turnLeft()));
         connect(m_TurnLeftButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_TurnRightButton, SIGNAL(pressed()),
               this, SLOT(turnRight()));
         connect(m_TurnRightButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_BackwardLeftButton, SIGNAL(pressed()),
               this, SLOT(moveBackwardLeft()));
         connect(m_BackwardLeftButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_BackwardButton, SIGNAL(pressed()),
               this, SLOT(moveBackward()));
         connect(m_BackwardButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_BackwardRightButton, SIGNAL(pressed()),
               this, SLOT(moveBackwardRight()));
         connect(m_BackwardRightButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         enableButtons(true);   // Enable buttons

         m_bConnected = true;
         m_ConnectButton->setEnabled(false); // Disable ConnectButton when already connected
      }
      catch (PlayerCc::PlayerError e)
      {
         std::cerr << e << std::endl;
         enableButtons(false);   // Disable buttons
         return;
      }
/*// COMMENT this try/catch block when NOT Using CAMERA interface:
      try        // to create camera proxy
      {
         // Read configuration file if camera interface is provided:
               // MISSING implementation
         m_pCameraProxy = new CameraProxy(m_pRobot, gIndex);
         connect(m_CameraSnapshotButton, SIGNAL(released()),
               this, SLOT(takePictureShot()));
      }
      catch (PlayerCc::PlayerError e)
      {
         std::cerr << e << std::endl;
         m_CameraSnapshotButton->setEnabled(false);   // Disable camera button(s)
         return;
      }
*/
   }
}

void SRVjoy::enableButtons(bool enabled)
{
   m_ForwardLeftButton->setEnabled(enabled);
   m_ForwardButton->setEnabled(enabled);
   m_ForwardRightButton->setEnabled(enabled);
   m_TurnLeftButton->setEnabled(enabled);
   m_CameraSnapshotButton->setEnabled(enabled);
   m_TurnRightButton->setEnabled(enabled);
   m_BackwardLeftButton->setEnabled(enabled);
   m_BackwardButton->setEnabled(enabled);
   m_BackwardButton->setEnabled(enabled);
   m_BackwardRightButton->setEnabled(enabled);
}

//vvvvvvvvvvvvvvvvvv begin SLOTs vvvvvvvvvvvvvvvvvvvvvv

void SRVjoy::moveForward()
{
   try
   {
      if(m_dSpeed < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      m_pPos2dProxy->SetSpeed(m_dSpeed, 0.0);

      printf("\nMoving Forward at %f m/sec\n", m_dSpeed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::moveForwardLeft()
{
   try
   {
      if(m_dSpeed < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      if(m_dTurnRateDegrees < 0.0)   // To turn left, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnRateRadians);

      printf("\nMoving Forward-Left at %f m/sec and %f deg/sec\n", m_dSpeed, m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::moveForwardRight()
{
   try
   {
      if(m_dSpeed < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      if(m_dTurnRateDegrees > 0.0)   // To turn right, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnRateRadians);

      printf("\nMoving Forward-Right at %f m/sec and %f deg/sec\n", m_dSpeed, m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::turnLeft()
{
   try
   {
      if(m_dTurnRateDegrees < 0.0)   // To turn left, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(0.0, m_dTurnRateRadians);

      printf("\nTurning Left at %f deg/sec\n", m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::turnRight()
{
   try
   {
      if(m_dTurnRateDegrees > 0.0)   // To turn right, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(0.0, m_dTurnRateRadians);

      printf("\nTurning Right at %f deg/sec\n", m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::moveBackward()
{
   try
   {
      if(m_dSpeed > 0.0)   // Use a negative value
      {
         reverseSpeed();
      }

      m_pPos2dProxy->SetSpeed(m_dSpeed, 0.0);
      printf("\nMoving Backward at %f m/sec\n", m_dSpeed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::moveBackwardLeft()
{
   try
   {
      if(m_dSpeed > 0.0)   // Use a negative value
         {
         reverseSpeed();
         }
      if(m_dTurnRateDegrees > 0.0)   // To turn back-left, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnRateRadians);

      printf("\nMoving Backward-Left at %f m/sec and %f deg/sec\n", m_dSpeed, m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::moveBackwardRight()
{
   try
   {
      if(m_dSpeed > 0.0)   // Use a negative value
         {
         reverseSpeed();
         }

      if(m_dTurnRateDegrees < 0.0)   // To turn back-right, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnRateRadians);

      printf("\nMoving Backward-Right at %f m/sec and %f deg/sec\n", m_dSpeed, m_dTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::stopMoving()
{
   try
   {
      m_pPos2dProxy->SetSpeed(0.0, 0.0);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::setLinearSpeed(int nSpeed)
{
   m_dSpeed = (double)(nSpeed/100.0);
}

void SRVjoy::takePictureShot()
{
   try
    {
      m_pRobot->Read();
      for(int i=0; i<1; i++)
         {
         m_pRobot->Read(); // It is BUGGY, because for some weird reason
                           // the previous frame appears, or doesn't get flushed
         m_pCameraProxy->SaveFrame("camera");
         std::cout << (*m_pCameraProxy) << std::endl;
         printf("\nTaking Picture\n");
         }
    }
   catch (PlayerCc::PlayerError e)
    {
       std::cerr << e << std::endl;
       enableButtons(false);   // Disable buttons
       return;
    }

}

//^^^^^^^^^^^^^^^^^^^ finish SLOTs ^^^^^^^^^^^^^^^^^^^^^^^

void SRVjoy::keyPressEvent(QKeyEvent *event)
{
   // +/- : increase/decrease only linear speed by 10%
    switch (event->key()) {
    case Qt::Key_Plus:
       if (event->modifiers() & Qt::ControlModifier) {
          increaseTurnRate();
       } else {
          increaseLinearSpeed();
       }
        break;
    case Qt::Key_Minus:
       if (event->modifiers() & Qt::ControlModifier) {
          decreaseTurnRate();
       } else {
          decreaseLinearSpeed();
       }
        break;
    case Qt::Key_Control:
       // Just make this an empty case to avoid Stopping when the "Ctrl" key is pressed
       break;
    case Qt::Key_1:
       moveBackwardLeft();
        break;
    case Qt::Key_2:
       moveBackward();
       break;
    case Qt::Key_3:
       moveBackwardRight();
        break;
    case Qt::Key_4:
       turnLeft();
        break;
    case Qt::Key_5:
       takePictureShot();
        break;
    case Qt::Key_6:
       turnRight();
        break;
    case Qt::Key_7:
       moveForwardLeft();
        break;
    case Qt::Key_8:
       moveForward();
        break;
    case Qt::Key_9:
       moveForwardRight();
        break;
    case Qt::Key_M:
       moveBackwardLeft();
        break;
    case Qt::Key_Comma:
       moveBackward();
       break;
    case Qt::Key_Period:
       moveBackwardRight();
        break;
    case Qt::Key_J:
       turnLeft();
        break;
    case Qt::Key_K:
       takePictureShot();
        break;
    case Qt::Key_L:
       turnRight();
        break;
    case Qt::Key_U:
       moveForwardLeft();
        break;
    case Qt::Key_I:
       moveForward();
        break;
    case Qt::Key_O:
       moveForwardRight();
        break;
    default:
        stopMoving();
        QWidget::keyPressEvent(event);
    }
}

void SRVjoy::setTurnrateInDegrees(double dDegrees)
{
   m_dTurnRateDegrees = dDegrees;
   m_dTurnRateRadians = DTOR(m_dTurnRateDegrees);
}

void SRVjoy::increaseTurnRate()
{
   m_dTurnRateDegrees = fabs(m_dTurnRateDegrees);
   if( m_dTurnRateDegrees <= m_dMaxTurnRateDegrees )
      {
      m_dTurnRateDegrees = m_dTurnRateDegrees + 30.0; // Increase Turn Rate by 30 degrees
      setTurnrateInDegrees(m_dTurnRateDegrees);
      }
}

void SRVjoy::decreaseTurnRate()
{
   m_dTurnRateDegrees = fabs(m_dTurnRateDegrees);

   if( m_dTurnRateDegrees >= 30 )
      {
      m_dTurnRateDegrees = m_dTurnRateDegrees - 30.0;    // Decrease Turn Rate by 30 degrees
      setTurnrateInDegrees(m_dTurnRateDegrees);
      }
}

void SRVjoy::reverseTurnRate()
{
   m_dTurnRateDegrees = m_dTurnRateDegrees * (-1.0);
   setTurnrateInDegrees(m_dTurnRateDegrees);
   }

void SRVjoy::increaseLinearSpeed()
{
   if( fabs(m_dSpeed) <= m_dMaxSpeed )
      {
      m_dSpeed = m_dSpeed * 1.10;    // Increase linear speed by 10%

      m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_dSpeed));
      }
}

void SRVjoy::decreaseLinearSpeed()
{
   if( fabs(m_dSpeed) >= m_dMinSpeed )
      {
      m_dSpeed = m_dSpeed * 0.90;    // Decrease linear speed by 10%

      m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_dSpeed));
      }
}

void SRVjoy::reverseSpeed()
{
   m_dSpeed = m_dSpeed * (-1.0);
}

int SRVjoy::normalizeSliderSpeed(double dSpeed)
{
   return abs(100*dSpeed);
}

