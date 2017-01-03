
#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\imgproc_c.h>
#include <opencv2\ml\ml.hpp>
#include <time.h>   
#include <math.h>
#include <dirent.h>
#include<iomanip>
#include<fstream>

using namespace std; 
using namespace cv; 
#define MAX_SIZE 32

string int2str(int &i) {
		string s;
		stringstream ss(s);
		ss << i;

		return ss.str();
}

int main(int argc,char**argv)
{
	int Height;
    int Width;
    DIR *dir;
    dirent *entry;
    IplImage *src = 0;          //�ӷ��v������
    IplImage *dst = 0;          //�ؼмv������
	IplImage *dst2 = 0;          //�ؼмv������
    double scale = 1;           //�Y�񭿼Ƭ�1��
    CvSize dst_cvsize;          //�ؼмv���ؤo
	CvSize dst_cvsize2;          //�ؼмv���ؤo
 
    LARGE_INTEGER startTime,endTime,fre;
    double times;
    //QueryPerformanceFrequency(&fre); //���oCPU�W�v
    //QueryPerformanceCounter(&startTime); //���o�}����{�b�g�L�X��CPU Cycle
    //doing something
	string data_dir = "..\\..\\Data\\test\\";
	dir=opendir(data_dir.c_str());//�}�ҥؼмv���Ҧb��m��Ƨ�
	int obj_num=1;
    while(entry=readdir(dir)){
        if(strstr(entry->d_name,".jpg")||
            strstr(entry->d_name,".JPG")||
            strstr(entry->d_name,".jpeg")||
            strstr(entry->d_name,".JPEG")||
            strstr(entry->d_name,".png")||
            strstr(entry->d_name,".PNG")||
			strstr(entry->d_name,".PPM")||
			strstr(entry->d_name,".ppm")||
			strstr(entry->d_name,".BMP")||
			strstr(entry->d_name,".bmp")){
			cout<<entry->d_name<<endl;
			string load_name = data_dir + entry->d_name;
			src=cvLoadImage(load_name.c_str(), 1);//�}�Ҽv��
            Height=src->height;//or Height=cvGetDimSize(src,0);
            Width=src->width;//or Width=cvGetDimSize(src,1);
            if(Height > MAX_SIZE || Width > MAX_SIZE){//�p�G���ΰ��j��MAX_SIZE
                if(Height >= Width)
                    scale=MAX_SIZE/(double)Height;
                else
                    scale=MAX_SIZE/(double)Width;
            }
            else{//�_�h�A���L�A���аO�o����v���O����
                cvReleaseImage(&src);   //����ӷ��v�����Ϊ��O����
                cvReleaseImage(&dst);   //����ؼмv�����Ϊ��O����
				cvReleaseImage(&dst2);   //����ؼмv�����Ϊ��O����
                continue;
            }

			//�]�w�ؼмv���j�p
            //dst_cvsize.width = src->width * scale;       //�ؼмv�����e�����v���e��scale��
            //dst_cvsize.height = src->height * scale; //�ؼмv�����������v������scale��
			dst_cvsize.width = 32;
			dst_cvsize.height = 32;
 
            //cout<<setw(15)<<entry->d_name
            //<<setw(3)<<'H'<<setw(5)<<Height
            //<<setw(3)<<'W'<<setw(5)<<Width
            //<<setw(3)<<'h'<<setw(4)<<dst_cvsize.height
            //<<setw(3)<<'w'<<setw(4)<<dst_cvsize.width<<endl;
 
            dst = cvCreateImage(dst_cvsize, src->depth, src->nChannels);  //�Хߥؼмv��
			
            cvResize(src, dst, CV_INTER_LINEAR);    //�Y��ӷ��v����ؼмv��
			string save_dir = data_dir+ "down_scale";
			//string save_name= save_dir +"\\"+ int2str(obj_num) + entry->d_name;
			string tmp = entry->d_name;//entry->d_name.find(".")-1
			string f_name = tmp.substr(0,tmp.find("."));
			string save_name= save_dir +"\\"+ f_name + ".bmp";
			if( opendir(save_dir.c_str())==NULL ){
				printf("down_scale �L����Ƨ�\n");
				system("pause");
				exit(1);
			}
			else{
				cvSaveImage(save_name.c_str(), dst);//�x�s�v��
			}
			obj_num++;

            cvReleaseImage(&src);   //����ӷ��v�����Ϊ��O����
            cvReleaseImage(&dst);   //����ؼмv�����Ϊ��O����
			cvReleaseImage(&dst2);   //����ؼмv�����Ϊ��O����
        }
    }
    //doing something
    //QueryPerformanceCounter(&endTime); //���o�}����{�����槹���g�L�X��CPU Cycle
    //times=((double)endTime.QuadPart-(double)startTime.QuadPart)/fre.QuadPart;
    //cout << fixed << setprecision(20) << times << endl;

	system("pause");
	return 0;
}
