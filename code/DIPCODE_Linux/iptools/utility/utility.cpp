#include "utility.h"
#include <vector>
#include <cstring>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <cstdio>
#include <cstring>
#define MAXRGB 255
#define MINRGB 0
#define MAXLEN 256

using namespace std;


string utility::intToString(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
    if (value > MAXRGB)
        return MAXRGB;
    if (value < MINRGB)
        return MINRGB;
    return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    for (int i=0; i<src.getNumberOfRows(); i++)
        for (int j=0; j<src.getNumberOfColumns(); j++)
        {
            tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
        }
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    for (int i=0; i<src.getNumberOfRows(); i++)
    {
        for (int j=0; j<src.getNumberOfColumns(); j++)
        {
            if (src.getPixel(i,j) < threshold)
                tgt.setPixel(i,j,MINRGB);
            else
                tgt.setPixel(i,j,MAXRGB);
        }
    }
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
    int rows = (int)((float)src.getNumberOfRows() * ratio);
    int cols  = (int)((float)src.getNumberOfColumns() * ratio);
    tgt.resize(rows, cols);
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {   
            /* Map the pixel of new image back to original image */
            int i2 = (int)floor((float)i/ratio);
            int j2 = (int)floor((float)j/ratio);
            if (ratio == 2) {
                /* Directly copy the value */
                tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
            }

            if (ratio == 0.5) {
                /* Average the values of four pixels */
                int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
                tgt.setPixel(i,j,checkValue(value/4));
            }
        }
    }
}


/*-----------------------------------------------------------------------**/
/*                              HOMEWORK 1                                */
/*-----------------------------------------------------------------------**/
void utility::hw1(image &src, image &tgt, char *param_file_name)
{
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    tgt.copyImage(src);

    FILE *fp;
    char str[MAXLEN];
    char *lp;
    int ques;
    int x1,x2,y1,y2,windowsize;
    int t1, t2;
    int cr,cg,cb,tc;
    int i=0;
    vector<struct roi> validROIs;
    struct roi current_roi;

    if ((fp = fopen(param_file_name, "r")) == NULL) {
        fprintf(stderr, "Input file does not exist at: %s\n", param_file_name);
        exit(1);
    }
    while(fgets(str,MAXLEN,fp) != NULL) {
        i++;
        lp = strtok(str, " ");
        ques = atoi(lp);
        lp = strtok(NULL, " ");
        x1 = atoi(lp);
        lp = strtok(NULL, " ");
        y1 = atoi(lp);
        lp = strtok(NULL, " ");
        x2 = x1 + atoi(lp);
        lp = strtok(NULL, " ");
        y2 = y1 + atoi(lp);
        
        current_roi = (roi){x1,y1,x2,y2};
        if (isRoiValid(validROIs, current_roi)){
            validROIs.push_back(current_roi);
            switch(ques){
                case 1:
                    lp = strtok(NULL, " ");
                    t1 = atoi(lp);
                    lp = strtok(NULL, " ");
                    t2 = atoi(lp);
                    if(t1>t2){
                        int t=t2;
                        t2=t1;
                        t1=t;
                    }
                    
                    doubleBinarize(src, tgt, current_roi, t1, t2);   
                    break;

                case 2:
                    lp = strtok(NULL, " ");
                    windowsize = atoi(lp);
                    if(windowsize%2 ==0 || windowsize <3 ){
                        cout << "Window Size must be add and greater than 1. Skipping ROI: " << i << "\n";
                        continue;
                    }
                    
                    meanSmoothFilter(src, tgt, current_roi, windowsize);   
                    break;

                case 3:
                    lp = strtok(NULL, " ");
                    cr = atoi(lp);
                    lp = strtok(NULL, " ");
                    cg = atoi(lp);
                    lp = strtok(NULL, " ");
                    cb = atoi(lp);
                    lp = strtok(NULL, " ");
                    tc = atoi(lp);

                    colorBinarization(src, tgt, current_roi, cr, cg, cb, tc);
                    break;
            }
        }
        else{
            cout << "Input invalid. Skipping ROI number: " << i << "\n";
            continue;
        }
        
    }
    fclose(fp);
}




void utility::doubleBinarize(image &src, image &tgt, struct roi current_roi, int t1, int t2)
{
    int i, j;
    for(i=current_roi.x1;i<=current_roi.x2;i++){
        for(j=current_roi.y1;j<current_roi.y2;j++){

            if (src.getPixel(i,j) >= t1 && src.getPixel(i,j) <= t2)
                tgt.setPixel(i,j,MINRGB);
            else
                tgt.setPixel(i,j,MAXRGB);
        }
    }
}

void utility::colorBinarization(image &src, image &tgt, struct roi current_roi, int cr, int cg, int  cb, int tc)
{
    int i, j; int r,g,b;
    for(i=current_roi.x1;i<=current_roi.x2;i++){
        for(j=current_roi.y1;j<current_roi.y2;j++){
            r=src.getPixel(i,j,RED);
            b=src.getPixel(i,j,BLUE);
            g=src.getPixel(i,j,GREEN);

            if(isInRange(cr,cg,cb,r,g,b,tc))
            {
                tgt.setPixel(i,j,RED,r);
                tgt.setPixel(i,j,GREEN,g);
                tgt.setPixel(i,j,BLUE,b);
            }else{
                tgt.setPixel(i,j,RED,MINRGB);
                tgt.setPixel(i,j,GREEN,MINRGB);
                tgt.setPixel(i,j,BLUE,MINRGB);
            }
        }
    }
}

bool utility::isInRange(int cr,int cg, int cb, int r,int g,int b,int tc){
    float dist = sqrt( (cr-r)*(cr-r)+(cg-g)*(cg-g)+(cb-b)*(cb-b) );
    if (dist < tc){
        return true;
    }
    return false;
}

void utility::meanSmoothFilter(image &src, image &tgt, struct roi current_roi , int windowsize)
{   
    int i, j;

    for(i=current_roi.x1;i<=current_roi.x2;i++){
        for(j=current_roi.y1;j<current_roi.y2;j++){
            tgt.setPixel(i,j, getPixelMeanValue(src, i, j, current_roi, windowsize));
        }
    }
}

int utility::getPixelMeanValue(image &src, int x, int y, struct roi current_roi, int windowsize)
{
    int distance = (int) (windowsize+1)/2;
    if(x-distance < current_roi.x1){
        distance = distance < (x-current_roi.x1) ? distance : (x-current_roi.x1);
    }

    if(x+distance > current_roi.x2){
        distance = distance < (current_roi.x2-x) ? distance : (current_roi.x2-x);
    }

    if(y-distance < current_roi.y1){
        distance = distance < (y-current_roi.y1) ? distance : (y-current_roi.y1);
    }

    if(y+distance > current_roi.y2){
        distance = distance < (current_roi.y2-y) ? distance : (current_roi.y2-y);
    }

    int sum = 0;
    for (int i=x-distance; i<=x+distance; i++)
    {
        for (int j=y-distance; j<=y+distance; j++)
        {   
            sum += src.getPixel(i,j);
        }
    }
    int mean_value = (int) (sum / ((distance*2+1)*(distance*2+1)));
    return mean_value;
}

bool utility::isRoiOverlapping(roi a, roi b){
    return a.x1 < b.x2 && a.x2 > b.x1 && a.y1 < b.y2 && a.y2 > b.y1;
}

bool utility::isRoiValid(vector<roi > validROIs, roi current_roi){
    if (validROIs.size() == 0){
        return true;

    }
    else{
        for (auto vectit = begin(validROIs); vectit != end(validROIs); ++vectit){
            roi used_roi = *vectit;

            if (isRoiOverlapping(used_roi, current_roi) == true){
                return false;
            }
         }
    }
    return true;
 }

