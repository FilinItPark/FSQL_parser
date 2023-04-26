//
// Created by Иван Березуцкий on 25.03.2023.
//

#include "Computer.h"

#include <utility>

Computer::Computer(string surname, int nCpu, string cpuType, int memorySize, types_gpu typeGpu,
                   int videoMemorySize, int externalMemorySize, operating_systems os) : surname(std::move(surname)), n_cpu(nCpu),
                                                                                          cpu_type(std::move(cpuType)),
                                                                                          memory_size(memorySize),
                                                                                          type_gpu(typeGpu),
                                                                                          video_memory_size(
                                                                                                  videoMemorySize),
                                                                                          external_memory_size(
                                                                                                  externalMemorySize),
                                                                                          os(os) {}

const string &Computer::getSurname() const {
    return surname;
}

void Computer::setSurname(const string &surname) {
    Computer::surname = surname;
}

int Computer::getNCpu() const {
    return n_cpu;
}

void Computer::setNCpu(int nCpu) {
    n_cpu = nCpu;
}

const string &Computer::getCpuType() const {
    return cpu_type;
}

void Computer::setCpuType(const string &cpuType) {
    cpu_type = cpuType;
}

int Computer::getMemorySize() const {
    return memory_size;
}

void Computer::setMemorySize(int memorySize) {
    memory_size = memorySize;
}

types_gpu Computer::getTypeGpu() const {
    return type_gpu;
}

void Computer::setTypeGpu(types_gpu typeGpu) {
    type_gpu = typeGpu;
}

int Computer::getVideoMemorySize() const {
    return video_memory_size;
}

void Computer::setVideoMemorySize(int videoMemorySize) {
    video_memory_size = videoMemorySize;
}

int Computer::getExternalMemorySize() const {
    return external_memory_size;
}

void Computer::setExternalMemorySize(int externalMemorySize) {
    external_memory_size = externalMemorySize;
}

operating_systems Computer::getOs() const {
    return os;
}

void Computer::setOs(operating_systems os) {
    Computer::os = os;
}
