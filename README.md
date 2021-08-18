# MessageBoxA-Hook-Roblox
Using MinHook we're able to modify the MessageBoxA calls and modify the caption and text.
There are many methods of doing this using VirtualProtect, check TacticalBFG's method out. (https://github.com/TacticalBFG/AntiBan/blob/master/AntiBan.cpp)

This code does not NOP any instruction out of the CrashUpload function since it's not really a great way of doing it.
Instead I would recommend using FFlags to disable crash uploading.
