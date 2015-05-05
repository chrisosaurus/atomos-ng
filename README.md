#atomos-ng 

atomos - no graph


##What

atomos-ng is a simple, non-graph based, reimplementation of
some of the ideas behind https://github.com/DomNomNom/atomos

if you want a useable implementation of atomos then see
https://github.com/DomNomNom/atomos_gpu


The purpose of atomos-ng is to provide some quick and simple profiling metrics
for the rough ideas behing atomos if we
ignore the existing implementation

atomos-ng is in no way intended as a replacement or competitor
and is only intended to gain some rough metrics on the runtime
costs of simulating atmospherics via random swapping of molecules
between neighbouring cells


##Running

    $ make run

    compiling main CC -o atomos-ng
    `which time` -f "total wall clock time: %e (s)"  ./atomos-ng

    Running simulation with dims '128' * '128' * '128' for '1000' ticks

    init
    total quantity of particles: 402653184

    ticking

    total wall clock time: 168.51 (s)

    make -s clean
    cleaning objects and temporary files
    cleaning executables


Which gives us

    169 seconds / 1000 ticks = 0.169 second per tick


Please note here that 1 tick does not map to 1 frame,
in fact we would require `many` ticks per frame


Current VSZ (captures using a simple ps) for 402 million particles in 128 ^ 3 volume is

    20404 KiB = 19.9 MiB

