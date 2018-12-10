# Aggregation simulation

The Aggregate simulation is a small stand alone program that can
simulate the formation of an aggregate.

## Build and Deployment

### Building the project

Building Aggregate simulation requires a modern C++ compiler and a CMake version 3.0 or
higher.

On linux, building should be as simple as (with git)

    git clone https://github.com/CorentinBT/Aggregation.git
    cd Aggregate
    mkdir build
    cd build
    cmake ..
    make

## Running

Go to the `bin/` directory and simply run the aggregate binary file. The binary is invoked with the following arguments:

```sh
./aggregate --filespawn FILE [--time] [--input FILE] [--output FILE] [--radroot RADIUS]
```

* `--filespawn` input file for spheres to spawn
* `--time` show computing time
* `--input` input file to begin with an initial aggregate
* `--output` output file for the aggregate (default : aggregat.txt)
* `--radroot` radius of the root sphere (default : 6.0)
* `--explrad` default exploration radius if not provided in the input file (see below)
* `--nbstep` default number of gradient step if not provided in the input file (see below)
* `--alpha` default angle of spawn in degree between 0 and 360
* `--beta` default angle of spawn in degree between -90 and 90

## Outputs

The `FILE` output, with option `--output`, contains a list of all spheres computed.
Each line characterize a sphere :

* The first column provides the ID of the sphere.
* The second, third and fourth column provide the x, y and z position of the sphere.
* The fifth column provides the radius of the sphere.

## Inputs

The `FILE` input, with option `--filespawn`, contains a list of all spheres to spawn.
Each line characterize a group of spheres :

* The first column provides the number sphere(s) to spawn.
* The second column provides the radius of sphere(s) to spawn.
* The third column provides the exploration radius for this group of sphere(s).

The third and fourth column are optionals if no values is provided the default values will be applied.

For example :
```
100 5 50 
25 2 25 
50 1
```
Is equivalent to :

Spawn 100 spheres of radius 5 and exploration radius of 50.  
Spawn 25 spheres of radius 2 and exploration radius of 25.  
Spawn 50 spheres of radius 1 and with default exploration radius.  


The `FILE` input, with option `--input`, contains a list of all spheres precomputed.
The simulation will then follow this precomputed aggregate. The `FILE` should follow the
same syntax as the output file (see above).

## Visualization

The `printSphere.m` matlab script is provided to visualize the computed aggregate.  