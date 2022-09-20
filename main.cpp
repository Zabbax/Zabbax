/*
ADVANTAGES/DISADVANTAGES LINKED LIST:
Linked lists utilize dynamic memory allocation this makes 
    lists easy to work with. This makes modifying the data within an array simple.
    Since anything added or deleted will have it's memory instantly freed.
The main issue with linked lists is the amount of resources and time it uses to
    traverse. This is especially noticeable when dealing with larger amounts of data.
    Since each element of the linked list must be passed through.

ADVANTAGES/DISADVANTAGES ARRAY:
Arrays make it easy to access any infomration within the array since the data
    is in order.
Memory allocatin is the main draw back of arrays. Because extending the array
 past it's initial allocation would require the a new larger array.
*/

#include <iostream>

#include "wrapper.h"

int main() 
{
    srand((unsigned)time(0));
    wrapper app("commands.csv", "scores.csv");
    app.run();
    return 0;
}