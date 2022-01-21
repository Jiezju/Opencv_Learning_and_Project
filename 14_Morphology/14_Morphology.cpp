
//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序48
//		程序描述：形态学图像处理――开运算、闭运算、形态学梯度、顶帽、黑帽
//		开发测试所用操作系统： Windows 7 64bit
//		开发测试所用IDE版本：Visual Studio 2010
//		开发测试所用OpenCV版本：	3.0 beta
//		2014年11月 Created by @浅墨_毛星云
//		2014年12月 Revised by @浅墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【头文件、命名空间包含部分】----------------------------
//		描述：包含程序所使用的头文件和命名空间
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------【全局变量声明部分】-----------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//原始图和效果图
int g_nElementShape = MORPH_RECT;//元素结构的形状

//变量接收的TrackBar位置参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;



//-----------------------------------【全局函数声明部分】--------------------------------------
//		描述：全局函数声明
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*);//回调函数
static void on_ErodeDilate(int, void*);//回调函数
static void on_TopBlackHat(int, void*);//回调函数
static void ShowHelpText();


//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( )
{
    //改变console字体颜色
    system("color 2F");

    ShowHelpText();

    //载入原图
    g_srcImage = imread("/home/bright/CLionProjects/opencv/14_Morphology/1.jpg");
    if( !g_srcImage.data ) {
        printf("Oh，no，读取srcImage错误~！ \n"); return false;
    }

    //显示原始图
    namedWindow("【原始图】");
    imshow("【原始图】", g_srcImage);

    // 形态学梯度 dilate(src) - eorde(src)
    namedWindow("【效果图】形态学梯度");
    //定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));

    cout << "element = " << endl << " " << element << endl << endl;

    //进行形态学操作
    morphologyEx(g_srcImage, g_dstImage, MORPH_GRADIENT, element);
    //显示效果图
    imshow("【效果图】形态学梯度", g_dstImage);

    //创建三个窗口
    namedWindow("【开运算/闭运算】",1);
    namedWindow("【腐蚀/膨胀】",1);
    namedWindow("【顶帽/黑帽】",1);

    //参数赋值
    g_nOpenCloseNum=9;
    g_nErodeDilateNum=9;
    g_nTopBlackHatNum=2;

    //分别为三个窗口创建滚动条
    createTrackbar("迭代值", "【开运算/闭运算】",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
    createTrackbar("迭代值", "【腐蚀/膨胀】",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
    createTrackbar("迭代值", "【顶帽/黑帽】",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

    //轮询获取按键信息
    while(1)
    {
        int c;

        //执行回调函数
        on_OpenClose(g_nOpenCloseNum, 0);
        on_ErodeDilate(g_nErodeDilateNum, 0);
        on_TopBlackHat(g_nTopBlackHatNum,0);

        //获取按键
        c = waitKey(0);

        //按下键盘按键Q或者ESC，程序退出
        if( (char)c == 'q'||(char)c == 27 )
            break;
        //按下键盘按键1，使用椭圆(Elliptic)结构元素结构元素MORPH_ELLIPSE
        if( (char)c == 49 )//键盘按键1的ASII码为49
            g_nElementShape = MORPH_ELLIPSE;
            //按下键盘按键2，使用矩形(Rectangle)结构元素MORPH_RECT
        else if( (char)c == 50 )//键盘按键2的ASII码为50
            g_nElementShape = MORPH_RECT;
            //按下键盘按键3，使用十字形(Cross-shaped)结构元素MORPH_CROSS
        else if( (char)c == 51 )//键盘按键3的ASII码为51
            g_nElementShape = MORPH_CROSS;
            //按下键盘按键space，在矩形、椭圆、十字形结构元素中循环
        else if( (char)c == ' ' )
            g_nElementShape = (g_nElementShape + 1) % 3;
    }

    return 0;
}


//-----------------------------------【on_OpenClose( )函数】----------------------------------
//		描述：【开运算/闭运算】窗口的回调函数
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*)
{
    //偏移量的定义
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
    int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
    //进行操作
    if( offset < 0 )
        // 开运算 dilate(erode(src)) 消除小物体、细小物体分离、不明显改变面积
        morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
    else
        // 闭运算 erode(dilate(src)) 填充黑色小洞
        morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);

    //显示图像
    imshow("【开运算/闭运算】",g_dstImage);
}


//-----------------------------------【on_ErodeDilate( )函数】----------------------------------
//		描述：【腐蚀/膨胀】窗口的回调函数
//-----------------------------------------------------------------------------------------------
static void on_ErodeDilate(int, void*)
{
    //偏移量的定义
    int offset = g_nErodeDilateNum - g_nMaxIterationNum;	//偏移量
    int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
    //进行操作
    if( offset < 0 )
        erode(g_srcImage, g_dstImage, element);
    else
        dilate(g_srcImage, g_dstImage, element);
    //显示图像
    imshow("【腐蚀/膨胀】",g_dstImage);
}


//-----------------------------------【on_TopBlackHat( )函数】--------------------------------
//		描述：【顶帽运算/黑帽运算】窗口的回调函数
//----------------------------------------------------------------------------------------------
static void on_TopBlackHat(int, void*)
{
    //偏移量的定义
    int offset = g_nTopBlackHatNum - g_nMaxIterationNum;//偏移量
    int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
    //进行操作
    if( offset < 0 )
        // 顶帽 src - open(src)  用于分离 较亮的有规律微小物体
        morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT , element);
    else
        // close(src) - src 用于分离 较暗的有规律微小物体 是边缘更加凸显
        morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
    //显示图像
    imshow("【顶帽/黑帽】",g_dstImage);
}

//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
    //输出欢迎信息和OpenCV版本
    printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
    printf("\n\n  ----------------------------------------------------------------------------\n");

    //输出一些帮助信息
    printf("\n\t请调整滚动条观察图像效果\n\n");
    printf( "\n\t按键操作说明: \n\n"
            "\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
            "\t\t键盘按键【1】- 使用椭圆(Elliptic)结构元素\n"
            "\t\t键盘按键【2】- 使用矩形(Rectangle )结构元素\n"
            "\t\t键盘按键【3】- 使用十字型(Cross-shaped)结构元素\n"
            "\t\t键盘按键【空格SPACE】- 在矩形、椭圆、十字形结构元素中循环\n"	);
}

