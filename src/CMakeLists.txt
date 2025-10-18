add_executable(TiffAnalyzer 
    main.cpp 

    Libs/qcustomplot.cpp

    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/contrastingWindow.cpp
    UI/pixelStatusBar.cpp
    UI/sppTable.cpp
    UI/pixelStatisticsPanel.cpp
    UI/contrastingPanel.cpp
    

    Utils/imagePainter.cpp
    Utils/imageConverter.cpp
    Utils/sppReader.cpp
    Utils/histogramCalculator.cpp
    Utils/pixelReader.cpp
    Utils/normalizer.cpp
    
    TypeDefs/tiff.cpp
    TypeDefs/bmp.cpp
    )

set_target_properties(TiffAnalyzer PROPERTIES AUTOMOC ON)