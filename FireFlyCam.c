
#include "FireFlyCam.h"

/*
/TO DO :
/
*/

int main(){

  dc1394error_t err = DC1394_SUCCESS;

  dc1394camera_t** ptr_cameras;
  dc1394_t* dc1394;
  dc1394camera_list_t list;
  dc1394video_frame_t *frame=NULL;

  Mat** pictures;

  char buffer[33];

  //instancie un context dans lequel les camera peuvent etre retrouver
  dc1394=dc1394_new();
  
  ptr_cameras=list_camera(ptr_cameras, dc1394, &list);
  printf("%u\n", list.num);

  err=start_camera(ptr_cameras,&list);
  
  //Capture une premiere frame pour pouvoir initialiser la structure mat de OPENCV
  frame=capture(ptr_cameras[0],frame);
  printf("ssl\n");
  //Initialise la structure mat
  pictures=init_mat_struct(frame,pictures,&list); //for opencv

  // Create  windows for display.
  multiple_window(list.num);
  dc1394_feature_set_mode(ptr_cameras[0],DC1394_FEATURE_BRIGHTNESS,DC1394_FEATURE_MODE_MANUAL); 

  dc1394_feature_change(ptr_cameras[0],DC1394_FEATURE_BRIGHTNESS,0);//,&list);

  while(!err){
      for (uint i=0; i<list.num;i++){

        frame=capture(ptr_cameras[i],frame);

        if(frame==NULL){
          printf("error\n");
          err = DC1394_FAILURE;
        }

        dc1394_frame_to_cv_mat(ptr_cameras[i],frame,pictures[i]);

        sprintf(buffer,"%d",i);
        imshow(buffer, *pictures[i] ); 

        if (waitKey(1) >= 0){

          printf("Done\n");
          destroyAllWindows();
          
           for (uint i=0; i<list.num;i++){
            dc1394_capture_stop(ptr_cameras[i]);
          }
        err=DC1394_FAILURE;
        }  
      }
      //printf("%d\n",err );
    }
  printf("all done\n");
  free_cam(dc1394,ptr_cameras,&list);
  return 0;
}

