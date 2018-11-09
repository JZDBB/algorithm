#pragma once
#ifndef _FACE_RECOGNITION_H_
#define _FACE_RECOGNITION_H_

//#include "common.h"

//void preDeal_original_img(const std::string recognitionPath, const std::string cascadeName);
std::vector<std::pair<cv::Mat, std::string >> get_CropFace_And_ImgPathName(const std::string recognitionPath, const std::string cascadeName);
bool matchFace(cv::Mat detectFace, cv::Mat dbFace);
//void face_recognition(std::string recognitionPath, const std::string cascadeName);

#endif