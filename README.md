# osh: The Open Shell

```osh``` is a rudimentary shell written in C for use in *nix systems. The original intent behind the shell was a project to introduce myself to systems programming, as well as to learn about the inner workings of a shell, and gain more experience with C programming.

## Functionality

At the moment, the shell supports three builtin commands, being ```cd```, ```help``` and ```exit```. 

Currently, I'm working on adding:
* Piping
* Redirection
* Parallel execution

## Building osh

In the top level directory, run ```make``` to create a ```osh``` executable and ```/build/``` directory with individual object files. To clear the executable and objects, run ```make clean```.

## Credits

This project adapts much of its base code from Stephen Brennan's [tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/), which I followed to create the base functionality of ```osh```.