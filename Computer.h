//
// Created by Иван Березуцкий on 25.03.2023.
//

#ifndef KP_6_COMPUTER_H
#define KP_6_COMPUTER_H

#include "string"

using namespace std;
enum types_gpu {
    integrated,
    external,
    agp,
    pci
};
enum operating_systems {
    windows,
    linux,
    macos
};

class Computer {
private:
    string surname;
    int n_cpu;
    string cpu_type;
    int memory_size;
    types_gpu type_gpu;
    int video_memory_size;
    int external_memory_size;
    operating_systems os;
public:
    [[nodiscard]] const string &getSurname() const;

    void setSurname(const string &surname);

    [[nodiscard]] int getNCpu() const;

    void setNCpu(int nCpu);

    [[nodiscard]] const string &getCpuType() const;

    void setCpuType(const string &cpuType);

    [[nodiscard]] int getMemorySize() const;

    void setMemorySize(int memorySize);

    [[nodiscard]] types_gpu getTypeGpu() const;

    void setTypeGpu(types_gpu typeGpu);

    [[nodiscard]] int getVideoMemorySize() const;

    void setVideoMemorySize(int videoMemorySize);

    [[nodiscard]] int getExternalMemorySize() const;

    void setExternalMemorySize(int externalMemorySize);

    [[nodiscard]] operating_systems getOs() const;

    void setOs(operating_systems os);

public:
    Computer(string surname, int nCpu, string cpuType, int memorySize, types_gpu typeGpu,
             int videoMemorySize, int externalMemorySize, operating_systems os);
};


#endif //KP_6_COMPUTER_H
