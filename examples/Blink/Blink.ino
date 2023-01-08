/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ReactiveArduinoLib.h"
using namespace Reactive;

auto timer = IntervalMillis(500);

void setup()
{
	timer
	>> Toggle<unsigned long>()
	>> ToDigitalOutput<bool>(LED_BUILTIN);
}

void loop()
{
	timer.Update();
}