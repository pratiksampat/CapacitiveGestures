#ifndef GESTURES_H
#define GESTURES_H

#include <CapacitiveSensor.h>

#define MAX_GESTURES 6

/**
 * List of currently supported gestures
 */

/**
 * Single sensor gesture
 */
#define TAP         0x0
#define LONGTAP     0x1
/**
 * Multi sensor gestures
 */
#define SWIPE_LEFT  0x2
#define SWIPE_RIGHT 0x3
#define SWIPE_UP    0x4
#define SWIPE_DOWN  0x5

/**
 * Classifes gestures into their own buckets while keeping track of metadeta
 * start_time: the time gesture is started
 * gesture_initiated: boolean to classify if gesture has begun
 */
class Gesture {
	public:

		Gesture(){}

		Gesture(int id):
			id(id),
			start_time(0),
			gesture_initiated(false) {}

		Gesture(int id, long start, bool gest_init):
			id(id),
			start_time(start),
			gesture_initiated(gest_init) {}

		int id;
		long start_time;
		bool gesture_initiated;
};


/**
 * Main Sensor library interface, inherits Gesture and Capacitive Sensor
 * @sens_val: Current value of that sensor
 * @sens_max: Threshold value after which a touch is considered genuine
 * @sens_min: Threshold value below which a touch is considered genuine
 * @gesture: Keeps track of the different gestures, index signifies a gesture
 * @tap(): Detect a tap on the sensor
 * @longtap(): Detect a long tap on the sensor
 * @detectTap(): Generic function for tap detection
 */
class Sensor: public CapacitiveSensor, public Gesture {
	public:

		/**
		 * Sensor() constructor:
		 * sendPin: Pin input
		 * recvPin: Pin output
		 * sensMax: Threshhold value after which a touch is valid
		 * sensMin: Threnshold value below which a touch is valid
		*/
		Sensor(uint8_t sendPin, uint8_t recvPin, int sensMax = 4000,
				int sensMin = 400):
				sens_max(sensMax),
				sens_min(sensMin),
				CapacitiveSensor(sendPin,recvPin) {
			for (int i = 0; i < MAX_GESTURES; i++) {
				gesture[i] = Gesture(i);
			}
		}

		long sens_val;
		int sens_max;
		int sens_min;
		Gesture gesture[MAX_GESTURES];
		bool tap(int, int);
		bool longTap(int, int);

	private:
		/* Single sensor gestures embedded in the class */
		bool detectTap(int, int, int);
};
#endif
