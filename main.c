#include "libs/algorithms/tasks/fill_matrix.h"
#include "libs/algorithms/tasks/game_life.h"
#include "libs/algorithms/tasks/median_filter.h"
#include "libs/algorithms/tasks/get_domains.h"
#include "libs/algorithms/tasks/get_submatrix.h"
#include "libs/algorithms/tasks/generate_numbers.h"
#include "libs/algorithms/tasks/get_binary_tree.h"
#include "libs/algorithms/tasks/rearrange_string.h"
#include "libs/algorithms/tasks/auto_fill.h"

void test() {
    test_fillMatrix();
    test_gameLife();
    test_medianFilter();
    test_getDomainsInFile();
    test_getSubmatrix();
    test_generateNumbers();
    test_generateTree();
    test_rearrangeStringInFile();
    test_autoFill();
}

int main() {
    test();

    return 0;
}