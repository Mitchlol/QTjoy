/*
 * SRVjoy.h
 *
 * Created on: Aug 18, 2009
 * Author: Carlos Jaramillo
 * Sponsored by: DREU Summer 2009
 */

#ifndef SRVJOY_H_
#define SRVJOY_H_

#include <QWidget>
#include <libplayerc++/playerc++.h>
#include "args.h"

//class QCheckBox;
class QLabel;
//class QLineEdit;
class QPushButton;
class QToolButton;
class QSlider;
class QAction;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;

// Moving Status Flags:
const char STOP = 0;
const char BACK_LEFT = 1;
const char BACK = 2;
const char BACK_RIGHT = 3;
const char ROTATE_CCW = 4;
const char ROTATE_CW = 6;
const char FORWARD_LEFT = 8;
const char FORWARD = 9;
const char FORWARD_RIGHT = 10;

class SRVjoy : public QWidget
{
   Q_OBJECT

   public:
      SRVjoy(QWidget *parent = 0);
      //signals:

   private slots:
      void
      connectToRobot();
      void
      moveForward();
      void
      moveForwardLeft();
      void
      moveForwardRight();
      void
      moveBackward();
      void
      moveBackwardLeft();
      void
      moveBackwardRight();
      void
      rotateCCW();
      void
      rotateCW();
      void
      stopMoving();
      void
      setLinearSpeed(int nSpeed);
      void
      setAngularSpeedInDegrees(int dDegrees);
      void
      takePictureShot();

   protected:
      void
      keyPressEvent(QKeyEvent *event);
      void
      keyReleaseEvent(QKeyEvent *event);
      //    bool eventFilter(QObject* obj, QEvent* event);
   private:
      void
      createActions();

      QLabel *m_LinearSpeedLabel;
      QLabel *m_AngularSpeedLabel;
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
      QSlider *m_LinearSpeedSlider;
      QSlider *m_AngularSpeedSlider;
      QHBoxLayout *layoutConnect;
      QGridLayout *layoutJoystick;
      QVBoxLayout *centralLayout;

      // Player client that represents the robot
      PlayerCc::PlayerClient *m_pRobot;

      // Variables to manipulate the robot's Position2d interface
      PlayerCc::Position2dProxy *m_pPos2dProxy;
      bool m_bConnected;
      int m_nTurnRateDegrees;
      player_pose2d m_Speed2D;

      // Variables to manipulate the robot's Camera interface
      PlayerCc::CameraProxy *m_pCameraProxy;

      // define the speed limits for the robot:
      static const double m_dMaxSpeed = 0.5; // m/second
      static const double m_dMinSpeed = 0.05; // m/second
      static const int m_nMaxTurnRateDegrees = 270; // rad/second

      char m_nCurrentMove; // Current moving status of the robot

      void
      enableButtons(bool enabled);
      void
      increaseAngularSpeed();
      void
      decreaseAngularSpeed();
      void
      reverseTurnRate();
      void
      increaseLinearSpeed();
      void
      decreaseLinearSpeed();
      void
      reverseSpeed();
      int
      normalizeSliderSpeed(double dSpeed);
      void
      refreshCurrentMove();
};

#endif /* SRVJOY_H_ */
