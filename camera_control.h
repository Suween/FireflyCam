#ifndef __CAMERA_CONTROL_H__
#define __CAMERA_CONTROL_H__

#include "dependencies.h"

dc1394error_t dc1394_feature_change_validation(dc1394camera_t* camera, dc1394feature_t feature, uint32_t value);

dc1394error_t dc1394_feature_change_all(dc1394camera_t** ptr_cameras, dc1394feature_t feature, uint32_t value, dc1394camera_list_t *list);

dc1394error_t dc1394_feature_change(dc1394camera_t* camera, dc1394feature_t feature,  uint32_t value);


#endif