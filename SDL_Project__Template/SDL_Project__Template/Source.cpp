#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>


std::vector<int> getPointsOfLine(int _x1, int _y1, int _x2, int _y2) {

    std::vector<int> points;  //create a vector to store the poins of a line 
   
    //find the changes in x and y
    //have to be absolute values
    int dx = abs(_x2 - _x1);
    int dy = abs( _y2 - _y1);


    int x, y, p;

    int xIncline = 1, yIncline = 1;


    //if the second point is lower in terms of x the 
    if (_x2 < _x1) {
        xIncline = -1;
    }

    if (_y2 < _y1) {
        yIncline = -1;
    }

    x = _x1;
    y = _y1;
    p = 2 * dy - dx;

    while (x != _x2) {
        
        x += xIncline;
        if (p > 0) {
            y += yIncline;
            p -= 2 * dx;
        }
        p += 2 * dy;
            

        //add points to the vector of pints to be rendered by the library
        points.push_back(x);
        points.push_back(y);
    }

    return points;
}

long double degToRad(float _angle)
{
    long double radian = _angle * M_PI / 180;
    return radian;
}


std::vector<long double> pointTransformations() {
     int x = 5;
     int y = 0;
     int z = 5;

    std::vector<long double> points;

    points.push_back(z);
    points.push_back(y);

    //rotate -30 on the x-axis
    float angle = 330;
    long double cosAngle = cos(degToRad(angle));
    long double sinAngle = sin(degToRad(angle));


   

    long double newZ = (z * cosAngle) - (y * sinAngle);
    long double newY = (y * cosAngle) + (z * sinAngle);

    std::cout << newZ << std::endl;
    std::cout << newY << std::endl;



    points.push_back(newZ);
    points.push_back(newY);
    
    //rotate 175 about y
    angle = 175;
    cosAngle = cos(degToRad(angle));
    sinAngle = sin(degToRad(angle));

    long double newX = (x * cosAngle) + (newZ * sinAngle);
    newZ = (newZ * cosAngle) - (x * sinAngle);
    
    
    std::cout << newX << std::endl;
    std::cout << newZ << std::endl;

    points.push_back(newX);
    points.push_back(newZ);


    //rotate 65 about z
    angle = 65;

    long double x2 = -4.60358;
    long double y2 = 2.5;

    cosAngle = cos(degToRad(angle));
    sinAngle = sin(degToRad(angle));

    long double thridNewX = (newX * cosAngle) - (sinAngle * newY);
    long double thridNewY = (newY * cosAngle) + (newX * sinAngle);

    std::cout << thridNewX << std::endl;
    std::cout << thridNewY << std::endl;

 
    points.push_back(thridNewX);
    points.push_back(thridNewY);
    

    


    

    return points;
    

}

int main(int argc, char* argv[])
{
    int width = 400;
    int height = 300;



    int x1, y1, x2, y2, x3, y3;
    int x, y;
    /*    std::cout << "Enter the co-ordinates of the first point: ";
    std::cin >> x1 >> y1;

    std::cout << "Enter the co-ordinates of the second point: ";
    std::cin >> x2 >> y2;

    std::cout << "Enter the co-ordinates of the third point: ";
    std::cin >> x3 >> y3;*/


    //window render
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    window = SDL_CreateWindow("Mathematics for computer graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderClear(renderer);


    //points for triangle
    x1 = 1;
    y1 = 1;
    x2 = 50;
    y2 = 5;
    x3 = 30;
    y3 = 20;

    //add points to be rendered from triangle calculations to a vector
    std::vector<int> coordinates = getPointsOfLine(x1, y1, x2, y2);
    std::vector<int> line2 = getPointsOfLine(x2, y2, x3, y3);
    std::vector<int> line3 = getPointsOfLine( x1, y1,x3, y3 );

    coordinates.insert(coordinates.end(), line2.begin(), line2.end());
    coordinates.insert(coordinates.end(), line3.begin(), line3.end());

    

    for (int i = 0; i < coordinates.size(); i += 2) //render all of the points from the lines
    {
        x = coordinates[i];
        y = coordinates[i + 1];
       // std::cout << x << " " << y << std::endl;
        SDL_RenderDrawPoint(renderer, x, y);
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);



    //rotations

    std::vector<long double> rotationPoints;

    rotationPoints = pointTransformations();

    //window render
    SDL_Window* window2 = NULL;
    SDL_Renderer* renderer2 = NULL;
    window2 = SDL_CreateWindow("Mathematics for computer graphics - Rotations", 400, 200, width, height, SDL_WINDOW_SHOWN);
    renderer2 = SDL_CreateRenderer(window2, -1, 0);

    SDL_SetRenderDrawColor(renderer2, 255, 255, 255, 255);

    std::vector<int> RotatedCoordinates;

    

    for (int i = 0; i < rotationPoints.size(); i += 2) //render all of the points of rotation
    {
        //values have been manipulated so they are visible on screen but original values are printed to console
        x = rotationPoints[i] * 10;
        y = rotationPoints[i + 1] * 10;
        // std::cout << x << " " << y << std::endl;
        //convert to float to render
              
        
        SDL_RenderDrawPoint(renderer2, float(x) + 50, float(y)+ 50);
        SDL_RenderPresent(renderer2);
        SDL_Delay(3000);  //wait three seconds to show it off
    }
    


    //draw a triangle between the 3 points

    std::vector<int> RotatedCoordinates1 = getPointsOfLine((float(rotationPoints[0]) * 10) + 50 , (float(rotationPoints[1]) * 10) + 50, (float(rotationPoints[2]) * 10) + 50, (float(rotationPoints[3]) * 10) + 50);
    std::vector<int> RotatedCoordinates2 = getPointsOfLine((float(rotationPoints[2]) * 10) + 50, (float(rotationPoints[3]) * 10) + 50, (float(rotationPoints[4]) * 10) + 50, (float(rotationPoints[5]) * 10) + 50);
    std::vector<int> RotatedCoordinates3 = getPointsOfLine((float(rotationPoints[4]) * 10) + 50, (float(rotationPoints[5]) * 10) + 50, (float(rotationPoints[0]) * 10) + 50, (float(rotationPoints[1]) * 10) + 50);
    
    RotatedCoordinates1.insert(RotatedCoordinates1.end(), RotatedCoordinates2.begin(), RotatedCoordinates2.end());
    RotatedCoordinates1.insert(RotatedCoordinates1.end(), RotatedCoordinates3.begin(), RotatedCoordinates3.end());

    for (int k = 0; k < RotatedCoordinates1.size(); k += 2) //render all of the points from the line
    {
        x = RotatedCoordinates1[k];
        y = RotatedCoordinates1[k + 1];
        // std::cout << x << " " << y << std::endl;
        SDL_RenderDrawPoint(renderer2, x, y);
        SDL_RenderPresent(renderer2);
    }

    SDL_Delay(8000);

    SDL_DestroyRenderer(renderer2);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}