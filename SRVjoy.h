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

class SRVjoy : public QWidget
{
    Q_OBJECT

public:
    SRVjoy(QWidget *parent = 0);
//signals:

private slots:
      void moveForward();
      void moveBackward();
      void stopMoving();
private:
    QLabel *m_Label;
    QPushButton *m_FordwardButton;
    QPushButton *m_BackwardButton;

    // Player client that represents the robot
    PlayerCc::PlayerClient    *m_pRobot;

    // Variables use to manipulate the robot's Position2d interface
    PlayerCc::Position2dProxy *m_pPos2dProxy;
    double m_turnrate, m_speed;
};


#endif /* SRVJOY_H_ */
