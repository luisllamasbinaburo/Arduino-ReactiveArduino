// Shared helpers for the ReactiveArduino unit tests.
#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "WProgram.h"
#include <vector>

// A terminal observer that records every value and completion it receives.
template <typename T>
struct Sink : IObserver<T>
{
	std::vector<T> values;
	int completeCount = 0;

	void OnNext(T v) override { values.push_back(v); }
	void OnComplete() override { completeCount++; }
};

// Reset the Arduino mock state before each test.
inline void resetMocks()
{
	g_millis = 0;
	g_micros = 0;
	g_pinModePin = 0xFF;
	g_pinModeMode = 0xFF;
	g_digitalPin = 0xFF;
	g_digitalValue = 0xFF;
	g_analogPin = 0xFF;
	g_analogValue = -1;
	g_analogRead = 0;
	g_digitalRead = 0;
	Serial.printCount = 0;
}

#endif
