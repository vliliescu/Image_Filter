# Image_Filter
The CImg library can only work natively with the following file types:
- RAW : consists in a very simple header (in ascii), then the image data.
- ASC (Ascii)
- HDR (Analyze 7.5)
- INR (Inrimage)
- PPM/PGM (Portable Pixmap)
- BMP (uncompressed)
- PAN (Pandore-5)
- DLM (Matlab ASCII)
For more diversity in image types, please install ImageMagick.

Description of buttons:
- Load image: Opens a dialog that allows loading an image for further processing.
- Clear image: Removes the currently loaded image.
- Edge Detection: Adds an Edge Detection filter in the command list.
- Gaussian: Adds a Gaussian filter in the command list.
- Sharpen: Adds a Sharpen filter in the command list. 
- Clear Filters: Clears the command list.
- Apply Filters: Executes all filters in the command list. The resulting image is saved as a file(output.bmp).
- Save Filter Configurtion: Saves the current loaded configuration in a text file (Output.txt). The configuration includes the path to the currently selected image, as well as the command list.
- Load Filter Configurtion: Loads the configuration currently saved in Output.txt and then executes all filters in the command list. If the path to the image is not correct, the previous image is kept and the filters loaded from the document will be applied on it. Also, all filters written in the document that are not in the correct format will be ignored.
