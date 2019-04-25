# Library ReactiveArduino

ReactiveArduino implements observable-observer pattern on a processor like Arduino. The purpose is to provide declarative programming approach, within the capacity constraints of a low-power MCU.

ReactiveArduino is heavly based on [ReactiveX](http://reactivex.io/) and [ReactiveUI](https://reactiveui.net/), adapted to the needs and limitations in a MCU.

## Instructions for use
The general use of ReactiveArduino consists of:
* Define an observable (Timer, Interval, FromArray, FromProperty...)
* Chain with one or more operators (Distinct, Where, Select, First, Last, Sum...) 
* Subscribe an observer (Do, DoFinally, ToProperty, ToArray...)

For example:
```c++
Reactive::FromRange<int>(10, 20)
>> Reactive::Select<int>([](int x) { return x + 10; })
>> Reactive::DoAndFinally<int>(
  [](int x) { Serial.println(x); },
  []() { Serial.println("No more items"); 
});
```

More examples in Wiki/[Examples](https://github.com/luisllamasbinaburo/Arduino-ReactiveArduino/wiki/Examples)


### Observable, observers and operators legend
More info about the Observables, Observers, and Operators available in the [Wiki](https://github.com/luisllamasbinaburo/Arduino-ReactiveArduino/wiki)

![alt text](https://github.com/luisllamasbinaburo/Arduino-ReactiveArduino/blob/master/ReactiveArduino%20Legend.png "Legend")

### Creating operators
Operators are generally generated through factory methods provided by the Reactive class.
For example:
```c++
Reactive::FromArray<int>(values, valuesLength)
```

### Chaining operators
To chain operators ReactiveArduino uses overload of operator `>>`, which allows to combine observable and observers.
For example:
```c++
observableInt >> Reactive::ToSerial<bool>();
```

### Templating
ReactiveArduino intensively uses templating to define the type of data that an operator receives or emits.
Some operators need one template
```c++
Reactive::Count<float>()
```
But other operators need two templates
```c++
Reactive::Cast<int, float>()
```
And other operators need no templates.

### Cool and hot observables
ReactiveArduino has two types of observables, hot and cold.
Hot observables emits the sequence when an observer subscribes to it. For example, `FromArray(...)` is a Hot Observable.
```c++
Reactive::FromArray<int>(values, valuesLength)
```
Cold observable does not emits any item when a observer suscribes to it. You have to explicitly call the `Next()` method whenever you want. For example, `FromArrayDefer(...)`
```c++
Reactive::FromArrayDefer<int>(values, valuesLength)
```
### Dynamic memory considerations
On many occasions we generate operators directly when we chain them, for example in the `Setup()`. However, creating an operator allocates dynamic memory. Therefore, you should avoid creating them in `Loop()`, or you coul run out of memory.
If you need to reuse (tipically, call some operator method later in your code) set it as a global variable, and chain as normal.
```c++
auto counter = Reactive::Count<int>();
...
//(later in code)
...
obsString >> counter >> Reactive::ToSerial<String>();
```

## Examples
This example show how to use Reactive Operator to perform a 3-elements Median filter, then a 4-elements Moving Average Filter, and make some action with the final filtered value.
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
		>> Reactive::Median3<float>()
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

More examples in Wiki/[Examples](https://github.com/luisllamasbinaburo/Arduino-ReactiveArduino/wiki/Examples)
