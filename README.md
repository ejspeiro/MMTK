# README File for the Mimetic Methods Toolkit (MTK)

By: **Eduardo J. Sanchez, Ph.D. - esanchez at mail dot sdsu dot edu**
    __________________________________________________________________

## 1. Description

We define numerical methods that are based on discretizations preserving the
properties of their continuum counterparts to be **mimetic**.

The **Mimetic Methods Toolkit (MTK)** is a C++ library for mimetic numerical
methods. It is arranged as a set of classes for **mimetic quadratures**,
**mimetic interpolation**, and **mimetic discretization** methods for the
numerical solution of ordinary and partial differential equations.

This collection of **MATLAB Wrappers for the MTK (MMTK)** allows developers to
invoke the MTK from a MATLAB environment.

    __________________________________________________________________

## 2. Dependencies

This README assumes all of these dependencies are installed in the following
folder:

```
$(HOME)/Libraries/
```

In this version, the MTK optionally uses ATLAS-optimized BLAS and LAPACK
routines for the internal computation on some of the layers. However, ATLAS
requires both BLAS and LAPACK in order to create their optimized distributions.
Therefore, the following dependencies tree arises:

### For Linux and OS X:

1. MATLAB R2014a or greater - Available from: http://www.mathworks.com/

1. MTK - Available from: http://csrc.sdsu.edu/mtk/
    __________________________________________________________________

## 3. Installation

The following instructions assume MATLAB R2014a or greater.

You have two options, either follow the instructions given, **expert install**,
or use the provided **patch file**, **naive install**.

### EXPERT PART 1. CONFIGURATION OF THE MEX COMPILER.

From your MATLAB prompt, type:

```
>> mex -setup C++
MEX configured to use 'g++' for C++ language compilation.
Warning: The MATLAB C and Fortran API has changed to support MATLAB
     variables with more than 2^32-1 elements. In the near future
     you will be required to update your code to utilize the
     new API. You can find more information about this at:

http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-
64-bit-api.html.
>>
```

### EXPERT PART 2. CONFIGURATION OF THE MEX COMPILER SETUP FILE.

The previous step creates the following file:

```
$(HOME)/.matlab/R2014a/mex_C++_glnxa64.xml
```

The purpose of this section is to configure the MATLAB R2014a Mex compiler so
that it can work with the latest C++ standard (C++11).

Please execute the following changes on the aforementioned file (line numbers
may differ):

Lines 26 and 27:

```
CMDLINE1="$CXX -std=c++11 -c $DEFINES $INCLUDE $CXXFLAGS $OPTIM $SRC -o $OBJ"
CMDLINE2="$LDXX -std=c++11 $LDFLAGS $LDTYPE $LINKOPTIM $LINKEXPORT $OBJS $CXXLIBS $LINKLIBS -o $EXE"
```

Line 33:

```
CXXFLAGS="-std=c++11 -ansi -fexceptions -fPIC -fno-omit-frame-pointer -pthread"
```

Line 35 and 26:

```
CXXOPTIMFLAGS="-std=c++11 -O -DNDEBUG"
CXXDEBUGFLAGS="-std=c++11 -g"
```

Line 38:

```
LDXX="gfortran"
```

Line 59:

```
CXXFLAGS="-std=c++11 -ansi -pthread"
```

### NAIVE PART 1. CONFIGURATION OF THE MEX COMPILER.

From your MATLAB prompt, type:

```
>> mex -setup C++
MEX configured to use 'g++' for C++ language compilation.
Warning: The MATLAB C and Fortran API has changed to support MATLAB
     variables with more than 2^32-1 elements. In the near future
     you will be required to update your code to utilize the
     new API. You can find more information about this at:

http://www.mathworks.com/help/matlab/matlab_external/upgrading-mex-files-to-use-
64-bit-api.html.
>>
```

### NAIVE PART 2. CONFIGURATION OF THE MEX COMPILER SETUP FILE.

```
cd $HOME/.matlab/R2014a
chmod +w mex_C++_glnxa64.xml
patch < mex_C++_glnxa64.patch
chmod -w mex_C++_glnxa64.xml
```
Exit terminal, and restart MATLAB. You can use C++11 to create MEX files now!

### PART 3: CONFIGURATION OF THE MAKEFILE.

The following steps are required the build and test the MTK. Please use the
accompanying `Makefile.inc` file, which should provide a solid template to
start with. The following command provides help on the options for make:

```
$ make help
-----
Makefile for the MMTK.

Options are:
- all: builds he library, the tests, and examples.

- gendoc: generates the documentation for the library.

- clean: cleans ALL the generated files.
-----
```

### PART 4. BUILD THE MMTK.

From your shell, at the base folder of the MMTK, just type:

```
make
```

If successful you'll read:

```
----- Library created! Check in /home/ejspeiro/Dropbox/MTK/lib
```
    __________________________________________________________________

## 4. Frequently Asked Questions

Q: Why haven't you guys implemented GBS to build the library?
A: I'm on it as we speak! ;)

Q: When will the other flavors be ready?
A: Soon! I'm working on getting help on developing those.

Q: Is there any main reference when it comes to the theory on Mimetic Methods?
A: Yes! Check: http://www.csrc.sdsu.edu/mimetic-book

Q: Do I need to generate the documentation myself?
A: You can if you want to... but if you DO NOT want to, just go to our website.
    __________________________________________________________________

## 5. Contact, Support, and Credits

The MTK is developed by researchers and adjuncts to the
[Computational Science Research Center (CSRC)](http://www.csrc.sdsu.edu/)
at [San Diego State University (SDSU)](http://www.sdsu.edu/).

Developers are members of:

1. Mimetic Numerical Methods Research and Development Group.
2. Computational Geoscience Research and Development Group.
3. Ocean Modeling Research and Development Group.

Currently the developers are:

- **Eduardo J. Sanchez, Ph.D. - esanchez at mail dot sdsu dot edu** - @ejspeiro
- Jose E. Castillo, Ph.D. - jcastillo at mail dot sdsu dot edu
- Guillermo F. Miranda, Ph.D. - unigrav at hotmail dot com
- Christopher P. Paolini, Ph.D. - paolini at engineering dot sdsu dot edu
- Angel Boada.
- Johnny Corbino.
- Raul Vargas-Navarro.

Finally, please feel free to contact me with suggestions or corrections:

**Eduardo J. Sanchez, Ph.D. - esanchez at mail dot sdsu dot edu** - @ejspeiro

Thanks and happy coding!
