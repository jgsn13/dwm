# dwm - dynamic window manager
A fork of [dwm](https://dwm.suckless.org/), an extremely fast, small, and dynamic window manager for X.


### Notes
I highly recomend you check out the config file to see the colors, icons, keybinds and other stuff.

I don't use the Xdefaults patch because I mean it's too trivial to use the [config.def.h](config.def.h) file.

The installation will create 4 binaries in your system:
- dwm_status_bar
- print_fullscreen
- print_select
- print_window
You can modify them if you have problems or you just want to, and then you must (re)compile it. They are avaliable inside the [scripts](scripts) folder.

All settings can be done in the [config.def.h](config.def.h) file if you don't like my settings, the installation process will remove the *config.h* file. I decided to did it because I don't like having two configuration files at the same time.

Throughout the [config file](config.def.h) you can check the keybings and all dependencies (I think you must do it, it's very important).


### Requirements
In order to build dwm you need the Xlib header files.

A [Nerd Font](https://www.nerdfonts.com) (I'm using **JetBrainsMono Nerd** btw) for the status bar.

**scrot** to take screenshots.

**viewnior** to see the screenshot instantly (it will open automatically in the 8th tag).

**[st](https://github.com/JoaquimGregorio/st)** is the default terminal emulator (there's also a keybind to launch **alacritty**).

**dmenu** to launch applications.

**amixer** to control the sound.

**nvim** (Optional) because there'is a keybind that launchs nvim inside st.

**ytop** (Optional).

**ranger** (Optional).

**slock** (Optional).

***Don't use root user to install, use `sudo`, otherwise the makefile will create folders/files in the wrong place***


### Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm:
```
sudo make clean install
```


### Running dwm
Add the following line to your ***.xinitrc*** (or any other xorg server starter) to start dwm using ***startx/xinit (or sx if you use it)***:
```
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your ***.xinitrc***:
```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```
**I highly recommend that you use the [script](scripts/dwm_status_bar) I made and run it in your .xinitrc before `exec dwm`.**
Example (my config):
*.config/sx/sxrc* or *.xinitrc*
```
xsetroot -cursor_name left_ptr &
${HOME}/.fehbg &
dwm_status_bar &
setxkbmap br dvorak
picom -f &
exec dwm
```


### Configuration
The configuration of dwm is done by editing ***config.def.h***
and (re)compiling the source code.


### Screenshots

![Look](screenshots/look.png)
