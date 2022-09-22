#include <metal_stdlib>

using namespace metal;

kernel void add_two_int_vectors(device const int* inA,
                       device const int* inB,
                       device int* result,
                       uint index [[thread_position_in_grid]])
{
    result[index] = inA[index] + inB[index];
            //inB[index] * inA[index] + inB[index] * inB[index] / 2 + 334 / inB[index] * inA[index] + inB[index] * inB[index] / 2 + 334;
}

kernel void multiply_two_int_matrices(const device int* inA [[buffer(0)]],
                                      const device int* inB [[buffer(1)]],
                                      constant int& m [[buffer(2)]], //4   rowa
                                      constant int& n [[buffer(3)]], //3   rowb = cola
                                      constant int& b [[buffer(4)]], //5   colb
                                      device int* result [[buffer(5)]],
                                      uint2 gid [[thread_position_in_grid]])
{
    int sum = 0;
    for (int k = 0; k < n; k += 1)
    {
         sum += inA[gid.y * n + k] * inB[k * b + gid.x];
         // (m-1) * n + (n-1)
    }

    //            function.setGridSize(MTL::Size::Make(columns, rows, 1));

    result[gid.y * b + gid.x] = sum;
    //result[gid.y * m + gid.x] = 17;
}