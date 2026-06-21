
# 1. Config file

Unless provided as parameter, program will try default location config.txt

Program works in two modes, based on configuration:
[1]. Input file
[2]. Data generation

If INPUT_FILE value exists, program will run in mode [1] regardless of other settings.
For working examples please view input_file.conf and data_generation.conf

# 2. Config file structure

# 2.1. Config file structure for mode [1]:
INPUT_FILE:x            //name of input file; Format of input file in section 4
OUTPUT_FILE:x           //name of output file
DATA_SET:samples        //int value. Any extra values will be omitted
DISPLAY_DATA:bool       //OPTIONAL. int: 0 - no logs displayed, 1 - display progress, 2 - display data (default); Set to 0 to mute displaying data tables pre and post sort;
SORTERS:x,y#x,y#x       //description of sorter configuration in section 3

# 2.2. Config file structure for mode [2]:
OUTPUT_FILE:x                                   //name of output file
DATA_TYPE:x                                     //where x: int, char, float, double
DATA_SET:initial_size,increment,steps,samples   //int values. Example: 100,100,9,10 means that tables of size from 100 to 1000 (100+9*100) will be generated, 10 samples for each size
PRE_SORT:order,percentage                       //OPTIONAL. Order: 1 - asc (default), 0 - desc; percentage int value [0 (default); 100]
DISPLAY_DATA:bool                               //OPTIONAL. Bool: 1 - yes (default), 0 - no; Set to 0 to mute displaying data tables pre and post sort;
SORTERS:x,y#x                                   //description of sorter configuration in section 3

# 3. Sorter configuration

SORTERS:x,y#x,y
    where x: int TYPE, y:OPTIONAL int VARIANT, #: separator (literal hash character)s
    TYPE:
        HEAP_SORT = 0,
        INSERTION_SORT = 1,
        QUICK_SORT = 2,
        SHELL_SORT = 3
    VARIANT (applies to QuickSort and Shell):
        QuickSort (pivot position):
            RANDOM = 0,
            LOW = 1,
            HIGH = 2,
            CENTER = 3
        Shell (gap sequence):
            KNUTH = 0,
            SHELL = 1

# 4. Input file format

type        //OPTIONAL character indicating data type: 'i' - int (default), 'c' - char, 'f' - float, 'd' - double
size        //int size of array
element1    //each array element in separate line
element2
...

# 5. Output file format

Run configuration:      //launch configuration in human-friendly form
Input file: filename    //OPTIONAL
Data type: type         //type of sorted data
Dataset:
initial size: x         //initial data size
increment: x            //size increase per step
steps: x                //how many data size increases
samples: x              //how many samples per one data size
Pre-sort mode: mode     //pre-sort mode description
Display data: 1         //1 for true, 0 for false
Sorters:
SorterName1             //used sorters, each name in separate line
SorterName2 - variant
...

Run result:
SortName - variant
data_size,average,median,min,max    //comma-separated columns of time results for array size, in [s*10^-6] (microseconds)
data_size,average,median,min,max
...
SortName - variant                  //next sorter with results
data_size,average,median,min,max
...

# 6. Running on selected processor

Use command:
start /affinity <hex> 1_sort.exe <your_config_file>
Where <hex> is hex mask of allowed processors: F0 means processors 7-4, FF 0-7, 1 just 0

# 7. Build

Project was written and built using JetBrains CLion. It utilises CMakeLists. Please find config files included with the code.

# 8. Tests

Project has very primitive prosthesis of unit tests, available to be built from CMakeLists as project Tests.

It can be ignored otherwise.

# 9. Utility classes

Project might have some unused utility classess and functions that were either borrowed from other projects or used earlier but ultimately orphaned.

Please ignore them.