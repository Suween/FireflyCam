#include "camera_init.h"


dc1394camera_t** list_camera (dc1394camera_t** ptr_cameras, dc1394_t* dc1394, dc1394camera_list_t *list){

  dc1394error_t err;
  dc1394camera_list_t* plist;

  printf("v1.1.1\n");

  //enumere toute les camera trouver dans une liste list;
  err=dc1394_camera_enumerate(dc1394,&plist);
  *list=*plist;

  if (list->num == 0) {
      printf("pas de camera\n" ); 
      return ptr_cameras;
    }

  ptr_cameras = (dc1394camera_t**)malloc(sizeof(dc1394camera_t*)*list->num);

   if (ptr_cameras == NULL){
      printf("malloc error\n");
      return ptr_cameras;
    }

  for (uint i=0; i<list->num;i++){

    //instancie tout les camera trouver
    ptr_cameras[i] = dc1394_camera_new(dc1394,list->ids[i].guid);

  }
  printf("done for listing\n");
  return ptr_cameras;
}


dc1394error_t start_camera(dc1394camera_t** ptr_camera,dc1394camera_list_t *list){

  dc1394video_modes_t video_modes;
  dc1394error_t err;

  err=dc1394_video_get_supported_modes(ptr_camera[0],&video_modes);

  err=dc1394_video_get_mode(ptr_camera[0],&(video_modes.modes[0]));

  for (uint i=0; i<(list->num);i++){

    err=dc1394_video_set_iso_speed(ptr_camera[i], DC1394_ISO_SPEED_400);
    err=dc1394_video_set_mode(ptr_camera[i], video_modes.modes[0]);
    err=dc1394_video_set_framerate(ptr_camera[i], DC1394_FRAMERATE_60);
    err=dc1394_capture_setup(ptr_camera[i],3, DC1394_CAPTURE_FLAGS_DEFAULT);
    err=dc1394_video_set_transmission(ptr_camera[i],DC1394_ON);
    
  }
   
  if(!err){
    printf("Initialisation Sucess\n");
    printf("_________________________________\n");
  }
  else{
      printf("pas de cam comme ca\n");
      ptr_camera = NULL;
      err=DC1394_CAMERA_NOT_INITIALIZED;
  }

  return err;
}


dc1394video_frame_t * capture(dc1394camera_t* camera, dc1394video_frame_t *frame) {

  dc1394error_t err;

  err=dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &frame);

  if(err){
    frame = NULL;
  }
  return frame;
}


Mat** init_mat_struct(dc1394video_frame_t* frame, Mat** pictures, dc1394camera_list_t *list){

  Mat *temp_picture = new Mat[list->num];

  pictures = (Mat**)malloc(sizeof(Mat*)*list->num);

   if (pictures ==NULL){
      printf("malloc error\n");
      return NULL;
    }

  for (uint i=0; i<(list->num);i++){

    temp_picture[i] = Mat(frame->size[INDEX_ROW],frame->size[INDEX_COL],CV_8UC1,Scalar::all(0));
    pictures[i] = &temp_picture[i];
  }
  printf("mats are done\n");
  return pictures;
}


void dc1394_frame_to_cv_mat(dc1394camera_t* camera, dc1394video_frame_t* frame, Mat* picture){

  picture->dims = IMAGE_DIMS;
  picture->data = frame->image;
  dc1394_capture_enqueue(camera,frame);
}

void multiple_window(int nb_windows){

  char buffer [10];
  
  for (int i=0; i<nb_windows;i++){
    sprintf(buffer,"%d",i);
    cv::namedWindow(buffer, WINDOW_AUTOSIZE );
  }
}

int free_cam (dc1394_t* dc1394, dc1394camera_t** ptr_cameras, dc1394camera_list_t *list){

  dc1394_free(dc1394);
  free(ptr_cameras);
  dc1394_camera_free_list(list);

  if(ptr_cameras==NULL){
    printf("Freeing Cam");
    return 1;
  }
  return 0; 
}
