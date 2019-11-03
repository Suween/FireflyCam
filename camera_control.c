#include "camera_control.h"


dc1394error_t dc1394_feature_change_validation(dc1394camera_t* camera, dc1394feature_t feature, uint32_t value){

	static dc1394error_t err;
	uint32_t actual_value;

	dc1394_feature_get_value(camera, feature, &actual_value);
	printf("%lu\n", actual_value );

	if (value == actual_value){
		printf("Already at that value\n");
		return err=DC1394_FAILURE;
	}
	else{
		return err=DC1394_SUCCESS;
	}

}

dc1394error_t dc1394_feature_change_all(dc1394camera_t** ptr_cameras, dc1394feature_t feature, uint32_t value, dc1394camera_list_t *list){

	static dc1394error_t err;
	
	for (uint i; i<list->num;i++){

		err=dc1394_feature_change(ptr_cameras[i],feature,value);
	}
	return err;
	
}

dc1394error_t dc1394_feature_change(dc1394camera_t* camera, dc1394feature_t feature,  uint32_t value){

	static dc1394error_t err;
	static dc1394bool_t validation;
	static uint32_t min, max;

	if (!dc1394_feature_is_present(camera, feature, &validation)){

		err=dc1394_feature_get_boundaries(camera, feature, &min, &max);
		printf("%lu\t%lu\n",min,max );
	}
	else{
		return err=DC1394_INVALID_FEATURE_MODE;
	}

	if(!dc1394_feature_change_validation(camera, feature, value)){
		printf("%lu\n",value );
		if(value >= min && value <= max){

			err=dc1394_feature_set_value(camera,feature,480);
		}
		else{
			printf("valeur n'est pas dans les bornes\n");
			return err = DC1394_REQ_VALUE_OUTSIDE_RANGE;
		}
	}

	return err;
}