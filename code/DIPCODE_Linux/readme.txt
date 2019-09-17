This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.

2. Binarization: binarize
Binarize the pixels with the threshold.

3. Scaling: Scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.

4. HW1: Apply the following methods in the given and non-overlapping ROI
	- doubleBinarize(): Binarize the ROI specific pixels using the two thresholds given
	- meanSmoothFilter(): Adaptive mean smoothning filter
	- colorBinarization(): Binarize the pixels of coloured image bases on RGB provided by user alongwith threshold of TC distance in RGB scale.



*** PARAMETERS FILE ***

- parameters.txt
There are for parameters:
1. the input file name;
2. the output file name;
3. the name of the filter. Use "add", "binarize", and "scale" or "doubleBinarize", "meanSmoothFilter" and "colorBinarization".
for your filters;
4. (optional) the value for adding intensity, threshold value for binarize filter, or the scaling factor for scale filter.

- param_hw1_q1.txt
This the parameter file used for inputs for function doubleBinarize.
<roi_x> <roi_y> <size_x> <size_y> <threshold_1> <threshold_2>

roi_x and roi_y 	co-ordinates of the top-left pixel,
size_x and size_y 	width and length of ROI, 
threshold_1 		lower limit of pixel value,
threshold_2 		upper limit of pixel value

E.g. 
0 0 150 150 50 150
300 300 200 200 100 200
100 200 300 300 100 160
175 175 100 100 80 150


- param_hw1_q2.txt
This the parameter file used for inputs for function meanSmoothFilter.
<roi_x> <roi_y> <size_x> <size_y> <window_size> 

roi_x and roi_y 	co-ordinates of the top-left pixel,
size_x and size_y 	width and length of ROI, 
Window Size 		Size of window - validity: Positive odd integer > 3

- param_hw1_q3.txt
This the parameter file used for inputs for function colorBinarization.
<roi_x> <roi_y> <size_x> <size_y> <R> <G> <B> <threshold>

roi_x and roi_y 	co-ordinates of the top-left pixel,
size_x and size_y 	width and length of ROI, 
R			red value for the color, 
G			green value for the color, 
B			blue value for the color,
threshold 		Distance from color point (R,G,B) in RGB-Space

Eg:
5 5 1000 1000 70 100 70 100
1100 1100 700 700 90 90 90 100
510 510 300 300 180 70 70 50


*** Run the program: ./iptool parameters.txt
