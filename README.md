# Hellbot Magna Dual

The MIXING_EXTRUDERS feature is disabled because I'm using 2 mechanically different extruders. In order for that to work I need to enable DISTINCT_E_FACTORS to configure steps/mm for each extruder individually, which is currently not compatible with MIXING_EXTRUDERS.

I don't really ming because I don't like the mixing_extruder feature and never use it.

To disable Mixing_extruders and get it to compile, I had to set the number of extruders to 2:
```C++
#define EXTRUDERS 2
```
and set singlenozzle
```C++
#define SINGLENOZZLE
```