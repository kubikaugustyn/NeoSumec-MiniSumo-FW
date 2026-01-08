# NeoSumec-MiniSumo-FW

NeoSumec MiniSumo Firmware - WIP

NeoSumec is a mini-sumo robot designed and built by engineering students
at [SPŠ na Proseku](https://www.sps-prosek.cz/).

## Adding a strategy

If you want to add a strategy, you'll first need to prepare a plan for what you want to do. If you have that, open the
`include/MainConfig.h` file and add two new lines next to the other strategy definitions:

```c++
// ...

// The strategy to use
#define STRATEGY_NEOSUMEC_2025_01_KEEP_RING
// ...
#define STRATEGY_NEOSUMEC_year_order_MY_NEW_COOL_STRATEGY

// Include all strategy headers. Only the single one enabled above will be compiled and used.
#include <strategy/2025_01_KeepRing.h>
// ...
#include <strategy/year_order_MyNewCoolStrategy.h>
```

After you've done that, create the strategy header file in `include/strategy/year_order_MyNewCoolStrategy.h` ideally by
copying an older strategy and adjusting it to use the tag you defined above in `#define STRATEGY_...`.

You'll also probably want to add code to the strategy.
This can be achieved by creating a new file in `src/strategy/year_order_MyNewCoolStrategy.cpp` (again, ideally by
copying an older strategy) and adding your code there after adjusting it.

I described the general process, there's nothing hard about it as long as you know programming.
If you don't know how to code, you shouldn't even be attempting to modify the code in the first place.