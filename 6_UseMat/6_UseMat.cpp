//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序19
//		程序描述：基础图像容器Mat类的使用
//		开发测试所用操作系统： Windows 7 64bit
//		开发测试所用IDE版本：Visual Studio 2010
//		开发测试所用OpenCV版本：	3.0 beta
//		2014年11月 Created by @浅墨_毛星云
//		2014年12月 Revised by @浅墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【头文件、命名空间包含部分】---------------------------
//          描述：包含程序所使用的头文件和命名空间
//-----------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace cv;


//-----------------------------【ShowHelpText( )函数】--------------------------------------
//		描述：输出帮助信息
//-------------------------------------------------------------------------------------------------
static void ShowHelpText() {
    //输出欢迎信息和OpenCV版本
    printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n");

    //输出一些帮助信息
    printf("\n\n\n\t欢迎来到【基本图像容器-Mat类】示例程序~\n\n");
    printf("\n\n\t程序说明：\n\n\t此示例程序用于演示Mat类的格式化输出功能，输出风格可为：");
    printf("\n\n\n\t【1】OpenCV默认风格");
    printf("\n\n\t【2】Python风格");
    printf("\n\n\t【3】逗号分隔风格");
    printf("\n\n\t【4】Numpy风格");
    printf("\n\n\t【5】C语言风格\n\n");
    printf("\n  --------------------------------------------------------------------------\n");


}


//--------------------------------------【main( )函数】-----------------------------------------
//          描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main(int, char **) {
    //改变控制台的前景色和背景色
    system("color 8F");

    //显示帮助文字
    ShowHelpText();

    /**************** 显示创建 Mat 的七种方法 *******************/
    // 1. Mat()
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;

    // 2. 构造函数初始化
    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC1, Scalar::all(0));

    // 3. IplImage 方式
    IplImage *img = cvLoadImage("/home/bright/CLionProjects/opencv/6_UseMat/1.jpg");
    Mat mtimg = cvarrToMat(img); // IplImage* -> img

    // 4. Create() 只是改变尺寸重新开辟空间
    M.create(4, 4, CV_8UC2);
    cout << "M = " << endl << " " << M << endl << endl;

    // Matlab 初始化
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;

    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;

    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;

    // 对小矩阵进行逗号分隔符初始化
    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;

    // 对矩阵进行截取复制
    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;

    Mat I = Mat::eye(4, 4, CV_64F);
    I.at<double>(1, 1) = CV_PI;
    cout << "\nI = " << I << ";\n" << endl;

    /**************** 格式化输出方法 *******************/
    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));


    cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
    cout << "r (Python风格) = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (Numpy风格) = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    cout << "r (逗号分隔风格) = " << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    cout << "r (C语言风格) = " << format(r, Formatter::FMT_C) << ";" << endl << endl;

    Point ipt(1,3);
    cout << "【2维点】p = " << ipt << ";\n" << endl;
    Point2f p(6, 2);
    cout << "【2维点】p = " << p << ";\n" << endl;

    Point3f p3f(8, 2, 0);
    cout << "【3维点】p3f = " << p3f << ";\n" << endl;

    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);

    cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n" << endl;

    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float) (i * 5), (float) (i % 7));

    cout << "【二维点向量】points = " << points << ";\n";

    Size is(4,5);
    cout << "【二维size向量】size = " << is << ";\n";

    Scalar s(255,255,0);
    cout << "【三维Scalar向量】size = " << s << ";\n";

    Rect rect1(0,0,10,10);
    Rect rect2(5,5,10,10);
    Rect rec3 = rect1 & rect2;
    Rect rec4 = rect1 + ipt;
    Rect rec5 = rect1 + is;

    getchar();//按任意键退出

    return 0;


}
