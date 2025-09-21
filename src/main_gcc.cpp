#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")  // 优化选项
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")           // 启用 AVX
#pragma GCC target("avx")                                                   // 启用 AVX
#include <bits/stdc++.h>
#include <x86intrin.h>  // AVX/SSE 指令集
#include <iostream>

/*
        [CTAGDRC/Source/util/include/SIMDMath.h at master · p-hlp/CTAGDRC](https://github.com/p-hlp/CTAGDRC/blob/master/Source/util/include/SIMDMath.h)
        [SSE 与 AVE 向量化编程](https://cuterwrite.top/p/simd/)
        [x64 (amd64) intrinsics list | Microsoft Learn](https://learn.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170)
        [Intel® Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
        [机器学习中的高性能计算（二）SSE优化](https://www.zhihu.com/tardis/zm/art/409973153?source_id=1003)
        [C++优化-SIMD指令集_samylee的博客-CSDN博客](https://blog.csdn.net/samylee/category_8805473.html)
        [SSE指令-CSDN博客](https://blog.csdn.net/fyire/article/details/120792319)
        [JUCE: SystemStats Class Reference](https://docs.juce.com/master/classSystemStats.html)
*/

float sum(const float* src, int num)
{

        __m128 mmSum = _mm_setzero_ps();

        int i = 0;
        int rounddown = num - (num % 16);

        for (; i < rounddown; i += 16)
        {
            __m128 v0 = _mm_loadu_ps(src + i + 0);
            __m128 v1 = _mm_loadu_ps(src + i + 4);
            __m128 s01 = _mm_add_ps(v0, v1);

            __m128 v2 = _mm_loadu_ps(src + i + 8);
            __m128 v3 = _mm_loadu_ps(src + i + 12);
            __m128 s23 = _mm_add_ps(v2, v3);

            mmSum = _mm_add_ps(mmSum, s01);
            mmSum = _mm_add_ps(mmSum, s23);
        }

        for (; i < num; i++)
            mmSum = _mm_add_ss(mmSum, _mm_load_ss(src + i));

        mmSum = _mm_hadd_ps(mmSum, mmSum);
        mmSum = _mm_hadd_ps(mmSum, mmSum);
        return _mm_cvtss_f32(mmSum);
    

    // // Fallback
    // float s = 0;
    // const float* e = src + num;

    // while (src != e)
    // {
    //     s += *src;
    //     src++;
    // }
    // return s;
}



int main() {
    float arr[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    std::cout << "Hello World!" << sum(arr, 10);
    return 0;
}
