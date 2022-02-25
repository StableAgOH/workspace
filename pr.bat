@echo off
if exist temp.cpp (
    copy temp.cpp backup.cpp
)
copy template.cpp temp.cpp
