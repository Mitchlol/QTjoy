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

   m_FordwardButton = new QToolButton(this);
   m_FordwardButton->adjustSize();
   m_FordwardButton->setEnabled(false);
   m_FordwardButton->setIcon(QIcon(":/images/buttons/forward.png"));

   m_BackwardButton = new QToolButton(this);
   m_FordwardButton->adjustSize();
   m_BackwardButton->setEnabled(false);
   m_BackwardButton->setIcon(QIcon(":/images/buttons/back.png"));

      // Layouts:
   layoutConnect = new QHBoxLayout;
   layoutConnect->addWidget(m_ConnectButton);

   layoutJoystick = new QGridLayout;
   layoutJoystick->setColumnStretch(1,10);
   layoutJoystick->addWidget(m_FordwardButton);
   layoutJoystick->addWidget(m_BackwardButton);

   centralLayout = new QVBoxLayout;
   centralLayout->addLayout(layoutConnect);
   centralLayout->addLayout(layoutJoystick);

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
         m_pRobot = new PlayerClient("localhost");
         std::cout << "\nDone Creating robot as PlayerClient\n";
         //      PlayerClient    robot(gHostname, gPort);
         m_pPos2dProxy = new Position2dProxy(m_pRobot,0);
         m_pPos2dProxy->SetMotorEnable(true);

         m_dTurnrate = 0.0; // turn ? degrees per second
         m_dSpeed = 0.0;

         m_FordwardButton->setEnabled(true);
         m_BackwardButton->setEnabled(true);

         connect(m_FordwardButton, SIGNAL(pressed()),
               this, SLOT(moveForward()));
         connect(m_FordwardButton, SIGNAL(released()),
               this, SLOT(stopMoving()));
         connect(m_BackwardButton, SIGNAL(pressed()),
               this, SLOT(moveBackward()));
         connect(m_BackwardButton, SIGNAL(released()),
               this, SLOT(stopMoving()));

         m_bConnected = true;
         m_ConnectButton->setEnabled(false); // Disable ConnectButton when already connected
      }
      catch (PlayerCc::PlayerError e)
      {
         std::cerr << e << std::endl;
         m_FordwardButton->setEnabled(false);
         m_BackwardButton->setEnabled(false);
         return;
      }
  }
}
void SRVjoy::moveForward()
{
   try
   {
      m_dTurnrate = 0.0; // turn ? degrees per second
      m_dSpeed=0.50;

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnrate);
      printf("\nMoving Forward at %f m/sec\n", m_dSpeed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      m_FordwardButton->setEnabled(false);
      m_BackwardButton->setEnabled(false);

      return;
   }
}

void SRVjoy::stopMoving()
{
   try
   {
      m_dTurnrate = 0.0; // turn ? degrees per second
      m_dSpeed=0.0;

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnrate);
      printf("\nMoving Forward at %f m/sec\n", m_dSpeed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      m_FordwardButton->setEnabled(false);
      m_BackwardButton->setEnabled(false);

      return;
   }
}

void SRVjoy::moveBackward()
{
   try
   {
      m_dTurnrate = 0.0; // turn ? degrees per second
      m_dSpeed=-0.50;

      m_pPos2dProxy->SetSpeed(m_dSpeed, m_dTurnrate);
      printf("\nMoving Forward at %f m/sec\n", m_dSpeed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      m_FordwardButton->setEnabled(false);
      m_BackwardButton->setEnabled(false);

      return;
   }
}
