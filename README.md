# wake
プログラムについての説明は以下のURLよりどうぞ（Japanese Description）

https://beneficial-baker-4bf.notion.site/C-wake-8b9893e7625f47d4b455b194cc6ec1e0?pvs=4

English Description here!

https://www.notion.so/C-Automation-Build-wake-cb4e47b8c91b438594ea14db4f2d3e9d?pvs=4

wake is automatically building Makefile to build your source code.
- analyze the dependency
- create a makefile

# constraints
- it is recommend that the OS follow POSIX

# what not supported yet
- some options (-L for a library)
- create a file with arbitrary (.c .cc or .hpp) file identifier

you can handle these problems by fixing the created makefile, or I'm welcome to your contribute for some extentions.

# quick tutorial
Wake is itself build by wake. SO only you have to do is just "make" to compile, then excecute ./wake.

wkconfig file is configuration file of wake.
- CC = gcc or g++ ? whatever compiler for C/C++
- BIN = binary code root directory
- SRC = source code root directory
- OPT = compiler options
- COMMAND = the name of excecutable file
Note that these are necessary to be filled with adequate value.

So, if you want to use wake to your original project, change the value of SRC and BIN and just excecute! After that, you can get Makefile, which is automatically built by wake. It depends on each project whether this process work or not. However, if it does't work for your project, I hope you fix the bugs or contributes! 

# feature works
is refered in Issues.

# how to contribute 
editing now! now feel free to contribute but at least clearness of the changes is necessary to read the pull requests.
