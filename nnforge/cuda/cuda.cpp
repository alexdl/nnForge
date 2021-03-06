/*
 *  Copyright 2011-2013 Maxim Milakov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "cuda.h"

#include "../nnforge.h"

#include "layer_testing_schema_factory.h"
#include "local_contrast_subtractive_layer_testing_schema.h"
#include "absolute_layer_testing_schema.h"
#include "hyperbolic_tangent_layer_testing_schema.h"
#include "average_subsampling_layer_testing_schema.h"
#include "convolution_layer_testing_schema.h"
#include "max_subsampling_layer_testing_schema.h"
#include "rectified_linear_layer_testing_schema.h"
#include "soft_rectified_linear_layer_testing_schema.h"
#include "softmax_layer_testing_schema.h"
#include "rgb_to_yuv_convert_layer_testing_schema.h"
#include "maxout_layer_testing_schema.h"

#include "layer_hessian_schema_factory.h"
#include "local_contrast_subtractive_layer_hessian_schema.h"
#include "absolute_layer_hessian_schema.h"
#include "hyperbolic_tangent_layer_hessian_schema.h"
#include "average_subsampling_layer_hessian_schema.h"
#include "convolution_layer_hessian_schema.h"
#include "max_subsampling_layer_hessian_schema.h"
#include "rectified_linear_layer_hessian_schema.h"
#include "soft_rectified_linear_layer_hessian_schema.h"
#include "softmax_layer_hessian_schema.h"
#include "maxout_layer_hessian_schema.h"

#include "layer_updater_schema_factory.h"
#include "local_contrast_subtractive_layer_updater_schema.h"
#include "absolute_layer_updater_schema.h"
#include "hyperbolic_tangent_layer_updater_schema.h"
#include "average_subsampling_layer_updater_schema.h"
#include "convolution_layer_updater_schema.h"
#include "max_subsampling_layer_updater_schema.h"
#include "rectified_linear_layer_updater_schema.h"
#include "soft_rectified_linear_layer_updater_schema.h"
#include "softmax_layer_updater_schema.h"
#include "rgb_to_yuv_convert_layer_updater_schema.h"
#include "maxout_layer_updater_schema.h"

#include "weight_vector_bound_cuda_factory.h"
#include "convolution_weight_vector_bound_cuda.h"

namespace nnforge
{
	namespace cuda
	{
		void cuda::init()
		{
			nnforge::init();

			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new local_contrast_subtractive_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new absolute_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new hyperbolic_tangent_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new average_subsampling_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new convolution_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new max_subsampling_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new rectified_linear_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new soft_rectified_linear_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new softmax_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new rgb_to_yuv_convert_layer_testing_schema()));
			single_layer_testing_schema_factory::get_mutable_instance().register_layer_testing_schema(layer_testing_schema_smart_ptr(new maxout_layer_testing_schema()));

			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new local_contrast_subtractive_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new absolute_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new hyperbolic_tangent_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new average_subsampling_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new convolution_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new max_subsampling_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new rectified_linear_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new soft_rectified_linear_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new softmax_layer_hessian_schema()));
			single_layer_hessian_schema_factory::get_mutable_instance().register_layer_hessian_schema(layer_hessian_schema_smart_ptr(new maxout_layer_hessian_schema()));

			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new local_contrast_subtractive_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new absolute_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new hyperbolic_tangent_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new average_subsampling_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new convolution_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new max_subsampling_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new rectified_linear_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new soft_rectified_linear_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new softmax_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new rgb_to_yuv_convert_layer_updater_schema()));
			single_layer_updater_schema_factory::get_mutable_instance().register_layer_updater_schema(layer_updater_schema_smart_ptr(new maxout_layer_updater_schema()));

			single_weight_vector_bound_factory::get_mutable_instance().register_weight_vector_bound(weight_vector_bound_cuda_smart_ptr(new convolution_weight_vector_bound_cuda()));
		}
	}
}
