set(CMAKE_AUTORCC ON)

add_library(PolygonChecker SHARED Utils/polygonChecker.cpp)

add_library(RouteFinder SHARED Utils/routeFinder.cpp TypeDefs/spp.cpp)
target_link_libraries(RouteFinder Qt5::Core PolygonChecker)

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
    UI/CalibrationWindow/calibrationWindow.cpp
    UI/CalibrationWindow/onePointCoordsPanel.cpp
    UI/CalibrationWindow/rectangleCoordsPanel.cpp
    UI/CalibrationWindow/kmlCoordsPanel.cpp

    Utils/imagePainter.cpp
    Utils/imageConverter.cpp
    Utils/sppTableReader.cpp
    Utils/histogramCalculator.cpp
    Utils/pixelReader.cpp
    Utils/normalizer.cpp
    Utils/logger.cpp
    Utils/directoryReader.cpp
    Utils/coordsConvertor.cpp
    
    TypeDefs/tiff.cpp
    TypeDefs/bmp.cpp
    TypeDefs/kml.cpp
    )

target_link_libraries(TiffAnalyzer PolygonChecker RouteFinder)

set_target_properties(TiffAnalyzer PROPERTIES AUTOMOC ON)