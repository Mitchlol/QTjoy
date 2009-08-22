/*
 * SRVjoy.h
 *
 *  Created on: Aug 18, 2009
 *      Author: carlos
 */

#ifndef SRVJOY_H_
#define SRVJOY_H_

#include <QWidget>
#include <libplayerc++/playerc++.h>
//#include "args.h"

//class QCheckBox;
class QLabel;
//class QLineEdit;
class QPushButton;
class QToolButton;
class QAction;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;

class SRVjoy : public QWidget
{
    Q_OBJECT

public:
    SRVjoy(QWidget *parent = 0);
//signals:

private slots:
      void connectToRobot();
      void moveForward();
      void moveBackward();
      void stopMoving();
private:
    void createActions();

    QLabel *m_Label;
    QPushButton *m_ConnectButton;
    QToolButton *m_FordwardButton;
    QToolButton *m_BackwardButton;
    QHBoxLayout *layoutConnect;
    QGridLayout *layoutJoystick;
    QVBoxLayout *centralLayout;

    // Player client that represents the robot
    PlayerCc::PlayerClient    *m_pRobot;

    // Variables use to manipulate the robot's Position2d interface
    PlayerCc::Position2dProxy *m_pPos2dProxy;
    bool m_bConnected;
    double m_dTurnrate, m_dSpeed;
};


#endif /* SRVJOY_H_ */
