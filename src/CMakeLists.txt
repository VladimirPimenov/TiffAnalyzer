set(CMAKE_AUTORCC ON)

add_executable(TiffAnalyzer
    resources.qrc
 
    main.cpp 

    Libs/qcustomplot.cpp

    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/contrastingWindow.cpp
    UI/pixelStatusBar.cpp
    UI/wavescaleTable.cpp
    UI/InstrumentsPanel/instrumentsPanel.cpp
    UI/InstrumentsPanel/pixelStatisticsPanel.cpp
    UI/InstrumentsPanel/imageOptionsPanel.cpp
    UI/calibrationWindow.cpp

    Utils/imagePainter.cpp
    Utils/imageConverter.cpp
    Utils/sppTableReader.cpp
    Utils/histogramCalculator.cpp
    Utils/pixelReader.cpp
    Utils/normalizer.cpp
    Utils/logger.cpp
    Utils/directoryReader.cpp
    Utils/routeFinder.cpp
    Utils/coordsConvertor.cpp
    
    TypeDefs/tiff.cpp
    TypeDefs/bmp.cpp
    TypeDefs/spp.cpp
    )

set_target_properties(TiffAnalyzer PROPERTIES AUTOMOC ON)