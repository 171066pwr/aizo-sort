
# 1. Config file

fixed name config.txt
Works in two modes:
[1]. Input file
[2]. Data generation

If INPUT_FILE exists, program will run in mode [1] regardless of other settings.
For working examples please view input_file.conf and data_generation.conf

# 2. Config file structure

# 2.1. Config file structure for mode [1]:
INPUT_FILE:x            //name of input file; Format of input file in section 4
OUTPUT_FILE:x           //name of output file
DATA_SET:samples        //int value. Any extra values will be omitted
DISPLAY_DATA:bool       //OPTIONAL. Bool: 1 - yes (default), 0 - no; Set to 0 to mute displaying data tables pre and post sort;
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
{x,y}SortName - variant:            //x - sort type enum, y - sort variant enum
data_size,average,median,min,max    //comma-separated columns of time results for array size
data_size,average,median,min,max
...
{x,y}SortName - variant:            //next sorter with results
data_size,average,median,min,max
...


