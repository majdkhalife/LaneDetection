Hello, welcome to my github repository.
Here, I will be implementing a Lane Detector using traditional methods like SIFT and Canny.
I will also  be giving you a quick tutorial on cpp, as it is the most commonly used applucation in the industry due to its fast processing ability.

1) What is CMake?
CMake is a tool that generates build instructions for your compiler.
You feed it your CMakeLists.txt, and it outputs platform specific build files. You can think of Cmake as your own recipe writer, it doesnt cook anything, it however writes down what your program will need to compile properly.
<br>

2) What is Make?
Make is the tool that actually compiles your code.
You feed it your Makefile and it will give you your executable program. 
You can think of make as the chef, it follows the recipe that CMake wrote.

So when do you run each?
Run cmake .. when:
First time setting up
You change CMakeLists.txt (add/remove files, change libraries)
You add/remove .cpp files to your project
NOT when you just edit existing code in main.cpp

Run make when:
You change any .cpp or .h files
Every time you want to recompile
After running cmake ..

The proposed flow:
1. Read and decode file
2. Define Region of Interest (ROI) - focus on road area only
3. Convert to Grayscale
4. Reduce Noise (Gaussian Blur)
5. Canny Edge Detection
6. Apply ROI mask to edges
7. Hough Transform to detect lines
8. Filter and average lines (separate left/right lanes)
9. Overlay lanes on original image

We will elaborate on each method, how we construct it in the following sections. But for now, just make sure you understadn the basics of file management in cpp

1) Read and decode file
In order to read and decode the file, we use OpenCVs VideoCapture method. This method allows us to 
Open a video file or image file sequence or a capturing device or a IP video stream for video capturing.
One thing worth remembering is that a video is just a bunch fo images stitched together.  Which is why we need to define a Mat object. 
We process the video frame by frame and pass each Mat obj to the frame. We keep doing this until either the video ends or until the user(you) clicks the esacpe button on your keyboard.
The next step would be to define the ROI. Why you might ask? Because we dont want to detect all edges, just the ones relevant to us.


