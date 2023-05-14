// Generates a cube with side length 1 with centter at (x, y, z)

const float s1 = 0.3333333333334f;
const float s2 = 0.6666666666666f;
const float r = 0.5f;
const float arr[6*4*8] = {
    -r, r, r, s1, 1.0f, 0.0f, 1.0f, 0.0f,
    r, r, r, s2, 1.0f, 0.0f, 1.0f, 0.0f,
    r, r, -r, s2, 0.75f, 0.0f, 1.0f, 0.0f,
    -r, r, -r, s1, 0.75f, 0.0f, 1.0f, 0.0f,
    
    -r, -r, -r, s1, 0.5f, -1.0f, 0.0f, 0.0f,
    -r, -r, r, 0.0f, 0.5f, -1.0f, 0.0f, 0.0f,
    -r, r, r, 0.0f, 0.75f, -1.0f, 0.0f, 0.0f,
    -r, r, -r, s1, 0.75f, -1.0f, 0.0f, 0.0f,
 
    r, -r, -r, s2, 0.5f, 0.0f, 0.0f, -1.0f,
    -r, -r, -r, s1, 0.5f, 0.0f, 0.0f, -1.0f,
    -r, r, -r, s1, 0.75f, 0.0f, 0.0f, -1.0f,
    r, r, -r, s2, 0.75f, 0.0f, 0.0f, -1.0f,
    
    r, -r, r, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f,
    r, -r, -r, s1, 0.5f, 1.0f, 0.0f, 0.0f,
    r, r, -r, s1, 0.75f, 1.0f, 0.0f, 0.0f,
    r, r, r, 1.0f, 0.75f, 1.0f, 0.0f, 0.0f,

    -r, -r, r, s1, 0.25f, 0.0f, 0.0f, 1.0f,
    r, -r, r, s2, 0.25f, 0.0f, 0.0f, 1.0f,
    r, r, r, s2, 0.0f, 0.0f, 0.0f, 1.0f,
    -r, r, r, s1, 0.0f, 0.0f, 0.0f, 1.0f,

    -r, -r, -r, s1, 0.5f, 0.0f, -1.0f, 0.0f,
    r, -r, -r, s2, 0.5f, 0.0f, -1.0f, 0.0f,
    r, -r, r, s2, 0.25f, 0.0f, -1.0f, 0.0f,
    -r, -r, r, s1, 0.25f, 0.0f, -1.0f, 0.0f,
};


void genCube(float* vbo, unsigned int* ebo, unsigned int place, float x, float y, float z) {
    for (int i = 0; i < 6*4*8; i += 8) {
        vbo[i]   = arr[i]   + x;
        vbo[i+1] = arr[i+1] + y;
        vbo[i+2] = arr[i+2] + z;

        vbo[i+3] = arr[i+3];
        vbo[i+4] = arr[i+4];

        vbo[i+5] = arr[i+5];
        vbo[i+6] = arr[i+6];
        vbo[i+7] = arr[i+7];
    }

   
    for (unsigned int i = 0; i < 36; i += 6) {
        ebo[i]   = place + i/6*4;
        ebo[i+1] = place + i/6*4 + 1;
        ebo[i+2] = place + i/6*4 + 2;
        ebo[i+3] = place + i/6*4 + 1;
        ebo[i+4] = place + i/6*4 + 2;
        ebo[i+5] = place + i/6*4 + 3;
    }
}