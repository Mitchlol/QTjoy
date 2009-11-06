#include "ImageThread.h"
ImageThread::ImageThread(){
	rate = 300;
}
void
ImageThread ::run()
{
	while(1){
		usleep(rate * 10000);
		//this sends signal which is picked up by the QWidget which "owns" this thread
		//this signal is connected to the slot that takes pictures in the camera portion connect robot function
		Q_EMIT threadCallPictureShot();
	}
}
//this slot is used to adjust the capture rate
//it is connected to the slide bar in the camera portion connect robot function
void
ImageThread::setAutoPictureShotRate(int x){
	rate = x;
}
