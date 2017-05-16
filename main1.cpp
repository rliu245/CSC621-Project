#include "test.h"
#include <string.h>

int main( int argc, char *argv[] ) {
  if (argc < 4) {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " DicomDirectory outputPrefix outputExtension " << std::endl;
    return 1;
  }

	//char* dimage = (char *) malloc(sizeof(char) * strlen(argv[2]));
	//memcpy(dimage, argv[2], sizeof(char) * strlen(argv[2]));
	//strcat(dimage, "+3d.mhd");
	char* dimage = "Image3D.mhd";

  DicomSeriesReadImageWrite2(argv[1], dimage);
	std::cout << "Convering 3d image to png series" << std::endl;
  ImageReadImageSeriesWrite(dimage, argv[2], argv[3]);

	//DicomSeriesReadImageWrite2(argv[1], argv[2]);
	//ImageReadImageSeriesWrite(argv[2], argv[2], argv[3]);

  return 0;
}