
#include <stdio.h>
#include <stdlib.h>
#include "boolcompiler.h"

int main() {

    Map* m = mapInit(10);

    mapInsert(m, 'a', 10);



    mapFree(m);

}