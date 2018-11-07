# TTK4155 Byggern
Lab in TTK4155 – Embedded and Industrial Computer Systems Design

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
