/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

// will print 10, 20, 10, 20 ... that is observable * 10, and stored in result variable
#include "ReactiveArduinoLib.h"
using namespace Reactive;

ObservableProperty<int> observableInt;
int result;

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);

	observableInt
		.Select([](int x) { return x * 10; })
		.ToProperty(result);
}

void loop()
{
	observableInt = 1;
	Serial.println(result);
	delay(1000);
	
	observableInt = 2;
	Serial.println(result);
	delay(1000);
}