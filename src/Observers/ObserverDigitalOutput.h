// ObserverDigitalOutput.h

#ifndef _REACTIVEOBSERVERDIGITALOUTPUT_h
#define _REACTIVEOBSERVERDIGITALOUTPUT_h

template <typename T>
class ObserverDigitalOutput : public IObserver<int>
{
public:
	ObserverDigitalOutput(uint8_t pin);

	void OnNext(int value) override;
	void OnComplete() override;

private:
	uint8_t _pin;
};

template <typename T>
ObserverDigitalOutput<T>::ObserverDigitalOutput(uint8_t pin)
{
	this->_pin = pin;
	pinMode(pin, OUTPUT);
}

template <typename T>
void ObserverDigitalOutput<T>::OnNext(int value)
{
	digitalWrite(this->_pin, value);
}

template <typename T>
void ObserverDigitalOutput<T>::OnComplete()
{
}

#endif