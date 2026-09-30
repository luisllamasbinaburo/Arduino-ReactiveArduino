// Minimal Arduino API stub used by the native PlatformIO unit tests.
// ReactiveArduinoLib.h includes "WProgram.h" when ARDUINO is not defined,
// so this file is picked up from the `test` include path.
#ifndef WPROGRAM_STUB_H
#define WPROGRAM_STUB_H

#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>

typedef unsigned char byte;

// ---- Minimal Arduino String ----
class String
{
public:
	String() {}
	String(const char* s) { if (s) _s = s; }
	String(char c) { _s.assign(1, c); }
	String(int v) { char b[16]; snprintf(b, sizeof(b), "%d", v); _s = b; }
	String(unsigned int v) { char b[16]; snprintf(b, sizeof(b), "%u", v); _s = b; }
	String(long v) { char b[24]; snprintf(b, sizeof(b), "%ld", v); _s = b; }
	String(unsigned long v) { char b[24]; snprintf(b, sizeof(b), "%lu", v); _s = b; }
	String(float v) { char b[32]; snprintf(b, sizeof(b), "%f", v); _s = b; }
	String(double v) { char b[40]; snprintf(b, sizeof(b), "%f", v); _s = b; }

	const char* c_str() const { return _s.c_str(); }
	unsigned int length() const { return (unsigned int)_s.size(); }
	char charAt(unsigned int i) const { return (i < _s.size()) ? _s[i] : '\0'; }

	String substring(unsigned int from, unsigned int to) const
	{
		if (from >= _s.size()) return String();
		if (to > _s.size()) to = (unsigned int)_s.size();
		if (to < from) to = from;
		return String(_s.substr(from, to - from).c_str());
	}

	void concat(char c) { _s += c; }
	void concat(const char* s) { if (s) _s += s; }
	int toInt() const { return (int)atoi(_s.c_str()); }
	float toFloat() const { return (float)atof(_s.c_str()); }

	String operator+(const String& o) const { String r(_s.c_str()); r._s += o._s; return r; }
	String& operator=(const String& o) { _s = o._s; return *this; }
	String& operator=(const char* o) { _s = (o ? o : ""); return *this; }
	bool operator==(const String& o) const { return _s == o._s; }
	bool operator==(const char* o) const { return _s == (o ? o : ""); }

private:
	std::string _s;
};

// ---- Controllable time ----
inline unsigned long g_millis = 0;
inline unsigned long g_micros = 0;
inline unsigned long millis() { return g_millis; }
inline unsigned long micros() { return g_micros; }

// ---- Pin I/O capture ----
inline uint8_t g_pinModePin = 0xFF;
inline uint8_t g_pinModeMode = 0xFF;
inline void pinMode(uint8_t pin, uint8_t mode) { g_pinModePin = pin; g_pinModeMode = mode; }

inline uint8_t g_digitalPin = 0xFF;
inline uint8_t g_digitalValue = 0xFF;
inline void digitalWrite(uint8_t pin, uint8_t value) { g_digitalPin = pin; g_digitalValue = value; }

inline uint8_t g_analogPin = 0xFF;
inline int g_analogValue = -1;
inline void analogWrite(uint8_t pin, int value) { g_analogPin = pin; g_analogValue = value; }

inline int g_analogRead = 0;
inline int analogRead(uint8_t) { return g_analogRead; }

inline int g_digitalRead = 0;
inline int digitalRead(uint8_t) { return g_digitalRead; }

// ---- Serial capture ----
struct SerialStub
{
	int printCount = 0;
	int available() { return 0; }
	int read() { return -1; }
	void begin(unsigned long) {}
	template <typename U> void println(const U&) { printCount++; }
};
inline SerialStub Serial;

#ifndef LOW
#define LOW 0
#endif
#ifndef HIGH
#define HIGH 1
#endif
#ifndef INPUT
#define INPUT 0
#endif
#ifndef OUTPUT
#define OUTPUT 1
#endif

#endif
