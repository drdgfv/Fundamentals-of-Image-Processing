<img width="1354" height="389" alt="Screenshot from 2025-09-11 01-10-15" src="https://github.com/user-attachments/assets/a08c86c3-c5e0-45d3-a49e-c077307038df" />

# Fundamentals-of-Image-Processing

This repository contains the assignments for the 'Fundamentals of Image Processing' course at UFRGS.
> By: Eduardo Veiga Ferreira

<details>
<summary><b>Assignment I - Basic Operations on Digital Images: An Overview</b></summary>

## Part I - Completed Satisfactorily

In this part of the project, I explored the compression/decompression processes more thoroughly. I noticed when saving that there is a size difference between the loaded (original) image and the one saved by the program. A quick search reveals that this is due to the decompression and compression process; when an image is opened, the algorithm used to compress the open image will almost never be able to recompress it to the same format as the original.

## Part II - Completed Satisfactorily

The QT6 library was used due to its popularity and affinity with C/C++, in addition to providing excellent support not only for window manipulation but also for images. The program can be run using the "qmake6" command to create the Makefile for the directory, if it has not already been created. Afterward, the make command can be used to compile and make run to execute it.

Three copies of the original image were used: the original image, a source image, and a destination image. This way, it is possible to accumulate operations and return to the original with a reset.

<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-39-30" src="https://github.com/user-attachments/assets/6d41398b-3311-4544-a5f6-c2aacff18399" />
Illustration 1: initial interface.

### Inversion Operations - Completed Satisfactorily

For the inversion operations, the logic of copying with memcpy was used, utilizing the image's height and width to calculate the positions of the first byte of the original image, the first byte of the last row of the destination image, and the last byte of the first row of the destination image. The program considers an RGBA system, therefore 4 bytes per pixel. This part was one of the most challenging, as the objective of the project was to implement the row and column manipulations at a lower level. With an understanding of pixel arrangement, the work flowed much more practically.

<table>
  <tr> 
    <td> <img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-43-47" src="https://github.com/user-attachments/assets/32ad051b-7a51-4925-9316-8c0291ac0611" /> </td>
    <td><img width="1917" height="1052" alt="Screenshot from 2025-09-11 00-44-30" src="https://github.com/user-attachments/assets/4e86d77a-9897-4fe2-9728-116e9ca8a06e" /> </td>
  </tr>
</table>

Illustration 2: The open button opens the directory for image selection. 

<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-45-10" src="https://github.com/user-attachments/assets/6c144f7a-c104-4fe1-b622-ce109e745e36" />
Illustration 3: X mirror and Y mirror operations performed successively.

### Grayscale Operation - Completed Satisfactorily

This operation took little time after I became more familiar with pixel manipulation. Sweeping through them one by one, the formula given in the activity's instructions is applied, which is quite intuitive. The alpha coefficient is ignored, and only the R, G, and B tones are altered.

<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-45-24" src="https://github.com/user-attachments/assets/5a203f06-ec38-4f48-a18d-d1442e543b30" />
Illustration 4: X mirror, Y mirror, and Grayscale operations performed successively.

### Quantization Operation - Completed Satisfactorily

This was one of the more time-consuming operations, as the logic of intervals, "bins," and the mathematical operations involved are not as intuitive. By studying and using generative AI to provide some more personalized explanations of the process, understanding was built through a few failed attempts. In this operation, some initial checks are made, and the Grayscale operation is used to obtain the necessary tone metrics beforehand and prevent redundant code snippets, in addition to performing the necessary grayscale for one-dimensional quantization.
<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-45-56" src="https://github.com/user-attachments/assets/47d31323-effc-41e4-9e58-169208e157e2" />

Illustration 5: Y mirror and Quantization 4 operations performed successively.

### Saving - Completed Satisfactorily

The program supports loading images of any common and popular extension such as jpg, jpeg, and png. The "Open" button opens the program's image directory but can load any image saved on the machine where it is running. The "Save" button saves a copy of the image, with or without alterations, in the image directory named "dst_[filename].jpeg".

<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-52-53" src="https://github.com/user-attachments/assets/6f0be272-7d9b-4dbf-88c2-3c7bb4d46c1a" />
Illustration 6: The Save button was clicked, the image is saved in JPEG format in the images directory, and the status label displays the image saved message.

### Extra Implementations

Beyond what was requested, some extra functionalities were implemented, such as state verification for certain operations, like ensuring values are between 0 and 255 for quantization, and a reset button to return the state of all images and their copies to the original state.

</details>

<details>

<summary><b>Assignment II - Linear Transformations, Histogram Equalization and Matching, Convolution and Filtering in the Spatial Domain </b></summary>

## Part I - Satisfactorily Completed

### 1) Calculate and display the histogram of a grayscale image - Satisfactorily Completed

To plot the graph, the Charts module from the QT library was used. Currently, many modules have been separated from the main installation to make it lighter and must be installed manually.
Therefore, the GrayScale operation was adjusted to return the image's histogram (calculated during the conversion) and the minimum and maximum values for the quantization operation. The program then generates a histogram for a grayscale version of the source image in a new dialog window, using a chart and other structures for the title and axes. The height of the columns was normalized to a range of 0 to 1, using the most frequent tone in the image as the maximum value (1).

Note: The action to view the histogram preserves the last operation performed on the image. This means it uses a grayscale image for the calculation but does not apply the grayscale conversion to the working copy of the image.

<img width="1920" height="1080" alt="Screenshot from 2025-09-26 23-31-27" src="https://github.com/user-attachments/assets/1b8ca30b-4ba8-4f19-9fa0-8e0da5c043f6" />
Illustration 1: A view of the grayscale histogram generated by the program for a color image.

### 2) Adjust image brightness - Satisfactorily Completed

The brightness adjustment operation was implemented by adding a value between -255 and 255 to all pixels in the image. A clamp function was used to ensure the final values remain within the 0 to 255 range.

<img width="1920" height="1053" alt="Screenshot from 2025-09-27 00-13-24" src="https://github.com/user-attachments/assets/33f4e770-0309-42ce-8879-00426e3d0e5d" />
Illustration 2: Image brightness adjusted by +50.

<table>
  <tr> 
    <td><img width="1020" height="555" alt="Screenshot from 2025-09-27 00-09-31" src="https://github.com/user-attachments/assets/751a186c-719a-48d4-9be5-4e99f1a3cbc7" /> </td>
    <td><img width="1020" height="555" alt="Screenshot from 2025-09-27 00-13-02" src="https://github.com/user-attachments/assets/a1628ea2-c924-4c10-9c2e-e2de451d5a1c" /> </td>
  </tr>
</table>
Illustration 3: Comparison of the histograms for the original image and the image with a brightness adjustment of +50.

### 3) Adjust image contrast - Satisfactorily Completed

The contrast adjustment operation was implemented by multiplying all pixels in the image by a value between 0 and 255. A clamp function was used to set the minimum and maximum limits to 0 and 255.

<img width="1920" height="1053" alt="Screenshot from 2025-09-27 01-40-25" src="https://github.com/user-attachments/assets/db901942-e566-4dc5-933d-6bb570126110" />
Illustration 4: Image contrast adjusted by a factor of 2.

<table>
  <tr> 
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 01-40-32" src="https://github.com/user-attachments/assets/140b45fb-6f9f-4016-ab22-02b0abdc57c6" /> </td>
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 01-40-38" src="https://github.com/user-attachments/assets/7c4a6be3-da9f-4fa0-a83c-189c7ef8864c" /> </td>
  </tr>
</table>
Illustration 5: Comparison of the histograms for the original image and the image with a contrast adjustment of 2.

### 4) Calculate and display the negative of an image - Satisfactorily Completed

The negative operation was implemented. For every pixel, its color value is subtracted from 255.

<img width="1920" height="1053" alt="Screenshot from 2025-09-27 01-56-22" src="https://github.com/user-attachments/assets/34f76a48-97a6-40e2-97b3-f1dd441c053e" />
Illustration 6: Calculation of the image negative.

<table>
  <tr> 
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 01-57-28" src="https://github.com/user-attachments/assets/786b7f1e-2525-4721-96d5-4f4ca1163dfd" /> </td>
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 01-59-41" src="https://github.com/user-attachments/assets/59c3c639-9f22-4bd8-b875-ef45aa844e67" /> </td>
  </tr>
</table>
Illustration 7: Comparison of the histograms for the original and negative images, showing their inverse relationship.

### 5) Equalize the histogram of an image - Satisfactorily Completed

The equalization operation was implemented based on the algorithm presented in class. A key starting point was recognizing that even grayscale photos have three components (R, G, and B). Therefore, the cumulative histogram component must correspond to the gray tone derived from the combination of these colors.

<img width="1920" height="1080" alt="Screenshot from 2025-09-27 16-33-03" src="https://github.com/user-attachments/assets/8cfbaed3-21ca-49da-a704-fc690f729e73" />
Illustration 8: Equalized grayscale image.

<table>
  <tr> 
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 02-16-32" src="https://github.com/user-attachments/assets/7f4c0641-486e-4953-9367-8a0bf1531602" /> </td>
    <td> <img width="1020" height="555" alt="Screenshot from 2025-09-27 16-36-14" src="https://github.com/user-attachments/assets/979f7eea-ceb9-4fd1-9644-f124005bb903" /> </td>
  </tr>
</table>
Illustration 9: Comparison between the original histogram and the equalized histogram (using the cumulative histogram).

### 6) Perform Histogram Matching on pairs of grayscale images - Satisfactorily Completed

The histogram matching operation was implemented. The program displays a scaled thumbnail of the target image between the source and copy images to suggest a matching operation. The code uses two QImage structures to preserve the original target image and generate its histogram. The operations for the target image are located in the upper-right corner of the window. Additionally, the grayscale and histogram functions were modified to accept image parameters, allowing them to operate on different images, as it is now necessary to generate histograms for two separate images.

The algorithm was implemented as suggested in the class slides. The histograms for the source and target images are declared and initialized, and their normalized cumulative histograms are calculated to handle different resolutions. Next, for each value in the normalized cumulative histogram of the source image, the closest value in the normalized cumulative histogram of the target image is found. Finally, the matched tones are assigned to each pixel.

<img width="1920" height="1053" alt="Screenshot from 2025-09-27 19-19-55" src="https://github.com/user-attachments/assets/9b5d57a3-539f-43df-bbc5-867e3918222c" />
Illustration 10: Matching the main image on the left with a target image in the center.

<img width="1020" height="555" alt="Screenshot from 2025-09-27 19-35-26" src="https://github.com/user-attachments/assets/6f0b2f8e-637f-4fab-8d5c-439282efb37a" />
Illustration 11: Histogram of the main image after matching (the original histogram can be seen in previous illustrations).

<img width="1020" height="555" alt="Screenshot from 2025-09-27 19-35-37" src="https://github.com/user-attachments/assets/3eeff42e-8531-4ebb-ae79-ba6b449ad66b" />
Illustration 12: Histogram of the target image (Robert Downey Jr).

## Part II - Satisfactorily Completed

### 7) Reduce an image (zoom out) using reduction factors sx and sy - Satisfactorily Completed

The zoom-out operation was implemented. The program creates a new image with its width and height reduced by factors of sx and sy, respectively. It then iterates through the source image in sx by sy blocks while simultaneously iterating through the pixels of the destination image. For each block, the average R, G, and B values are calculated, and these become the RGB components of the corresponding pixel in the destination image. The main challenge was understanding how to move through the blocks in the source image while iterating pixel-by-pixel through the destination image.

<img width="1920" height="1053" alt="Screenshot from 2025-09-27 22-03-29" src="https://github.com/user-attachments/assets/a7871271-b0e2-461f-b100-310a8104e3c5" />
Illustration 13: Image zoomed out by a factor of 2x2.

### 8) Enlarge the image (zoom in) using a 2x2 factor - Satisfactorily Completed

The zoom-in operation was implemented. The program creates a new image with its width and height increased by width-1 and height-1, respectively. This creates an image large enough to alternate between the rows and columns of the original image. First, the columns and rows from the source image are copied to the destination image in an interleaved pattern. Next, the odd-numbered columns are interpolated using the adjacent even-numbered columns. Finally, all odd-numbered rows are interpolated, resulting in an enlarged image created through pixel interpolation.

<img width="1920" height="1080" alt="Screenshot from 2025-09-27 23-47-08" src="https://github.com/user-attachments/assets/4daf391a-1a48-4285-880c-5d03e7532049" />
Illustration 14: Image zoomed in by a factor of 2x2.

### 9) Rotate the image by 90° (both clockwise and counter-clockwise) - Satisfactorily Completed

The rotation operation was implemented for both directions. The program creates a new image by swapping the width and height of the original image. Then, for each pixel (i, j) in the original image, it calculates its new rotated position in the destination image.
<table>
  <tr> 
    <td> <img width="1920" height="1053" alt="Screenshot from 2025-09-28 01-13-52" src="https://github.com/user-attachments/assets/e75df094-2a7d-48c6-8916-a416819b186a" /> </td>
    <td> <img width="1920" height="1053" alt="Screenshot from 2025-09-28 01-14-53" src="https://github.com/user-attachments/assets/83762890-5bd5-49d7-919d-01d109e5f09c" /> </td>
  </tr>
</table>
Illustration 15: Image rotated by 90° and -90°.

### 10) Implement a procedure to perform convolution between an image and an arbitrary 3x3 filter - Satisfactorily Completed

The convolution operation was implemented here. Using auxiliary buttons, it is possible to select a pre-defined kernel for the operation. The process follows the algorithm seen in class: each pixel's new value is calculated from the sum of multiplications performed by overlaying the kernel on that pixel and its neighbors. The most complicated part was understanding the correct way to adjust and clamp the results, especially when using high-pass filters.

<img width="1920" height="1053" alt="Screenshot from 2025-09-28 23-55-59" src="https://github.com/user-attachments/assets/90433b94-26f7-499d-afb1-eaa6b021ec23" />
Illustration 16: Image after applying a Gaussian filter 10 times.

<table>
  <tr> 
    <td> ![dst_Space_187k](https://github.com/user-attachments/assets/1e759b0d-194d-4d13-b2f3-a8ce93b1bc16) </td>
    <td> ![dst_Gramado_72k](https://github.com/user-attachments/assets/e2ffdb9d-626e-4b9a-aa49-a80d537d50b0) </td>
  </tr> 
  <tr>
   <td> ![dst_Underwater_53k](https://github.com/user-attachments/assets/1d2b5cac-d069-482d-b9d5-7f54b88d9685) </td>
   <td> ![dst_rdj](https://github.com/user-attachments/assets/e9b19015-0569-4bff-b2a5-63187a4aa474) </td>
  </tr>
</table>
Illustration 17: Results of image convolution with the generic high-pass, Laplacian, Prewitt Hy, and Sobel Hx filters, respectively.
  
</details>

<details>
<summary><b> Assignment III – Video Processing with OpenCV </b> </summary>
  
## 1) Configure your programming environment and run the base program — Completed Satisfactorily

The initial stage required more time due to the installation and configuration of the OpenCV library, downloaded from the link provided in the project specification. Integration into the project was handled via a CMakeLists.txt file.

The base program was modified to display two simultaneous captures, allowing side-by-side visualization of the original and processed video streams.

<img width="1920" height="1080" alt="Screenshot from 2025-10-17 21-21-04" src="https://github.com/user-attachments/assets/2c0c0689-a13c-435e-8291-f9b24929fde5" />
Illustration 1: Visualization of the two video captures (original and processed).

## 2) Apply GaussianBlur using a Trackbar — Completed Satisfactorily

The following functions were used:
- `createTrackbar`
- `GaussianBlur`

The trackbar controls a value from 0 to 50, internally mapped to positive odd kernel sizes.

A helper function was created:

```
int operations(Mat src, Mat cpy, int operation, int size)
```

Return values:
- `0` → key does not trigger an operation  
- `1` → key corresponds to an effect to be applied  

This enables clean switch-based handling of multiple transformations.

<img width="1920" height="1080" alt="Screenshot from 2025-10-17 23-02-02" src="https://github.com/user-attachments/assets/acab819f-37ac-493b-b821-d96d3212cc7c" />
Illustration 2: Blur operation controlled by a trackbar, shown next to the original video.

## 3) Edge detection using Canny — Completed Satisfactorily

The `cvtColor` function was used for the required RGB → Grayscale conversion.  
Pipeline:

1. Convert frame to grayscale  
2. Apply `Canny`  
3. Convert back to RGB for unified display format  
4. Combine with previously applied operations if needed  

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 01-10-52" src="https://github.com/user-attachments/assets/827d6267-19e7-4e8e-8076-129fb16fff26" />
Illustration 3: Canny edge detection applied to the video stream.

## 4) Gradient estimation using the Sobel operator — Completed Satisfactorily

The implementation uses:
- `cvtColor` for grayscale conversion  
- reconversion to a 3-channel image to preserve consistency  
- application of `Sobel`  
- `convertTo` for clamping and normalizing output values  

This produces the classic Sobel effect taught throughout the course.

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 01-52-40" src="https://github.com/user-attachments/assets/ca2aac6c-c932-43b0-871c-c937c249d1b9" />
Illustration 4: Sobel gradient visualization beside the original video.


## 5) Brightness adjustment, contrast adjustment, and negative using convertTo — Completed Satisfactorily

The copy window was extended to support multiple trackbars:
- Blur Level  
- Brightness Level  
- Contrast Level  

All transformations use the standard linear pointwise formula:

```
g(x,y) = alpha * f(x,y) + beta
```

This enables:
- Brightness increase/decrease  
- Contrast expansion/compression  
- Negative effect  

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 03-18-27" src="https://github.com/user-attachments/assets/9ab7e7ea-96f0-4531-aadd-a8d76f8629a3" />
Illustration 5.1: Negative operation applied to the video.

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 03-19-34" src="https://github.com/user-attachments/assets/158631de-41f9-42a2-af54-a7221331e507" />
Illustration 5.2: Brightness adjustment applied to the video.

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 03-20-21" src="https://github.com/user-attachments/assets/3fab7619-a4b8-4bcf-96f3-3ed0d9c8962c" />
Illustration 5.3: Contrast adjustment applied to the video.

## 6) RGB to Grayscale conversion — Completed Satisfactorily

Implemented using:

```
cvtColor(src, gray, COLOR_BGR2GRAY);
```

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 06-03-42" src="https://github.com/user-attachments/assets/48a5b077-b33a-40b7-b92a-48f6eaf2b530" />
Illustration 6: Grayscale (luminance) operation applied to the video.

## 7) Resize the video to half of its dimensions — Completed Satisfactorily

Performed with:

```
resize(src, dst, Size(), 0.5, 0.5);
```

Supports other scaling factors as well.

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 06-04-18" src="https://github.com/user-attachments/assets/4c841c00-f2bf-40a2-a006-ed0f7dd6f73a" />
Illustration 7: Video scaled down to 50% of its original dimensions.

## 8) Rotate the video by 90 degrees — Completed Satisfactorily

Rotation implemented using:

```
rotate(src, dst, ROTATE_90_CLOCKWISE);
```

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 06-04-47" src="https://github.com/user-attachments/assets/52e27858-9e13-41ea-9d8c-74e767ab424e" />
Illustration 8: 90-degree rotation applied to the video.

## 9) Horizontal and vertical mirroring — Completed Satisfactorily

Implemented with:

```
flip(src, dst, 0);  // vertical
flip(src, dst, 1);  // horizontal
```

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 04-19-00" src="https://github.com/user-attachments/assets/7fad46b3-b89c-4999-8982-43b9b8f67278" />
Illustration 9.1: Horizontal flip applied to the video.  

<img width="1920" height="1080" alt="Screenshot from 2025-10-20 06-08-46" src="https://github.com/user-attachments/assets/5f10b5d3-f904-4c95-b9cb-6dc09e10a7f0" />
Illustration 9.2: Vertical flip applied to the video.

## 10) Video recording including all effects (except rotation and resizing) — Completed Satisfactorily

This stage required deeper understanding of OpenCV structures, including:
- how `VideoWriter` behaves  
- codec selection and handling  
- matching resolution and FPS between input and output  

The chosen codec was **Motion-JPEG**, generating `.avi` files.

A challenge encountered involved FPS synchronization: the recorded video played faster than the live capture, despite the frame acquisition appearing slower. The issue remains partially unresolved, but the resulting

<img width="1169" height="426" alt="Screenshot from 2025-10-20 06-13-39" src="https://github.com/user-attachments/assets/6fd67b6a-5a94-421d-a161-28e9dd760008" />
Illustration 10: Demonstration of saving.

</details>
