#include <QtCore>
#include <iostream>
#include "machineid.h"

int main()
{
    std::cout << "MachineID: " << machineID().toStdString() << std::endl;
    std::cout << "MachineIDHash: " << machineIDHash() << std::endl;
    return 0;
}
