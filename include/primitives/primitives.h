//
// Created by Campbell Cole on 12/28/21.
//

#ifndef PSLIGHTDASH_PRIMITIVE_H
#define PSLIGHTDASH_PRIMITIVE_H

namespace dash {

  struct GLShape {
    unsigned int *indices = {};
    float *vertices = {};
    unsigned int vertexCount = 0, indexCount = 0;
  };

  namespace primitives {

    static GLShape TEXTURED_CUBE(float size, float &sideLength) {
      float v = 0.5f * size;
      sideLength = v * 2;
      return {
        new unsigned int[] {
          0,1,2,
          2,3,0,
          4,5,6,
          6,7,4,
          8,9,10,
          10,4,8,
          11,2,12,
          12,13,11,
          10,14,5,
          5,4,10,
          3,2,11,
          11,15,3
        },new float[] {
          -v, -v, -v,  0.0f, 0.0f,//0
           v, -v, -v,  1.0f, 0.0f,//1
           v,  v, -v,  1.0f, 1.0f,//2
          -v,  v, -v,  0.0f, 1.0f,//3
          -v, -v,  v,  0.0f, 0.0f,//4
           v, -v,  v,  1.0f, 0.0f,//5
           v,  v,  v,  1.0f, 1.0f,//6
          -v,  v,  v,  0.0f, 1.0f,//7
          -v,  v,  v,  1.0f, 0.0f,//8
          -v,  v, -v,  1.0f, 1.0f,//9
          -v, -v, -v,  0.0f, 1.0f,//10
           v,  v,  v,  1.0f, 0.0f,//11
           v, -v, -v,  0.0f, 1.0f,//12
           v, -v,  v,  0.0f, 0.0f,//13
           v, -v, -v,  1.0f, 1.0f,//14
          -v,  v,  v,  0.0f, 0.0f,//15
        }, 80, 36
      };
    }

    /*static const GLShape TEXTURED_CUBE = {
      new unsigned int[] {
        0,1,2,
        2,3,0,
        4,5,6,
        6,7,4,
        8,9,10,
        10,4,8,
        11,2,12,
        12,13,11,
        10,14,5,
        5,4,10,
        3,2,11,
        11,15,3
        },new float[] {
        -0.125f, -0.125f, -0.125f,  0.0f, 0.0f, //0
         0.125f, -0.125f, -0.125f,  1.0f, 0.0f, //1
         0.125f,  0.125f, -0.125f,  1.0f, 1.0f, //2
        -0.125f,  0.125f, -0.125f,  0.0f, 1.0f, //3
        -0.125f, -0.125f,  0.125f,  0.0f, 0.0f, //4
         0.125f, -0.125f,  0.125f,  1.0f, 0.0f,//5
         0.125f,  0.125f,  0.125f,  1.0f, 1.0f,//6
        -0.125f,  0.125f,  0.125f,  0.0f, 1.0f,//7
        -0.125f,  0.125f,  0.125f,  1.0f, 0.0f,//8
        -0.125f,  0.125f, -0.125f,  1.0f, 1.0f,//9
        -0.125f, -0.125f, -0.125f,  0.0f, 1.0f,//10
         0.125f,  0.125f,  0.125f,  1.0f, 0.0f,//11
         0.125f, -0.125f, -0.125f,  0.0f, 1.0f,//12
         0.125f, -0.125f,  0.125f,  0.0f, 0.0f,//13
         0.125f, -0.125f, -0.125f,  1.0f, 1.0f,//14
        -0.125f,  0.125f,  0.125f,  0.0f, 0.0f,//15
      }, 80, 36
    };*/

  }

}

#endif //PSLIGHTDASH_PRIMITIVE_H
