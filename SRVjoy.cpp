/*
 * SRVjoy.cpp
 *
 *  Created on: Aug 18, 2009
 *
 *  SRVjoy for Player/Stage - One Hell of a Robot Server
 *
 *  Copyleft (>) 2009 -
 *      Carlos Jaramillo (ubuntuslave@gmail.com)
 *  Supervised by Professor Elizabeth Sklar from Brooklyn College, CUNY
 *  Research experience funded by DREU Summer 2009
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc., 51
 *  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <QtGui>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include "SRVjoy.h"

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

//   m_LinearSpeedLabel = new QLabel(tr("Linear &Speed:"));
   m_LinearSpeedLabel = new QLabel(tr("L\ni\nn\ne\na\nr\n\nS\np\ne\ne\nd"));
   m_LinearSpeedLabel->setAlignment(Qt::AlignCenter);
   m_AngularSpeedLabel = new QLabel(tr("Angular Speed"));
   m_AngularSpeedLabel->setAlignment(Qt::AlignCenter);

//    lineEdit = new QLineEdit;
//    label->setBuddy(lineEdit);

   // Initialize Control Buttons:
   int nIconSquareSize = 48;  // pixels

   m_ForwardLeftButton = new QToolButton(this);
//   m_ForwardLeftButton->adjustSize();
   m_ForwardLeftButton->setIcon(QIcon(":/images/buttons/fwdleft.png"));
   m_ForwardLeftButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_ForwardButton = new QToolButton(this);
   m_ForwardButton->setIcon(QIcon(":/images/buttons/forward.png"));
   m_ForwardButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_ForwardRightButton = new QToolButton(this);
   m_ForwardRightButton->setIcon(QIcon(":/images/buttons/fwdright.png"));
   m_ForwardRightButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_TurnLeftButton = new QToolButton(this);
   m_TurnLeftButton->setIcon(QIcon(":/images/buttons/ccw.png"));
   m_TurnLeftButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_CameraSnapshotButton = new QToolButton(this);
   m_CameraSnapshotButton->setIcon(QIcon(":/images/buttons/camera-photo.png"));
   m_CameraSnapshotButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_TurnRightButton = new QToolButton(this);
   m_TurnRightButton->setIcon(QIcon(":/images/buttons/cw.png"));
   m_TurnRightButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_BackwardLeftButton = new QToolButton(this);
   m_BackwardLeftButton->setIcon(QIcon(":/images/buttons/backleft.png"));
   m_BackwardLeftButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_BackwardButton = new QToolButton(this);
   m_BackwardButton->setIcon(QIcon(":/images/buttons/backward.png"));
   m_BackwardButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   m_BackwardRightButton = new QToolButton(this);
   m_BackwardRightButton->setIcon(QIcon(":/images/buttons/backright.png"));
   m_BackwardRightButton->setIconSize(QSize(nIconSquareSize,nIconSquareSize));

   enableButtons(false);   // Start with disabled Joystick buttons

   // Speed Control Sliders
   m_LinearSpeedSlider = new QSlider(Qt::Vertical);
   m_LinearSpeedSlider->setRange(abs(m_dMinSpeed*100),abs(m_dMaxSpeed*100));  // 100x scale

   m_AngularSpeedSlider = new QSlider(Qt::Horizontal);
   m_AngularSpeedSlider->setRange(0,abs(m_nMaxTurnRateDegrees)); // 1x scale

   // Layouts:
   layoutConnect = new QHBoxLayout;
   layoutConnect->addWidget(m_ConnectButton);

   layoutJoystick = new QGridLayout;
   layoutJoystick->setSpacing(0);
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
   layoutJoystick->addWidget(m_AngularSpeedSlider, 3, 0, 1, 3); // spans 3 columns
   layoutJoystick->addWidget(m_LinearSpeedLabel, 0, 4, 3, 1); // spans 3 rows
   layoutJoystick->addWidget(m_AngularSpeedLabel, 4, 0, 1, 3); // spans 3 columns

   centralLayout = new QVBoxLayout;
   centralLayout->addLayout(layoutConnect);
   centralLayout->addLayout(layoutJoystick);
   centralLayout->setStretchFactor(layoutJoystick,2);
    setLayout(centralLayout);

    setWindowTitle(tr("SRVjoy Console (Player/Stage)"));
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

         // Setup speed values to send them to the robot.
         // speed.px is speed in the x direction
         // speed.py is speed in the y direction
         // speed.pa is rotational speed.
         m_Speed2D.px = 0.10;  // Start at 0.10 meters per second

         // Default Speeds to begin with:
         setAngularSpeedInDegrees(90.0);   // Start with 90 degrees per second

         // Set m_LinearSpeedSlider to the current speed:
         m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_Speed2D.px));
         connect(m_LinearSpeedSlider, SIGNAL(valueChanged(int)),
               this, SLOT(setLinearSpeed(int)));

         // Set m_AngularSpeedSlider to the current speed:
         m_AngularSpeedSlider->setValue(abs(m_nTurnRateDegrees));
         connect(m_AngularSpeedSlider, SIGNAL(valueChanged(int)),
               this, SLOT(setAngularSpeedInDegrees(int)));

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
               this, SLOT(rotateCCW()));
         connect(m_TurnLeftButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         connect(m_TurnRightButton, SIGNAL(pressed()),
               this, SLOT(rotateCW()));
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
// COMMENT this try/catch block when NOT Using CAMERA interface:
      try        // to create camera proxy
      {
         // Read configuration file if camera interface is provided:
               // MISSING implementation
         m_pRobot->ReadIfWaiting();  // A nonblocking Read

         m_pCameraProxy = new CameraProxy(m_pRobot, gIndex);
         connect(m_CameraSnapshotButton, SIGNAL(clicked()),
               this, SLOT(takePictureShot()));
      }
      catch (PlayerCc::PlayerError e)
      {
         std::cerr << e << std::endl;
         m_CameraSnapshotButton->setEnabled(false);   // Disable camera button(s)
         return;
      }
// finish COMMENT here

   }
}

void SRVjoy::enableButtons(bool enabled)
{
   //Buttons:
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
      if(m_Speed2D.px < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      m_pPos2dProxy->SetSpeed(m_Speed2D.px, 0.0);

      m_nCurrentMove = FORWARD;

      printf("\nMoving Forward at %f m/sec\n", m_Speed2D.px);

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
      if(m_Speed2D.px < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      if(m_nTurnRateDegrees < 0)   // To turn left, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_Speed2D);

      m_nCurrentMove = FORWARD_LEFT;

      printf("\nMoving Forward-Left at %f m/sec and %i deg/sec\n", m_Speed2D.px, m_nTurnRateDegrees);
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
      if(m_Speed2D.px < 0.0)   // Use a positive value
         {
         reverseSpeed();
         }

      if(m_nTurnRateDegrees > 0)   // To turn right, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_Speed2D);

      m_nCurrentMove = FORWARD_RIGHT;

      printf("\nMoving Forward-Right at %f m/sec and %i deg/sec\n", m_Speed2D.px, m_nTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::rotateCCW()
{
   try
   {
      if(m_nTurnRateDegrees < 0)   // To turn left, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(0.0, m_Speed2D.pa);

      m_nCurrentMove = ROTATE_CCW;

      printf("\nTurning Left at %i deg/sec\n", m_nTurnRateDegrees);
   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      enableButtons(false);   // Disable buttons
      return;
   }
}

void SRVjoy::rotateCW()
{
   try
   {
      if(m_nTurnRateDegrees > 0)   // To turn right, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(0.0, m_Speed2D.pa);

      m_nCurrentMove = ROTATE_CW;

      printf("\nTurning Right at %i deg/sec\n", m_nTurnRateDegrees);
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
      if(m_Speed2D.px > 0.0)   // Use a negative value
      {
         reverseSpeed();
      }

      m_pPos2dProxy->SetSpeed(m_Speed2D.px, 0.0);
      m_nCurrentMove = BACK;
      printf("\nMoving Backward at %f m/sec\n", m_Speed2D.px);
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
      if(m_Speed2D.px > 0.0)   // Use a negative value
         {
         reverseSpeed();
         }
      if(m_nTurnRateDegrees > 0)   // To turn back-left, turn rate must be a negative value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_Speed2D);
      m_nCurrentMove = BACK_LEFT;
      printf("\nMoving Backward-Left at %f m/sec and %i deg/sec\n", m_Speed2D.px, m_nTurnRateDegrees);
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
      if(m_Speed2D.px > 0.0)   // Use a negative value
         {
         reverseSpeed();
         }

      if(m_nTurnRateDegrees < 0)   // To turn back-right, turn rate must be a positive value
         {
         reverseTurnRate();
         }

      m_pPos2dProxy->SetSpeed(m_Speed2D);
      m_nCurrentMove = BACK_RIGHT;
      printf("\nMoving Backward-Right at %f m/sec and %i deg/sec\n", m_Speed2D.px, m_nTurnRateDegrees);
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
      m_nCurrentMove = STOP;
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
   m_Speed2D.px = (double)(nSpeed/100.0);
}

void SRVjoy::setAngularSpeedInDegrees(int nDegrees)
{
   m_nTurnRateDegrees = nDegrees;
   m_Speed2D.pa = DTOR(m_nTurnRateDegrees);
}

void SRVjoy::takePictureShot()
{
   try
    {
      m_pRobot->Read();  // A blocking Read
         m_pCameraProxy->SaveFrame("camera");
         std::cout << (*m_pCameraProxy) << std::endl;
    }
   catch (PlayerCc::PlayerError e)
    {
       std::cerr << e << std::endl;
       enableButtons(false);   // Disable buttons
       return;
    }

}

//^^^^^^^^^^^^^^^^^^^ finish SLOTs ^^^^^^^^^^^^^^^^^^^^^^^

//vvvvvvvvvvvv FINISH Re-implemented Event Handlers vvvvvvvvvvvvvvvvv

void SRVjoy::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
       if (event->modifiers() & Qt::ControlModifier) {
          increaseAngularSpeed();
       } else {
          increaseLinearSpeed();
       }
        break;
    case Qt::Key_Minus:
       if (event->modifiers() & Qt::ControlModifier) {
          decreaseAngularSpeed();
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
       rotateCCW();
        break;
    case Qt::Key_5:
       takePictureShot();
        break;
    case Qt::Key_6:
       rotateCW();
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
       rotateCCW();
        break;
    case Qt::Key_K:
       takePictureShot();
        break;
    case Qt::Key_L:
       rotateCW();
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
void SRVjoy::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
     case Qt::Key_1:
        stopMoving();
        break;
    case Qt::Key_2:
       stopMoving();
       break;
    case Qt::Key_3:
       stopMoving();
        break;
    case Qt::Key_4:
       stopMoving();
        break;
    case Qt::Key_6:
       stopMoving();
       break;
    case Qt::Key_7:
       stopMoving();
        break;
    case Qt::Key_8:
       stopMoving();
        break;
    case Qt::Key_9:
       stopMoving();
        break;
    case Qt::Key_M:
       stopMoving();
        break;
    case Qt::Key_Comma:
       stopMoving();
       break;
    case Qt::Key_Period:
       stopMoving();
        break;
    case Qt::Key_J:
       stopMoving();
        break;
    case Qt::Key_L:
       stopMoving();
        break;
    case Qt::Key_U:
       stopMoving();
        break;
    case Qt::Key_I:
       stopMoving();
        break;
    case Qt::Key_O:
       stopMoving();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

//bool SRVjoy::eventFilter(QObject* obj, QEvent* event)
//{
//   if(event->spontaneous())
//      {
//      if(event->type()==QEvent::KeyPress)
//         printf("key pressed");
//
//      if(event->type()==QEvent::KeyRelease)
//         printf("key released");
//      }
//   return QObject::eventFilter(obj,event);
//}



//^^^^^^^^^^^^^^^^ FINISH Re-implemented Event Handlers ^^^^^^^^^^^^^^^^^^^^^^^

void SRVjoy::increaseAngularSpeed()
{
   m_nTurnRateDegrees = abs(m_nTurnRateDegrees);
   if( m_nTurnRateDegrees <= m_nMaxTurnRateDegrees )
      {
      setAngularSpeedInDegrees(m_nTurnRateDegrees+30);   // Increase Turn Rate by 30 degrees/sec
      m_AngularSpeedSlider->setValue(m_nTurnRateDegrees);
      refreshCurrentMove();
      }
}

void SRVjoy::decreaseAngularSpeed()
{
   m_nTurnRateDegrees = abs(m_nTurnRateDegrees);

   if( m_nTurnRateDegrees >= 30 )
      {
      setAngularSpeedInDegrees(m_nTurnRateDegrees-30);   // Decrease Turn Rate by 30 degrees/sec
      m_AngularSpeedSlider->setValue(m_nTurnRateDegrees);
      }
   else{
      setAngularSpeedInDegrees(0);   // Turn Rate has reached 0 degrees/sec
      m_AngularSpeedSlider->setValue(m_nTurnRateDegrees);
   }

   refreshCurrentMove();

}

void SRVjoy::reverseTurnRate()
{
   setAngularSpeedInDegrees(m_nTurnRateDegrees * (-1));
}

void SRVjoy::increaseLinearSpeed()
{
   if( fabs(m_Speed2D.px) <= m_dMaxSpeed )
      {
      m_Speed2D.px = m_Speed2D.px * 1.10;    // Increase linear speed by 10%
      refreshCurrentMove();
      m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_Speed2D.px));
      }
}

void SRVjoy::decreaseLinearSpeed()
{
   if( fabs(m_Speed2D.px) >= m_dMinSpeed )
      {
      m_Speed2D.px = m_Speed2D.px * 0.90;    // Decrease linear speed by 10%
      refreshCurrentMove();
      m_LinearSpeedSlider->setValue(normalizeSliderSpeed(m_Speed2D.px));
      }
}

void SRVjoy::reverseSpeed()
{
   m_Speed2D.px = m_Speed2D.px * (-1.0);
}

int SRVjoy::normalizeSliderSpeed(double dSpeed)
{
   printf("\nNormalized Speed is %i", abs(100*dSpeed));
   return abs(100*dSpeed);
}

void SRVjoy::refreshCurrentMove()
{
   switch (m_nCurrentMove) {
      case STOP:
         stopMoving();
         break;
      case BACK_LEFT:
         moveBackwardLeft();
         break;
      case BACK:
         moveBackward();
         break;
      case BACK_RIGHT:
         moveBackwardRight();
         break;
      case ROTATE_CCW:
         rotateCCW();
         break;
      case ROTATE_CW:
         rotateCW();
         break;
      case FORWARD_LEFT:
         moveForwardLeft();
         break;
      case FORWARD:
         moveForward();
         break;
      case FORWARD_RIGHT:
         moveForwardRight();
         break;
      default:
         stopMoving();
   }
}

