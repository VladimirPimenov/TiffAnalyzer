#pragma once

#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>

#include <string>
#include <map>

#include "sppTableReader.h"

class WavescaleTable
{
public:
    WavescaleTable(int rowsCount, int colsCount);
    
    void loadFromSppFile(std::string sppPath);
    
    bool hasData();
    
    double * getWaveLengthValues();
    
    void show();

private:
    QWidget * window;
    QHBoxLayout * box;
    QTableView * table;
    QStandardItemModel * model;
    
    void fillModel(std::map<int, std::map<std::string, float>> & data);
};