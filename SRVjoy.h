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
      void moveForwardLeft();
      void moveForwardRight();
      void moveBackward();
      void moveBackwardLeft();
      void moveBackwardRight();
      void turnLeft();
      void turnRight();
      void stopMoving();

      // To be implemented:
      void takePictureShot();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void createActions();

    QLabel *m_Label;
    QPushButton *m_ConnectButton;
    QToolButton *m_ForwardLeftButton;
    QToolButton *m_ForwardRightButton;
    QToolButton *m_ForwardButton;
    QToolButton *m_TurnLeftButton;
    QToolButton *m_TurnRightButton;
    QToolButton *m_BackwardLeftButton;
    QToolButton *m_BackwardRightButton;
    QToolButton *m_BackwardButton;
    QToolButton *m_CameraSnapshotButton;
    QHBoxLayout *layoutConnect;
    QGridLayout *layoutJoystick;
    QVBoxLayout *centralLayout;

    // Player client that represents the robot
    PlayerCc::PlayerClient    *m_pRobot;

    // Variables use to manipulate the robot's Position2d interface
    PlayerCc::Position2dProxy *m_pPos2dProxy;
    bool m_bConnected;
    double m_dTurnRateRadians;
    double m_dTurnRateDegrees;
    double m_dSpeed;

    // define the speed limits for the robot:
    static const double m_dMaxSpeed = 0.5; // m/second
    static const double m_dMinSpeed = 0.05; // m/second
    static const double m_dMaxTurnRateDegrees = 270; // rad/second

    void enableButtons(bool enabled);

    void setTurnrateInDegrees(double degrees);
    void increaseTurnRate();
    void decreaseTurnRate();
    void reverseTurnRate();
    void increaseLinearSpeed();
    void decreaseLinearSpeed();
    void reverseSpeed();
};


#endif /* SRVJOY_H_ */
