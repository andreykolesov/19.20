#include "libs/algorithms/tasks/fill_matrix.h"
#include "libs/algorithms/tasks/game_life.h"
#include "libs/algorithms/tasks/median_filter.h"
#include "libs/algorithms/tasks/get_domains.h"

void test() {
    test_fillMatrix();
    test_gameLife();
    test_medianFilter();
    test_getDomainsInFile();
}

int main() {
    test();

    return 0;
}