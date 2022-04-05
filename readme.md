# Graphic filters (image_processor)

This project is a part of learning to code with C++. This is a console app to edit pictures in 24-bit [BMP](http://en.wikipedia.org/wiki/BMP_file_format) format.

## Format of command line arguments

Description of the format of command line arguments:

`{program name} {path to input file} {path to output file}
[-{filter name 1} [filter parameter 1] [filter parameter 2] ...]
[-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...`

When running without arguments, the program outputs help.

### Example
`./image_processor input.tmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

In this example
1. The image is loaded from the file `input.bmp`
2. Cropped to an image with the beginning in the upper left corner and the size of 800x600 pixels
3. Translates to shades of gray
4. A blur with sigma 0.5 is applied
5. The resulting image is saved to the file `/tmp/output.bmp`

The filter list may be empty, then the image must be saved unchanged.
Filters are applied in the order in which they are listed in the command line arguments.

## Filters

In the formulas, we further assume that each color component
is represented by a real number from 0 to 1. Pixel colors
are represented by triples `(R, G, B)'. Thus, `(0, 0, 0)` – black, 
`(1, 1, 1)` – white.

### List of basic filters

#### [Matrix filter](filters/matrix_filter.cpp) (no user-usage due to it is inside component of the project)
If the filter is set by a matrix, it means that the value of each of the colors is determined by the weighted sum
of the values of this color in neighboring pixels in accordance with the matrix. In this case, the target pixel
corresponds to the central element of the matrix.

For example, for a filter given by a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D1%20&%202%20&%203%20%5C%5C4%20&%205%20&%206%20%5C%5C7%20&%208%20&%209%20%5C%5C%5Cend%7Bbmatrix%7D)

The value of each of the colors of the target pixel `C[x][y]` will be determined by the formula

```
C[x][y] =
  min(1, max(0,
   1*C[x-1][y-1] + 2*C[x][y-1] + 3*C[x+1][y-1] +
   4*C[x-1][y]   + 5*C[x][y]   + 6*C[x+1][y]   +
   7*C[x-1][y+1] + 8*C[x][y+1] + 9*C[x+1][y+1]
))
```

When processing pixels close to the edge of the image, part of the matrix may extend beyond the image boundary.
In this case, we will use the value of the image pixel closest to it as the value of the pixel that goes beyond the border.

#### [Crop](filters/crop_filter.cpp) (-crop width height)
Crops the image to the specified width and height. The upper left part of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available part of the image is given.

#### [Grayscale](filters/grayscale_filter.cpp) (-gs)
Converts the image to grayscale using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)

#### [Negative](filters/negative_filter.cpp) (-neg)
Converts an image to a negative using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)

#### [Sharpening](filters/sharp_filter.cpp) (-sharp)
Sharpening. It is applied by using a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

#### [Edge Detection](filters/edge_detection_filter.cpp) (-edge threshold)
Border selection. The image is converted to grayscale and a matrix is applied

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Pixels with a value exceeding the threshold are colored white, the rest are black.

#### [Gaussian Blur](filters/gaussian_blur.cpp) (-blur sigma)
[Gaussian blur](https://ru.wikipedia.org/wiki/Blurry_gaussu),
the parameter is sigma.

The value of each of the pixel colors `C[x0][y0]` is determined by the formula

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20=%20%5Csum_%7Bx=0,y=0%7D%5E%7Bwidth-1,%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B%5Csqrt%5B%5D%7B2%5Cpi%5Csigma%5E2%7D%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20&plus;%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

#### [Crystallize](filters/crystallize_filter.cpp) (-crystallize points_amount)
This filter turns picture into set of crystalls with the same color, the parameter is the amount of crystalls.

It works like this: first, an array of random points of a given size is created, after that the value of each pixel turns into the value of the closest pixel from our array. That is how it works.

#### [Crystallize advanced](filters/crystallize_advanced_filter.cpp) (-crystallize_advanced points_amount)
Advanced version of the previous one, but here the value of pixel turns into a weighted sum of two closest points with the weights proportional to the default distanses between the points.
