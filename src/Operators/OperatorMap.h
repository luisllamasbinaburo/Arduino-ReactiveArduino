/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _OPERATORMAP_h
#define _OPERATORMAP_h

template <typename Torig, typename Tdest>
class OperatorMap : public Operator<Torig, Tdest>
{
public:
	ReactiveMap<Torig, Tdest> _map;

	OperatorMap<Torig, Tdest>(ReactiveMap<Torig, Tdest> map);

	void OnNext(Torig value);
};

template <typename Torig, typename Tdest>
OperatorMap<Torig, Tdest>::OperatorMap(ReactiveMap<Torig, Tdest> map)
{
	this->_map = map;
}

template<typename Torig, typename Tdest>
inline void OperatorMap<Torig, Tdest>::OnNext(Torig value)
{
	Tdest newValue = (Tdest)(this->_map(value));

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(newValue);
}
#endif