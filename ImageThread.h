/*
 * ImageThread.h
 *
 *  Created on: Nov 5, 2009
 *      Author: mitch
 */

#ifndef IMAGETHREAD_H_
#define IMAGETHREAD_H_

#include <QThread>

class ImageThread : public QThread
{
    Q_OBJECT

Q_SIGNALS:
    void threadCallPictureShot();

private Q_SLOTS:
	void setAutoPictureShotRate(int x);

public:
	ImageThread();

protected:
    void run();

private:
    int rate;

};

#endif /* IMAGETHREAD_H_ */
