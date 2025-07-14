#include "../../include/sppTable.h"
#include <iostream>

SppTable::SppTable(int rowsCount, int colsCount)
{
    table = new QTableView();

    sppModel = new QStandardItemModel(rowsCount, colsCount);
}

void SppTable::loadSppFromFile(std::string sppPath)
{
    std::map<int, std::map<std::string, float>> sppData;
    
    SppReader::readSppData(sppPath, sppData);
    fillSppModel(sppData);

    table->setModel(sppModel);
        
    sppData.clear();    
}

void SppTable::fillSppModel(std::map<int, std::map<std::string, float>> & sppData)
{
    sppModel->setHeaderData(0, Qt::Horizontal, "Канал");
    sppModel->setHeaderData(1, Qt::Horizontal, "Длина волны");
    sppModel->setHeaderData(2, Qt::Horizontal, "Ширина канала");

    int currentRow = 0;

    for(auto it = sppData.begin(); it != sppData.end(); it++)
    {
        int channelNum = it->first;
        int waveLen = sppData[channelNum]["WaveLen"];
        int waveDelta = sppData[channelNum]["WaveDelta"];
        
        sppModel->setItem(currentRow, 0, new QStandardItem(QString::fromStdString(std::to_string(channelNum))));
        sppModel->setItem(currentRow, 1, new QStandardItem(QString::fromStdString(std::to_string(waveLen))));
        sppModel->setItem(currentRow, 2, new QStandardItem(QString::fromStdString(std::to_string(waveDelta))));
        
        currentRow++;
    }
}

void SppTable::show()
{
    table->show();
}