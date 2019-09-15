#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void doublebinarize(image &src, image &tgt, int lower_threshold, int upper_threshold    );
};

#endif

