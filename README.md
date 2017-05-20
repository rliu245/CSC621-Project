# CSC621_Project
Biomedical Imaging and Analysis Final Project

## Test Images obtained from NBIA National Cancer Institute's Database
https://imaging.nci.nih.gov/ncia/login.jsf

Collection ID: QIN Breast DCE-MRI-Demo
Subject ID: QIN-Berast-DCE-MRI-BC01

## Brain MRI's obtained from PCIR
http://www.pcir.org/researchers/downloads_available.html

## Image files viewed using ImageJ and Kang Li's MetaImage_Reader plugin
http://www.cs.cmu.edu/~kangli/code/MetaImage_Reader_Writer.html

### Instructions
This program uses DICOM files and MHD files. For the first phase of the data pipeline we expect the DICOM directory, name of the output file (for example Imaging.mhd), output prefix of the PNG series (for example IMG), and the output extension (for example png). The output of the first phase of the pipeline is a 3D image (preferably MHD) and a 2D image (perferably PNG series). The second phase of the pipeline is registration. The parameter for registration is the output image files names (for example Registration_Image.mhd). The last phase of the pipeline is segmentation. First, user is prompted how many times they would like to repeat the segmentation process. We then proceed to ask the user the follow 3 parameters for each iteration: name of the output image (Output_1.mhd), the lower threshold (0.01),  the output scale level (0.15). 

This program lacks proper delimiting for inputs of the parameters. Therefore, do not use spaces for file paths and file names. Also, quotations will not work.