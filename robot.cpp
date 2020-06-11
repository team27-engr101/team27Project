#include "robot.hpp"
#include <iostream>
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
	// Opens the current image
    OpenPPMFile("cam.ppm",cameraView);
    SavePPMFile("current.ppm",cameraView);
    
    double averageX = 0.0;	// The average X position of white pixels
    int numberWhite = 0;	// The total number of white pixels
    
    // Loop through each pixel in the bottom tenth of the frame
    for(int i = 0;i<cameraView.width;i++){
		for (int j = cameraView.height*9.0/10.0; j < cameraView.height; j++){
			
			int luminocity = get_pixel(cameraView, j, i, 0);	// Gets the luminocity of the pixel
			// If the pixel is white increase white count and add position to averageX
			if(luminocity > 240){
				numberWhite++;
				averageX+=i;
			}
		}    
    }
    if(numberWhite != 0){
		averageX = averageX/numberWhite;	//Get the average x position of the white pixels
	}
	// Return positive if right of center and return negitive if on the left of center
    return averageX -(cameraView.width/2.0);
}

/* 
 * Function that will make the robot turn left or right
 * according to the error margin inorder to follow the line
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
    SavePPMFile("i0.ppm",cameraView);
    while(1){
		takePicture();
		SavePPMFile("cam.ppm",cameraView);
        followLine();	// Calls followLine for new frame
        
        //cout<<"Left = "<<vLeft<<"Right = "<<vRight<<endl;
        setMotors(vLeft,vRight);   
        //std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000); //10000
  }
}
