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
   m_Label = new QLabel(tr("Linear &Speed:"));
//    lineEdit = new QLineEdit;
//    label->setBuddy(lineEdit);

   m_FordwardButton = new QPushButton(tr("&Forward"));
   m_FordwardButton->setDefault(true);
   m_FordwardButton->setEnabled(true);

   m_BackwardButton = new QPushButton(tr("&Backward"));
   m_BackwardButton->setDefault(false);
   m_BackwardButton->setEnabled(true);

   try
         {
        m_pRobot = new PlayerClient("localhost");
           std::cout << "\nDone Creating robot as PlayerClient\n";
     //      PlayerClient    robot(gHostname, gPort);
           m_pPos2dProxy = new Position2dProxy(m_pRobot,0);
           m_pPos2dProxy->SetMotorEnable(true);

           m_turnrate = 0.0; // turn ? degrees per second
           m_speed = 0.0;

         }
         catch (PlayerCc::PlayerError e)
         {
           std::cerr << e << std::endl;
           m_FordwardButton->setEnabled(false);
           m_BackwardButton->setEnabled(false);
           return;
         }


    connect(m_FordwardButton, SIGNAL(pressed()),
            this, SLOT(moveForward()));
    connect(m_FordwardButton, SIGNAL(released()),
            this, SLOT(stopMoving()));
    connect(m_BackwardButton, SIGNAL(pressed()),
            this, SLOT(moveBackward()));
    connect(m_BackwardButton, SIGNAL(released()),
            this, SLOT(stopMoving()));


    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_FordwardButton);
    centralLayout->addWidget(m_BackwardButton);

//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addLayout(leftLayout);
//    mainLayout->addLayout(rightLayout);
    setLayout(centralLayout);

    setWindowTitle(tr("Surveyor GUI (Player/Stage)"));
    setFixedHeight(sizeHint().height());

}

void SRVjoy::moveForward()
{
   try
   {
      m_turnrate = 0.0; // turn ? degrees per second
      m_speed=0.50;

      m_pPos2dProxy->SetSpeed(m_speed, m_turnrate);
      printf("\nMoving Forward at %f m/sec\n", m_speed);

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
      m_turnrate = 0.0; // turn ? degrees per second
      m_speed=0.0;

      m_pPos2dProxy->SetSpeed(m_speed, m_turnrate);
      printf("\nMoving Forward at %f m/sec\n", m_speed);

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
      m_turnrate = 0.0; // turn ? degrees per second
      m_speed=-0.50;

      m_pPos2dProxy->SetSpeed(m_speed, m_turnrate);
      printf("\nMoving Forward at %f m/sec\n", m_speed);

   }
   catch (PlayerCc::PlayerError e)
   {
      std::cerr << e << std::endl;
      m_FordwardButton->setEnabled(false);
      m_BackwardButton->setEnabled(false);

      return;
   }
}
