#include<opencv2/opencv.hpp>
#include<iostream>
#include <cstdio>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>


using namespace std;
using namespace cv;

static bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs)
{
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    return true;
}

int main()
{
    char buffer[1000];
    Mat myImage;
    namedWindow("Video Player");
    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 2000);
    cap.set(CAP_PROP_FRAME_HEIGHT, 2000);
    Mat cameraMatrix, distCoeffs;
    readCameraParameters("calib.txt", cameraMatrix, distCoeffs);
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_100);
    Vec3d tvecs42,rvecs42 ;
    Mat mat42 = Mat::eye(3,3,CV_64F);


  if (!cap.isOpened())
    {
        cout << "No video stream detected" << endl;
        system("pause");
        return-1;
    }

    vector<int> ids;
    vector<std::vector<cv::Point2f>> corners;
    vector<Vec3d> rvecs, tvecs;

    while (true)
    {
        cap >> myImage;

        aruco::detectMarkers(myImage, dictionary, corners, ids);
        aruco::drawDetectedMarkers(myImage, corners, ids);

            for(int i=0; i<ids.size(); i++)
            {
            aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
            aruco::drawAxis(myImage, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
            if (ids[i] == 42) {
                tvecs42 = tvecs[i];
                rvecs42 = rvecs[i];
                Rodrigues(rvecs42, mat42);
                mat42 = mat42.inv();
            } else {
                Mat mat = Mat::eye(3,3,CV_64F);
                Rodrigues(rvecs[i], mat);
                cv::Mat tdest = mat42 * (tvecs[i] - tvecs42);
                cv::Mat matDest = mat42 * mat;
                cv::Vec3d rdest;
                Rodrigues(matDest, rdest);
                stringstream stream;

                cout << "t" << ids[i] << "/42: " << 100.0*tdest.t() << "  r" << ids[i] << "/42: " << (180.0/M_PI)*rdest << endl;
                stream << "t" << ids[i] << "/42: " << 100.0*tdest.t() << "  r" << ids[i] << "/42: " << (180.0/M_PI)*rdest << endl;
                //cout << stream;
                //stream.c_str();  // stream.c_str()=buffer  --> buffer est un tablau de caractere ascii
                }

            }


        if (myImage.empty())
        {
            break;
        }

        imshow("Video Player", myImage);

        char c = (char)waitKey(10);
        if (c == 27)
        {
            break;
        }
    }
    cap.release();
    return 0;
}
