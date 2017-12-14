#include <ctime>
#include "../include/MeasureFile.h"

MeasureFile::MeasureFile(std::string filename, std::string header) {
    init(filename, header);
}

MeasureFile::MeasureFile(std::string header) {
    time_t now = time(0);
    char* date = ctime(&now);
    std::string filename("measure-");
    filename += date;

    init(filename, header);
}

void MeasureFile::init(std::string filename, std::string header) {
    file.open(filename, std::ios::out);
    writeHeader(header);
}

void MeasureFile::writeHeader(std::string header) {
    file << header;
}

void MeasureFile::writeMeasure(std::vector<double> measure) {
    int measureLength = measure.size();

    file << "\n";
    for (int i = 0; i < measureLength - 1; i++) {
        file << measure[i] << " ";
    }
    if (measureLength != 0) {
        file << measure[measureLength - 1];
    }
}

void MeasureFile::close() {
    file.close();
}
