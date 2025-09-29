add_executable(TiffAnalyzer 
    main.cpp 
    UI/mainWindow.cpp 
    UI/imageLabel.cpp 
    UI/channelSelectionWindow.cpp
    UI/contrastingWindow.cpp
    UI/pixelStatusBar.cpp
    UI/histogramPanel.cpp
    UI/sppTable.cpp
    UI/pixelGraphicsWindow.cpp

    Utils/imagePainter.cpp
    Utils/histogramPainter.cpp
    Utils/imageConverter.cpp
    Utils/sppReader.cpp
    Utils/histogramContrastingCalculator.cpp
    Utils/pixelReader.cpp
    Utils/normalizer.cpp

    TypeDefs/tiff.cpp
    TypeDefs/bmp.cpp
)