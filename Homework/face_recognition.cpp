#include "face_recognition.h"

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2\objdetect\objdetect_c.h>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
using namespace std;
using namespace cv;

std::vector<std::pair<cv::Mat, std::string >> get_CropFace_And_ImgPathName(const std::string recognitionPath, const std::string cascadeName)
{
	std::vector<std::pair<cv::Mat, std::string>> cropFaceAndImgPathNames;
	std::pair<cv::Mat, std::string> cropFaceAndImgPathName;

	cv::CascadeClassifier cascade;
	cascade.load(cascadeName);
	if (cascade.empty())
	{
		std::cout << "Cascade path error!" << std::endl;
		return std::vector<std::pair<cv::Mat, std::string >>();
	}

	std::ifstream fdatabase;
	fdatabase.open(recognitionPath);
	if (!fdatabase)
	{
		std::cout << "Cannot open " + recognitionPath << std::endl;
		return std::vector<std::pair<cv::Mat, std::string >>();
	}

	double scale = 1.3;
	std::vector<cv::Rect> faces;
	cv::Mat gray;
	std::string name;

	std::cout << "[";

	while (getline(fdatabase, name)) {
		if (name.empty())
		{
			continue;
		}
		name.erase(0, name.find_first_not_of(" \t"));
		name.erase(name.find_last_not_of(" \t") + 1);

		// Read Image
		cv::Mat img = cv::imread(name);
		if (img.empty())
		{
			continue;
		}
		cv::Mat image;
		if (img.channels() != 1)
		{
			cvtColor(img, image, CV_BGR2GRAY);
			image.convertTo(image, CV_8UC1);
		}
		else {
			image = img;
		}

		// Read Opencv Detection Bbx
		cv::Mat smallImg(cvRound(image.rows / scale), cvRound(image.cols / scale), CV_8UC1); //cvRound对double型数据进行四舍五入
		cv::resize(image, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
		cv::equalizeHist(smallImg, smallImg);                                              //equalizeHist提高图像的亮度和对比度
		// --Detection
		cascade.detectMultiScale(smallImg, faces,
			1.1, 3, 0
			/*|CV_HAAR_FIND_BIGGEST_OBJECT
			|CV_HAAR_DO_ROUGH_SEARCH*/
			| CV_HAAR_SCALE_IMAGE
			,
			cv::Size(30, 30));
		for (std::vector<cv::Rect>::iterator r = faces.begin(); r != faces.end(); r++)
		{
			cv::Rect face;
			face.x = int(r->x * scale);
			face.y = int(r->y * scale);
			face.width = int(r->width * scale);
			face.height = int(r->height * scale);

			// 边界检查，左边界，上边界，右边界，下边界。
			/*face.x = face.x < 1 ? 1 : face.x;
			face.y = face.y < 1 ? 1 : face.y;
			face.width = (face.x + face.width) > image.cols ? (image.cols - face.x) : face.width;
			face.height = (face.y + face.height) > image.rows ? (image.rows - face.y) : face.height;*/

			cv::Mat cropFace;
			cropFace = img(face);
			/*cv::moveWindow("cropface", 960 - cropFace.cols / 2, 540 - cropFace.rows / 2);
			cv::imshow("cropface", cropFace);
			cv::waitKey(100);
			cv::destroyWindow("cropface");*/

			cropFaceAndImgPathName = make_pair(cropFace, name);  //cropFaceAndImgPathName = std::pair<cv::Mat, std::string>(cropFace, name);

			cropFaceAndImgPathNames.push_back(cropFaceAndImgPathName);

			std::cout << '.';
		}

	}

	fdatabase.close();

	std::cout << "]" << std::endl;

	return cropFaceAndImgPathNames;
}

bool matchFace(cv::Mat detectFace, cv::Mat dbFace)
{
	
	int hbins = 30, sbins = 32;
	int histSize[] = { hbins, sbins };
	// hue varies from 0 to 179, see cvtColor
	float hranges[] = { 0, 180 };
	// saturation varies from 0 (black-gray-white) to
	// 255 (pure spectrum color)
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	MatND Histogram1, Histogram2;
	int channels[] = { 0, 1 };
	int histSize[] = { 30, 32 };
	/*CvHistogram *Histogram1 = CreateHist(1, &histogramBins, CV_HIST_ARRAY, histogramRange);
	CvHistogram *Histogram2 = CreateHist(1, &histogramBins, CV_HIST_ARRAY, histogramRange);*/
	
	calcHist(&detectFace, 1, channels, Mat(), Histogram1, 2, histSize, ranges, true, false);
	calcHist(&dbFace, 1, channels, Mat(), Histogram2, 2, histSize, ranges, true, false);

	/*double factor = 1;
	cvNormalizeHist(Histogram1, factor);
	NormalizeHist(Histogram2, factor);*/


	// CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似  
	//printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));
	//printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));  


	// CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似  
	//printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));  
	//printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));
	double simility = compareHist(Histogram1, Histogram2, CV_COMP_CHISQR);

	if (simility > 0.5)
	{
		return false;
	}

	return true;
}

//void face_recognition(std::string recognitionPath, const std::string cascadeName)
//{
//	bool isPreDeal = false;
//	if (isPreDeal)              //是否进行预处理
//	{
//		preDeal_original_img(recognitionPath, cascadeName);
//		recognitionPath = "../camera_face/";
//	}
//
//	//获取数据库中人脸图像
//	std::string face_Database = "../face_database/Path_Images.txt";
//	std::vector<std::pair<cv::Mat, std::string>> cropFaceAndImgPathNames;
//	std::cout << "开始数据库中人脸数据的读取..." << std::endl;
//	cropFaceAndImgPathNames = get_CropFace_And_ImgPathName(face_Database, cascadeName);
//	std::cout << "结束数据库中人脸数据的读取。" << std::endl;
//
//	//开始人脸匹配
//	std::ifstream frecognition;
//	frecognition.open(recognitionPath);
//	if (!frecognition)
//	{
//		std::cout << "Images path Error!" << std::endl;
//		return;
//	}
//
//	cv::CascadeClassifier cascade;
//	cascade.load(cascadeName);
//	if (cascade.empty())
//	{
//		std::cout << "Cascade path error!" << std::endl;
//		return;
//	}
//
//	double scale = 1.3;
//	std::vector<cv::Rect> faces;
//	cv::Mat gray;
//	std::string name;
//
//	bool isExist = false;   //数据库中是否存在该匹配文件
//
//	while (getline(frecognition, name)) {
//		if (name.empty())
//		{
//			continue;
//		}
//		name.erase(0, name.find_first_not_of(" \t"));
//		name.erase(name.find_last_not_of(" \t") + 1);
//
//		// Read Image
//		cv::Mat img = cv::imread(name);
//		cv::Mat image;
//		if (img.channels() != 1)
//		{
//			cvtColor(img, image, CV_BGR2GRAY);
//			image.convertTo(image, CV_8UC1);
//		}
//		else {
//			image = img;
//		}
//
//		// Read Opencv Detection Bbx
//		cv::Mat smallImg(cvRound(image.rows / scale), cvRound(image.cols / scale), CV_8UC1); //cvRound对double型数据进行四舍五入
//		cv::resize(image, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
//		cv::equalizeHist(smallImg, smallImg);                                              //equalizeHist提高图像的亮度和对比度
//		// --Detection
//		cascade.detectMultiScale(smallImg, faces,
//			1.1, 3, 0
//			/*|CV_HAAR_FIND_BIGGEST_OBJECT
//			|CV_HAAR_DO_ROUGH_SEARCH*/
//			| CV_HAAR_SCALE_IMAGE
//			,
//			cv::Size(30, 30));
//		for (std::vector<cv::Rect>::iterator r = faces.begin(); r != faces.end(); r++)
//		{
//			cv::Rect face;
//			face.x = int(r->x * scale);
//			face.y = int(r->y * scale);
//			face.width = int(r->width * scale);
//			face.height = int(r->height * scale);
//
//			cv::Mat detectFace = img(face);
//
//			for (std::vector<std::pair<cv::Mat, std::string>>::iterator dbFace = cropFaceAndImgPathNames.begin(); dbFace != cropFaceAndImgPathNames.end(); dbFace++)
//			{
//				std::pair<cv::Mat, std::string> dbFaceImg = *dbFace;
//				bool isMatch = matchFace(detectFace, dbFaceImg.first);
//				if (isMatch) {
//					std::cout << name + " Matching " + dbFaceImg.second + " successful!" << std::endl;
//					cv::imshow("detectFace", detectFace);
//					cv::imshow("databaseFace", dbFaceImg.first);
//					cv::waitKey(200);
//					cv::destroyWindow("detectFace");
//					cv::destroyWindow("databaseFace");
//					isExist = true;
//				}
//			}
//
//		}
//	}
//
//	if (!isExist)
//	{
//		std::cout << name + " Matching failed!" << std::endl;
//	}
//
//	frecognition.close();
//}