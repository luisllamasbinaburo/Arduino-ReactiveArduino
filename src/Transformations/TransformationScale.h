/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONSCALE_h
#define _REACTIVETRANSFORMATIONSCALE_h

template <typename T>
class TransformationScale : public Operator<T, T>
{
public:
	TransformationScale<T>(T input_min, T input_max, T output_min, T output_max);

	void OnNext(T value) override;

private:
	T _input_min = T();
	T _input_max = T();
	T _output_min = T();
	T _output_max = T();
};

template <typename T>
TransformationScale<T>::TransformationScale(T input_min, T input_max, T output_min, T output_max)
{
	_input_min = input_min;
	_input_max = input_max;
	_output_min = output_min;
	_output_max = output_max;
}


template <typename T>
void TransformationScale<T>::OnNext(T value)
{
	T scaled = (value - _input_min) * (_output_max - _output_min) / (_input_max - _input_min) + _output_min;
	this->_childObserver->OnNext(scaled);
}
#endif

