#include "ceres/ceres.h"
#include "ceres/rotation.h"
#include "glog/logging.h"
#include <opencv2/opencv.hpp>
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
// A templated cost functor that implements the residual r = 10 -
// x. The method operator() is templated so that we can then use an
// automatic differentiation wrapper around it to generate its
// derivatives.
struct CostFunctor {
  template <typename T> bool operator()(const T* const x, T* residual) const {
    residual[0] = 10.0 - x[0];
    return true;
  }
};
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  // The variable to solve for with its initial value. It will be
  // mutated in place by the solver.
  double x = 0.5;
  const double initial_x = x;
  // Build the problem.
  Problem problem;
  // Set up the only cost function (also known as residual). This uses
  // auto-differentiation to obtain the derivative (jacobian).
  CostFunction* cost_function =
      new AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
  problem.AddResidualBlock(cost_function, NULL, &x);
  // Run the solver!
  Solver::Options options;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << "\n";
  std::cout << "x : " << initial_x
            << " -> " << x << "\n";
  Eigen::Vector3d v;
  double pi = 3.14159;
  //Eigen::AngleAxis rotation_vector();
  Eigen::AngleAxisd rotation_vector ( M_PI/2, Eigen::Vector3d ( 0,1,0 ) );  
  Eigen::Matrix3d rotationMatrix = rotation_vector.toRotationMatrix();
  std::cout<<"R:\n"<<rotationMatrix<<std::endl;
  
  Eigen::AngleAxisd rotation_vector2(rotationMatrix);
  std::cout<<"rotation_vector2: "<<rotation_vector2.angle()*rotation_vector2.axis()<<std::endl;
  
  double rvec[3]={(rotation_vector2.angle()*rotation_vector2.axis())[0],(rotation_vector2.angle()*rotation_vector2.axis())[1],(rotation_vector2.angle()*rotation_vector2.axis())[2]};
  double Rvec[9];
  ceres::AngleAxisToRotationMatrix(rvec,Rvec);
  Eigen::Matrix3d Rvec2;
  //ceres::AngleAxisToRotationMatrix(rvec,Rvec2);
  
  
  
  std::cout<<"rvec: ";
  for(int i=0;i<3;++i)
  {
    std::cout<<rvec[i]<<" ";
  }
  std::cout<<std::endl;
  for(int i=0;i<3;++i)
  {
    for(int j=0;j<3;++j)
    {
      std::cout<<Rvec[i*3+j]<<" ";
    }
    std::cout<<std::endl;
  }
  
  for(int i=0;i<9;++i)
  {
    Rvec2(i%3,i/3)=Rvec[i];
  }
  
  std::cout<<"Rvec2: \n"<<Rvec2<<std::endl;
  
  
  double Rvec3[9];
  for(int i=0;i<9;++i)
  {
    Rvec3[i]=Rvec2(i%3,i/3);
  }
  
  ceres::RotationMatrixToAngleAxis(Rvec3,rvec);
  for(int i=0;i<3;++i)
  {
    std::cout<<rvec[i]<<" ";
  }
  std::cout<<std::endl; 
  
  
  cv::Mat cvrvec = cv::Mat(3,1,CV_64F);
  cvrvec.at<double>(0) = rvec[0];
  cvrvec.at<double>(1) = rvec[1];
  cvrvec.at<double>(2) = rvec[2];
  cv::Mat cvR;
  cv::Rodrigues(cvrvec,cvR);
  std::cout<<"cvR:\n"<<std::endl;
  std::cout<<cvR.at<double>(0,0)<<" "<<cvR.at<double>(0,1)<<" "<<cvR.at<double>(0,2)<<std::endl;
  std::cout<<cvR.at<double>(1,0)<<" "<<cvR.at<double>(1,1)<<" "<<cvR.at<double>(1,2)<<std::endl;
  std::cout<<cvR.at<double>(2,0)<<" "<<cvR.at<double>(2,1)<<" "<<cvR.at<double>(2,2)<<std::endl;
  return 0;
}
