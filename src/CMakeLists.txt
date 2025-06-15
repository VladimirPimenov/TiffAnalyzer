add_executable(TiffAnalyzer 
    main.cpp 
    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/pixelStatusBar.cpp

    Utils/tiff.cpp
    Utils/pixelsNormalizer.cpp
)