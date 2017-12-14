#ifndef MEASURE_FILE_H
#define MEASURE_FILE_H

#include <fstream>
#include <string>
#include <vector>

class MeasureFile {

public:
    MeasureFile(std::string filename, std::string header);
    MeasureFile(std::string header);

    void writeMeasure(std::vector<double> measure);
    void close();

private:
    void init(std::string filename, std::string header);
    void writeHeader(std::string header);

    std::fstream file;

};

#endif
