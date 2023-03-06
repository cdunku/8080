# 8080 Core

The complete emulation of the Intel 8080 CPU written completely in the C99 standard.


## Goals:


- Make it as **readable** as possible without the cost of performance. 

- Make it **portable**; It has been tested on MacOS Ventura (13.x), Fedora 36, Windows 11. MacOS and Fedora tests were baremetal and Windows 11 was tested on a virtual machine. (Software used: [UTM](https://mac.getutm.app/))

- Make it as **accurate**; tried different test suites, like the [Intel 8080 KR580VM80A (Russian model)](https://github.com/begoon/i8080-core/tree/master/assets) and the [altairclone](https://altairclone.com/downloads/cpu_tests/) being one of them.


The emulator was tested on different machines with the following specifications:

`Machine 1 (MacOS)`:


`CPU` = i5 10500 

`RAM` = 64GB DDR4-2666MHz

The test lasted roughly `~20 seconds`



`Machine 2 (Linux)`:


`CPU` = Ryzen 7 5700U

`RAM` = 24GB DDR4-3200MHz

The test lasted rougly `~22 seconds`




`Machine 3 (Windows 11)`:


`CPU` = Pentium 4 HT

`RAM` = 32GB DDR4-2666MHz

The test lasted roughly `~26 seconds`


## Compilation:

The emulator was tested on all 3 popular operating systems.

Compilers used on every platform:

`Linux`: `GCC`

`MacOS`: `GCC & CLANG`

`Windows`: `MinGW`

### Linux

`GCC` is preinstalled to most Linux distrubitions. 

### MacOS

In order to install `GCC` on MacOS you firstly need to open the `Terminal`. `Command + Space` to open Spotlight and type `Terminal` and insert the following command: ``xcode-select --install``.

### Windows

Installing `GCC` on Windows is much more time consuming. First and foremost, you can install all the GNU Compilers on [SourceForge](https://sourceforge.net/projects/mingw/). Go through the setup process until you reach the MinGW installation manager and mark the desired options for installation and click apply. I'd recommend you to pick `mingw-developer-tools`, `mingw-32 base`, `mingw-32-gcc-g++` and `msys-base` (Other options include different compilers for different languages, e.g. `g++` is for `C++`). Next you'll need to change your system's Enviornment Variables. Run `Super/Windows + R`, type `systempropertiesadvanced`, select `Environment Variables`, double click `Path` and in the `System variables` section click `New` and add `C:\MinGW\bin` as a path. Open PowerShell and insert `gcc -v`, the output should look something like this:


```
PS C:\Users\user> gcc -v
Using built-in specs.
COLLECT_GCC=C:\MinGW\bin\gcc.exe
COLLECT_LTO_WRAPPER=c:/mingw/bin/../libexec/gcc/mingw32/6.3.0/lto-wrapper.exe
Target: mingw32
Configured with: ../src/gcc-6.3.0/configure --build=x86_64-pc-linux-gnu --host=mingw32 --target=mingw32 --with-gmp=/mingw --with-mpfr --with-mpc=/mingw --with-isl=/mingw --prefix=/mingw --disable-win32-registry --with-arch=i586 --with-tune=generic --enable-languages=c,c++,objc,obj-c++,fortran,ada --with-pkgversion='MinGW.org GCC-6.3.0-1' --enable-static --enable-shared --enable-threads --with-dwarf2 --disable-sjlj-exceptions --enable-version-specific-runtime-libs --with-libiconv-prefix=/mingw --with-libintl-prefix=/mingw --enable-libstdcxx-debug --enable-libgomp --disable-libvtv --enable-nls
Thread model: win32
gcc version 6.3.0 (MinGW.org GCC-6.3.0-1)
```


For some reason I couldn't install `Make` with MinGW so I did the following:

Open `Windows Powershell` with administrator permissions and run the following command in order to install `Chocolatey`: 

`Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))`. 

When `Chocolatey` is installed run `choco install make` to install `Make`. After that you're good to go!


## Emulator output:

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


## Resources:

[Superzazu's 8080 implementation](https://github.com/superzazu/8080)

[Intel 8080/8085 opcode table](https://tobiasvl.github.io/optable/intel-8080/)

[Intel 8080 Assembly Programming Manual](https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf)

[Emulator101](http://www.emulator101.com/)
