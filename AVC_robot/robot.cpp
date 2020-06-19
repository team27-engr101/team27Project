#include "robot.hpp"
#include <iostream>
#include <math.h>
using namespace std;

double startSpeed = 30;	// The initial speed of the robot
// Speed of the left and right wheels
double vLeft = startSpeed;
double vRight = startSpeed;

/* 
 * Function that calculates the margin of error
 * 
 * This will analyse a portion of pixels infront of the robot
 * and calculate where the majority of the white pixels are located in the frame
 * 
 * Will return negitive value if to the left and positive if to the right
 */
double error(){
    double averageXLeft = 0.0;	// The average X position of white pixels for the right side
    double averageXRight = 0.0;	// The average X position of white pixels for the left side
    double averageXMid = 0.0;
    int numberWhiteLeft = 0;	// The total number of white pixels for the right side
    int numberWhiteRight = 0;	// The total number of white pixels for the left side
    int numWhiteMid = 0;
    
    // Loop through each pixel in the bottom tenth of the frame
    for(int i = 0;i<cameraView.width;i++){
		for (int j = cameraView.height*8.0/10.0; j < cameraView.height; j++){
			int luminocity = get_pixel(cameraView, j, i, 3);	// Gets the luminocity of the pixel
			
			// If the pixel is white increase white count and add position to averageX
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
}

/* 
 * Function that will make the robot turn left or right
 * according to the error margin inorder to follow the line
 */
void followLine(){
    double margin = error();	// Gets the error margin
    
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
 * Main function of program
 * allows the robot to constantly follow the line
 */
int main(){
    if (initClientRobot() !=0){
        std::cout<<" Error initializing robot"<<std::endl;
    }
    takePicture();
    while(1){
		takePicture();
        followLine();	// Calls followLine for new frame

        setMotors(vLeft,vRight);   
		usleep(10000); //10000
  }
}
