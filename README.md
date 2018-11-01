As an independent IT contractor I work on a variety of projects with a variety
of clients.  And one thing these projects have in common is that they generally
have nothing in common.  These project use a wide range of development environments
and a array of differing IDE's. I find myself managing multiple versions of Java
Development Kits, Eclipse IDE's, differing versions of CMake, GCC, etc.  Legacy and 
EOL'ed software is a way of life.

For a long time I managed project specific scripts that my development environment.
These scripts would add the appropriate software to PATH and set other 
environment variables.

This only worked moderately well though.  Installing minor releases of software
would requiring finding and sorting through all these scripts to find which ones
required updating.  This could get tedious at times.

Out of this pain was born envsel.  A rather simple program to define projects,
applications, scripts, and their relationships to setup an environment.  Everything
is driven by one simple JSON file that consolidates all the information into one
location that can be easily updated.



