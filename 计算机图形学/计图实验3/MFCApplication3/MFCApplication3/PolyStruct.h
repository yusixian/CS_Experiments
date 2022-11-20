#pragma once
const int POINTNUM = 6;      //多边形点数.  
/******定义结构体用于活性边表AET和新边表NET **********/
typedef struct XET {
    float x;
    float dx, ymax;
    struct XET* next;
} AET, NET;
/******定义点结构体point******************************************************/
struct point {
    float x;
    float y;
}; 
//mypoint[POINTNUM]={100,100,200,100,200,200,100,200};//正方形  
// 250,50,550,150,550,400,250,250,100,350,100,100  
//{500,100,650,150,650,300,500,250,350,350,350,100};//多边形顶点  

