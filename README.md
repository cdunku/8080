# 8080

The complete emulation of the Intel 8080 CPU written completely in C99. 


## Goals:


- Make it as **readable** as possible without the cost of performance. 

- Make it **portable**; It has been tested on MacOS Ventura (13.x) and Fedora 36. **(Windows compatibility will come soon)**

- Make it as **accurate**; tried different test suites, like the [Intel 8080 KR580VM80A (Russian model)](https://github.com/begoon/i8080-core) and the [altairclone](https://altairclone.com/downloads/cpu_tests/) being one of them.


The emulator was tested on different machines with the following specifications:

Machine 1:
CPU = i5 10500 
RAM = 64GB DDR4-2666MHz
The test lasted roughly ~20 seconds

Machine 2:
CPU = Ryzen 7 5700U
RAM = 24GB DDR4-3200MHz
The test lasted rougly ~22 seconds


The `altairclone` test should have the desired output:

```
 ________  ________  ________  ________
|\   __  \|\   __  \|\   __  \|\   __  \
\ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \
 \ \   __  \ \  \|\  \ \   __  \ \  \|\  \
  \ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \
   \ \_______\ \_______\ \_______\ \_______\
    \|_______|\|_______|\|_______|\|_______|


*** FILE LOADED: test_files/altairclone/TST8080.COM
MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC
 VERSION 1.0  (C) 1980

 CPU IS OPERATIONAL

*** FILE LOADED: test_files/altairclone/CPUTEST.COM

DIAGNOSTICS II V1.2 - CPU TEST
COPYRIGHT (C) 1981 - SUPERSOFT ASSOCIATES

ABCDEFGHIJKLMNOPQRSTUVWXYZ
CPU IS 8080/8085
BEGIN TIMING TEST
END TIMING TEST
CPU TESTS OK


*** FILE LOADED: test_files/altairclone/8080PRE.COM
8080 Preliminary tests complete

*** FILE LOADED: test_files/altairclone/8080EXM.COM
8080 instruction exerciser
dad <b,d,h,sp>................  PASS! crc is:14474ba6
aluop nn......................  PASS! crc is:9e922f9e
aluop <b,c,d,e,h,l,m,a>.......  PASS! crc is:cf762c86
<daa,cma,stc,cmc>.............  PASS! crc is:bb3f030c
<inr,dcr> a...................  PASS! crc is:adb6460e
<inr,dcr> b...................  PASS! crc is:83ed1345
<inx,dcx> b...................  PASS! crc is:f79287cd
<inr,dcr> c...................  PASS! crc is:e5f6721b
<inr,dcr> d...................  PASS! crc is:15b5579a
<inx,dcx> d...................  PASS! crc is:7f4e2501
<inr,dcr> e...................  PASS! crc is:cf2ab396
<inr,dcr> h...................  PASS! crc is:12b2952c
<inx,dcx> h...................  PASS! crc is:9f2b23c0
<inr,dcr> l...................  PASS! crc is:ff57d356
<inr,dcr> m...................  PASS! crc is:92e963bd
<inx,dcx> sp..................  PASS! crc is:d5702fab
lhld nnnn.....................  PASS! crc is:a9c3d5cb
shld nnnn.....................  PASS! crc is:e8864f26
lxi <b,d,h,sp>,nnnn...........  PASS! crc is:fcf46e12
ldax <b,d>....................  PASS! crc is:2b821d5f
mvi <b,c,d,e,h,l,m,a>,nn......  PASS! crc is:eaa72044
mov <bcdehla>,<bcdehla>.......  PASS! crc is:10b58cee
sta nnnn / lda nnnn...........  PASS! crc is:ed57af72
<rlc,rrc,ral,rar>.............  PASS! crc is:e0d89235
stax <b,d>....................  PASS! crc is:2b0471e9
Tests complete
Program executed in 19 seconds
```


## Resources

[Superzazu's 8080 implementation](https://github.com/superzazu/8080)

[Intel 8080/8085 opcode table](https://tobiasvl.github.io/optable/intel-8080/)

[Intel 8080 Assembly Programming Manual](https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf)

[Emulator101](http://www.emulator101.com/)
