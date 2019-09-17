#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <math.h>
#include <list>
#include <vector>
#include <fstream>

struct roi
{
   int x1, y1, x2, y2;
};

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);

		// TA's functions
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);

		// Assigment_1
		static void hw1(image &src, image &tgt, int q, char* param_file_name);
		
		// Questions 1,2,3 for HW1
		static void doubleBinarize(image &src, image &tgt, struct roi current_roi, int t1, int t2);
		static void meanSmoothFilter(image &src, image &tgt, struct roi current_roi , int windowsize);
		static void colorBinarization(image &src, image &tgt, struct roi current_roi, int cr, int cg, int  cb, int tc);

		// Helper functions
		static bool isRoiOverlapping(roi a, roi b);
		static bool isRoiValid(vector<roi > validROIs, struct roi current_roi);
		static bool isInRange(int cr,int cg, int cb, int r,int g,int b,int tc);
		static int getPixelMeanValue(image &src, int x, int y, struct roi current_roi, int windowsize);
};

#endif

