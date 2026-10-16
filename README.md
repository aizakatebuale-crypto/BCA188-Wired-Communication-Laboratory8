# Wired Communication


### Pin Table
| Signal | GPIO Used | Board`s Label |
|---|---|---|
| UART TX | 17 |	D17 |
| UART RX | 16 |	D16 |
| I²C SDA |	21 |	D21 |
| I²C SCL |	22 |	D22 |
| SPI SCK	| 18 |	D18 |
| SPI MOSI	| 23 |	D23 |
| SPI MISO	| 19 |	D19 |
| SPI CS | 	27 |	D27 |

### Wiring Diagram
<img width="4096" height="3072" alt="image" src="https://github.com/user-attachments/assets/1c50e841-3615-46a7-bbaa-66d5de33f1ab" />


### Serial Monitor output

uart loopback
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/8a4d9873-8acf-4284-a5eb-e854707d6123" />


i²c scanner
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/25fefca1-80a2-48a2-b835-59ab5ef194ed" />


spi loopback
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/960b3d1b-2c5f-47fc-b27d-972d2792d43a" />


### Expected vs Observed table
| Test | Expected | Observed |
| :--- | :--- | :--- |
| UART with jumper | Prints PING every 1 second | Prints PING every 1 second |
| UART without jumper | Nothing prints | Nothing prints |
| I²C with module | Found device at 0x.. | Found device at 0x.. |
| I²C without module | No I2C devices found | No I2C devices found |
| SPI with jumper | Sent 0xA5, received 0xA5 | Sent 0xA5, received 0xA5 |
| SPI without jumper | Received not A5 (e.g., FF or 0) | Received not A5 (e.g., FF or 0) |
| Sketch at 9600, monitor at 115200 | Garbled characters | Garbled characters |
| Sketch at 9600, monitor at 9600 | Clear PING | Clear PING |

### Questions
1. Why does UART need both sides to use the same baud rate, while SPI uses a clock line?
UART operates without a dedicated clock line, so the receiving end has to rely entirely on its own internal timer to sample incoming bits, making matching baud rates essential for both sides to stay in sync. SPI avoids this by sending a master-driven clock signal (SCK), which directly tells the slave exact moment to sample the data

2. Why can two devices with the same address not share one I²C bus?
I²C uses device addresses to target specific chips on the bus. If two slaves share the same address, both will attempt to respond simultaneously by pulling the SDA line high or low at the same time, leading to bus contention, data corruption, and unreadable communication.

3. Why is CS set HIGH between SPI transfers?
Pulling Chip Select (CS) HIGH deselects the target slave, resetting its internal transmission logic and releasing its data line back into a high-impedance state. Pulsing CS LOW starts a fresh transaction and driving it back HIGH marks the end, which prevents data crosstalk when multiple slaves share the exact same MISO/MOSI pins.
