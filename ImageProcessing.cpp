#include "ImageProcessing.h"
#include <iostream>
#include <string>

/*
 * In this program, Image processing is done on two DICOM series. One of the two images are baseline and the other  After image processing, a DICOM series is converted into a 3D image(MHD file format is best) and a PNG series.
 * Upon completion of Image Processing, Registration and Segmentation is performed.
 *
 */

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

  /* User would like to perform only Image Processing */
  if(choice == 1) {
    std::cout << "What would you like to do?\n"
            << "1. Convert Dicom Series to 3D\n"
            << "2. Convert 3D image to PNG Series\n"
            << "3. Convert Dicom Series to PNG Series" << std::endl;

    std::cout << "Input: ";
    std::cin >> choice;
    std::cout << std::endl;

    // User wants to convert Dicom Series to 3D image
    if(choice == 1) {
      std::cout << "Expecting 2 parameters: DicomDirectory output3DImageFile" << std::endl;
      std::string DicomDirectory, output3DImageFile;
      std::cout << "Input: ";
      std::cin >> DicomDirectory >> output3DImageFile;
      std::cout << std::endl;

      std::cout << "Converting dicom series to 3D image" << std::endl;
      DicomSeriesReadImageWrite2(DicomDirectory.c_str(), output3DImageFile.c_str());

    // User wants to convert 3D Image to PNG Series
    } else if(choice == 2) {
      std::cout << "Expecting 3 parameters: input3DImageFile outputPrefix outputExtension" << std::endl;
      std::string input3DImageFile, outputPrefix, outputExtension;
      std::cout << "Input: ";
      std::cin >> input3DImageFile >> outputPrefix >> outputExtension;
      std::cout << std::endl;

      std::cout << "Converting 3D image to png series" << std::endl;
      ImageReadImageSeriesWrite(input3DImageFile.c_str(), outputPrefix.c_str(), outputExtension.c_str());
    }

    // User wants to convert Dicom Series to PNG Series
    else if(choice == 3) {
      std::cout << "Expecting 4 parameters: DicomDirectory output3DImageFile outputPrefix outputExtension" << std::endl;
      std::string DicomDirectory, output3DImageFile, outputPrefix, outputExtension;
      std::cout << "Input: ";
      std::cin >> DicomDirectory >> output3DImageFile >> outputPrefix >> outputExtension;
      std::cout << std::endl;

      std::cout << "Converting dicom series to 3D image" << std::endl;
      DicomSeriesReadImageWrite2(DicomDirectory.c_str(), output3DImageFile.c_str());
      std::cout << "Converting 3D image to png series" << std::endl;
      ImageReadImageSeriesWrite(output3DImageFile.c_str(), outputPrefix.c_str(), outputExtension.c_str());
    }
 
  /* User would like to perform only Watershed Segmentation */
  } else if(choice == 2) {
    std::cout << "\nPerforming Watershed Segmentation now." << std::endl << std::endl;

    int repeat;
    std::cout << "How many times would you like to perform watershed segmentation?" << std::endl;
    std::cin >> repeat;
    std::cout << std::endl;

    // Perform Watershed Segmentation
    for(int i = 0; i < repeat; i++) {
      std::cout << "Expecting 4 parameters: inputImage outputImage lowerThreshold outputScaleLevel" << std::endl;
	  std::string inputImage, outputImage, lowerThreshold, outputScaleLevel;
      std::cin >> inputImage >> outputImage >> lowerThreshold >> outputScaleLevel;
      WatershedSegmentation2(inputImage.c_str(), outputImage.c_str(), lowerThreshold.c_str(), outputScaleLevel.c_str());
    }

  /* User would like to perform only Registration */
  } else if(choice == 3) {
    std::cout << "\nPerforming Registration now." << std::endl << std::endl;

    std::string fixedImageFile, movingImageFile, outputImageFile;

    // Perform BSpline Registration
    std::cout << "Expecting 3 parameters: fixedImageFile movingImageFile outoutImageFile" << std::endl;
    std::cin >> fixedImageFile >> movingImageFile >> outputImageFile;
    BSplineRegistration(fixedImageFile.c_str(), movingImageFile.c_str(), outputImageFile.c_str());

  /* User would like to perform only Quantization */
  } else if(choice == 4) {
    std::cout << "Quantization not yet implemented." << std::endl;

  /* User would like to process the images, perform segmentation, registration, and quantization */
  } else if(choice == 5) {
    std::string DicomDirectory1, output3DImageFile1, outputPrefix1, outputExtension1;
    std::string DicomDirectory2, output3DImageFile2, outputPrefix2, outputExtension2;
 
    for(int i = 0; i < 2; i++) {
      if(i == 0) {
        std::cout << "Converting Baseline images" << std::endl;    

        std::cout << "Expecting 4 parameters: DicomDirectory output3DImageFile outputPrefix outputExtension" << std::endl;
        std::cout << "Input: ";
        std::cin >> DicomDirectory1 >> output3DImageFile1 >> outputPrefix1 >> outputExtension1;
        std::cout << std::endl;
      
        std::cout << "Converting dicom series to 3D image" << std::endl;
        DicomSeriesReadImageWrite2(DicomDirectory1.c_str(), output3DImageFile1.c_str());
        std::cout << "Converting 3D image to png series" << std::endl;
        ImageReadImageSeriesWrite(output3DImageFile1.c_str(), outputPrefix1.c_str(), outputExtension1.c_str());
      } else if(i == 1) {
        std::cout << "Converting Baseline+Movement images" << std::endl; 
        
        std::cout << "Expecting 4 parameters: DicomDirectory output3DImageFile outputPrefix outputExtension" << std::endl;
        std::cout << "Input: ";
        std::cin >> DicomDirectory2 >> output3DImageFile2 >> outputPrefix2 >> outputExtension2;
        std::cout << std::endl;
      
        std::cout << "Converting dicom series to 3D image" << std::endl;
        DicomSeriesReadImageWrite2(DicomDirectory2.c_str(), output3DImageFile2.c_str());
        std::cout << "Converting 3D image to png series" << std::endl;
        ImageReadImageSeriesWrite(output3DImageFile2.c_str(), outputPrefix2.c_str(), outputExtension2.c_str());
      }
    }

    std::cout << "\nPerforming Registration now." << std::endl << std::endl;

    std::string outputImageFile;

    // Perform BSpline Registration
    std::cout << "Expecting 1 parameter: outoutImageFile" << std::endl;
    std::cin >> outputImageFile;
    BSplineRegistration(output3DImageFile1.c_str(), output3DImageFile2.c_str(), outputImageFile.c_str());


    std::cout << "\nPerforming Watershed Segmentation now." << std::endl << std::endl;

    int repeat;
    std::cout << "How many times would you like to perform watershed segmentation?" << std::endl;
    std::cin >> repeat;
    std::cout << std::endl;

    // Perform Watershed Segmentation
    for(int i = 0; i < repeat; i++) {
      std::cout << "Expecting 3 parameters: outputImage lowerThreshold outputScaleLevel" << std::endl;
	  std::string outputImage, lowerThreshold, outputScaleLevel;
      std::cin >> outputImage >> lowerThreshold >> outputScaleLevel;
      WatershedSegmentation2(outputImageFile.c_str(), outputImage.c_str(), lowerThreshold.c_str(), outputScaleLevel.c_str());
    }
    
    std::cout << "\nFinished ImageProcessing, Registration, and Segmentation of images" << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
    return 1;
  }

  return 0;
}