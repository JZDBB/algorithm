#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

unsigned char *pBmpBuf;//读入图像数据的指针

int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针

int biBitCount;//图像类型，每像素位数

//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool readBmp(char *bmpName)
{
	FILE *fp = fopen(bmpName, "rb");//二进制读方式打开指定的图像文件

	if (fp == 0)
		return 0;

	//跳过位图文件头结构BITMAPFILEHEADER

	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中

	BITMAPINFOHEADER head;

	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp); //获取图像宽、高、每像素所占位数等信息

	bmpWidth = head.biWidth;

	bmpHeight = head.biHeight;

	biBitCount = head.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）

	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256

	if (biBitCount == 8)
	{

		//申请颜色表所需要的空间，读颜色表进内存

		pColorTable = new RGBQUAD[256];

		fread(pColorTable, sizeof(RGBQUAD), 256, fp);

	}

	//申请位图数据所需要的空间，读位图数据进内存

	pBmpBuf = new unsigned char[lineByte * bmpHeight];

	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	fclose(fp);//关闭文件

	return 1;//读取文件成功
}

bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

	//如果位图数据指针为0，则没有数据传入，函数返回

	if (!imgBuf)
		return 0;

	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0

	int colorTablesize = 0;

	if (biBitCount == 8)
		colorTablesize = 1024;

	//待存储图像数据每行字节数为4的倍数

	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//以二进制写的方式打开文件

	FILE *fp = fopen(bmpName, "wb");

	if (fp == 0)
		return 0;

	//申请位图文件头结构变量，填写文件头信息

	BITMAPFILEHEADER fileHead;

	fileHead.bfType = 0x4D42;//bmp类型

	//bfSize是图像文件4个组成部分之和

	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;

	fileHead.bfReserved1 = 0;

	fileHead.bfReserved2 = 0;

	//bfOffBits是图像文件前3个部分所需空间之和

	fileHead.bfOffBits = 54 + colorTablesize;

	//写文件头进文件

	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	//申请位图信息头结构变量，填写信息头信息

	BITMAPINFOHEADER head;

	head.biBitCount = biBitCount;

	head.biClrImportant = 0;

	head.biClrUsed = 0;

	head.biCompression = 0;

	head.biHeight = height;

	head.biPlanes = 1;

	head.biSize = 40;

	head.biSizeImage = lineByte * height;

	head.biWidth = width;

	head.biXPelsPerMeter = 0;

	head.biYPelsPerMeter = 0;

	//写位图信息头进内存

	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//如果灰度图像，有颜色表，写入文件 

	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

	//写位图数据进文件

	fwrite(imgBuf, height*lineByte, 1, fp);

	//关闭文件

	fclose(fp);

	return 1;

}
void doIt()
{
	char readPath[] = "12.bmp";
	readBmp(readPath);
	// 输出整体图像信息
	cout << "width=" << bmpWidth << "height=" << bmpHeight << "biBitCount=" << biBitCount << endl;
	// 图像的字节数
	int linebyte1 = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	int n = 0, m = 0, count_xiang_su = 0;

	// ofstream outfile("图像像素.txt",ios::in|ios::trunc);将像素数据存入TXT文件。
   //初始化原始像素的数组。

	if (biBitCount == 8)
	{
		for (int i = 0; i < bmpHeight /2; i++)
		{
			for (int j = 0; j < bmpWidth /2; j++)
				*(pBmpBuf + i * linebyte1 + j) = 0;
		}
	}

	if (biBitCount == 24)
	{
		for (int i = 0; i < bmpHeight /2; i++)
		{
			for (int j = 0; j < bmpWidth /2; j++)
			{
				for (int k = 0; k < 3; k++)//每像素RGB三个分量分别置0才变成黑色
				{
					m = *(pBmpBuf + i * linebyte1 + j * 3 + k);

					count_xiang_su++;

				}
				n++;
			}


		}
		cout << "总的像素个素为:" << n << endl;
		cout << "----------------------------------------------------" << endl;
	}

	// jiang tuxiang shuju cunpan .
	char writePath[] = "3.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间

	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;

}



//------------------------------【两步法新改进版】----------------------------------------------
// 对二值图像进行连通区域标记,从1开始标号
void  Two_PassNew(const Mat &bwImg, Mat &labImg)
{
	assert(bwImg.type() == CV_8UC1);
	labImg.create(bwImg.size(), CV_32SC1);   //bwImg.convertTo( labImg, CV_32SC1 );
	labImg = Scalar(0);
	labImg.setTo(Scalar(1), bwImg);
	assert(labImg.isContinuous());
	const int Rows = bwImg.rows - 1, Cols = bwImg.cols - 1;
	int label = 1;
	vector<int> labelSet;
	labelSet.push_back(0);
	labelSet.push_back(1);
	//the first pass
	int *data_prev = (int*)labImg.data;   //0-th row : int* data_prev = labImg.ptr<int>(i-1);
	int *data_cur = (int*)(labImg.data + labImg.step); //1-st row : int* data_cur = labImg.ptr<int>(i);
	for (int i = 1; i < Rows; i++)
	{
		data_cur++;
		data_prev++;
		for (int j = 1; j < Cols; j++, data_cur++, data_prev++)
		{
			if (*data_cur != 1)
				continue;
			int left = *(data_cur - 1);
			int up = *data_prev;
			int neighborLabels[2];
			int cnt = 0;
			if (left > 1)
				neighborLabels[cnt++] = left;
			if (up > 1)
				neighborLabels[cnt++] = up;
			if (!cnt)
			{
				labelSet.push_back(++label);
				labelSet[label] = label;
				*data_cur = label;
				continue;
			}
			int smallestLabel = neighborLabels[0];
			if (cnt == 2 && neighborLabels[1] < smallestLabel)
				smallestLabel = neighborLabels[1];
			*data_cur = smallestLabel;
			// 保存最小等价表
			for (int k = 0; k < cnt; k++)
			{
				int tempLabel = neighborLabels[k];
				int& oldSmallestLabel = labelSet[tempLabel];  //这里的&不是取地址符号,而是引用符号
				if (oldSmallestLabel > smallestLabel)
				{
					labelSet[oldSmallestLabel] = smallestLabel;
					oldSmallestLabel = smallestLabel;
				}
				else if (oldSmallestLabel < smallestLabel)
					labelSet[smallestLabel] = oldSmallestLabel;
			}
		}
		data_cur++;
		data_prev++;
	}
	//更新等价队列表,将最小标号给重复区域
	for (size_t i = 2; i < labelSet.size(); i++)
	{
		int curLabel = labelSet[i];
		int prelabel = labelSet[curLabel];
		while (prelabel != curLabel)
		{
			curLabel = prelabel;
			prelabel = labelSet[prelabel];
		}
		labelSet[i] = curLabel;
	}
	//second pass
	data_cur = (int*)labImg.data;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < bwImg.cols - 1; j++, data_cur++)
			*data_cur = labelSet[*data_cur];
		data_cur++;
	}
}

//-------------------------------【老版两步法】-------------------------------------------
void Two_PassOld(const cv::Mat& _binImg, cv::Mat& _lableImg)
{
	//connected component analysis (4-component)
	//use two-pass algorithm
	//1. first pass: label each foreground pixel with a label
	//2. second pass: visit each labeled pixel and merge neighbor label
	//
	//foreground pixel: _binImg(x,y) = 1
	//background pixel: _binImg(x,y) = 0

	if (_binImg.empty() || _binImg.type() != CV_8UC1)
	{
		return;
	}

	// 1. first pass
	_lableImg.release();
	_binImg.convertTo(_lableImg, CV_32SC1);

	int label = 1;  // start by 2
	std::vector<int> labelSet;
	labelSet.push_back(0);   //background: 0
	labelSet.push_back(1);   //foreground: 1

	int rows = _binImg.rows - 1;
	int cols = _binImg.cols - 1;
	for (int i = 1; i < rows; i++)
	{
		int* data_preRow = _lableImg.ptr<int>(i - 1);
		int* data_curRow = _lableImg.ptr<int>(i);
		for (int j = 1; j < cols; j++)
		{
			if (data_curRow[j] == 1)
			{
				std::vector<int> neighborLabels;
				neighborLabels.reserve(2); //reserve(n)  预分配n个元素的存储空间
				int leftPixel = data_curRow[j - 1];
				int upPixel = data_preRow[j];
				if (leftPixel > 1)
				{
					neighborLabels.push_back(leftPixel);
				}
				if (upPixel > 1)
				{
					neighborLabels.push_back(upPixel);
				}
				if (neighborLabels.empty())
				{
					labelSet.push_back(++label);   //assign to a new label
					data_curRow[j] = label;
					labelSet[label] = label;
				}
				else
				{
					std::sort(neighborLabels.begin(), neighborLabels.end());
					int smallestLabel = neighborLabels[0];
					data_curRow[j] = smallestLabel;

					//save equivalence
					for (size_t k = 1; k < neighborLabels.size(); k++)
					{
						int tempLabel = neighborLabels[k];
						int& oldSmallestLabel = labelSet[tempLabel];
						if (oldSmallestLabel > smallestLabel)
						{
							labelSet[oldSmallestLabel] = smallestLabel;
							oldSmallestLabel = smallestLabel;
						}
						else if (oldSmallestLabel < smallestLabel)
						{
							labelSet[smallestLabel] = oldSmallestLabel;
						}
					}
				}

			}
		}
	}
	//update equivalent labels
	//assigned with the smallest label in each equivalent label set
	for (size_t i = 2; i < labelSet.size(); i++)
	{
		int curLabel = labelSet[i];
		int prelabel = labelSet[curLabel];
		while (prelabel != curLabel)
		{
			curLabel = prelabel;
			prelabel = labelSet[prelabel];
		}
		labelSet[i] = curLabel;
	}

	//2. second pass
	for (int i = 0; i < rows; i++)
	{
		int *data = _lableImg.ptr<int>(i);
		for (int j = 0; j < cols; j++)
		{
			int& pixelLabel = data[j];
			pixelLabel = labelSet[pixelLabel];
		}
	}
}


//---------------------------------【种子填充法老版】-------------------------------
void SeedFillOld(const cv::Mat& binImg, cv::Mat& lableImg)   //种子填充法
{
	// 4邻接方法


	if (binImg.empty() ||
		binImg.type() != CV_8UC1)
	{
		return;
	}

	lableImg.release();
	binImg.convertTo(lableImg, CV_32SC1);

	int label = 1;

	int rows = binImg.rows - 1;
	int cols = binImg.cols - 1;
	for (int i = 1; i < rows - 1; i++)
	{
		int* data = lableImg.ptr<int>(i);
		for (int j = 1; j < cols - 1; j++)
		{
			if (data[j] == 1)
			{
				std::stack<std::pair<int, int>> neighborPixels;
				neighborPixels.push(std::pair<int, int>(i, j));     // 像素位置: <i,j>
				++label;  // 没有重复的团，开始新的标签
				while (!neighborPixels.empty())
				{
					std::pair<int, int> curPixel = neighborPixels.top(); //如果与上一行中一个团有重合区域，则将上一行的那个团的标号赋给它
					int curX = curPixel.first;
					int curY = curPixel.second;
					lableImg.at<int>(curX, curY) = label;

					neighborPixels.pop();

					if (lableImg.at<int>(curX, curY - 1) == 1)
					{//左边
						neighborPixels.push(std::pair<int, int>(curX, curY - 1));
					}
					if (lableImg.at<int>(curX, curY + 1) == 1)
					{// 右边
						neighborPixels.push(std::pair<int, int>(curX, curY + 1));
					}
					if (lableImg.at<int>(curX - 1, curY) == 1)
					{// 上边
						neighborPixels.push(std::pair<int, int>(curX - 1, curY));
					}
					if (lableImg.at<int>(curX + 1, curY) == 1)
					{// 下边
						neighborPixels.push(std::pair<int, int>(curX + 1, curY));
					}
				}
			}
		}
	}

}




//-------------------------------------------【种子填充法新版】---------------------------
void SeedFillNew(const cv::Mat& _binImg, cv::Mat& _lableImg)
{
	// connected component analysis(4-component)
	// use seed filling algorithm
	// 1. begin with a forgeground pixel and push its forground neighbors into a stack;
	// 2. pop the pop pixel on the stack and label it with the same label until the stack is empty
	// 
	//  forground pixel: _binImg(x,y)=1
	//  background pixel: _binImg(x,y) = 0


	if (_binImg.empty() ||
		_binImg.type() != CV_8UC1)
	{
		return;
	}

	_lableImg.release();
	_binImg.convertTo(_lableImg, CV_32SC1);

	int label = 0; //start by 1

	int rows = _binImg.rows;
	int cols = _binImg.cols;

	Mat mask(rows, cols, CV_8UC1);
	mask.setTo(0);
	int *lableptr;
	for (int i = 0; i < rows; i++)
	{
		int* data = _lableImg.ptr<int>(i);
		uchar *masKptr = mask.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			if (data[j] == 255 && mask.at<uchar>(i, j) != 1)
			{
				mask.at<uchar>(i, j) = 1;
				std::stack<std::pair<int, int>> neighborPixels;
				neighborPixels.push(std::pair<int, int>(i, j)); // pixel position: <i,j>
				++label; //begin with a new label
				while (!neighborPixels.empty())
				{
					//get the top pixel on the stack and label it with the same label
					std::pair<int, int> curPixel = neighborPixels.top();
					int curY = curPixel.first;
					int curX = curPixel.second;
					_lableImg.at<int>(curY, curX) = label;

					//pop the top pixel
					neighborPixels.pop();

					//push the 4-neighbors(foreground pixels)

					if (curX - 1 >= 0)
					{
						if (_lableImg.at<int>(curY, curX - 1) == 255 && mask.at<uchar>(curY, curX - 1) != 1) //leftpixel
						{
							neighborPixels.push(std::pair<int, int>(curY, curX - 1));
							mask.at<uchar>(curY, curX - 1) = 1;
						}
					}
					if (curX + 1 <= cols - 1)
					{
						if (_lableImg.at<int>(curY, curX + 1) == 255 && mask.at<uchar>(curY, curX + 1) != 1)
							// right pixel
						{
							neighborPixels.push(std::pair<int, int>(curY, curX + 1));
							mask.at<uchar>(curY, curX + 1) = 1;
						}
					}
					if (curY - 1 >= 0)
					{
						if (_lableImg.at<int>(curY - 1, curX) == 255 && mask.at<uchar>(curY - 1, curX) != 1)
							// up pixel
						{
							neighborPixels.push(std::pair<int, int>(curY - 1, curX));
							mask.at<uchar>(curY - 1, curX) = 1;
						}
					}
					if (curY + 1 <= rows - 1)
					{
						if (_lableImg.at<int>(curY + 1, curX) == 255 && mask.at<uchar>(curY + 1, curX) != 1)
							//down pixel
						{
							neighborPixels.push(std::pair<int, int>(curY + 1, curX));
							mask.at<uchar>(curY + 1, curX) = 1;
						}
					}
				}
			}
		}
	}
}


//---------------------------------【颜色标记程序】-----------------------------------
//彩色显示
cv::Scalar GetColor()
{
	uchar r = 255 / 4;
	uchar g = 255 / 3;
	uchar b = 255 / 2;
	return cv::Scalar(b, g, r);
}


void LabelColor(const cv::Mat& labelImg, cv::Mat& colorLabelImg)
{
	int num = 0;
	if (labelImg.empty() ||
		labelImg.type() != CV_32SC1)
	{
		return;
	}

	std::map<int, cv::Scalar> colors;

	int rows = labelImg.rows;
	int cols = labelImg.cols;

	colorLabelImg.release();
	colorLabelImg.create(rows, cols, CV_8UC3);
	colorLabelImg = cv::Scalar::all(0);

	for (int i = 0; i < rows; i++)
	{
		const int* data_src = (int*)labelImg.ptr<int>(i);
		uchar* data_dst = colorLabelImg.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			int pixelValue = data_src[j];
			if (pixelValue > 1)
			{
				if (colors.count(pixelValue) <= 0)
				{
					colors[pixelValue] = GetColor();
					num++;
				}

				cv::Scalar color = colors[pixelValue];
				*data_dst++ = color[0];
				*data_dst++ = color[1];
				*data_dst++ = color[2];
			}
			else
			{
				data_dst++;
				data_dst++;
				data_dst++;
			}
		}
	}
	printf("color num : %d \n", num);
}

//------------------------------------------【测试主程序】-------------------------------------
int main()
{

	Mat binImage;
	binImage = imread("1.bmp", IMREAD_COLOR);
	cvtColor(binImage, binImage, COLOR_RGB2GRAY);
	Mat labelImg;
	
	//对应四种方法，需要哪一种，则调用哪一种
	//Two_PassOld(binImage, labelImg);
	//Two_PassNew(binImage, labelImg);
	//SeedFillOld(binImage, labelImg);
	SeedFillNew(binImage, labelImg);
	
	//彩色显示
	Mat colorLabelImg;
	LabelColor(labelImg, colorLabelImg);
	imshow("colorImg", colorLabelImg);
	waitKey(0);
}
