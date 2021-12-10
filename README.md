# Acknex-Game-Launcher

Standalone launcher similar to Unity's Configuration window.

# What it does:
- Creates a config file that contains the following settings:
-screen resolution (set from the list of available screen resolutions retrived by WinAPI)
-display mode (windowed, borderless fullscreen and fullscreen)
-graphics quality (low, medium, high, ultra)
-input keybindings (atm no gamepad support)
-language
-path to game's executable (in case end-user messed something up).
You can easily show/hide any of those settings (check out beginning on main.c).
- Launches the game (predefined executable)

# How to get it working
All you need to do is initialize all the settings from the config file at the start of your game (example will follow soon).

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
