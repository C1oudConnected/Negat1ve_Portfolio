#include <iostream>
#include "CustomMath/CustomMath.h"

const int width = 41;
const int height = 41;

//FLOAT z_dim[height][width] = {};
bool map[height][width] = {};

int main()
{
    // Basis to translate coordinates to.
    Vector basis2D[2];

    // Points of a cube;
    Vector cubeQuadsCoordinates[9] = {
        Vector(-10,-10, -10, 0),
        Vector(-10, 10, -10, 0),
        Vector(10,-10, -10, 0),
        Vector(10, 10, -10, 0),
        Vector(-10,-10, 10, 0),
        Vector(-10, 10, 10, 0),
        Vector(10,-10, 10, 0),
        Vector(10, 10, 10, 0),
    };


    Vector eye(25, 50, 60, 0);
    Vector at(0, 0, 0, 0);
    Vector eyeDir = (at - eye).nrmlzd();

	 basis2D[1] = eyeDir.cross(Vector(0, 0, 1, 0));
	 basis2D[0] = basis2D[1].cross(eyeDir);

    // Main transforming episode.
    for (int i = 0; i < 8; i++) {
        Vector v = (cubeQuadsCoordinates[i] - (cubeQuadsCoordinates[i] - eye).proj(eyeDir));

        float based_coords[2]{  v.proj(basis2D[0]).dot(basis2D[0]),
                                v.proj(basis2D[1]).dot(basis2D[1])};

        int a[2]{ int((height / 2) - based_coords[0]), int((width / 2) - based_coords[1]) };

        if (a[0] < height && a[0] > 0 && a[1] < width && a[1] > 0)
            map[a[0]][a[1]] = true;
    }

    // Console output.
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << (map[i][j] ? '#' : '_') << " ";
        }
        std::cout << std::endl;
    }


}
