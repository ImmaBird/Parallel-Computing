#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

extern int *imageToMat(char *name, int *dims);
extern void matToImage(char *name, int *mat, int *dims);

int to1dim(int x, int y, int n);
int *filterImage(int *ans, int *image);
void applyFilter(int *ans, int *image, int x, int y);

int resx;
int resy;
int windowSize;
double *filter;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("USAGE: command filter kernel_size\n");
        return 1;
    }

    char *name = "image.jpg";
    const char *filter_name = argv[1];
    windowSize = atoi(argv[2]);

    // get the image
    int *dims = malloc(2 * sizeof(*dims)); // resolution of image
    int *mat = imageToMat(name, dims);     // the image in array form

    // assign values
    resx = dims[0];
    resy = dims[1];

    filter = malloc(windowSize * windowSize * sizeof(*filter));

    // filter stuff --------------------------------------------------

    if (strcmp(filter_name, "blur") == 0)
    {
        // blur filter
        printf("Bluring image...\n");
        for (int i = 0; i < windowSize * windowSize; i++)
        {
            filter[i] = 1.0 / (windowSize * windowSize);
        }
    }
    else if (strcmp(filter_name, "sharpen") == 0)
    {
        // sharpen
        printf("Sharpening image...\n");
        for (int i = 0; i < windowSize * windowSize; i++)
        {
            filter[i] = 0;
        }
        filter[to1dim(windowSize / 2, windowSize / 2, windowSize)] = 2;
        for (int i = 0; i < windowSize * windowSize; i++)
        {
            filter[i] -= 1.0 / (windowSize * windowSize);
        }
    }
    else if (strcmp(filter_name, "shift_up") == 0)
    {
        // shift up filter
        printf("Shifting image...\n");
        for (int i = 0; i < windowSize * windowSize; i++)
        {
            filter[i] = 0;
        }
        filter[to1dim(windowSize - 1, windowSize / 2, windowSize)] = 1;
    }

    // end filter stuff --------------------------------------------------

    int *ans = malloc((resx * resy) * sizeof(*ans));

    // compute new image with filter
    filterImage(ans, mat);

    // convert back to image
    matToImage("processedImage.jpg", ans, dims);

    // free stuff
    free(mat);
    free(ans);
    free(filter);
    // return success
    return 0;
}

int *filterImage(int *ans, int *image)
{
    printf("Number of Threads, Execution Time (seconds)\n");
    double start_time = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        {
            printf("%d,", omp_get_num_threads());
        }

#pragma omp for
        for (int x = 0; x < resx; x++)
        {
            for (int y = 0; y < resy; y++)
            {
                applyFilter(ans, image, x, y);
            }
        }
    }
    double elapsed_time = omp_get_wtime() - start_time;
    printf("%.4f\n", elapsed_time);
    return ans;
}

void applyFilter(int *ans, int *image, int x, int y)
{
    int offset = (windowSize - 1) / 2; // offset from center of kernel to edge
    int imagex = x - offset;
    int imagey = y - offset;
    int newImagex = 0;
    int newImagey = 0;
    double sum = 0.0;

    for (int i = 0; i < windowSize; i++)
    {
        imagey = y - offset;
        for (int j = 0; j < windowSize; j++)
        {
            // calculates new x in image bounds
            newImagex = imagex;
            if (imagex < 0)
            {
                newImagex = 0;
            }
            else if (imagex >= resx)
            {
                newImagex = resx - 1;
            }

            // calculates new y in image bounds
            newImagey = imagey;
            if (imagey < 0)
            {
                newImagey = 0;
            }
            else if (imagey >= resy)
            {
                newImagey = resy - 1;
            }

            sum += image[to1dim(newImagex, newImagey, resy)] * filter[to1dim(i, j, windowSize)];

            // increment image pixel
            imagey++;
        }
        imagex++;
    }

    ans[to1dim(x, y, resy)] = (int)(sum);
}

int to1dim(int x, int y, int n)
{
    return (x * n) + y;
}