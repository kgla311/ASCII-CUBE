#include <math.h>
#include <stdio.h>
#include <string.h>
#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void sleep(int sleepS) {
#ifdef LINUX
    usleep(sleepMs * 1000);
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

float A = 0.0, B = 0.0, C = 0.0;
const int width = 160, height = 44;
float zBuffer[width * height];
char buffer[width * height];
int backgroundASCIICode = ' ';
int distanceFromCam = 100;
float horizontalOffset = 0;
float K1 = 40;
float incrementSpeed = 0.2;

float x, y, z;
float ox = 0, oy = 0, oz = -300; // Light source coordinates from camera

float sinA;
float sinB;
float sinC;

float cosA;
float cosB;
float cosC;

float ooz;
int xp, yp;
int idx;
const float fov = 3.1415f / 3.0f;

float calculateX(int i, int j, int k) {
    return j * sinA * sinB * cosC - k * cosA * sinB * cosC +
        j * cosA * sinC + k * sinA * sinC + i * cosB * cosC;
}

float calculateY(int i, int j, int k) {
    return j * cosA * cosC + k * sinA * cosC -
        j * sinA * sinB * sinC + k * cosA * sinB * sinC -
        i * cosB * sinC;
}

float calculateZ(int i, int j, int k) {
    return k * cosA * cosB - j * sinA * cosB + i * sinB;
}

char getASCII(float brightness) {
    const char* chars = ".:-=+*#%@";
    int index = (int)(brightness * 9); // brightness in 0..9 range
    if (index < 0) index = 0;
    if (index > 9) index = 9;
    return chars[index];
}

char calculateChar(float cubeX, float cubeY, float cubeZ) {
    // Rotated coordinates
    float rx = calculateX(cubeX, cubeY, cubeZ);
    float ry = calculateY(cubeX, cubeY, cubeZ);
    float rz = calculateZ(cubeX, cubeY, cubeZ);

    // Light vector
    float dx = ox - rx;
    float dy = oy - ry;
    float dz = oz - rz;
    float length = sqrtf(dx * dx + dy * dy + dz * dz);
    dx /= length;
    dy /= length;
    dz /= length;

    // Normal vector (approx. as vector from center to surface point)
    float nx = rx;
    float ny = ry;
    float nz = rz;
    float nLength = sqrtf(nx * nx + ny * ny + nz * nz);
    nx /= nLength;
    ny /= nLength;
    nz /= nLength;

    float brightness = dx * nx + dy * ny + dz * nz;
    brightness = (brightness + 1.0f) / 2.0f; // Normalize to 0..1

    return getASCII(brightness);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch) {
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

    if (z == 0) z = 1e-6;

    ooz = 1 / z;

    xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
    yp = (int)(height / 2 + K1 * ooz * y);

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    printf("\x1b[2J"); // clear screen

    while (1) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * sizeof(float));

        

        sinA = sin(A), cosA = cos(A);
        sinB = sin(B), cosB = cos(B);
        sinC = sin(C), cosC = cos(C);

        for (float cubeX = -20; cubeX < 20; cubeX += 0.5) {
            for (float cubeY = -20; cubeY < 20; cubeY += 0.5) {
                calculateForSurface(cubeX, cubeY, -20, calculateChar(cubeX, cubeY, -20));
                calculateForSurface(20, cubeY, cubeX, calculateChar(20, cubeY, cubeX));
                calculateForSurface(-20, cubeY, -cubeX, calculateChar(-20, cubeY, -cubeX));
                calculateForSurface(-cubeX, cubeY, 20, calculateChar(-cubeX, cubeY, 20));
                calculateForSurface(cubeX, -20, -cubeY, calculateChar(cubeX, -20, -cubeY));
                calculateForSurface(cubeX, 20, cubeY, calculateChar(cubeX, 20, cubeY));
            }
        }

        printf("\x1b[H");

        for (int k = 0; k < width * height; k++) {
            putchar(buffer[k]);
            if (k % width == width - 1) putchar('\n');
        }

        A += incrementSpeed;
        B += incrementSpeed;
        C += 0.01;

        sleep(16); // for 3 fps because im bad programmer
    }

    return 0;
}

