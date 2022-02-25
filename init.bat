@echo off
if not exist src (
    md src
)
if not exist in.in (
    type nul > in.in
)
if not exist out.out (
    type nul > out.out
)
code in.in out.out
del init.bat
