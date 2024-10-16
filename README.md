# cmsc-falcon-cube
Christa McAuliffe Space Center Falcon cube

Change the settings in `include/definitions.h` to set this device's settings. 
Follow the comments for instructions.


# Installation
1. Use VSCode for programming  
2. Open the project folder
3. Install the `PlatformIO` extension
4. Use the buttons in the status bar for uploading the code

#### The buttons
1. `✓` (checkmark: compile the code)
2. `→` (right arrow: compile and upload the code)
3. `🗑` (trashcan: clean the built code)
4. `🧪` (chemistry vial: run tests. I've never used this)
5. `🔌` (power plug: connect to Serial to view print statements; handy for debugging)


## FAQ (Probably)
#### How do I find my subnet and gateway IP addresses?  
Your machine should already be connected to the internet so you can google the   
commands to show your machine's subnet and gateway IP addresses.   
Change the file defined defined above to make the necessary adjustments.

#### Which IP addresses should I use for the remote control and the Cube?  
Whichever ones aren't currently used. If you suddenly have connection issues,  
perhaps another device has taken one of those IP addresses.  

If you want to be really clever, get the MAC addresses of the remote control and  
Cube, and setup your router to reserve those IP addresses. This will ensure that  
no other device will ever get those IP addresses by accident but that is probably  
unnecessary.

#### What are statements like `#ifdef IS_CUBE`? 
These are used to determine which code is compiled and run. Since the files contain  
code for both the remote control and the Cube, these directives are used to ensure  
the correct code is uploaded to the uC.

#### What's with the `F("some_string_here");` code?  
`F()` allocates the string to the static memory space, saving room in  
RAM for actual code execution. Is it necessary on this uC? No. Is it a good habit? Yes.