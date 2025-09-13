<img width="1354" height="389" alt="image" src="https://github.com/user-attachments/assets/5cac28d0-e7cf-452f-8263-b375f35fe899" />

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

<img width="1920" height="1053" alt="Screenshot from 2025-09-11 00-43-47" src="https://github.com/user-attachments/assets/32ad051b-7a51-4925-9316-8c0291ac0611" />
<img width="1917" height="1052" alt="Screenshot from 2025-09-11 00-44-30" src="https://github.com/user-attachments/assets/4e86d77a-9897-4fe2-9728-116e9ca8a06e" />

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
