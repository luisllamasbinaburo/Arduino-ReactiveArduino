/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERPASSBAND_h
#define _REACTIVEFILTERPASSBAND_h

template <typename T>
class FilterPassBand : public Operator<T, T>
{
public:
	FilterPassBand<T>(double alpha1, double alpha2);
	void OnNext(T value) override;

private:
	double _alphaLow;
	double _alphaHigh;

	T _lowPassFilterLow = T();
	T _lowPassFilterHigh = T();
	T _bandPassFilter = T();
	T _bandStopFilter = T();
};

template<typename T>
FilterPassBand<T>::FilterPassBand(const double alpha1, const double alpha2)
{
	_alphaLow = alpha1 < alpha2 ? alpha1 : alpha2;
	_alphaHigh = alpha1 >= alpha2 ? alpha1 : alpha2;
}

template <typename T>
void FilterPassBand<T>::OnNext(T value)
{
	_lowPassFilterLow = (T)(_alphaLow * value + (1 - _alphaLow) * _lowPassFilterLow);
	_lowPassFilterHigh = (T)(_alphaHigh * value + (1 - _alphaHigh) * _lowPassFilterHigh);
	_bandPassFilter = _lowPassFilterHigh - _lowPassFilterLow;
	_bandStopFilter = value - _bandPassFilter;

	this->_childObservers.OnNext(_bandPassFilter);
}

#endif