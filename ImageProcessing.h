//ImageProcessing.h
#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

void DicomSeriesReadImageWrite2(const char * dicom_directory, char * outputfilename );
void ImageReadImageSeriesWrite( char * input_file, const char * output_prefix, const char * output_extension );
void WatershedSegmentation2(char* input_image, char* output_image, char* lower_threshold, char* output_scalelevel );
void DemonsRegistration(const char* fixedImageFile, const char* movingImageFile, const char* outputImageFile );
void BSplineRegistration(const char* fixedImageFile, const char* movingImageFile, const char* outputImageFile);

#endif  