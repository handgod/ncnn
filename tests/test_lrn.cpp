// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "testutil.h"

#include "layer/lrn.h"

static int test_lrn(const ncnn::Mat& a, int region_type, int local_size, float alpha, float beta, float bias)
{
    ncnn::ParamDict pd;
    pd.set(0, region_type);
    pd.set(1, local_size);
    pd.set(2, alpha);
    pd.set(3, beta);
    pd.set(4, bias);

    std::vector<ncnn::Mat> weights(0);

    ncnn::Option opt;
    opt.num_threads = 1;
    opt.use_vulkan_compute = true;
    opt.use_int8_inference = false;
    opt.use_fp16_packed = false;
    opt.use_fp16_storage = false;
    opt.use_fp16_arithmetic = false;
    opt.use_int8_storage = false;
    opt.use_int8_arithmetic = false;

    int ret = test_layer<ncnn::LRN>("LRN", pd, weights, opt, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_lrn failed a.dims=%d a=(%d %d %d) region_type=%d local_size=%d alpha=%f beta=%f bias=%f\n", a.dims, a.w, a.h, a.c, region_type, local_size, alpha, beta, bias);
    }

    return ret;
}

static int test_lrn_0()
{
    ncnn::Mat a = RandomMat(11, 7, 4);

    return 0
        || test_lrn(a, 0, 1, 1.f, 0.75f, 1.f)
        || test_lrn(a, 0, 5, 2.f, 0.12f, 1.33f)
        || test_lrn(a, 1, 1, 0.6f, 0.4f, 2.4f)
        || test_lrn(a, 1, 3, 1.f, 0.75f, 0.5f)
        ;
}

static int test_lrn_1()
{
    ncnn::Mat a = RandomMat(12, 10, 9);

    return 0
        || test_lrn(a, 0, 1, 1.f, 0.75f, 1.f)
        || test_lrn(a, 0, 5, 2.f, 0.12f, 1.33f)
        || test_lrn(a, 1, 1, 0.6f, 0.4f, 2.4f)
        || test_lrn(a, 1, 3, 1.f, 0.75f, 0.5f)
        ;
}

int main()
{
    SRAND(7767517);

    return 0
        || test_lrn_0()
        || test_lrn_1()
        ;
}
