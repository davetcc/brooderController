## Open Brooder and Incubator

**BE AWARE THAT THIS PROJECT USES MAINS VOLATAGES, do not proceed unless you are confident to work with such voltages safely.**

This project discusses how to build a simple incubator / brooder for hatching chicks. The project was initially a bit rushed as the chicks outgrew a tiny egg incubator very quickly, so I had to generate this in a few days. Given the situation, it turned out pretty well.

This project uses TcMenu and for me, it runs on a spare Uno I had hanging around. Why Uno, I want to keep Uno around in my libraries for as long as possible and this provides the ultimiate requirement to keep it going. Use a display directly wired to the Uno, the wiring is discussed in the menuProject. But it is essentially an Uno directly connected, a rotary encoder directly connected, and heater, fan, and temperature on Uno pins. There is also a power off sensor attached too that saves the menu structure before power is lost.

The project is split into three sections:

* brooderCircuit - contains the schematics
* designs - contain a few paper based and tinkercad designs for the vero / patch board layout I used
* menuProject - contains a tcMenu based sketch that builds in platformIO.
