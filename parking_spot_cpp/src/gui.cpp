
#include <parking_spot_cpp/lib/gui.h>
#include <parking_spot_cpp/lib/globals.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
// #include <vector>
#include <parking_spot_cpp/lib/logger.h>
#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/layout.h>

// using std::vector;

void gui::imgshowLayouts(const vector<layout>& layouts, const vector<point>& terrain) {
    int terrain_min_x = INT_MAX;
    int terrain_min_y = INT_MAX;
    int terrain_max_x = INT_MIN;
    int terrain_max_y = INT_MIN;

    for(point p : terrain) {
        if(p.x > terrain_max_x) terrain_max_x = p.x;
        if(p.y > terrain_max_y) terrain_max_y = p.y;
        if(p.x < terrain_min_x) terrain_min_x = p.x;
        if(p.y < terrain_min_y) terrain_min_y = p.y;
    }

    // TODO test if diff really works when the diff is bigger the INT_MAX
    const uint diff_x = terrain_max_x - terrain_min_x;
    const uint diff_y = terrain_max_y - terrain_min_y;
    const float scale_x = float(VIEW_WIDTH) / float(diff_x);
    const float scale_y = float(VIEW_HEIGHT) / float(diff_y);
    float scale = std::min(scale_x, scale_y);
    if(scale > 1) scale = 1;
    // std::cout << "diff_x: " << diff_x << std::endl; 
    // std::cout << "diff_y: " << diff_y << std::endl; 
    // std::cout << "scale: " << scale << std::endl; 

    const int offset_x = ((WINDOWS_WIDTH - (diff_x * scale)) / 2) - (terrain_min_x * scale);
    const int offset_y = ((WINDOWS_HEIGHT - (diff_y * scale)) / 2) - (terrain_min_y * scale);
    // std::cout << "offset_x: " << offset_x << std::endl; 
    // std::cout << "offset_y: " << offset_y << std::endl; 
    // std::cout << "terrain: " << std::endl; 
    // logger::print(terrain); 
    // std::cout << std::endl; 

    
    vector<cv::Point> terrainPoints;
    for(point p : terrain) {
        int x = (p.x * scale) + offset_x;
        int y = (p.y * scale) + offset_y;
        // std::cout << "x: " << x << ", y: " << y << std::endl; 
        // int x = p.x;
        // int y = p.y;
        cv::Point cvPoint(x, y);
        terrainPoints.push_back(cvPoint);
    }

    cv::InputArray terrainCvPoints = cv::InputArray(terrainPoints);

    cv::namedWindow("Layout");
    cv::moveWindow("Layout", 1000,20);

    cv::Scalar terrain_color(125, 125, 0);
    cv::Mat image(WINDOWS_HEIGHT, WINDOWS_WIDTH, CV_8UC3, cv::Scalar(0, 0, 0));

    int i = 0;
    const int n = layouts.size();
    while (i < n) {
        std::cout << std::endl << "---------------------------" << std::endl; 
        image=cv::Scalar(0, 0, 0);

        cv::fillConvexPoly(image, terrainCvPoints, terrain_color);

        for (rect r : layouts[i].spots) {

          std::cout << "r.tl.x: " << r.tl.x << std::endl; 
          std::cout << "r.tl.y: " << r.tl.y << std::endl; 
          std::cout << "r.tr.x: " << r.tr.x << std::endl; 
          std::cout << "r.tr.y: " << r.tr.y << std::endl; 
          std::cout << "r.br.x: " << r.br.x << std::endl; 
          std::cout << "r.br.y: " << r.br.y << std::endl; 
          std::cout << "r.bl.x: " << r.bl.x << std::endl; 
          std::cout << "r.bl.y: " << r.bl.y << std::endl; 
          std::cout << std::endl << std::endl; 

            r.tl.x = (r.tl.x * scale) + offset_x;
            r.tl.y = (r.tl.y * scale) + offset_y;
            r.tr.x = (r.tr.x * scale) + offset_x;
            r.tr.y = (r.tr.y * scale) + offset_y;
            r.bl.x = (r.bl.x * scale) + offset_x;
            r.bl.y = (r.bl.y * scale) + offset_y;
            r.br.x = (r.br.x * scale) + offset_x;
            r.br.y = (r.br.y * scale) + offset_y;

            // std::cout << "r.tl.y: " << r.tl.y << std::endl; 
            // std::cout << "r.tl.x: " << r.tl.x << std::endl; 
            // std::cout << "r.tr.y: " << r.tr.y << std::endl; 
            // std::cout << "r.tr.x: " << r.tr.x << std::endl; 
            // std::cout << "r.br.y: " << r.br.y << std::endl; 
            // std::cout << "r.br.x: " << r.br.x << std::endl; 
            // std::cout << "r.bl.y: " << r.bl.y << std::endl; 
            // std::cout << "r.bl.x: " << r.bl.x << std::endl; 
            // std::cout << std::endl << std::endl; 
            

            vector<cv::Point> rectPoints1 = {{cv::Point(r.tl.x, r.tl.y), cv::Point(r.tr.x, r.tr.y), cv::Point(r.br.x, r.br.y), cv::Point(r.bl.x, r.bl.y)}};
            cv::InputArray rectPoints = cv::InputArray(rectPoints1);
            cv::Scalar color(0, 255, 0);  
            cv::Scalar color2(0, 125, 125);  
            cv::fillConvexPoly(image, rectPoints, color);
            cv::polylines(image, rectPoints, true, color2, 5);
        }

        cv::imshow("Layout", image);
        int waitKey = cv::waitKey(0);
        // std::cout << "waitkey: " << waitKey << std::endl;
        if (waitKey == 27)
            break;

        if(waitKey == 97 || waitKey == 81) {
          i-=2;
          if(i <= -2) i = -1;
        }

        i++;
    }
}