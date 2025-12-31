#pragma once

#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>

#include <QString>

#include <map>

#include "sppTableReader.h"
#include "spp.h"

class WavescaleTable
{
public:
    WavescaleTable(unsigned rowsCount);
    
    void loadFromSppFile(Spp spp);
    
    bool hasData();
    
    double * getWaveLengthValues();
    
    void show();

private:
    QWidget * window;
    QHBoxLayout * box;
    QTableView * table;
    QStandardItemModel * model;
    
    void fillModel(std::map<unsigned, std::map<QString, double>> & data);
};