@echo off
if not exist in.in (
    type nul > in.in
)
if not exist out.out (
    type nul > out.out
)
