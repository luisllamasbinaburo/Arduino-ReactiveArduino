/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

// will print 20, 30, 20, 30 ... that is observable * 10, only if observable > 1, and using Do to pass our function

#include "ReactiveArduinoLib.h"
using namespace Reactive;

ObservableProperty<int> observableInt;
int result;

void MyFunction(int x)
{
	// do whatever you want...
	Serial.println(x);
}

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);

	observableInt
		.Where([](int x) { return x > 1; })
		.Select([](int x) { return x * 10; })
		.Do(MyFunction);
}

void loop()
{
	observableInt = 1;
	delay(1000);
	
	observableInt = 2;
	delay(1000);
	
	observableInt = 3;
	delay(1000);
}