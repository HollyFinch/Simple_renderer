#include <stdio.h>

int main() {

    int image_W = 500;
    int image_H = 500;

    FILE *file = fopen("render_image.ppm", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "P3\n%d %d\n255\n", image_W, image_H);

    for (int i = 0; i < image_W; i++) {
        for (int j = 0; j < image_H; j++) {
            fprintf(file, "255 0 0\n"); 
        }
    }

    fclose(file);
    return 0;
}