/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONTHRESHOLD_h
#define _REACTIVETRANSFORMATIONTHRESHOLD_h

template <typename T>
class TransformationThreshold : public Operator<T, int>
{
public:
	TransformationThreshold<T>(T threshold) : TransformationThreshold<T>(threshold, threshold, false) {}
	TransformationThreshold<T>(T threshold, bool state) : TransformationThreshold<T>(threshold, threshold, state) {}
	TransformationThreshold<T>(T lowThreshold, T highThreshold, bool state);

	void OnNext(T value) override;

private:
	T _fallThreshold = T();
	T _riseThreshold = T();
	bool _state = false;
};

template<typename T>
TransformationThreshold<T>::TransformationThreshold(T threshold1, T threshold2, bool state)
{
	_fallThreshold = threshold1 <= threshold2 ? threshold1 : threshold2;
	_riseThreshold = threshold1 > threshold2 ? threshold1 : threshold2;
	_state = state;
}

template <typename T>
void TransformationThreshold<T>::OnNext(T value)
{
	if (!_state && value > _riseThreshold)
		_state = true;

	if (_state && value < _fallThreshold)
		_state = false;
	
	this->_childObservers.OnNext(_state);
}
#endif

