//set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
//include_directories($ {EIGEN3_INCLUDE_DIRS})
#include <iostream>
#include <vector>
#include "ceres/ceres.h"
#include "ceres/rotation.h"
#include "glog/logging.h"
#include <opencv2/opencv.hpp>
using namespace std;
//std::vector<>
std::vector<std::vector<cv::Point3d>> p3dObjects;
std::vector<std::vector<cv::Point2d>> p2dObjects;
std::ofstream bafile("bafile.txt");
void globalCoor(std::vector<std::vector<cv::Point3d>>& p3dObjects,  std::vector<std::vector<cv::Point2d>>& p2dObjects,const std::vector<int>& detector)
{
  std::vector<int> detectors;
  for(int i=0;i<detectors.size();++i)
  {
    int id = detectors[i];
    int idsave=id;
    int boardId = id/9;
    id=id%9;
    cv::Point3d lbp3d,rbp3d,rtp3d,ltp3d;
    cv::Point2d lbp2d,rbp2d,rtp2d,ltp2d;
    p3dObjects[boardId].push_back(lbp3d);
    p3dObjects[boardId].push_back(rbp3d);
    p3dObjects[boardId].push_back(rtp3d);
    p3dObjects[boardId].push_back(ltp3d);
    
    p2dObjects[boardId].push_back(lbp2d);
    p2dObjects[boardId].push_back(rbp2d);
    p2dObjects[boardId].push_back(rtp2d);
    p2dObjects[boardId].push_back(ltp2d);
    int cameraIndex=1;
    bafile<<cameraIndex<<" "<<idsave*4+0<<lbp2d.x<<" "<<lbp2d.y<<std::endl;
    bafile<<cameraIndex<<" "<<idsave*4+1<<rbp2d.x<<" "<<rbp2d.y<<std::endl;
    bafile<<cameraIndex<<" "<<idsave*4+2<<rtp2d.x<<" "<<rtp2d.y<<std::endl;
    bafile<<cameraIndex<<" "<<idsave*4+3<<ltp2d.x<<" "<<ltp2d.y<<std::endl;
    
  }
  return;
}

int main()
{
  int boardNum=8;

 // globalCoor(p3dObjects, p2dObjects); 
  cv::Mat rvec= cv::Mat(3,1,CV_64F);
  cv::Mat tvec=cv::Mat(3,1,CV_64F);
  std::vector<std::vector<double>> cameraData;
  while(true)//图片一直未中断
  {
    ;
    std::vector<int> detector;
    //检测 f(detector)
      std::vector<std::vector<cv::Point3d>> p3dObjects(boardNum);
      std::vector<std::vector<cv::Point2d>> p2dObjects(boardNum);
      int boardIdCameraPoseRelativeTo=-1;
    for(int i=0;i<detector.size();++i)
    {
      globalCoor(p3dObjects,p2dObjects,detector);
      
    }
     for(int i=0;i<p3dObjects.size();++i)
      {
	if(p3dObjects[i].size()!=0)
	{
	  boardIdCameraPoseRelativeTo=i;
	  //solvePnp(rvec,tvec,p3dObjects[i],p2dObjects[i]);
	  break;
	}
      }
  //while()
    if(boardIdCameraPoseRelativeTo==-1)
    {
      //TODO no observation
      boardIdCameraPoseRelativeTo=0;
    }
    vector<double> cameraPose(7);
    cameraPose[0]=boardIdCameraPoseRelativeTo;
    for(int i=0;i<3;++i)
    {
      cameraPose[i+1]=rvec.at<double>(i);
    }
    for(int i=0;i<3;++i)
    {
      cameraPose[i+4]=tvec.at<double>(i);
    }
    cameraData.push_back(cameraPose);
  }
  
  for(int i=0;i<cameraData.size();++i)
  {
    for(int j=0;j<7; ++j)
    {
      bafile<<cameraData[i][j]<<" ";
    }
    bafile<<std::endl;
  }
  //std::vector<int> detector;
  //while()
  //for(int i=0;i<p3dObjects.size();++i)
  //{
    //if(p3dObjects[i].size()!=0)
    //{
      
    //}
  //}
  return 0;
}


void ceresfunction()
{
  //observation doesn't change
  //camera 7
  //index+1 like point
  //point data load
  //traverse camera data, update init value
  int boardNum=10;
  std::vector<std::vector<double>> relativePose(10);
  std::vector<double> T12={1,1,1,1,1,1};
  std::vector<double> T13={1,1,1,1,1,1};
  std::vector<double> T14={1,1,1,1,1,1};
  //.....
  //set init value more accuracy
  
  int cameraNum=100;
  vector<double> cameraData;
  for(int i=0;i<cameraNum;++i)
  {
    int boardIdCameraPoseRelativeTo = cameraData[7*i+0];
    if(boardIdCameraPoseRelativeTo!=0)
    {
      //pose cM, T1M, result Pc TC1=TC2*T21=cameradata * T12inverse
      //update init
    }
  }
  
}


