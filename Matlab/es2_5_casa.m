clc
clear all
close all

x = 1:20;
y = [243 209 181 179 180 166 163 157 187 192 138 95 56 32 21 12 11 61 146 186];
z = [7.5 14.5];
s = interp1(x, y, z)
plot(x, y, "b", z, s, "ko", "LineWidth", 3)