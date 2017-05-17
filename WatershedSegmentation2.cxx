/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

// Software Guide : BeginLatex
//
// The following example illustrates how to preprocess and segment images using
// the \doxygen{WatershedImageFilter} for the particular case of grayscale
// scalar image.
//
// Software Guide : EndLatex

#include "ImageProcessing.h"

void WatershedSegmentation2(char* input_image, char* output_image, char* lower_threshold, char* output_scalelevel )
{
  typedef float                             InternalPixelType;
  typedef itk::RGBPixel<unsigned char>      RGBPixelType;

  const   unsigned int                      Dimension = 3;

  typedef itk::Image< InternalPixelType,  Dimension >  InternalImageType;
  typedef itk::Image< RGBPixelType,       Dimension >  RGBImageType;


  //
  // We instantiate reader and writer types
  //
  typedef  itk::ImageFileReader< InternalImageType   >  ReaderType;
  typedef  itk::ImageFileWriter< RGBImageType  >        WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( input_image );
  writer->SetFileName( output_image );


  //
  //  Instantiate the GradientMagnitude image filter
  //
  typedef   itk::GradientMagnitudeRecursiveGaussianImageFilter<
                                                     InternalImageType,
                                                     InternalImageType
                                                          > GradientMagnitudeFilterType;

  GradientMagnitudeFilterType::Pointer gradienMagnitudeFilter = GradientMagnitudeFilterType::New();

  gradienMagnitudeFilter->SetInput( reader->GetOutput() );
  gradienMagnitudeFilter->SetSigma( 1.0 );


  //
  //  Instantiate the Watershed filter
  //

  typedef  itk::WatershedImageFilter<
                              InternalImageType
                                            > WatershedFilterType;

  WatershedFilterType::Pointer watershedFilter = WatershedFilterType::New();

  watershedFilter->SetInput( gradienMagnitudeFilter->GetOutput() );

  watershedFilter->SetThreshold( atof( lower_threshold ) );
  watershedFilter->SetLevel(     atof( output_scalelevel ) );


  //
  //  Instantiate the filter that will encode the label image
  //  into a color image (random color attribution).
  //

  typedef itk::Functor::ScalarToRGBPixelFunctor<
                                           unsigned long
                                                    > ColorMapFunctorType;

  typedef WatershedFilterType::OutputImageType  LabeledImageType;

  typedef itk::UnaryFunctorImageFilter<
                                LabeledImageType,
                                RGBImageType,
                                ColorMapFunctorType
                                                > ColorMapFilterType;

  ColorMapFilterType::Pointer colorMapFilter = ColorMapFilterType::New();

  colorMapFilter->SetInput(  watershedFilter->GetOutput() );

  writer->SetInput( colorMapFilter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }

}
