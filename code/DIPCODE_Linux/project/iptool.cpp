/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "../iptools/core.h"
#include <strings.h>
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		char *pch;
		pch = strtok(str, " ");
		src.read(pch);
		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " ");


        if (strncasecmp(pch,"add",MAXLEN)==0) {
			/* Add Intensity */
			pch = strtok(NULL, " ");
        		utility::addGrey(src,tgt,atoi(pch));
        }

        else if (strncasecmp(pch,"binarize",MAXLEN)==0) {
			/* Thresholding */
			pch = strtok(NULL, " ");
			utility::binarize(src,tgt,atoi(pch));
		}

		else if (strncasecmp(pch,"scale",MAXLEN)==0) {
			/* Image scaling */
			pch = strtok(NULL, " ");
			utility::scale(src,tgt,atof(pch));
		}

		else if (strncasecmp(pch,"doubleBinarization",MAXLEN)==0 || strncasecmp(pch,"doubleBinarization\n",MAXLEN)==0) {
			/* Double Thresholding */
			utility::hw1(src, tgt, 1,"param_hw1_q1.txt");
			
		}
		else if (strncasecmp(pch,"smoothFilter",MAXLEN)==0 || strncasecmp(pch,"smoothFilter\n",MAXLEN)==0) {
			/* Filtering using Mean Uniform Filter */
			utility::hw1(src, tgt, 2,"param_hw1_q2.txt");
		}
		else if (strncasecmp(pch,"colorThreshold",MAXLEN)==0 || strncasecmp(pch,"colorThreshold\n",MAXLEN)==0) {
			/* Color Thresholding */
			utility::hw1(src, tgt, 3, "param_hw1_q3.txt");
		}

		else {
			printf("No function: %s\n", pch);
			continue;
		}
		tgt.save(outfile);
	}
	fclose(fp);
	return 0;
}

