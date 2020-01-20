
# ARM Sailboat project
Made by Clément GEHIN, Ruben GRES, Lucas PERARD and Philippe SAADE.
This project aim is to discover embed-programming with a STM32 microcontroller. The goal is to have a fully functionnal mini-sailboat, reacting to the the wind to adjust its sail.

## Implemented features :

* Weather vane : used an incremental encoder to get the angle of the vane.

* Servomotor : used to control the sail according to the angle of the weather vane. We use a PWM output to control the motor. The sail can be angled from 30° to 100°.
We use a non linear model to control the sail : if the vane is between an angle ranging from X to Y, we put the sail at angle Z. It is much smoother.

* Board control : used to simulate the water. Uses a direct current motor, which we control through a PWM output. 

* Remote : used to control the mouvement of the board. We receive a PWM input, and we have to convert it to a signal for the board.

	
## Files :

* Each module is located is MyDrivers.
