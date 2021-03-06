//
// Created by Bright on 2022/5/11.
//

//---------------------------------【头文件、命名空间包含部分】----------------------------
//		描述：包含程序所使用的头文件和命名空间
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


//-----------------------------------【ShowHelpText( )函数】-----------------------------
//          描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText() {

    //输出欢迎信息和OpenCV版本
    printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
    printf("\n\n\t\t\t此为本书OpenCV3版的第73个配套示例程序\n");
    printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
    printf("\n\n  ----------------------------------------------------------------------------\n");

    //输出一些帮助信息
    printf("\n\n\n\t\t\t欢迎来到【矩形包围示例】示例程序~\n\n");
    printf("\n\n\t按键操作说明: \n\n"
           "\t\t键盘按键【ESC】、【Q】、【q】- 退出程序\n\n"
           "\t\t键盘按键任意键 - 重新生成随机点，并寻找最小面积的包围矩形\n");
}

int main() {
    //改变console字体颜色
    system("color 1F");

    //显示帮助文字
    ShowHelpText();

    //初始化变量和随机值
    Mat image(600, 600, CV_8UC3);
    RNG &rng = theRNG();

    //循环，按下ESC,Q,q键程序退出，否则有键按下便一直更新
    while (1) {
        //参数初始化
        int count = rng.uniform(3, 103);//随机生成点的数量
        vector<Point> points;//点值

        //随机生成点坐标
        for (int i = 0; i < count; i++) {

            Point point;
            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

            points.push_back(point);
        }

        //对给定的 2D 点集，寻找最小面积的包围矩形
        RotatedRect box = minAreaRect(Mat(points));
        Point2f vertex[4];
        box.points(vertex);

        // 寻找最小面积的包围圆
        Point2f center;
        float radius = 0;
        minEnclosingCircle(Mat(points), center, radius);

        //绘制出随机颜色的点
        image = Scalar::all(0);
        for (int i = 0; i < count; i++)
            circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED,
                   LINE_AA);


        //绘制出最小面积的包围矩形
        for (int i = 0; i < 4; i++)
            line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);


        //显示窗口
        imshow("矩形包围示例", image);

        //绘制出最小面积的包围圆
        circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2,
               LINE_AA);

        //显示窗口
        imshow("圆形包围示例", image);

        //按下ESC,Q,或者q，程序退出
        char key = (char) waitKey();
        if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
            break;
    }

    return 0;
}