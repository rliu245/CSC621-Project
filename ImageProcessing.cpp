#include "ImageProcessing.h"
#include <string>

int main( int argc, char *argv[] ) {
  int choice = 0;

  std::cout << "What would you like to do?\n"
            << "1. Perform Image processing\n"
            << "2. Perform WatershedSegmentation\n"
            << "3. Perform Registration\n"
            << "4. Perform Quantization\n"
            << "5. All of the Above" << std::endl;

  std::cout << "Input: ";
  std::cin >> choice;
  std::cout << std::endl;

  if(choice == 1) {
    std::cout << "Expecting 3 parameters: DicomDirectory outputPrefix outputExtension" << std::endl;
    std::string DicomDirectory, outputPrefix, outputExtension;
    std::cout << "Input: ";
    std::cin >> DicomDirectory >> outputPrefix >> outputExtension;
    std::cout << std::endl;

    char* dimage = "Image3D.mhd";

    std::cout << "Converting dicom series to 3D image" << std::endl;
    DicomSeriesReadImageWrite2(DicomDirectory.c_str(), dimage);
    std::cout << "Converting 3D image to png series" << std::endl;
    ImageReadImageSeriesWrite(dimage, outputPrefix.c_str(), outputExtension.c_str());

  } else if(choice == 2) {
    std::cout << "\nPerforming Watershed Segmentation now." << std::endl << std::endl;

    int repeat;
    std::cout << "How many times would you like to perform watershed segmentation?" << std::endl;
    std::cin >> repeat;
    std::cout << std::endl;

    std::string temp1, temp2, temp3;

    // Perform Watershed Segmentation
    for(int i = 0; i < repeat; i++) {
      std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
      std::cin >> temp1 >> temp2 >> temp3;
      char* outputImage = (char*) malloc(sizeof(char) * temp1.length());
      strcpy(outputImage, temp1.c_str());
      char* lowerThreshold = (char*) malloc(sizeof(char) * temp2.length());
      strcpy(lowerThreshold, temp2.c_str());
      char* outputScaleLevel = (char*) malloc(sizeof(char) * temp3.length());
      strcpy(outputScaleLevel, temp3.c_str());
      WatershedSegmentation2(dimage, outputImage, lowerThreshold, outputScaleLevel);
      
      free(outputImage);
      free(lowerThreshold);
      free(outputScaleLevel);
    }

  } else if(choice == 3) {
    /*
    std::cout << "\nPerforming Registration now." << std::endl << std::endl;

    String outputImage, lowerThreshold, outputScaleLevel;

    // Perform Watershed Segmentation
    std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
    std::cin >> outputImage >> lowerThreshold >> outputScaleLevel;
    WatershedSegmentation2(dimage, outputImage, lowerThreshold, outputScaleLevel);
    */
  } else if(choice == 4) {
    std::cout << "Quantization not yet implemented." << std::endl;
  } else if(choice == 5) {
    std::cout << "Expecting 3 parameters: DicomDirectory outputPrefix outputExtension" << std::endl;
    std::string DicomDirectory, outputPrefix, outputExtension;
    std::cout << "Input: ";
    std::cin >> DicomDirectory >> outputPrefix >> outputExtension;
    std::cout << std::endl;

    char* dimage = "Image3D.mhd";

    std::cout << "Converting dicom series to 3D image" << std::endl;
    DicomSeriesReadImageWrite2(DicomDirectory.c_str(), dimage);
    std::cout << "Converting 3D image to png series" << std::endl;
    ImageReadImageSeriesWrite(dimage, outputPrefix.c_str(), outputExtension.c_str());

    std::cout << "\nPerforming Watershed Segmentation now." << std::endl << std::endl;

    int repeat;
    std::cout << "How many times would you like to perform watershed segmentation?" << std::endl;
    std::cin >> repeat;
    std::cout << std::endl;

    std::string temp1, temp2, temp3;

    // Perform Watershed Segmentation
    for(int i = 0; i < repeat; i++) {
      std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
      std::cin >> temp1 >> temp2 >> temp3;
      char* outputImage = (char*) malloc(sizeof(char) * temp1.length());
      strcpy(outputImage, temp1.c_str());
      char* lowerThreshold = (char*) malloc(sizeof(char) * temp2.length());
      strcpy(lowerThreshold, temp2.c_str());
      char* outputScaleLevel = (char*) malloc(sizeof(char) * temp3.length());
      strcpy(outputScaleLevel, temp3.c_str());
      WatershedSegmentation2(dimage, outputImage, lowerThreshold, outputScaleLevel);
      
      free(outputImage);
      free(lowerThreshold);
      free(outputScaleLevel);
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