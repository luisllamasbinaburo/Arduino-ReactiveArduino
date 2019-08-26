/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONADCTOVOLTAGE_h
#define _REACTIVETRANSFORMATIONADCTOVOLTAGE_h

template <typename T>
class TransformationAdcToVoltage : public Operator<T, float>
{
public:
	TransformationAdcToVoltage<T>(T input_max = 1023, T output_max = 5.0);

	void OnNext(T value) override;

private:
	T _input_max = T();
	T _output_max = T();
};

template <typename T>
TransformationAdcToVoltage<T>::TransformationAdcToVoltage(T input_max, T output_max)
{
	this->_input_max = input_max;
	this->_output_max = output_max;
}


template <typename T>
void TransformationAdcToVoltage<T>::OnNext(T value)
{
	this->_childObserver->OnNext((value * _output_max) / _input_max);
}

#endif