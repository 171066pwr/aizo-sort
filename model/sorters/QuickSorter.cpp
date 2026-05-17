#include "QuickSorter.h"


// template<typename T>
// void QuickSorter<T>::sort(SorTable<T> * sorTable) {
//     qsort(sorTable, 0, sorTable->size-1);
// }
//
// template<typename T>
// void QuickSorter<T>::qsort(SorTable<T> * sorTable, int left, int right)
// {
//     if(left<right)
//     {
//         int m=left;
//         for(int i=left+1;i<=right;i++)
//             if((*sorTable)[i] < (*sorTable)[left])
//                 swap(sorTable,++m,i);
//         swap(sorTable,left,m);
//         qsort(sorTable,left,m-1);
//         qsort(sorTable,m+1,right);
//     }
// }
//
// template<typename T>
// void QuickSorter<T>::swap (SorTable<T> * sorTable, int i, int j){
//     T temp = (*sorTable)[i];
//     (*sorTable)[i] = (*sorTable)[j];
//     (*sorTable)[j] = temp;
// }
