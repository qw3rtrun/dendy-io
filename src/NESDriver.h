#include "Arduino.h"

#ifndef NESDRIVER_H
#define NESDRIVER_H

class NESController {
	public:
		NESController();
		void begin(int dataPin);
		bool isConnected();
		bool isChanged();
		int xAxis();
		int yAxis();
		bool up();
		bool down();
		bool left();
		bool right();
		bool start();
		bool select();
		bool a();
		bool b();
		void read(int i);
		int state();
		int previous();
	private:
		bool button(int mask);
		int _dataPin;
		byte _state;
		byte _previous;
};

class _NESDriver {
private:
	int _latchPin;
	int _clockPin;
	int _count;
	NESController _state[4];
	void begin(int latchPin, int clockPin, int count, int dataPin[]);

	public:
		_NESDriver();

		void begin(int latchPin, int clockPin, int dataPin);
		void begin(int latchPin, int clockPin, int dataPin1, int datePin2);
		void begin(int latchPin, int clockPin, int dataPin1, int datePin2, int datePin3);
		void begin(int latchPin, int clockPin, int dataPin1, int datePin2, int datePin3, int dataPin4);

		void updateState();

		NESController state(int n);
		NESController state1() {
			return state(0);
		}
		NESController state2() {
			return state(1);
		}
		NESController state3() {
			return state(2);
		}
		NESController state4() {
			return state(3);
		}
};

extern _NESDriver NESDriver;

#endif
