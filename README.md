# Acknex-Game-Launcher

Standalone launcher similar to Unity's Configuration tool.

# What it does:
Creates:
- project's folder in *user/documents* to place a config file in

Creates a config file that contains the following settings (can enable/disable any of those, check beginning of main.c):
- screen resolution (set from the list of available screen resolutions of a primary monitor retrived by WinAPI)
- display mode (windowed, borderless and fullscreen)
- fps cap for windowed/borderless display modes
- vsync for fullscreen mode (double/triple buffer)
- graphics quality (low, medium, high, ultra)
- input keybindings (atm no gamepad support)
- language
- path to game's executable (in case end-user messed something up)

And at the end it launches the game's executable! Which is defined automatically (*work_dir* + project's name + .exe) OR can be done by hand.

# How to get it working
All you need to do is initialize all the settings from the config file at the start of your game (check out example folder).

# How to test without compiling
There is a compiled version which can be found inside of *example/bin* folder.

# Known issues
- no gamepad support for keybindings (only mouse+keyboard) as I don't own xinput device. I might add support in future;

# Credits
This tool uses:
- imgui wrapper/plugin which was originally made by Patrick Jendral (jenGs), edited by forum members Txesmi and EVO. Original sources can be found here: https://github.com/ocornut/imgui and https://github.com/pjen/imgui-Lite-C-integration and https://github.com/txesmi/imgui-Lite-C-integration.
- WinAPI to find all supported resolutions of the primary monitor (big thanks to forum members Superku and Emre).

# Screenshots
![Alt text](https://github.com/3RUN/Acknex-Game-Launcher/blob/main/screenshots/shot_0.jpg?raw=true "Preview.")
![Alt text](https://github.com/3RUN/Acknex-Game-Launcher/blob/main/screenshots/shot_1.jpg?raw=true "Preview 1.")
![Alt text](https://github.com/3RUN/Acknex-Game-Launcher/blob/main/screenshots/shot_2.jpg?raw=true "Preview 2.")
![Alt text](https://github.com/3RUN/Acknex-Game-Launcher/blob/main/screenshots/shot_3.jpg?raw=true "Preview 3.")
