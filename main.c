#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline static int validHex(char c) { return ('0' <= c  && c <= '9') || ('A' <= c  && c <= 'F') || ('a' <= c && c <= 'f'); };

// Convert an rgb value to its hex equivalent.
// Passing invalid rgb values will result in undefined behavior.
static char* rgbToHex(int r, int g, int b) {
    // determine the value of each hex digit
    int h2 = r%16;
    int h1 = (r - h2)/16;

    int h4 = g%16;
    int h3 = (g - h4)/16;

    int h6 = b%16;
    int h5 = (b - h6)/16;    

    // begin the string
    char* hex = (char*) malloc(7 * sizeof(char));

    // first digit
    if (h1 < 10) { hex[0] = '0' + h1; }
    else { hex[0] = 'A' + (h1 - 10); }

    // second digit
    if (h2 < 10) { hex[1] = '0' + h2; }
    else { hex[1] = 'A' + (h2 - 10); }

    // third digit
    if (h3 < 10) { hex[2] = '0' + h3; }
    else { hex[2] = 'A' + (h3 - 10); }

    // fourth digit
    if (h4 < 10) { hex[3] = '0' + h4; }
    else { hex[3] = 'A' + (h4 - 10); }

    // fifth digit
    if (h5 < 10) { hex[4] = '0' + h5; }
    else { hex[4] = 'A' + (h5 - 10); }

    // sixth digit
    if (h6 < 10) { hex[5] = '0' + h6; }
    else { hex[5] = 'A' + (h6 - 10); }

    hex[6] = '\0';
    return hex;
};

// Convert a hex value to its RGB equivalent.
// Passing an invalid hex will result in undefined behavior.
static int* hexToRGB(char* hex) {
    // allocate the memory for the rgb format
    int* rgb = (int*) malloc(3 * sizeof(int));

    // populate the array
    // r entry
    if (hex[0] <= '9') { rgb[0] = 16*(hex[0] - '0'); }
    else if (hex[0] <= 'F') { rgb[0] = 16*(hex[0] - 'A' + 10); }
    else { rgb[0] = 16*(hex[0] - 'a' + 10); }

    if (hex[1] <= '9') { rgb[0] += hex[1] - '0'; }
    else if (hex[1] <= 'F') { rgb[0] += (hex[1] - 'A' + 10); }
    else { rgb[0] += (hex[1] - 'a' + 10); }

    // g entry
    if (hex[2] <= '9') { rgb[1] = 16*(hex[2] - '0'); }
    else if (hex[2] <= 'F') { rgb[1] = 16*(hex[2] - 'A' + 10); }
    else { rgb[1] = 16*(hex[2] - 'a' + 10); }

    if (hex[3] <= '9') { rgb[1] += hex[3] - '0'; }
    else if (hex[3] <= 'F') { rgb[1] += (hex[3] - 'A' + 10); }
    else { rgb[1] += (hex[3] - 'a' + 10); }

    // b entry
    if (hex[4] <= '9') { rgb[2] = 16*(hex[4] - '0'); }
    else if (hex[4] <= 'F') { rgb[2] = 16*(hex[4] - 'A' + 10); }
    else { rgb[2] = 16*(hex[4] - 'a' + 10); }

    if (hex[5] <= '9') { rgb[2] += hex[5] - '0'; }
    else if (hex[5] <= 'F') { rgb[2] += (hex[5] - 'A' + 10); }
    else { rgb[2] += (hex[5] - 'a' + 10); }

    return rgb;
};

int main (int argc, char* argv[]) {
    printf("---------------------\nColor Converter v1.0\n---------------------\n\n");
    printf("Please follow directions stated in the prompts.\nFailure to do so will result in inaccurate results.\n\n");

    if (argc <= 1) {
        // determine the formats to convert from and to
        int startingFormat, endingFormat;

        printf("Enter the format of your color:\n  1. RGB\n  2. Hex\n  3. Normalized RGB\n\n> ");
        scanf("%i", &startingFormat);

        printf("\nEnter the format you want to convert your color to:\n  1. RGB\n  2. Hex\n  3. Normalized RGB\n\n> ");
        scanf("%i", &endingFormat);

        // read in the values to convert
        switch (startingFormat) {
            case 1: {
                int r, g, b;

                printf("\nEnter the rgb value as 3 space separated numbers: ");
                scanf("%i", &r);
                scanf("%i", &g);
                scanf("%i", &b);

                // ensure none were entered outside the bounds
                if (r < 0 || r > 255 || b < 0 || b > 255 || g < 0 || g > 255) {
                    printf("\n[ERROR] RGB format not entered. Numbers must be between 0 and 255.\n");
                    return 1;
                }

                // convert to the other format
                switch (endingFormat) {
                    case 1: {
                        printf("\nNot sure why you converted to the same format you started with, but the RGB is %i, %i, %i", r, g, b);
                        break;
                    }

                    case 2: {
                        char* hex = rgbToHex(r, g, b);
                        printf("\nHex for your color 0x%s", hex);
                        free(hex);
                        break;
                    }

                    case 3: {
                        printf("\nNormalized RGB for your color: %f, %f, %f", (r/255.0f), (g/255.0f), (b/255.0f));
                        break;
                    }
                }

                break;
            }

            case 2: {
                char* hex = (char*) malloc(7 * sizeof(char));

                // read in the hex
                printf("\nEnter the hex value as a 6 digit hex number: ");
                scanf("%s", hex);
                hex[6] = '\0';

                // ensure it is in the proper format
                for (int i = 0; i < 6; ++i) {
                    if (!validHex(hex[i])) {
                        printf("\n[ERROR] Hex format not entered. Hex digits must be between 0 and F.\n");
                        return 1;
                    }
                }

                // convert to the other format
                switch (endingFormat) {
                    case 1: {
                        int* rgb = hexToRGB(hex);
                        printf("\nRGB for your color: %i, %i, %i", rgb[0], rgb[1], rgb[2]);
                        free(rgb);
                        break;
                    }

                    case 2: {
                        printf("\nNot sure why you converted to the same format you started with, but the hex is %s", hex);
                        break;
                    }

                    case 3: {
                        int* rgb = hexToRGB(hex);
                        float r = (float) rgb[0]/255.0f, g = (float) rgb[1]/255.0f, b = (float) rgb[2]/255.0f;
                        printf("Normalized RGB for your color: %f, %f, %f", r, g, b);
                        free(rgb);
                        break;
                    }
                }

                free(hex);
                break;
            }

            case 3: {
                float r, g, b;

                // read in the normalized RGB values
                printf("\nEnter the normalized RGB value as 3 spaced separated floats: ");
                scanf("%f", &r);
                scanf("%f", &g);
                scanf("%f", &b);

                // ensure none were entered outside the bounds
                if (r < 0.0f || r > 1.0f || b < 0.0f || b > 1.0f || g < 0.0f || g > 1.0f) {
                    printf("\n[ERROR] Normalized RGB format not entered. Numbers must be between 0.0 and 1.0.\n");
                    return 1;
                }

                // convert to the other format
                switch (endingFormat) {
                    case 1: {
                        printf("\nRGB for your color: %i, %i, %i", (int) (255*r + 0.5f), (int) (255*g + 0.5f), (int) (255*b + 0.5f));
                        break;
                    }

                    case 2: {
                        char* hex = rgbToHex(255*r + 0.5f, 255*g + 0.5f, 255*b + 0.5f);
                        printf("\nHex for your color: 0x%s", hex);
                        free(hex);
                        break;
                    }
                    
                    case 3: {
                        printf("\nNot sure why you converted to the same format you started with, but the normalized RGB is %f, %f, %f", r, g, b);
                        break;
                    }
                }

                break;
            }
        }

        return 0;
    }

    // todo set up command line stuff later if I feel like it
    if (!strcmp(argv[1], "--help")) {
        // todo print help message
    }

    if (!strcmp(argv[1], "-r")) {
        // todo handle starting format as rgb
    }

    if (!strcmp(argv[1], "-h")) {
        // todo handle starting format as hex
    }

    if (!strcmp(argv[1], "-nr")) {
        // todo handle starting format as normalized rgb
    }

    if (!strcmp(argv[1], "-rh")) {
        // todo rgb to hex
    }

    if (!strcmp(argv[1], "-hr")) {
        // todo hex to rgb
    }

    if (!strcmp(argv[1], "-rnr")) {
        // todo rgb to normalized rgb
    }

    if (!strcmp(argv[1], "-nrr")) {
        // todo normalized rgb to rgb
    }

    // todo potentially add more formats

    return 0;
};
