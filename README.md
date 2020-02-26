# MOTION GENERATOR COMPONENT

### DESCRIPTION:
This component replaces the *joystick* and *motion_translator* components. It guides the rover using a series of user-specified commands to change the translational and rotational speed at given times. It can also send a PTU command at the very beginning to pan and tilt the PTU to a desired angle.


### USAGE:
This task removes the need of the joystick task and replaces the motion_translator task, it has the same outputs as motion_translator that then have to be connected to the locomotion_switcher and ptu_control tasks inputs.  
To see an example of implementation similar to the usual "control.rb" script look at "vo_test_gen.rb" in "bundles/exoter/scripts"


### CONFIGURATION:
The desired motion will be defined in the config file.
```sh
cd ~/rock/bundles/rover/config/orogen
vim  motion_generator::Task.yml 
```

This is how the config file looks like:
```sh
--- name:default
# List containing time to execute the commands
commandsTime:           [0.0, 10.0, 15.0, 30.0] 
# List containing the translation velocity command associated to the CommandsTimes
commandsTranslation:    [0.0, 0.07, 0.0, 0.0]
# List containing the rotation velocity command associated to the CommandsTimes
commandsRotation:       [0.0, 0.0, 0.05, 0.0]
# List containing the locomotion_mode switches associated to the CommandsTimes
# 1 = DRIVING
# 2 = WHEEL_WALKING
commandsLocomotionMode: [1, 1, 1]
# Flag to execute or not a PTU position command at the beginning
commandsPTU: 0
# Pan position (double) in radians to be executed
commandsPan: 0
# Tilt position (double) in radians to be executed
commandsTilt: 0.628
```
In this case the generated motion would start by pitching the PTU by 0.628rad = 36deg, and then moving the rover after 10s at 0.07m/s forward, then after 5s (at 15s from the start) it will perform a point turn (no translational velocity and only rotational velocity), until 15s later it stops completely

