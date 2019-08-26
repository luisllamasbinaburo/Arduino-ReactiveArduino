/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERSTOPBAND_h
#define _REACTIVEFILTERSTOPBAND_h

template <typename T>
class FilterStopBand : public Operator<T, T>
{
public:
	FilterStopBand<T>(double alpha1, double alpha2);
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
FilterStopBand<T>::FilterStopBand(const double alpha1, const double alpha2)
{
	this->_alphaLow = alpha1 < alpha2 ? alpha1 : alpha2;
	this->_alphaHigh = alpha1 >= alpha2 ? alpha1 : alpha2;
}

template <typename T>
void FilterStopBand<T>::OnNext(T value)
{
	this->_lowPassFilterLow = (T)(this->_alphaLow * value + (1 - this->_alphaLow) * this->_lowPassFilterLow);
	this->_lowPassFilterHigh = (T)(this->_alphaHigh * value + (1 - this->_alphaHigh) * this->_lowPassFilterHigh);
	this->_bandPassFilter = this->_lowPassFilterHigh - this->_lowPassFilterLow;
	this->_bandStopFilter = value - this->_bandPassFilter;

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(_bandStopFilter);
}

#endif