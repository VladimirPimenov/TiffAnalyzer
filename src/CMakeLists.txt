add_executable(TiffAnalyzer 
    main.cpp 
    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/contrastingWindow.cpp
    UI/pixelStatusBar.cpp
    UI/histogramPanel.cpp

    Utils/tiff.cpp
    Utils/imagePainter.cpp
    Utils/histogramPainter.cpp
)