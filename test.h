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

void DicomSeriesReadImageWrite2( char * dicom_directory, char * outputfilename );
void ImageReadImageSeriesWrite( char * input_file, char * output_prefix, char * output_extension );

#endif  