#include "robot.hpp"
#include <iostream>
using namespace std;
double startSpeed = 20;
double vLeft = startSpeed;
double vRight = startSpeed;
double error(){
    OpenPPMFile("cam.ppm",cameraView);
    SavePPMFile("current.ppm",cameraView);
    double average = 0.0;
    int number = 0;
    for(int i = 0;i<cameraView.width;i++){
        int red = get_pixel(cameraView,cameraView.height*9.0/10.0,i,0);
        int green = get_pixel(cameraView,cameraView.height*9.0/10.0,i,1);
        int blue = get_pixel(cameraView,cameraView.height*9.0/10.0,i,2);
        if(red >235 and green >235 and blue > 235){
            cout<<"white detected"<<endl;
            number++;
            average+=i;
        }
        
    }
    if(number != 0){
		average = average*1.0/number;
		average = average-(cameraView.width/2.0);}
    return(average);
} 
void followLine(){
    double margin = error();
    cout<<"error = "<<margin<<endl;
    if(margin > 0){
        vLeft = startSpeed + startSpeed/10.0*margin;
        vRight = startSpeed;
    }else{
        vLeft = startSpeed;
        vRight = startSpeed - startSpeed/10.0*margin;
    }
}

int main(){
    if (initClientRobot() !=0){
        std::cout<<" Error initializing robot"<<std::endl;
    }
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
		takePicture();
		SavePPMFile("cam.ppm",cameraView);
        followLine();
        
        cout<<"Left = "<<vLeft<<"Right = "<<vRight<<endl;
        setMotors(vLeft,vRight);   
        std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000); //10000
  } //while//

}

