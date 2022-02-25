@echo off
if not exist src (
    md src
)
if not exist in.in (
    type nul > in.in
)
if exist src\temp.cpp (
    copy src\temp.cpp backup.cpp
)
copy template.cpp src\temp.cpp
