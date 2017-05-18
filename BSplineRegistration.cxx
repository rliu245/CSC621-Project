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
// This example illustrates the use of the \doxygen{RegularStepGradientDescentOptimizer}
// in the context of a deformable registration problem. The code of this example is almost
// identical to the one in Section~\ref{sec:DeformableRegistration8}.
//
// \index{itk::BSplineTransform}
// \index{itk::BSplineTransform!DeformableRegistration}
// \index{itk::RegularStepGradientDescentOptimizer}
//
//
// Software Guide : EndLatex

#include "itkImageRegistrationMethod.h"
#include "itkMattesMutualInformationImageToImageMetric.h"

#include "itkTimeProbesCollectorBase.h"
#include "itkMemoryProbesCollectorBase.h"

//  Software Guide : BeginLatex
//
//  The following are the most relevant headers to this example.
//
//  \index{itk::BSplineTransform!header}
//  \index{itk::RegularStepGradientDescentOptimizer!header}
//
//  Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
#include "itkBSplineTransform.h"
#include "itkRegularStepGradientDescentOptimizer.h"
// Software Guide : EndCodeSnippet

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkResampleImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkSquaredDifferenceImageFilter.h"

#include "itkTransformFileReader.h"

#include "ImageProcessing.h"

//  The following section of code implements a Command observer
//  used to monitor the evolution of the registration process.
//
#include "itkCommand.h"
class CommandIterationUpdate : public itk::Command
{
public:
  typedef  CommandIterationUpdate   Self;
  typedef  itk::Command             Superclass;
  typedef itk::SmartPointer<Self>   Pointer;
  itkNewMacro( Self );

protected:
  CommandIterationUpdate() {};

public:
  typedef itk::RegularStepGradientDescentOptimizer OptimizerType;
  typedef   const OptimizerType *                  OptimizerPointer;

  void Execute(itk::Object *caller, const itk::EventObject & event) ITK_OVERRIDE
    {
    Execute( (const itk::Object *)caller, event);
    }

  void Execute(const itk::Object * object, const itk::EventObject & event) ITK_OVERRIDE
    {
    OptimizerPointer optimizer = static_cast< OptimizerPointer >( object );
    std::cout << optimizer->GetCurrentIteration() << "   ";
    std::cout << optimizer->GetValue() << "   ";
    std::cout << std::endl;
    }
};

void BSplineRegistration( const char* fixedImageFile, const char* movingImageFile, const char* outputImageFile )
{

  const    unsigned int    ImageDimension = 3;
  typedef  signed short    PixelType;

  typedef itk::Image< PixelType, ImageDimension >  FixedImageType;
  typedef itk::Image< PixelType, ImageDimension >  MovingImageType;

  const unsigned int SpaceDimension = ImageDimension;
  const unsigned int SplineOrder = 3;
  typedef double CoordinateRepType;

  typedef itk::BSplineTransform<
                            CoordinateRepType,
                            SpaceDimension,
                            SplineOrder >     TransformType;

  typedef itk::RegularStepGradientDescentOptimizer       OptimizerType;

  typedef itk::MattesMutualInformationImageToImageMetric<
                                    FixedImageType,
                                    MovingImageType >    MetricType;

  typedef itk:: LinearInterpolateImageFunction<
                                    MovingImageType,
                                    double          >    InterpolatorType;

  typedef itk::ImageRegistrationMethod<
                                    FixedImageType,
                                    MovingImageType >    RegistrationType;

  MetricType::Pointer         metric        = MetricType::New();
  OptimizerType::Pointer      optimizer     = OptimizerType::New();
  InterpolatorType::Pointer   interpolator  = InterpolatorType::New();
  RegistrationType::Pointer   registration  = RegistrationType::New();

  registration->SetMetric(        metric        );
  registration->SetOptimizer(     optimizer     );
  registration->SetInterpolator(  interpolator  );

  TransformType::Pointer  transform = TransformType::New();
  registration->SetTransform( transform );

  typedef itk::ImageFileReader< FixedImageType  > FixedImageReaderType;
  typedef itk::ImageFileReader< MovingImageType > MovingImageReaderType;

  FixedImageReaderType::Pointer  fixedImageReader  = FixedImageReaderType::New();
  MovingImageReaderType::Pointer movingImageReader = MovingImageReaderType::New();

  fixedImageReader->SetFileName(  fixedImageFile );
  movingImageReader->SetFileName( movingImageFile );

  FixedImageType::ConstPointer fixedImage = fixedImageReader->GetOutput();

  registration->SetFixedImage(  fixedImage   );
  registration->SetMovingImage(   movingImageReader->GetOutput()   );

  fixedImageReader->Update();

  FixedImageType::RegionType fixedRegion = fixedImage->GetBufferedRegion();

  registration->SetFixedImageRegion( fixedRegion );

  unsigned int numberOfGridNodesInOneDimension = 5;

  // Software Guide : BeginCodeSnippet

  TransformType::PhysicalDimensionsType   fixedPhysicalDimensions;
  TransformType::MeshSizeType             meshSize;
  TransformType::OriginType               fixedOrigin;

  for( unsigned int i=0; i< SpaceDimension; i++ )
    {
    fixedOrigin[i] = fixedImage->GetOrigin()[i];
    fixedPhysicalDimensions[i] = fixedImage->GetSpacing()[i] *
      static_cast<double>(
      fixedImage->GetLargestPossibleRegion().GetSize()[i] - 1 );
    }
  meshSize.Fill( numberOfGridNodesInOneDimension - SplineOrder );

  transform->SetTransformDomainOrigin( fixedOrigin );
  transform->SetTransformDomainPhysicalDimensions(
    fixedPhysicalDimensions );
  transform->SetTransformDomainMeshSize( meshSize );
  transform->SetTransformDomainDirection( fixedImage->GetDirection() );

  typedef TransformType::ParametersType     ParametersType;

  const unsigned int numberOfParameters =
               transform->GetNumberOfParameters();

  ParametersType parameters( numberOfParameters );

  parameters.Fill( 0.0 );

  transform->SetParameters( parameters );

  registration->SetInitialTransformParameters( transform->GetParameters() );
  // Software Guide : EndCodeSnippet

  parameters.Fill( 0.0 );

  transform->SetParameters( parameters );

  registration->SetInitialTransformParameters( transform->GetParameters() );
  // Software Guide : EndCodeSnippet

  //  Software Guide : BeginLatex
  //
  //  Next we set the parameters of the RegularStepGradientDescentOptimizer object.
  //
  //  Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  optimizer->SetMaximumStepLength( 10.0 );
  optimizer->SetMinimumStepLength(  0.01 );

  optimizer->SetRelaxationFactor( 0.7 );
  optimizer->SetNumberOfIterations( 50 );
  // Software Guide : EndCodeSnippet

  // Create the Command observer and register it with the optimizer.
  //
  CommandIterationUpdate::Pointer observer = CommandIterationUpdate::New();
  optimizer->AddObserver( itk::IterationEvent(), observer );

  metric->SetNumberOfHistogramBins( 50 );

  const unsigned int numberOfSamples =
    static_cast<unsigned int>( fixedRegion.GetNumberOfPixels() * 20.0 / 100.0 );

  metric->SetNumberOfSpatialSamples( numberOfSamples );
  metric->ReinitializeSeed( 76926294 );

  // Add time and memory probes
  itk::TimeProbesCollectorBase chronometer;
  itk::MemoryProbesCollectorBase memorymeter;

  std::cout << std::endl << "Starting Registration" << std::endl;

  try
    {
    memorymeter.Start( "Registration" );
    chronometer.Start( "Registration" );

    registration->Update();

    chronometer.Stop( "Registration" );
    memorymeter.Stop( "Registration" );

    std::cout << "Optimizer stop condition = "
              << registration->GetOptimizer()->GetStopConditionDescription()
              << std::endl;
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    }

  OptimizerType::ParametersType finalParameters =
                    registration->GetLastTransformParameters();

  // Report the time and memory taken by the registration
  chronometer.Report( std::cout );
  memorymeter.Report( std::cout );

  transform->SetParameters( finalParameters );

  typedef itk::ResampleImageFilter<
                            MovingImageType,
                            FixedImageType >    ResampleFilterType;

  ResampleFilterType::Pointer resample = ResampleFilterType::New();

  resample->SetTransform( transform );
  resample->SetInput( movingImageReader->GetOutput() );

  resample->SetSize(    fixedImage->GetLargestPossibleRegion().GetSize() );
  resample->SetOutputOrigin(  fixedImage->GetOrigin() );
  resample->SetOutputSpacing( fixedImage->GetSpacing() );
  resample->SetOutputDirection( fixedImage->GetDirection() );

  // This value is set to zero in order to make easier to perform
  // regression testing in this example. However, for didactic
  // exercise it will be better to set it to a medium gray value
  // such as 100 or 128.
  resample->SetDefaultPixelValue( 0 );

  typedef  signed short  OutputPixelType;

  typedef itk::Image< OutputPixelType, ImageDimension > OutputImageType;

  typedef itk::CastImageFilter<
                        FixedImageType,
                        OutputImageType > CastFilterType;

  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  WriterType::Pointer      writer =  WriterType::New();
  CastFilterType::Pointer  caster =  CastFilterType::New();

  writer->SetFileName( outputImageFile );

  caster->SetInput( resample->GetOutput() );
  writer->SetInput( caster->GetOutput()   );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    }

  typedef itk::SquaredDifferenceImageFilter<
                                  FixedImageType,
                                  FixedImageType,
                                  OutputImageType > DifferenceFilterType;

  DifferenceFilterType::Pointer difference = DifferenceFilterType::New();

  WriterType::Pointer writer2 = WriterType::New();
  writer2->SetInput( difference->GetOutput() );
}
