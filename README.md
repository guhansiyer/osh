# osh: The Open Shell

```osh``` is a rudimentary shell written in C for use in *nix systems. The original intent behind the shell was a project to introduce myself to systems programming, as well as to learn about the functionality of a shell, and gain more experience with C programming.

## Functionality

All implemented shell commands are represented as built-ins, which so far includes:
* `cd`
* `echo`
* `exit`
* `help`
* `sinfo`: reports system information (memory usage, uptime, kernel & CPU info)

All other classic shell commands (not builtins) such as `ls` work through their native *nix implementations currently.  

Currently, I'm working on adding:
* Piping
* Redirection
* Persistent command history
* Parallel execution

## Building osh

In the top level directory, run ```make``` to create a ```osh``` executable and ```/build/``` directory with individual object files. To clear the executable and objects, run ```make clean```.

## Credits

This project adapts much of its base code from Stephen Brennan's [tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/), which I followed to create the base functionality of ```osh```.