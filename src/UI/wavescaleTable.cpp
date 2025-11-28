#include "../../include/wavescaleTable.h"

#include <QHeaderView>

WavescaleTable::WavescaleTable(int rowsCount, int colsCount)
{
    window = new QWidget();
    window->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    
    table = new QTableView();
    
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->verticalHeader()->setVisible(false);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    
    box = new QHBoxLayout(window);
    box->addWidget(table);

    model = new QStandardItemModel(rowsCount, colsCount);
}

void WavescaleTable::loadFromSppFile(std::string sppPath)
{
    std::map<int, std::map<std::string, float>> sppData;
    
    SppTableReader::readSppData(sppPath, sppData);
    fillModel(sppData);

    table->setModel(model);
        
    sppData.clear();    
}

void WavescaleTable::fillModel(std::map<int, std::map<std::string, float>> & data)
{
    model->setHeaderData(0, Qt::Horizontal, "Канал");
    model->setHeaderData(1, Qt::Horizontal, "Длина волны");
    model->setHeaderData(2, Qt::Horizontal, "Ширина канала");

    int currentRow = 0;

    for(auto it = data.begin(); it != data.end(); it++)
    {
        int channelNum = it->first;
        double waveLen = data[channelNum]["WaveLen"];
        double waveDelta = data[channelNum]["WaveDelta"];
        
        model->setItem(currentRow, 0, new QStandardItem(QString::fromStdString(std::to_string(channelNum))));
        model->setItem(currentRow, 1, new QStandardItem(QString::fromStdString(std::to_string(waveLen))));
        model->setItem(currentRow, 2, new QStandardItem(QString::fromStdString(std::to_string(waveDelta))));
        
        currentRow++;
    }
}

double * WavescaleTable::getWaveLengthValues()
{
    int rowCount = model->rowCount();
    
    double * waveValues = new double[rowCount];
    
    for(int row = 0; row < rowCount; row++)
    {
        waveValues[row] = (model->data(model->index(row, 1))).toDouble();
    }
    
    return waveValues;
}

bool WavescaleTable::hasData()
{
    if(model->item(0) == nullptr)
        return false;
    return true;
}

void WavescaleTable::show()
{
    window->show();
}