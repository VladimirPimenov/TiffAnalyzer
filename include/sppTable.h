#pragma once

#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>

#include <string>
#include <map>

#include "sppReader.h"

class SppTable
{
public:

    SppTable(int rowsCount, int colsCount);
    
    void loadSppFromFile(std::string sppPath);
    
    void show();

private:
    QWidget * window;
    QHBoxLayout * box;
    QTableView * table;
    QStandardItemModel * sppModel;
    
    void fillSppModel(std::map<int, std::map<std::string, float>> & sppData);
};