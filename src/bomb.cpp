#include "C:\raylib\raylib\src\raylib.h"

int main()
{
    // Initialization (you may need to adjust the window size)
    InitWindow(800, 600, "Image to C Code Exporter");

    // Load the image from your specified path
    Image img = LoadImage("C:\\Users\\vaay\\tetwist-cmsc123\\src\\bomb.jpg");

    // Export the image as C code
    ExportImageAsCode(img, "bomb.h");

    // Unload the image to free memory
    UnloadImage(img);

    CloseWindow(); // Close the Raylib window and deinitialize
    return 0;
}