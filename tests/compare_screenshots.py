import os
from os import path
import shutil
import unittest

from PIL import Image, ImageChops, ImageEnhance, ImageOps


def link(uri, label=None):
    if label is None:
        label = uri
    parameters = ''

    # OSC 8 ; params ; URI ST <name> OSC 8 ;; ST
    escape_mask = '\033]8;{};{}\033\\{}\033]8;;\033\\'

    return escape_mask.format(parameters, uri, label)


def calc_diff_percentage(diff):
    diff_count = sum(1 for _ in diff.getdata() if sum(_) > 0)
    pixels_count = diff.size[0] * diff.size[1]
    return diff_count / pixels_count


def image_with_diff(img, diff):
    diff = ImageOps.invert(diff.convert('L'))

    img_darken = ImageEnhance.Brightness(img)
    img_darken = img_darken.enhance(0.64)

    red = Image.new('RGBA', img.size, color='#F00')
    img_diffed = Image.composite(img_darken, red, diff)
    return img_diffed


class MyTestCase(unittest.TestCase):
    def test_screenshots(self):
        current_directory_path = path.dirname(__file__)

        screenshots_path = path.join(current_directory_path, 'screenshots')
        if not path.exists(screenshots_path):
            os.makedirs(screenshots_path)

        screenshots_new_path = path.join(current_directory_path, 'screenshots_new')
        if not path.exists(screenshots_new_path):
            os.makedirs(screenshots_new_path)

        screenshots_diff_path = path.join(current_directory_path, 'screenshots_diff')
        if path.exists(screenshots_diff_path):
            for diff in os.listdir(screenshots_diff_path):
                os.remove(path.join(screenshots_diff_path, diff))
        else:
            os.makedirs(screenshots_diff_path)

        screenshots = set(os.listdir(screenshots_path))
        screenshots_new = set(os.listdir(screenshots_new_path))

        for screenshot in screenshots_new:
            if screenshot not in screenshots:
                shutil.copy(path.join(screenshots_new_path, screenshot), path.join(screenshots_path, screenshot))
                screenshots.add(screenshot)

        for screenshot in screenshots:
            msg = f"\nMissing new screenshot for {link(path.join(screenshots_path, screenshot))}"
            self.assertIn(screenshot, screenshots_new, msg=msg)

        for screenshot in screenshots:
            old = Image.open(path.join(screenshots_path, screenshot)).convert('RGBA')
            new = Image.open(path.join(screenshots_new_path, screenshot)).convert('RGBA')
            self.assertEqual(old.size, new.size, msg='Screenshots sizes are different')

            diff = ImageChops.difference(old, new)
            image_with_diff(old, diff).save(path.join('screenshots_diff', screenshot))
            msg = f"\nScreenshots have difference, checkout it here: {link(path.join(screenshots_diff_path, screenshot))}"
            self.assertAlmostEqual(calc_diff_percentage(diff), 0, delta=1e-7, msg=msg)


if __name__ == '__main__':
    unittest.main()
