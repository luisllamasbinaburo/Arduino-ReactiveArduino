/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONREDUCE_h
#define _REACTIVETRANSFORMATIONREDUCE_h

template <typename Torig, typename Tdest>
class TransformationReduce : public Operator<Torig, Tdest>
{
public:
	ReactiveReduce<Torig, Tdest> _function;

	TransformationReduce<Torig, Tdest>(ReactiveReduce<Torig, Tdest> function, Tdest init);

	void OnNext(Torig value) override;

private:
	Tdest _rst;
};

template <typename Torig, typename Tdest>
TransformationReduce<Torig, Tdest>::TransformationReduce(ReactiveReduce<Torig, Tdest> function, Tdest init)
{
	this->_function = function;
	this->_rst = init;
}

template <typename Torig, typename Tdest>
void TransformationReduce<Torig, Tdest>::OnNext(Torig value)
{
	this->_rst = this->_function(this->_rst, value);
	Tdest newValue = this->_rst;
	this->_childObservers.Fire(newValue);
}
#endif
