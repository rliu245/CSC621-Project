#include "test.h"
#include <string.h>

int main( int argc, char *argv[] ) {
  int choice = 0;

  std::cout << "What would you like to do?\n"
            << "1. Perform Image processing\n"
            << "2. Perform WatershedSegmentation\n"
            << "3. Perform Registration\n"
            << "4. Perform Quantization\n"
            << "5. All of the Above" << std::endl;

  if(choice == 1) {
    std::cout << "Expecting 3 parameters: DicomDirectory outputPrefix outputExtension" << std::endl;
  } else if(choice == 2) {

  } else if(choice == 3) {

  } else if(choice == 4) {

  } else if(choice == 5) {
    std::cout << "Expecting 3 parameters: DicomDirectory outputPrefix outputExtension" << std::endl;

    char* dimage = "Image3D.mhd";

    std::cout << "Converting dicom series to 3D image" << std::endl;
    DicomSeriesReadImageWrite2(argv[1], dimage);
    std::cout << "Converting 3D image to png series" << std::endl;
    ImageReadImageSeriesWrite(dimage, argv[2], argv[3]);

    std::cout << "\nPerforming Watershed Segmentation now." << std::endl << std::endl;

    int repeat;
    std::cout << "How many times would you like to perform watershed segmentation?" << std::endl;
    std::cin >> repeat;
    std::cout << std::endl;

    String outputImage, lowerThreshold, outputScaleLevel;

    // Perform Watershed Segmentation
    for(int i = 0; i < repeat; i++) {
      std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
      std::cin >> outputImage >> lowerThreshold >> outputScaleLevel;
      WatershedSegmentation2(dimage, outputImage, lowerThreshold, outputScaleLevel);
    }
    /*
    std::cout << "\nPerforming Registration now." << std::endl << std::endl;

    String outputImage, lowerThreshold, outputScaleLevel;

    // Perform Watershed Segmentation
    std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
    std::cin >> outputImage >> lowerThreshold >> outputScaleLevel;
    WatershedSegmentation2(dimage, outputImage, lowerThreshold, outputScaleLevel);
    */
    std::cout << "\nFinished ImageProcessing, Registration, and Segmentation of images" << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }

  return 0;
}