
""" Module to process images. """

import numpy as np

from PIL import Image

class Im(object):
    """ Class that allows individual pixel access of images.

        Example Usage:

        >>> im = Im(`FILENAME`)
        >>> im.get_pixel(5, 4)
        (255, 255, 128)
    """
    def __init__(self, filename):
        """ Convert an image into an object that can be processed. """
        # Open the image
        im = Image.open(filename)

        # Get the size
        self._w, self._h = im.size

        # Construct a 2D array of pixels
        d = np.array(im.getdata(), dtype=np.uint8)
        self._data = d.reshape((self._h, self._w, 3))

    def get_size(self):
        """ Returns the width and height of the image.

        Returns:
            (w, h)
        """
        return (self._w, self._h)

    def all_colors(self):
        """ Returns a set of all colors that appear in the image.
        
        Returns:
            set of tuples (r, g, b)
        """
        return set([tuple(t) for t in self._data.reshape((self._w * self._h, 3))])

    def get_pixel(self, x, y):
        """ Get the pixel at position x, y.

        Args:
            x: int
            y: int

        Returns:
            (r, g, b) tuple (values 0-255)
        """
        return tuple(self._data[y][x])

    def set_pixel(self, x, y, color):
        """ Set the pixel at `x` and `y` to `color`.

        Args:
            x: int
            y: int
            color: (r, g, b) tuple

        Returns:
            (r, g, b) tuple (values 0-255)
        """
        self._data[y][x] = color

    def save(self, filename):
        """ Save image to file.

        Args:
            filename: filename
        """
        im = Image.fromarray(self._data, "RGB")
        im.save(filename)

if __name__ == "__main__":
    i = Im("painting.jpg")
    #i.save("test.png")
