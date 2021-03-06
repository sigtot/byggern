# TTK4155 Byggern
Lab in TTK4155 – Embedded and Industrial Computer Systems Design
## Project
This repository contains the code for the implementation of a physical ping pong machine. It contains the game logic, as well as drivers for all the different components.

In addition to the actual machine implemented in low level C code, the project was set up with a rest API and a simple web frontend. The game could also be played automatically, through the means of computer vision with the [OpenCV library](https://opencv.org/). For this, a kalman filter was implemented to track and predict the ping pong ball's future movements. The code for this can be found in the following github repos:
* https://github.com/sigtot/byggern-rest
* https://github.com/sigtot/byggern-frontend
* https://github.com/sigtot/circle-detection
* https://github.com/sigtot/kalman

### Node 2 UART Api
The internal state of node2 is simply the reference servo and motor positions for the physical machine.
```c
typedef struct Reference_State {
    int servo_pos;
    int motor_pos;
} Reference_State;
```
The positions are percentage values ranging from 0 to 100.
This global state can be mutated by via a UART api. This is done by sending a string such as
```
{servo=35&motor=78}
```
over UART to node2.
Both parameters `servo` and `motor` are optional, so `{servo=35}` and {`motor=78}` are just as valid.

## Writing and running tests
Integration tests are found in `nodeN/tests/integration`

### Running tests
Tests are run with the following command:
```bash
sh runtest.sh TEST
```

So, to run for example `integration/ir_test.c` on node2, run the following command (requires sudo)
```bash
./runtest.sh integration/ir_test.c
```

To run all the tests, instead do
```bash
./runall.sh
```

### Writing new tests
Tests should be .c files placed in `nodeN/tests/integration` or similar.
When executing the test, the actual `main.c` file in `nodeN/src` will be replaced with
the test, and flashed to the node. Therefore, you should write your tests as
you would write a main file. As an example, look at the very simple `ir_test.c`:
```C
#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"

#include "ir.h"

int main() {
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit,NULL);

	printf("Test instruction: Hold the IR emitter up to the photo diode. The test will alert you when the state changes.\n\r");
	ir_init();
	sei();

	int ir_light_received = !Ir_is_blocked();
	printf("%s\n\r", ir_light_received ? "RECEIVING IR LIGHT" : "NOT RECEIVING IR LIGHT");
	while(1) {
		int new = !Ir_is_blocked();
		if (ir_light_received != new) {
			ir_light_received = new;
			printf("%s\n\r", ir_light_received ? "RECEIVING IR LIGHT" : "NOT RECEIVING IR LIGHT");
		}
	}
	return 0;
}
```
