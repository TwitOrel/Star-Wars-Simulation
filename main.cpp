#include <iostream>
#include "./header/Controller.h"


using namespace std;

int main(int argc, char *argv[]) {
    cout.precision(2);
    cout << std::fixed;

    Controller controller;
    controller.run(argc, argv);

    return 0;
}
