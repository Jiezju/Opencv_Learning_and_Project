//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序01
//		程序描述：OpenCV开发环境的配置，载入一张图片并显示
//		开发测试所用操作系统： Windows 7 64bit
//		开发测试所用IDE版本：Visual Studio 2010
//		开发测试所用OpenCV版本：	3.0 beta
//		2014年11月 Created by @浅墨_毛星云
//		2014年11月 Revised by @浅墨_毛星云
//------------------------------------------------------------------------------------------------

#include <opencv2/opencv.hpp> //头文件
#include <iostream>
#include <string>

using namespace cv; //包含cv命名空间

std::string filePath = "/home/bright/CLionProjects/opencv/1_HelloOpenCV/";

/*
 * argc 表示 命令行 字符串的数量
 * argv[0] 可执行程序名
 * argv[1] 执行命令第一参数
 * argv[2] 执行命令第二参数
 * ...
 *
 * argv[argc] NULL
 * */

int main(int argc, char* argv[]) {
    // 【1】读入一张图片
    Mat img = imread(filePath + "1.jpg",1);
    Mat dstImg;
    if (img.empty())
        std::cout << "图片为空" << std::endl;

    cvtColor(img, dstImg, COLOR_BGR2GRAY);

    // 【2】在窗口中显示载入的图片
    imshow("【载入的图片】", img);
    imshow("【输出的图片】", dstImg);
    // 【3】等待6000 ms后窗口自动关闭
    waitKey(6000);

    return 0;
}