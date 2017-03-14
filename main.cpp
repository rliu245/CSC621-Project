#include "itkImage.h"

using namespace std;

int main() {
  typedef itk::Image<unsigned short, 3> ImageType;
  ImageType::Pointer image = ImageType::New();

  cout << "ITK Hello World!" << endl;
  cout << image << endl;

  return 0;
}
