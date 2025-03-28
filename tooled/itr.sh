#!/bin/bash

./obj/compiler test/test1.c -o out.dot
xdot out.dot 2>/dev/null