OSAL / Embedded System
--------------------------------------------------------------------------------

OSAL is an operating system abstraction layer. It provides an API to develop
portable, platform independent code with a particular application in embedded
systems. This directory contains an example application setup in an OSAL
environment.  A stripped-down minimalist OSAL library for linux/i86 is
contained in this directory and used a realistic setup. 

In the center of the example lies the implementation of 'ByteLoader_OSAL'. It
is an example of how to adapt towards a particular operating system API. The
few lines of its implementation demonstrate the ease of how to adapt to
different setups. Adapting to other, possibly embedded, systems should be 
restricted to developing a derivate of the 'ByteLoader' class.

FILES: 
    main.c      -- OSAL startup procedure (tasks, muteces, queues).
    tasks.c     -- tasks: lexical analyzer, receiver, and a system monitor.
    auxiliary.c -- auxiliary helper functions.

LICENSE/COPYRIGHT:

    Non-OSAL files in this directory: (C) Frank-Rene Schaefer; License: MIT.
    
    OSAL is distributed under license terms named 'NASA Open Source Agreement
    Version 1.3'. It was originally developed by the Flight Software Systems
    Branch at NASA Goddard Space Flight Center.
--------------------------------------------------------------------------------
