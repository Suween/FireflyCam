#ifndef __CAMERA_INIT_H__
#define __CAMERA_INIT_H__

#include "dependencies.h"

//Dimension de l'array
#define INDEX_COL 0
#define INDEX_ROW 1
#define IMAGE_DIMS 2	

/* dc1394camera_t** list_camera(dc1394camera_t* cameras, dc1394_t* dc1394);
/  Cette fonction initie une liste de pointeur de toutes les cameras instancies
/  Retourne : Une tableau de pointeur du type cd1394camera_t
*/
dc1394camera_t** list_camera(dc1394camera_t** ptr_cameras, dc1394_t* dc1394, dc1394camera_list_t *list);

/* dc1394camera_t* start_camera(dc1394camera_t** ptr_cameras);
/  Cette fonction initie une channel USB et le protocole de transfere d<une camera
/  Argument: Une tableau de pointeur de structure de camera du type cd1394camera_t
/  Retourne : erreur dans la fonction
*/
dc1394error_t start_camera(dc1394camera_t** ptr_cameras, dc1394camera_list_t *list);

/* dc1394video_frame_t * capture(dc1394camera_t* camera, dc1394video_frame_t *frame);
/  Cette fonction capture la frame donne par une camera
/  Argument: Un pointeur de structure de camera du type cd1394camera_t
/  Retourne : L'image de la camera donnee
*/
dc1394video_frame_t * capture(dc1394camera_t* camera, dc1394video_frame_t *frame);


/* Mat** init_mat_struct(dc1394video_frame_t* frame, Mat** pictures);
/  Pour pouvoir afficher une frame de la camera sur le module OPENCV, on doit faire une
/  conversion sur la frame DC1394. Cette fonction initie les recipeint des frame (structure MAT)
/  Argument: Un pointeur de structure de camera du type cd1394camera_t et une tableau de pointeur de class MAT
/  Retourne : Le tableau de pointeur de classe
*/
Mat** init_mat_struct(dc1394video_frame_t* frame, Mat** pictures,dc1394camera_list_t *list);


/* void dc1394_frame_to_cv_mat(dc1394camera_t* ptr_cameras,dc1394video_frame_t* frame, Mat* picture);
/  convertie la frame DC1394 en OPENVC Mat
/  Argument: Un pointeur de structure de camera du type cd1394camera_t et une tableau de pointeur de class MAT
/			 et une frame dc1394
/  Retourne : (void)
*/
void dc1394_frame_to_cv_mat(dc1394camera_t* camera, dc1394video_frame_t* frame, Mat* picture);

/* void multiple_window(int nb_windows);
/  Fonction qui cree autant de fenetre qu'il y a de camera demander
/  Argument: Nombre de camera
/  Retourne : (void)
*/
void multiple_window(int nb_windows);


/* int free_cam (dc1394_t* dc1394, dc1394camera_t** ptr_cameras,dc1394camera_list_t *list);
/  Delivre tout les pointeurs, memoire buffer etc demander par le programme (a appeler pour finir le prog)
/  Argument: Nombre de camera
/  Retourne : (succes
*/
int free_cam (dc1394_t* dc1394, dc1394camera_t** ptr_cameras,dc1394camera_list_t *list);
#endif