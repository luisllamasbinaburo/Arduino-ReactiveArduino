// ObserverDigitalOutput.h

#ifndef _OBSERVERDIGITALOUTPUT_h
#define _OBSERVERDIGITALOUTPUT_h

template <typename T>
class ObserverDigitalOutput : public IObserver<T>
{
public:
	ObserverDigitalOutput(uint8_t pin);

	void OnNext(T value);
	void OnComplete();

private:
	uint8_t _pin;
};

template <typename T>
inline ObserverDigitalOutput<T>::ObserverDigitalOutput(uint8_t pin)
{
	this->_pin = pin;
	pinMode(pin, OUTPUT);
}

template <typename T>
inline void ObserverDigitalOutput<T>::OnNext(T value)
{
	digitalWrite(this->_pin, value);
}

template <typename T>
inline void ObserverDigitalOutput<T>::OnComplete()
{
}
#endif

