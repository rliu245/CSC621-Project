//ImageProcessing.h
#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

void DicomSeriesReadImageWrite2(const char * dicom_directory, const char * outputfilename );
void ImageReadImageSeriesWrite(const char * input_file, const char * output_prefix, const char * output_extension );
void WatershedSegmentation2(const char* input_image, const char* output_image, const char* lower_threshold, const char* output_scalelevel );
void DemonsRegistration(const char* fixedImageFile, const char* movingImageFile, const char* outputImageFile );
void BSplineRegistration(const char* fixedImageFile, const char* movingImageFile, const char* outputImageFile);

#endif  