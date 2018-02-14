/*
 * NESController.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: qw3rtrun
 */

#include "NESDriver.h"
#include "Arduino.h"

#define A 0x80
#define B 0x40
#define SELECT 0x20
#define START 0x10
#define UP 0x08
#define DOWN 0x04
#define LEFT 0x02
#define RIGHT 0x01

_NESDriver::_NESDriver() {
}

void _NESDriver::begin(int latchPin, int clockPin, int count, int dataPin[]) {
	_latchPin = latchPin;
	_clockPin = clockPin;
	pinMode(_latchPin, OUTPUT);
	digitalWrite(_latchPin, HIGH);
	pinMode(_clockPin, OUTPUT);
	digitalWrite(_clockPin, HIGH);
	_count = count;
	for (int i = 0; i < count; i++) {
		_state[i].begin(dataPin[i]);
	}
}

void _NESDriver::begin(int latchPin, int clockPin, int dataPin1) {
	begin(latchPin, clockPin, 1, &dataPin1);
}

void _NESDriver::begin(int latchPin, int clockPin, int dataPin1, int dataPin2) {
	int dataPin[] = {dataPin1, dataPin2};
	begin(latchPin, clockPin, 2, dataPin);
}

void _NESDriver::begin(int latchPin, int clockPin, int dataPin1, int dataPin2, int dataPin3) {
	int dataPin[] = {dataPin1, dataPin2, dataPin3};
	begin(latchPin, clockPin, 3, dataPin);
}

void _NESDriver::begin(int latchPin, int clockPin, int dataPin1, int dataPin2, int dataPin3, int dataPin4) {
	int dataPin[] = {dataPin1, dataPin2, dataPin3, dataPin4};
	begin(latchPin, clockPin, 4, dataPin);
}

void _NESDriver::updateState() {
	digitalWrite(_latchPin, LOW);
	delayMicroseconds(90);
	for (int i = 0; i < 8; i++) {
		digitalWrite(_clockPin, LOW);
		for (int j = 0; j < _count; j++) {
			_state[j].read(i);
		}
		digitalWrite(_clockPin, HIGH);
	}
	digitalWrite(_latchPin, HIGH);
}

NESController _NESDriver::state(int n) {
	return _state[n % 4];
}

NESController::NESController() {
	_dataPin = -1;
	_state = 0;
	_previous = 0;
}

void NESController::begin(int dataPin) {
  pinMode(dataPin, INPUT_PULLUP);
	_dataPin = dataPin;
}

bool NESController::isConnected() {
	return _dataPin >= 0 && _state != 0;
}

bool NESController::isChanged() {
	return _state != _previous;
}

void NESController::read(int i) {
	if (i == 0) {
		_previous = _state;
	}
	if (_dataPin > 0) {
		int bit = digitalRead(_dataPin);
		_state = (_state << 1) | bit;
	}
}

int NESController::state() {
	return _state;
}

bool NESController::button(int mask) {
	return isConnected() && !(_state & mask);
}

bool NESController::a() {
	return button(A);
}

bool NESController::b() {
	return button(B);
}

bool NESController::select() {
	return button(SELECT);
}

bool NESController::start() {
	return button(START);
}

bool NESController::up() {
	return button(UP);
}

bool NESController::down() {
	return button(DOWN);
}

int NESController::xAxis() {
	return button(UP) - button(DOWN);
}

bool NESController::right() {
	return button(RIGHT);
}

bool NESController::left() {
	return button(LEFT);
}

int NESController::yAxis() {
	return button(RIGHT) - button(LEFT);
}

_NESDriver NESDriver;
