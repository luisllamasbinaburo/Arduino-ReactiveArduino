/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "ReactiveArduinoLib.h"
using namespace Reactive;

ObservableProperty<int> observableInt;

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);

	observableInt
		>> Distinct<int>()
		>> Where<int>([](int x) { return x > 2; })
		>> DoAndFinally<int>(
			[](int x) { Serial.println(x); },
			[]() { Serial.println("No more items"); }
		);
}

void loop()
{
	observableInt = 1;
	delay(200);
	observableInt = 3;
	delay(200);
	observableInt = 3;
	delay(200);
	observableInt = 1;
	delay(200);
	observableInt = 5;
	delay(200);
}