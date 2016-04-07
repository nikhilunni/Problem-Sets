
""" Main module """

from image import Im
from markov import Markov

import moviepy.editor as mpy

IMAGE_COUNT = 100

def main():
    # Import an image and train a Markov model on its neighbors
    im = Im("painting.jpg")
    w, h = im.get_size()
    dxys = [(-1, 0), (0, -1), (1, 0), (0, 1)]

    # Get all colors
    states = list(im.all_colors())

    markov = Markov(states)

    for x in range(w):
        for y in range(h):
            # Source pixel
            src_color = im.get_pixel(x, y)

            # Destination pixels
            dest_colors = []
            for (dx, dy) in dxys:
                nx = x + dx
                ny = y + dy

                if nx < 0:
                    nx += w
                elif nx >= w:
                    nx -= w
                if ny < 0:
                    ny += h
                elif ny >= h:
                    ny -= h

                dest_color = im.get_pixel(nx, ny)
                markov.update_transition(dest_color, src_color)

    image_fnames = []
    # Model trained, now generate new images!
    for i in range(IMAGE_COUNT):
        # Save old image
        image_fname = "images/image{0}.png".format(i)
        image_fnames.append(image_fname)
        im.save(image_fname)

        # Generate new image
        for x in range(w):
            for y in range(h):
                # Get old color
                color = im.get_pixel(x, y)

                # Set state
                markov.state = color

                # Get new color
                new_color = markov.step()

                # Paint over image
                im.set_pixel(x, y, new_color)

    animation = mpy.ImageSequenceClip(image_fnames, fps=20)
    animation.write_gif("images/animation.gif", fps=20)

if __name__ == "__main__":
    main()
