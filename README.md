# Library ReactiveArduino

ReactiveArduino implements observable-observer pattern on a processor like Arduino. The purpose is to provide declarative programming approach, within the capacity constraints of a low-power MCU.

ReactiveArduino is heavly based on ReactiveX and ReactiveUI, adapted to the needs and limitations in a MCU.

## Instructions for use
The general use of ReactiveArduino consists of:
* Define an observable (Timer, Interval, FromArray, FromProperty...)
* Chain with one or more operators (Distinct, Where, Select, First, Last, Sum...) 
* Subscribe an observer (Do, DoFinally, ToProperty, ToArray...)

For example:
```c++
Reactive::FromRange<int>(10, 20)
>> Reactive::Select<int>([](int x) { return x + 10; })
>> Reactive::ToSerial<int>();
>> Reactive::DoAndFinally<int>(
  [](int x) { Serial.println(x); },
  []() { Serial.println("No more items"); 
});
```

More info about the Observables, Observers, and Operators available in the [Wiki](https://github.com/luisllamasbinaburo/Arduino-ReactiveArduino/wiki)

### Creating operators
Operators are generally generated through factory methods provided in the reactive class.
For example:
```c++
Reactive::FromArray<int>(values, valuesLength)
```

### Chaining operators
To chain operators ReactiveArduino uses the overload of `>>`, which allows to combine observable and observers.
For example:
```c++
observableInt >> Reactive::ToSerial<bool>();
```

### Templating
ReactiveArduino intensively uses templating to define the type of data that an operator receives or sends.
Some operators need one template
```c++
Reactive::Count<float>()
```
But other operators need two templates
```c++
Reactive::Cast<int, float>()
```
Ant other operatos need no templates.

### Cool and hot observables
ReactiveArduino has two types of observables, hot and cold.
Hot observables launch the actions when another operator subscribes to it. For example, `FromArray(...)` is a HotObservable.
```c++
Reactive::FromArray<int>(values, valuesLength)
```
By cons in the cold observable subscribe does not generate any action. To run we will have to explicitly call the `Next()` method when we want. For example, `FromArrayDefer(...)`
```c++
Reactive::FromArrayDefer<int>(values, valuesLength)
```
### Dynamic memory considerations
On many occasions we generate the operators directly when we chain the operators, for example in the `Setup()`. However, keeping in mind that creating an operator implies allocate dynamic memory. Therefore, we should avoid generating them in `Loop()` because could run out of memory.
If you need to reuse or call an operator set it as a global variable, and chain as normal.
```c++
auto counter = Reactive::Count<int>();
...
//(later in code)
...
obsString >> counter >> Reactive::ToSerial<String>();
```

## Examples
```c++
#include "ReactiveArduinoLib.h"

int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int valuesLength = sizeof(values) / sizeof(values[0]);

void setup()
{
	Serial.begin(9600);
	while (!Serial) delay(1);

	Reactive::FromArray<int>(values, valuesLength)
		>> Reactive::Cast<int, float>()
		>> Reactive::MovingAverage<float>(4)
		>> Reactive::DoAndFinally<float>(
			[](float x) { Serial.println(x); },
			[]() { Serial.println("No more items"); }
	);
}

void loop() 
{
	delay(2000);
}
```
