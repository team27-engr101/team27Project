#include "robot.hpp"
#include <iostream>
#include <math.h>
using namespace std;

double startSpeed = 30;	// The initial speed of the robot
@@ -16,30 +17,52 @@ double vRight = startSpeed;
 * Will return negitive value if to the left and positive if to the right
 */
double error(){
	// Opens the current image
    OpenPPMFile("cam.ppm",cameraView);
    SavePPMFile("current.ppm",cameraView);

    double averageX = 0.0;	// The average X position of white pixels
    int numberWhite = 0;	// The total number of white pixels
    double averageXLeft = 0.0;	// The average X position of white pixels for the right side
    double averageXRight = 0.0;	// The average X position of white pixels for the left side
    double averageXMid = 0.0;
    int numberWhiteLeft = 0;	// The total number of white pixels for the right side
    int numberWhiteRight = 0;	// The total number of white pixels for the left side
    int numWhiteMid = 0;

    // Loop through each pixel in the bottom tenth of the frame
    for(int i = 0;i<cameraView.width;i++){
		for (int j = cameraView.height*9.0/10.0; j < cameraView.height; j++){
		for (int j = cameraView.height*8.0/10.0; j < cameraView.height; j++){
			int luminocity = get_pixel(cameraView, j, i, 3);	// Gets the luminocity of the pixel

			int luminocity = get_pixel(cameraView, j, i, 0);	// Gets the luminocity of the pixel
			// If the pixel is white increase white count and add position to averageX
			if(luminocity > 240){
				numberWhite++;
				averageX+=i;
			if(luminocity > 200){
				// If pixel on the left
				if(i < cameraView.width/3){
					numberWhiteLeft++;
					averageXLeft +=i;
				}// If pixel on the left
				else if(i > cameraView.width*2/3){
					numberWhiteRight++;
					averageXRight +=i;
				}// If pixel in the middle
				else{
					numWhiteMid++;
					averageXMid +=i;
				}
			}
		}    
    }
    if(numberWhite != 0){
		averageX = averageX/numberWhite;	//Get the average x position of the white pixels
    // If there are no white pixels
    if(numWhiteMid == 0){
		return NAN;
	}// If there are Pixels to the left
	if(numberWhiteLeft > 0){
		averageXLeft = (averageXLeft + averageXMid)/(numberWhiteLeft + numWhiteMid);
		return averageXLeft - cameraView.width/2.0;
	}// If there are pixels to the right
	else if(numberWhiteRight > 0){
		averageXLeft = (averageXRight + averageXMid)/(numberWhiteRight + numWhiteMid);
		return averageXLeft - cameraView.width/2.0;
	}// Pixels in the center
	else{
		averageXMid = averageXMid/numWhiteMid;
		return averageXMid - cameraView.width/2;
	}
	// Return positive if right of center and return negitive if on the left of center
    return averageX -(cameraView.width/2.0);
}

/* 
@@ -48,18 +71,23 @@ double error(){
 */
void followLine(){
    double margin = error();	// Gets the error margin
    //cout<<"error = "<<margin<<endl;

    // If the error margin is to the right
    if(margin > 0){
		// Turn right
        vLeft = startSpeed + startSpeed/30.0*margin;
        vRight = startSpeed;
    }else{
		// Turn left
        vLeft = startSpeed;
        vRight = startSpeed - startSpeed/30.0*margin;
    }
    if(!isnan(margin)){
		// If the error margin is to the right
		if(margin > 0){
			// Turn right
			vLeft = startSpeed + startSpeed/30.0*margin;
			vRight = startSpeed;
		}else{
			// Turn left
			vLeft = startSpeed;
			vRight = startSpeed - startSpeed/30.0*margin;
		}
	}// No white turn around untill it finds white
	else{
		vLeft = -startSpeed;
		vRight = startSpeed;
	}
}

/* 
@@ -71,15 +99,11 @@ int main(){
        std::cout<<" Error initializing robot"<<std::endl;
    }
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
		takePicture();
		SavePPMFile("cam.ppm",cameraView);
        followLine();	// Calls followLine for new frame

        //cout<<"Left = "<<vLeft<<"Right = "<<vRight<<endl;

        setMotors(vLeft,vRight);   
        //std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000); //10000
		usleep(10000); //10000
  }
}
