CFLAGS ?= -std=c++98 -Wall -Wextra

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = lib_info

all: $(ALL)

# -------------------------
# Executables

lib_info: lib_info.cpp
	g++ $(CFLAGS) -o lib_info lib_info.cpp

