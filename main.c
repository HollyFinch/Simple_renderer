#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <float.h>

typedef struct {
    float x, y, z;
} Vec3;

Vec3 vec3(float x, float y, float z) {
    Vec3 v = {x, y, z};
    return v;
}

Vec3 add(Vec3 a, Vec3 b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 sub(Vec3 a, Vec3 b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 mul(Vec3 a, float b) {
    return vec3(a.x * b, a.y * b, a.z * b);
}

float dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// bounce back to Unit Vector
Vec3 normalise(Vec3 v) {
    float magnitude = sqrt(dot(v,v));
    return vec3(v.x/magnitude, v.y / magnitude, v.z / magnitude);
}

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

// bounce up by distance t
Vec3 pointAtParameter( Ray r, float t) {
    return add(r.origin, mul(r.direction, t));
}

typedef struct {
    Vec3 center;
    float radius;
} Spherro;

float intersectRay(Ray r, Spherro spherro) {
    Vec3 oc = sub(r.origin, spherro.center);
    // you can just use 1 here 
    // HOWEVER, in case ray direction is for some reason not a unit vector ...
    float a = dot(r.direction,r.direction);
    float b = 2.0f * dot(oc, r.direction);
    float c = dot(oc, oc) - spherro.radius * spherro.radius;
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f) {
        return -1.0f;
    } 
    else {
        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
        if (t1 > 0.001f && t1 < t2) return t1;
        if (t2 > 0.001f) return t2;
        return - 1.0f;
    }   
}

int main() {

    int image_W = 1000;
    int image_H = 1000;

    //float aspect = (float)image_W/ (float)image_H;

    uint64_t holly = 0;

    FILE *file = fopen("render_image.ppm", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

   fprintf(file, "P3\n%d %d\n255\n", image_W, image_H);


    Spherro spherro = {vec3(0.0f, 0.0f, -1.0f), 0.5f};

    // camera

    Vec3 lower_left = vec3(-2.0f, -2.0f, -1.0f);
    Vec3 horizontal = vec3(4.0f, 0.0f, 0.0f);
    Vec3 vertical = vec3(0.0f, 4.0f, 0.0f);
    Vec3 origin = vec3(0.0f, 0.0f, 0.0f);

    for (int j = 0; j < image_H; j++) {
        for (int i = 0; i < image_W; i++) {
            
            float u = (float)i / (float)(image_W);
            float v = (float)j / (float)(image_H);

            Ray shame_about_Ray;
            shame_about_Ray.origin = origin;
            shame_about_Ray.direction = sub(add(lower_left, add(mul(horizontal,u), mul(vertical,v))), origin); 
            shame_about_Ray.direction = normalise(shame_about_Ray.direction);

            float t_boop = intersectRay(shame_about_Ray, spherro);
            if (t_boop > 0.0f) {
                Vec3 boop_location = pointAtParameter(shame_about_Ray, t_boop);
                Vec3 normal = sub(boop_location, spherro.center);
                normal = normalise(normal);
                float red = 0.5f * (normal.x + 1.0f) ;
                float green = 0.5f * (normal.y + 1.0f);
                float blue = 0.5f * (normal.z + 1.0f);

                int ir = (int)(255.99f * red);
                int ig = (int)(255.99f * green);  
                int ib = (int)(255.99f * blue); 

                fprintf(file, "%d %d %d\n", ir, ig, ib);
            } 
            else {
                Vec3 unit_dir = normalise(shame_about_Ray.direction);
                float t = 0.5f * (unit_dir.y + 1.0f);
                Vec3 c = add(mul(vec3(1.0f,1.0f,1.0f), (1.0f - t)), mul(vec3(0.5f, 0.7f,1.0f), t));
                int ir = (int)(255.99f * c.x);
                int ig = (int)(255.99f * c.y);
                int ib = (int)(255.99f * c.z);

                fprintf(file, "%d %d %d\n", ir, ig, ib);
            }

        }}


    fclose(file);
    return 0;
}