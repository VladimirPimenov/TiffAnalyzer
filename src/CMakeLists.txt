add_executable(TiffAnalyzer 
    main.cpp 
    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/contrastingWindow.cpp
    UI/pixelStatusBar.cpp
    UI/histogramPanel.cpp
    UI/sppTable.cpp

    Utils/tiff.cpp
    Utils/imagePainter.cpp
    Utils/histogramPainter.cpp
    Utils/bmp.cpp
    Utils/imageConverter.cpp
    Utils/sppReader.cpp
)