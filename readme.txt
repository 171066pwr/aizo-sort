Config file
fixed name config.txt

structure:_____________________
DATA_TYPE:x                                     //where x: i - int, c - char, f - float, d - double
DATA_SET:initial_size,increment,steps,samples   //int values. Example: 100,100,9,10 means that tables of size from 100 to 1000 (100+9*100) will be generated, 10 samples for each size
PRE_SORT:order,percentage                       //OPTIONAL. Order: 1 - asc (default), 0 - desc; percentage int value 0 (default)-100
DISPLAY_DATA:bool                               //OPTIONAL. Bool: 1 - yes (default), 0 - no; Set to 0 to mute displaying data tables pre and post sort;
SORTERS:{{entry_1},{entry_1},{entry_1}}         //entry:int type, OPTIONAL int variant (default 0); Types and variants might duplicate.
/*
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
*/
_______________________________
