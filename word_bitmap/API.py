from flask import Flask, request
from PIL import Image, ImageDraw, ImageFont
import json
import random

app = Flask(__name__)



def generate_char_bitmap(char, font_size, image_size):
    image = Image.new('1', image_size, 0)
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("zimo.ttf", font_size)
    
    bbox = draw.textbbox((0, 0), char, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    
    x = (image_size[0] - text_width) // 2
    y = (image_size[1] - text_height) // 2

    draw.text((x, y), char, 1, font=font)

    return image

def to_binary_string(bitmap):
    binary_string = ""
    for y in range(bitmap.height):
        for x in range(bitmap.width):
            pixel = bitmap.getpixel((x, y))
            binary_string += "1" if pixel else "0"
        binary_string += '\n'
    return binary_string

def incode(binary_string):
    s_incode = ""
    i = 0
    while i < len(binary_string):
        t = hex(int("0b" + binary_string[i:i+4], 2))[2:]
        s_incode += t
        if binary_string[i+4] == '\n':
            i += 5
            s_incode += '&'
        else:
            i += 4
    s_incode = "".join(s_incode[:-1]) + "#"
    return s_incode

@app.route('/char')
def get_word_bitmap():
    # 从 URL 中获取传递的 Unicode 码点
    unicode_point = request.args.get('unicode')
    
    # 将 Unicode 码点转换为字符
    char = chr(int(unicode_point, 16))  # 假设使用十六进制码点
    
    font_size = 12
    image_size = (20, 20)
    image = generate_char_bitmap(char, font_size, image_size)
    binary_string = to_binary_string(image)
    return incode(binary_string)


wordsdata = {
    "words": [
       {
            "word": "ごじゅうおんず",
            "meaning": "意思2",
        },
    ]
}
@app.route("/word")
def choice__word():
    selected_word = random.choice(wordsdata["words"])
    word_str = selected_word["word"]
    meaning_str = selected_word["meaning"]
    selected_word["font_meaning"] = [format(ord(char), 'x') for char in meaning_str]
    selected_word["font_word"] = [format(ord(char), 'x') for char in word_str]
    return json.dumps(selected_word, ensure_ascii=False, indent=4)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8888)
