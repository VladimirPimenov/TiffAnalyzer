set(CMAKE_AUTORCC ON)

add_library(PolygonChecker SHARED Utils/polygonChecker.cpp)
add_library(RouteFinder SHARED Utils/routeFinder.cpp TypeDefs/spp.cpp)
target_link_libraries(RouteFinder Qt5::Core PolygonChecker)

add_library(HttpClient SHARED
    ../include/httpClient.h
    ../include/httpRequest.h
    ../include/httpResponse.h
    Utils/httpClient.cpp
)
target_compile_definitions(HttpClient PRIVATE HTTPCLIENT_LIB)
target_link_libraries(HttpClient Qt5::Network Qt5::Core Qt5::Widgets)

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
    UI/snapshotLoadWindow.cpp

    Utils/imagePainter.cpp
    Utils/imageConverter.cpp
    Utils/histogramCalculator.cpp
    Utils/pixelReader.cpp
    Utils/normalizer.cpp
    Utils/logger.cpp
    Utils/directoryReader.cpp
    Utils/coordsConvertor.cpp
    Utils/sppTableReader.cpp
    
    Utils/snapshotLoader.cpp
    Utils/snapshotReader.cpp

    TypeDefs/tiff.cpp
    TypeDefs/bmp.cpp
    TypeDefs/kml.cpp
    TypeDefs/spp.cpp
    )

target_link_libraries(TiffAnalyzer PolygonChecker RouteFinder HttpClient)

set_target_properties(TiffAnalyzer PROPERTIES AUTOMOC ON)