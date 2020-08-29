#include "TransmitTask.h"

using namespace AppSoft;

int main(int argc, char* argv[])
{
    TransmitArgs args;

    if (args.parse(argc, argv) == 0) {
        TransmitTask task(args);
        task.run();
    }

    return 0;
}