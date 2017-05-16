//ImageProcessing.h
#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

// Include necessary headers for DicomSeriesReadImageWrite2
#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"

// Include necessary headers for ImageReadImageSeriesWrite
#include "itkImageFileReader.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"

// Include necessary headers for WatershedSegmenation
#include "itkWatershedImageFilter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"

void DicomSeriesReadImageWrite2( char * dicom_directory, char * outputfilename );
void ImageReadImageSeriesWrite( char * input_file, char * output_prefix, char * output_extension );
void WatershedSegmentation2( char* input_image, char* output_image, char* lower_threshold, char* output_scalelevel );

#endif  